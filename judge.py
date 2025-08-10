#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
CP Local Judge & Diff Viewer

Features
- Auto-picks source file if you pass a positional *.cpp/cc/cxx (no --src needed).
- Compiles with hardened flags, discovers tests N.in / N.ans, writes N.out.
- Reads per-file Time/Memory Limit from input header; adopts TL in banner automatically.
- Compares outputs using a single, crystal-clear side-by-side console diff:
    * EXPECTED on the LEFT, YOUR OUTPUT on the RIGHT
    * stable center gutter │ (ANSI-aware padding)
    * inline character highlighting (green on left, red on right)
    * visible whitespace glyphs: space=·, tab=⇥
- On failure, infers sub-test index k (multiple heuristics) and prints ONLY that sub-test’s input.
- Optional GUI diff (VS Code / Meld / KDiff3) with robust HTML fallback.
- Cleanup modes remove generated .out files and (optionally) the binary (.exe on Windows), with per-file listing.
"""

import argparse
import subprocess
import sys
import time
import difflib
import re
import textwrap
import shutil
import webbrowser
import tempfile
import os
from pathlib import Path
from typing import Optional

# ===== Colors / Pretty =========================================================
RESET = "\033[0m"; BOLD = "\033[1m"; DIM = "\033[2m"
RED   = "\033[31m"; GRN  = "\033[32m"; YLW = "\033[33m"
BLU   = "\033[34m"; MAG  = "\033[35m"; CYN = "\033[36m"; WHT = "\033[37m"; GRY = "\033[90m"

# Extra (optional) styles
UNDER = "\033[4m"
REV   = "\033[7m"
FG_BLK= "\033[30m"; FG_WHT="\033[97m"
BG_RED= "\033[41m"; BG_GRN="\033[42m"; BG_YLW="\033[43m"
BG_BLU= "\033[44m"; BG_MAG="\033[45m"; BG_CYN="\033[46m"; BG_GRY="\033[100m"

def supports_color() -> bool:
    return sys.stdout.isatty()

def c(color: str, s: str) -> str:
    return (color + s + RESET) if supports_color() else s

# ANSI helpers so borders/gutters stay aligned even with colored text
ANSI_RE = re.compile(r"\x1b\[[0-?]*[ -/]*[@-~]")

def strip_ansi(s: str) -> str:
    return ANSI_RE.sub("", s)

def vlen(s: str) -> int:
    """Visible length (without ANSI codes)."""
    return len(strip_ansi(s))

def pad_visible(s: str, width: int) -> str:
    """Pad with spaces to reach visible width."""
    pad = max(0, width - vlen(s))
    return s + (" " * pad)

def trim_to_visible(s: str, maxw: int) -> str:
    """Trim string to max visible width, preserving ANSI codes."""
    if vlen(s) <= maxw:
        return s
    out = []
    vis = 0
    i = 0
    while i < len(s) and vis < maxw:
        m = ANSI_RE.match(s, i)
        if m:
            out.append(m.group(0))
            i = m.end()
            continue
        out.append(s[i])
        vis += 1
        i += 1
    return "".join(out)

# ===== Compile flags ===========================================================
GPP = "g++"
CPP_FLAGS = [
    "-std=c++23",
    "-Wextra","-Wall","-Wconversion","-Wshadow",
    "-Wformat=2","-Wfloat-equal","-Wlogical-op","-Wshift-overflow=2",
    "-Wduplicated-cond","-Wcast-qual","-Wcast-align","-Wfatal-errors",
    "-Wno-sign-conversion","-Wno-unused-result",
    "-D_GLIBCXX_DEBUG","-D_GLIBCXX_DEBUG_PEDANTIC",
    "-O2","-pedantic",
    "-D_FORTIFY_SOURCE=2","-fstack-protector-all",
    "-DLOCAL","-DLOCALCLK",
    "-Wl,--stack=268435456",
]
FLAG_DESCRIPTIONS = {
    "-std=c++23":"Use the C++23 standard.",
    "-Wall":"Common warnings.",
    "-Wextra":"Extra warnings.",
    "-Wconversion":"Warn on narrowing conversions.",
    "-Wshadow":"Warn if a variable shadows another.",
    "-Wformat=2":"Strict printf/scanf checks.",
    "-Wfloat-equal":"Warn on float equality checks.",
    "-Wlogical-op":"Suspicious logical ops.",
    "-Wshift-overflow=2":"UB from bit shifts.",
    "-Wduplicated-cond":"Duplicated conditions.",
    "-Wcast-qual":"Dropping const/volatile via cast.",
    "-Wcast-align":"Alignment-changing casts.",
    "-Wfatal-errors":"Stop after first error.",
    "-Wno-sign-conversion":"Silence some sign-conv noise.",
    "-Wno-unused-result":"Ignore some unused results.",
    "-D_GLIBCXX_DEBUG":"STL bounds/iterator checks.",
    "-D_GLIBCXX_DEBUG_PEDANTIC":"Extra STL checks.",
    "-O2":"Optimize reasonably.",
    "-pedantic":"Warn on non-standard extensions.",
    "-D_FORTIFY_SOURCE=2":"Safer libc at O2+.",
    "-fstack-protector-all":"Stack canaries.",
    "-DLOCAL":"Enable local code paths.",
    "-DLOCALCLK":"Enable timing logs.",
    "-Wl,--stack=268435456":"~256MB stack (mainly Windows).",
}

# ===== Banner (box with centered title + all info inside) ======================
def make_box(title: str, lines: list) -> str:
    """Draw a Unicode box with centered title; right boundary stays straight."""
    content = "\n".join(lines)
    max_line_len = max([0] + [vlen(l) for l in content.splitlines()])
    width = max(84, max(vlen(title) + 8, max_line_len + 2))
    top = "╔" + "═"*(width-2) + "╗"
    # centered title row
    title_text = f"  {title}  "
    pad_left = (width - 2 - vlen(title_text)) // 2
    pad_right = width - 2 - vlen(title_text) - pad_left
    title_row = "║" + " "*pad_left + c(BOLD+WHT, title_text) + " "*pad_right + "║"
    # separator
    sep = "╟" + "─"*(width-2) + "╢"
    # body rows with ANSI-aware padding (trim long lines)
    body_rows = []
    for raw in content.splitlines():
        raw = trim_to_visible(raw, width - 3)
        body_rows.append("║ " + raw + " "*(width - 3 - vlen(raw)) + "║")
    bot = "╚" + "═"*(width-2) + "╝"
    return "\n".join([c(BOLD+CYN, top), c(BOLD+CYN, title_row), c(BOLD+CYN, sep),
                      *body_rows, c(BOLD+CYN, bot)])

def summarize_flags() -> str:
    out = [c(BOLD, "Compile Flags")]
    for fl in CPP_FLAGS:
        out.append(f"  {fl:<24} {c(DIM, FLAG_DESCRIPTIONS.get(fl, ''))}")
    return "\n".join(out)

def cli_cheatsheet(d: dict) -> str:
    return textwrap.dedent(f"""\
      -f, --src PATH        C++ source (default: {d['src']}; or pass positional: `python judge.py file.cpp`)
      -o, --bin NAME        Output binary (default: {d['bin']})
      -d, --tests DIR       Tests dir (default: {d['tests']})
      -t, --time SECONDS    Time limit if not in header (default: {d['time']})
      -w, --ws MODE         Whitespace: auto|strict|ignore (default: {d['ws']})
      -e, --float-tol EPS   Numeric tolerance if text compare fails
      -x, --stop-on-fail    Stop after first failing test (default: off)
      -g, --gui-diff MODE   none|auto|code|meld|kdiff3|html (default: {d['gui_diff']})
      -m, --mark-ws         Show whitespace glyphs (· space, ⇥ tab)
      -L, --enforce-limits  Enforce Memory Limit from header (POSIX)
      -c, --cleanup WHAT    none|outputs|all (default: {d['cleanup']})
      -C, --cleanup-only    Only cleanup then exit
      -i, --ignore-case     Case-insensitive compare/diff (treat 'A' == 'a')
    """)

def banner(d: dict) -> None:
    sections = [
        summarize_flags(),
        "",
        c(BOLD, "CLI Options (quick)"),
        cli_cheatsheet(d).rstrip(),
        "",
        c(BOLD, "Configuration (current)"),
        f"  Source       : {Path(d['src']).resolve()}",
        f"  Binary       : {Path(d['bin']).resolve()}",
        f"  Tests dir    : {Path(d['tests']).resolve()}",
        f"  Time limit   : {d['time']:.2f} s",  # Adopted from source header if present
        f"  Whitespace   : {d['ws']}",
        f"  Ignore case  : {'on' if d.get('ignore_case') else 'off'}",
        f"  Float tol    : {d['float_tol'] if d['float_tol'] is not None else '—'}",
        f"  GUI diff     : {d['gui_diff']}",
        f"  Cleanup      : {d['cleanup']}{' (cleanup-only)' if d['cleanup_only'] else ''}",
    ]
    print(make_box("CP Local Judge & Diff Viewer", sections))

# ===== Logging helpers =========================================================
def info(msg: str): print(c(BLU,  f"ℹ️  {msg}"))
def ok(msg: str):   print(c(GRN,  f"✅ {msg}"))
def warn(msg: str): print(c(YLW,  f"⚠️  {msg}"))
def err(msg: str):  print(c(RED,  f"❌ {msg}"))
def step(msg: str): print(c(MAG,  f"▶ {msg}"))

# ===== Header parsing from input/source comments ===============================
HEADER_RE = re.compile(r"^\s*/\*\*(.*?)\*/", re.DOTALL)
TIME_RE   = re.compile(r"Time\s+Limit:\s*([0-9]+)\s*ms", re.IGNORECASE)
MEM_RE    = re.compile(r"Memory\s+Limit:\s*([0-9]+)\s*MB", re.IGNORECASE)
NAME_RE   = re.compile(r"Problem\s+Name:\s*(.+)", re.IGNORECASE)

def parse_header(text: str) -> dict:
    """Parse /** ... */ header for Problem Name, Time Limit (ms), Memory Limit (MB)."""
    m = HEADER_RE.search(text)
    if not m: return {}
    block = m.group(1)
    meta = {}
    tl = TIME_RE.search(block); ml = MEM_RE.search(block); nm = NAME_RE.search(block)
    if tl: meta["time_ms"] = int(tl.group(1))
    if ml: meta["mem_mb"]  = int(ml.group(1))
    if nm: meta["problem"] = nm.group(1).strip()
    return meta

def strip_header(text: str) -> str:
    """Remove the first /** ... */ block to expose pure input."""
    return HEADER_RE.sub("", text, count=1)

# ===== Whitespace / token utilities ===========================================
def needs_strict_ws(ans_text: str) -> bool:
    """If expected output depends on spacing/tabs/trailing spaces, prefer strict compare."""
    for line in ans_text.splitlines():
        if "\t" in line: return True
        if re.search(r"[ \t]+$", line): return True
        if "  " in line: return True
    return False

def normalize(s: str, mode: str) -> str:
    """CRLF/LF normalize; optionally collapse whitespace for ignore mode."""
    s = s.replace("\r\n","\n").replace("\r","\n")
    if mode == "ignore":
        s = "\n".join(" ".join(ln.strip().split()) for ln in s.split("\n")).strip()
        if s: s += "\n"
    return s

# ===== Inline char-level highlighting =========================================
def inline_highlight(a: str, b: str, show_ws: bool,
                     left_changed_color: str = RED + BOLD,
                     right_changed_color: str = GRN + BOLD,
                     ignore_case: bool = False):
    """
    Color per-character differences between strings a (left) and b (right).
    left_changed_color applies to replace/delete on the left,
    right_changed_color to insert/replace on the right.
    If ignore_case is True, matching is done case-insensitively
    but the original text is displayed.
    """
    def glyph(ch: str) -> str:
        if ch == "\t": return "⇥"
        if ch == " ":  return "·"
        if ch == "\n": return "¶"
        return ch

    ac = a.casefold() if ignore_case else a
    bc = b.casefold() if ignore_case else b

    sm = difflib.SequenceMatcher(a=ac, b=bc)
    a_out, b_out = [], []
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        a_seg, b_seg = a[i1:i2], b[j1:j2]  # slice originals to display
        if tag == "equal":
            segA = "".join(glyph(ch) if show_ws else ch for ch in a_seg)
            segB = "".join(glyph(ch) if show_ws else ch for ch in b_seg)
            a_out.append(segA); b_out.append(segB)
        elif tag == "replace":
            segA = "".join(glyph(ch) if show_ws else ch for ch in a_seg)
            segB = "".join(glyph(ch) if show_ws else ch for ch in b_seg)
            a_out.append(c(left_changed_color, segA)); b_out.append(c(right_changed_color, segB))
        elif tag == "delete":
            segA = "".join(glyph(ch) if show_ws else ch for ch in a_seg)
            a_out.append(c(left_changed_color, segA))
        elif tag == "insert":
            segB = "".join(glyph(ch) if show_ws else ch for ch in b_seg)
            b_out.append(c(right_changed_color, segB))
    return "".join(a_out), "".join(b_out)

def first_diff_linecol(a: str, b: str, ignore_case: bool = False):
    """Return (line, col, lineA, lineB) for first differing line; None if identical."""
    aL, bL = a.splitlines(), b.splitlines()
    aC = [s.casefold() for s in aL] if ignore_case else aL
    bC = [s.casefold() for s in bL] if ignore_case else bL
    n = max(len(aL), len(bL))
    for i in range(n):
        la = aL[i] if i < len(aL) else ""
        lb = bL[i] if i < len(bL) else ""
        lac = aC[i] if i < len(aC) else ""
        lbc = bC[i] if i < len(bC) else ""
        if lac != lbc:
            j = 0; m = min(len(lac), len(lbc))
            while j < m and lac[j] == lbc[j]: j += 1
            return (i+1, j+1, la, lb)
    return None

def first_diff_token(a: str, b: str, ignore_case: bool = False):
    """Return (token_index, tokenA, tokenB) for first differing token; None if identical."""
    ta, tb = a.split(), b.split()
    tac = [t.casefold() for t in ta] if ignore_case else ta
    tbc = [t.casefold() for t in tb] if ignore_case else tb
    n = max(len(tac), len(tbc))
    for i in range(n):
        xa = tac[i] if i < len(tac) else "<EOF>"
        xb = tbc[i] if i < len(tbc) else "<EOF>"
        if xa != xb:
            oa = ta[i] if i < len(ta) else "<EOF>"
            ob = tb[i] if i < len(tb) else "<EOF>"
            return (i+1, oa, ob)
    return None

def nearly_equal_numeric(a: str, b: str, tol: float) -> bool:
    """Token-wise numeric compare within tolerance."""
    import math
    ta, tb = a.split(), b.split()
    if len(ta) != len(tb): return False
    for x, y in zip(ta, tb):
        try:
            fx, fy = float(x), float(y)
            if math.isfinite(fx) and math.isfinite(fy):
                if abs(fx - fy) > tol: return False
            else:
                if x != y: return False
        except Exception:
            if x != y: return False
    return True

# ===== Sub-test inference & extraction ========================================
def infer_subtest_index(inp_text_noheader: str, exp_text: str,
                        diff_line_idx: Optional[int], diff_token_idx: Optional[int]):
    """
    Infer sub-test k using multiple signals:
      1) If first token is integer t:
         a) len(output lines) == t  -> k = diff_line_idx
         b) len(non-empty lines)==t -> k = diff_line_idx
         c) len(tokens)==t          -> k = diff_token_idx
         d) If totals divisible by t, map by equal-size blocks (lines/tokens).
    Returns (k or None, reason, t or None).
    """
    toks = inp_text_noheader.split()
    t = None
    if toks and toks[0].lstrip("-+").isdigit():
        try:
            t_val = int(toks[0]);  t = t_val if t_val > 0 else None
        except Exception:
            t = None

    L_all = exp_text.splitlines()
    L_nz  = [ln for ln in L_all if ln.strip() != ""]
    Tok   = exp_text.split()

    subtest = None; reason = None
    if t is not None:
        if diff_line_idx and len(L_all) == t:
            subtest = max(1, min(diff_line_idx, t)); reason = "by output line count == t"
        elif diff_line_idx and len(L_nz) == t:
            subtest = max(1, min(diff_line_idx, t)); reason = "by non-empty line count == t"
        elif diff_token_idx and len(Tok) == t:
            subtest = max(1, min(diff_token_idx, t)); reason = "by output token count == t"
        else:
            if diff_line_idx and t > 0 and len(L_all) % t == 0:
                per = max(1, len(L_all)//t)
                subtest = max(1, min((diff_line_idx - 1)//per + 1, t))
                reason = f"by equal line blocks (≈{per}/test)"
            elif diff_token_idx and t > 0 and len(Tok) % t == 0:
                per = max(1, len(Tok)//t)
                subtest = max(1, min((diff_token_idx - 1)//per + 1, t))
                reason = f"by equal token blocks (≈{per}/test)"
    return subtest, reason, t

def extract_subtest_input(inp_text_noheader: str, k: int):
    """
    Extract ONLY the kth sub-test input.
    1) Exact: leading t with blank-line-separated blocks => return that block.
    2) Approx: leading t but not block-split => return equal-sized line chunk for k.
    3) Else: ("", reason).
    """
    lines = inp_text_noheader.splitlines()
    if not lines: return ("", "no-input")
    # find first non-empty line -> try read t
    idx = 0
    while idx < len(lines) and lines[idx].strip() == "": idx += 1
    if idx < len(lines) and lines[idx].strip().lstrip("-+").isdigit():
        try:
            t = int(lines[idx].strip()); start = idx+1
            # exact splitting by blank lines
            block, blocks = [], []
            for ln in lines[start:]:
                if ln.strip() == "":
                    if block: blocks.append(block); block = []
                else:
                    block.append(ln)
            if block: blocks.append(block)
            if len(blocks) == t and 1 <= k <= t:
                return ("\n".join(blocks[k-1]), "block-split")
            # approx equal-sized chunks of remaining lines
            rem = lines[start:]
            if t > 0 and len(rem) >= t:
                per = max(1, len(rem)//t)
                s = start + (k-1)*per
                e = min(len(lines), s + per)
                if 0 <= s < len(lines):
                    return ("\n".join(lines[s:e]), f"approx-lines (~{per} lines/test)")
        except Exception as e:
            return ("", f"parse-error: {e}")
    return ("", "no-leading-t")

# ===== Console diff (single style: improved side-by-side) ======================
def term_width(default=120) -> int:
    try:
        return shutil.get_terminal_size((default, 30)).columns
    except Exception:
        return default

def sbs_diff(expected: str, your: str, mark_ws: bool, context=3, ignore_case: bool = False) -> str:
    """
    Side-by-side diff with stable vertical gutter:
      LEFT  = EXPECTED (green highlights)
      RIGHT = YOUR OUTPUT (red highlights)
    """
    eL, yL = expected.splitlines(), your.splitlines()
    eC = [s.casefold() for s in eL] if ignore_case else eL
    yC = [s.casefold() for s in yL] if ignore_case else yL

    n = max(len(eL), len(yL))
    diff_idxs = [i for i in range(n) if (eC[i] if i < len(eC) else "") != (yC[i] if i < len(yC) else "")]
    if not diff_idxs:
        return c(DIM, "No differences.\n")

    start = max(0, min(diff_idxs) - context)
    end   = min(n-1, max(diff_idxs) + context)

    cols = term_width()
    gutter = " │ "  # center boundary
    numw = 5
    colw = max(20, (cols - len(gutter) - (numw+1)*2) // 2)

    header = (
        f"{'':>{numw}} {pad_visible(c(BOLD+WHT,'EXPECTED'), colw)}{gutter}"
        f"{'':>{numw}} {c(BOLD+WHT,'YOUR OUTPUT')}"
    )
    out = [header, c(DIM, "—"*cols)]

    for i in range(start, end+1):
        L = eL[i] if i < len(eL) else ""
        R = yL[i] if i < len(yL) else ""
        L_show = L.replace("\t","⇥").replace(" ","·") if mark_ws else L
        R_show = R.replace("\t","⇥").replace(" ","·") if mark_ws else R

        different = (eC[i] if i < len(eC) else "") != (yC[i] if i < len(yC) else "")

        if different:
            # expected on left (green), yours on right (red)
            Lh, Rh = inline_highlight(
                L_show, R_show, show_ws=mark_ws,
                left_changed_color=BG_GRN+FG_BLK+BOLD,   # what you SHOULD have (expected)
                right_changed_color=BG_RED+FG_WHT+BOLD,  # what to FIX/REMOVE (your output)
                ignore_case=ignore_case
            )
        else:
            Lh, Rh = c(DIM, L_show), c(DIM, R_show)

        # Trim & pad by visible width to keep columns tight and gutter straight
        Lh = pad_visible(trim_to_visible(Lh, colw), colw)
        Rh = trim_to_visible(Rh, colw)

        left  = f"{i+1:>{numw}} {Lh}"
        right = f"{i+1:>{numw}} {Rh}"
        out.append(f"{left}{gutter}{right}")

    out.append(c(DIM, "—"*cols))
    return "\n".join(out) + "\n"

# ===== GUI diff helpers (safe & informative) ==================================
def write_html_diff(a: str, b: str, fromfile: str, tofile: str) -> str:
    html = difflib.HtmlDiff(wrapcolumn=120).make_file(
        a.splitlines(), b.splitlines(), fromfile, tofile, context=True, numlines=3
    )
    fd, path = tempfile.mkstemp(prefix="judge_diff_", suffix=".html")
    with os.fdopen(fd, "w", encoding="utf-8", newline="") as f:
        f.write(html)
    return path

def open_external_diff(gui_choice: str, expected: Path, got: Path):
    """
    Try to open a desktop diff tool. Returns (launched: bool, note: str).
    - Never crashes; if not available, returns a clear message.
    - Falls back to HTML diff and opens in browser.
    """
    def try_launch(cmd_desc, cmd):
        try:
            subprocess.Popen(cmd)
            return True, f"Opened GUI diff via {cmd_desc}."
        except FileNotFoundError:
            return False, f"Tool not found: {cmd[0]} is not in PATH."
        except Exception as e:
            return False, f"Failed to launch {cmd_desc}: {e}"

    def have(exe): return shutil.which(exe) is not None

    if gui_choice == "none":
        return False, "GUI diff disabled (use --gui-diff auto|code|meld|kdiff3|html)."

    if gui_choice in ("code","meld","kdiff3"):
        exe = gui_choice
        if not have(exe):
            return False, f"{exe} not found in PATH. Install it or use --gui-diff html."
        cmd = ["code","-d",str(expected),str(got)] if exe=="code" else [exe,str(expected),str(got)]
        return try_launch(exe, cmd)

    if gui_choice in ("auto","html"):
        for exe, cmd in (("code",["code","-d"]),("meld",["meld"]),("kdiff3",["kdiff3"])):  # try in order
            if have(exe):
                return try_launch(exe, cmd + [str(expected), str(got)])
        # fallback to HTML
        html_path = write_html_diff(expected.read_text(encoding="utf-8", errors="ignore"),
                                    got.read_text(encoding="utf-8", errors="ignore"),
                                    "expected","your_output")
        try:
            webbrowser.open(f"file://{html_path}")
            return True, f"No desktop diff tool detected; opened HTML diff in your browser ({html_path})."
        except Exception as e:
            return False, f"Could not open HTML diff automatically: {e}. Open manually: {html_path}"

    return False, "Unsupported --gui-diff mode."

# ===== Test discovery (no leading zeros; use N.in / N.ans / N.out) ============
DIGITS_RE = re.compile(r"(\d+)\.in$")

def discover_tests(tdir: Path):
    inputs = []
    for p in tdir.glob("*.in"):
        m = DIGITS_RE.search(p.name)
        if m:
            case_id = int(m.group(1))
            inputs.append((case_id, p))
    inputs.sort(key=lambda x: x[0])
    return inputs

# ===== Limits (time/memory) ====================================================
def build_preexec_for_memory(mem_mb: int):
    """POSIX-only memory cap using RLIMIT_AS (best-effort)."""
    try:
        import resource
        def set_limits():
            if mem_mb:
                bytes_ = int(mem_mb) * 1024 * 1024
                resource.setrlimit(resource.RLIMIT_AS, (bytes_, bytes_))
        return set_limits
    except Exception:
        return None

# ===== Runner =================================================================
def run_case(bin_path: Path, inp: Path, out_path: Path, tlim: float,
             mem_mb: int, enforce_limits: bool):
    """
    Execute compiled program with argv: prog <input_path> <output_path>
    - Captures stdout/stderr for logs (program should write actual output to <out_path>).
    - Enforces time limit via subprocess timeout.
    - Optionally enforces memory limit on POSIX using RLIMIT_AS.
    Returns: (exit_code | "TLE", stderr_text, elapsed_ms | None)
    """
    try:
        start = time.perf_counter()
        kw = {}
        if enforce_limits and mem_mb and os.name == "posix":
            pre = build_preexec_for_memory(mem_mb)
            if pre is not None:
                kw["preexec_fn"] = pre
        res = subprocess.run(
            [str(bin_path), str(inp), str(out_path)],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            timeout=tlim,
            **kw
        )
        ms = (time.perf_counter() - start) * 1000.0
        return res.returncode, res.stderr.decode(errors="ignore"), ms
    except subprocess.TimeoutExpired:
        return "TLE", "", None

# ===== Cleanup =================================================================
def cleanup(tdir: Path, bin_path: Path, what: str):
    """Remove generated files: tests/*.out, temp HTML diffs; and binary if 'all'. Returns list of removed paths."""
    removed = []

    # Remove test outputs
    if what in ("outputs","all"):
        if tdir.exists():
            for p in sorted(tdir.glob("*.out")):
                try:
                    p.unlink()
                    removed.append(p)
                except Exception:
                    pass
        # Temp HTML diffs from this tool
        tmp = Path(tempfile.gettempdir())
        for p in sorted(tmp.glob("judge_diff_*.html")):
            try:
                p.unlink()
                removed.append(p)
            except Exception:
                pass

    # Remove compiled binary
    if what in ("all",):
        try:
            if bin_path.exists():
                bin_path.unlink()
                removed.append(bin_path)
        except Exception:
            pass
        # On Windows, also remove .exe sibling if -o was given without .exe
        if os.name == "nt" and not str(bin_path).lower().endswith(".exe"):
            exe = bin_path.with_suffix(".exe")
            if exe.exists():
                try:
                    exe.unlink()
                    removed.append(exe)
                except Exception:
                    pass

    if removed:
        ok(f"Cleanup removed {len(removed)} file(s):")
        for p in removed:
            try:
                rel = os.path.relpath(p, Path.cwd())
            except Exception:
                rel = str(p)
            print("   •", rel)
    else:
        info("Nothing to clean.")
    return removed

# ===== Auto source detection (positional *.cpp) ================================
CPP_EXTS = (".cpp",".cc",".cxx",".CPP",".Cp",".cp",".c++",".C")

def resolve_src_from_positional_or_scan(args_src: str, pos_src: Optional[str]) -> str:
    """
    Priority:
      1) Positional source if it looks like a C++ file (by extension).
      2) If --src exists, use it.
      3) Scan cwd for a single *.cpp-like; prefer main.*; else newest modified.
    """
    if pos_src and Path(pos_src).suffix in CPP_EXTS:
        return pos_src
    if args_src and Path(args_src).exists():
        return args_src
    candidates = [str(p) for ext in CPP_EXTS for p in Path(".").glob(f"*{ext}")]
    if not candidates:
        return args_src  # will error later if missing
    mains = [p for p in candidates if Path(p).stem.lower() == "main"]
    if len(mains) == 1:
        return mains[0]
    if len(candidates) == 1:
        return candidates[0]
    candidates.sort(key=lambda p: Path(p).stat().st_mtime, reverse=True)
    return candidates[0]

# ===== Windows binary name helper =============================================
def ensure_windows_exe(path: Path) -> Path:
    """
    On Windows, g++ creates prog.exe even if -o prog was given.
    Normalize to .exe so subprocess can find it reliably.
    """
    if os.name == "nt":
        if path.suffix.lower() != ".exe":
            return path.with_suffix(".exe")
    return path

# ===== Main ====================================================================
def main():
    ap = argparse.ArgumentParser(
        formatter_class=argparse.RawTextHelpFormatter,
        description="Judge with clear side-by-side diffs, per-file TL/ML, sub-test view, GUI fallback, and cleanup."
    )
    # Positional source (optional) lets you do: python judge.py file.cpp
    ap.add_argument("pos_src", nargs="?", help="(optional) source file; same as --src")
    ap.add_argument("-f","--src", default="main.cpp")
    ap.add_argument("-o","--bin", default="prog")
    ap.add_argument("-d","--tests", default="tests")
    ap.add_argument("-t","--time", type=float, default=2.0, help="Time limit if not specified in source header (seconds)")
    ap.add_argument("-w","--ws", choices=["auto","strict","ignore"], default="auto",
                    help="Whitespace: strict=exact, ignore=normalize, auto=infer from .ans")
    ap.add_argument("-e","--float-tol", type=float, default=None,
                    help="Token-wise numeric tolerance if text compare fails")
    ap.add_argument("-x","--stop-on-fail", action="store_true", help="Stop after first failing test")
    ap.add_argument("-g","--gui-diff", choices=["none","auto","code","meld","kdiff3","html"], default="none")
    ap.add_argument("-m","--mark-ws", action="store_true", help="Show whitespace glyphs (·, ⇥)")
    ap.add_argument("-L","--enforce-limits", action="store_true", help="Enforce Memory Limit (POSIX)")
    ap.add_argument("-c","--cleanup", choices=["none","outputs","all"], default="all",
                    help="What to clean after run (only if all tests pass). Default: all")
    ap.add_argument("-C","--cleanup-only", action="store_true",
                    help="Just clean and exit (uses --cleanup target; default: all)")
    ap.add_argument("-i","--ignore-case", action="store_true",
                    help="Case-insensitive compare/diff (treat 'A' == 'a')")
    args = ap.parse_args()

    # Choose source file smartly (positional, --src, or scan)
    args.src = resolve_src_from_positional_or_scan(args.src, args.pos_src)

    tdir = Path(args.tests).resolve()
    binp = Path(args.bin).resolve()
    srcp = Path(args.src).resolve()

    # If source header contains Time Limit, adopt it for banner/default TL
    if srcp.exists():
        try:
            src_txt = srcp.read_text(encoding="utf-8", errors="ignore")
            src_meta = parse_header(src_txt)
            if "time_ms" in src_meta:
                args.time = max(0.001, src_meta["time_ms"] / 1000.0)
        except Exception:
            pass

    # On Windows, normalize binary path to .exe so we can execute it reliably
    binp = ensure_windows_exe(binp)

    # Show banner (compile flags, CLI, config — all inside the box)
    d = {
        "src": args.src, "bin": str(binp), "tests": args.tests, "time": args.time,
        "ws": args.ws, "float_tol": args.float_tol, "gui_diff": args.gui_diff,
        "cleanup": args.cleanup, "cleanup_only": args.cleanup_only, "ignore_case": args.ignore_case
    }
    banner(d)

    # Cleanup-only mode (report per-file) — works without compiling/running
    if args.cleanup_only:
        step(f"Cleanup: {args.cleanup}")
        cleanup(tdir, binp, args.cleanup)
        return

    # Basic checks
    if not srcp.exists(): err(f"Source not found: {srcp}"); sys.exit(1)
    if not tdir.exists(): err(f"Tests dir not found: {tdir}"); sys.exit(1)

    # Compile
    step("Compiling with hardening + pedantic warnings …")
    cmd = [GPP, *CPP_FLAGS, str(srcp), "-o", str(binp)]
    info(" ".join(cmd))
    res = subprocess.run(cmd, capture_output=True, text=True)
    if res.returncode != 0:
        if res.stdout.strip(): print(res.stdout)
        if res.stderr.strip(): print(res.stderr)
        err("Compilation failed. Fix the errors above."); sys.exit(1)
    ok("Compilation succeeded.")

    # Discover tests
    tests = discover_tests(tdir)
    if not tests:
        warn("No tests like tests/1.in, tests/2.in …"); sys.exit(0)

    info("Discovered: " + ", ".join(str(cid) for cid,_ in tests))

    total, passed = len(tests), 0
    for case_id, inp in tests:
        base = inp.with_suffix("")
        ansf = base.with_suffix(".ans")
        outf = base.with_suffix(".out")

        raw_in = inp.read_text(encoding="utf-8", errors="ignore")
        meta = parse_header(raw_in)
        # Per-file TL from input header takes precedence per test
        eff_time = (meta.get("time_ms", 0)/1000.0) or args.time
        eff_mem  = meta.get("mem_mb", 0)

        head_info = []
        if meta.get("problem"): head_info.append(f"Problem: {meta['problem']}")
        if meta.get("time_ms"): head_info.append(f"TL={meta['time_ms']} ms")
        if meta.get("mem_mb"):  head_info.append(f"ML={meta['mem_mb']} MB")
        extra = (" [" + ", ".join(head_info) + "]") if head_info else ""

        step(f"Test #{case_id}: {inp.name}{extra}")
        if not ansf.exists():
            warn(f"Missing expected file: {ansf.name}. Generating {outf.name} only.")

        code, stderr, ms = run_case(binp, inp, outf, eff_time, eff_mem, args.enforce_limits)
        if code == "TLE":
            err(f"⏱  TLE (> {eff_time:.2f}s) on {inp}")
            if args.stop_on_fail: break
            continue
        if code != 0:
            err(f"Runtime error on {inp} (exit {code}). See stderr below.")
            if stderr.strip(): print(stderr)
            if args.stop_on_fail: break
            continue

        got = outf.read_text(encoding="utf-8", errors="ignore") if outf.exists() else ""
        if not ansf.exists():
            ok(f"Wrote {outf.name} [{ms:.1f} ms]. (Skipped compare)")
            continue

        exp = ansf.read_text(encoding="utf-8", errors="ignore")

        # Whitespace strategy
        ws_mode = args.ws
        if ws_mode == "auto":
            ws_mode = "strict" if needs_strict_ws(exp) else "ignore"
        ic = " + ignore-case" if args.ignore_case else ""
        info(f"Compare mode: {ws_mode}{ic}" + (c(DIM, " (auto)") if args.ws == "auto" else ""))

        # Normalized text for compare
        A = normalize(got, ws_mode)  # YOUR OUTPUT
        B = normalize(exp, ws_mode)  # EXPECTED

        # Case-insensitive compare (for text equality)
        A_cmp = A.casefold() if args.ignore_case else A
        B_cmp = B.casefold() if args.ignore_case else B

        same = (A_cmp == B_cmp); used_tol = False
        if not same and args.float_tol is not None:
            used_tol = True; same = nearly_equal_numeric(A, B, args.float_tol)

        if same:
            ok(f"PASS [{ms:.1f} ms]" + (f" • tol={args.float_tol}" if used_tol else ""))
            passed += 1
        else:
            # First-diff focus (line/col + inline highlight)
            dlc = first_diff_linecol(A, B, ignore_case=args.ignore_case)
            dtok = first_diff_token(A, B, ignore_case=args.ignore_case)
            if dlc:
                L, C, la, lb = dlc
                la_h, lb_h = inline_highlight(
                        la, lb, show_ws=True,
                        left_changed_color=BG_GRN+FG_BLK+BOLD,   # expected
                        right_changed_color=BG_RED+FG_WHT+BOLD,  # your output
                        ignore_case=args.ignore_case
                    )
                info(f"First diff at line {L}, col {C}")
                print(c(BOLD+WHT, "expected: ") + lb_h)
                print(c(BOLD+WHT, "   got : ") + la_h)
            if dtok:
                Ti, xa, xb = dtok
                info(f"Token mismatch at token #{Ti}: got={xa} expected={xb}")
                info(f"Token counts: got={len(A.split())}, expected={len(B.split())}")

            # Infer sub-test and show ONLY that sub-test input values
            sub_idx, reason, t_val = infer_subtest_index(strip_header(raw_in), B,
                                                         dlc[0] if dlc else None,
                                                         dtok[0] if dtok else None)
            fail_head = f"FAIL on {inp.name} [{ms:.1f} ms]"
            if sub_idx: fail_head += f" • inferred sub-test #{sub_idx} ({reason})"
            err(fail_head)

            if sub_idx:
                tc_text, how = extract_subtest_input(strip_header(raw_in), sub_idx)
                if tc_text:
                    print(c(BOLD+WHT, f"\n🔎 Sub-test #{sub_idx} input ({how}):"))
                    for i, ln in enumerate(tc_text.splitlines(), 1):
                        shown = ln
                        print(f"{i:>4}:  {shown}")
                else:
                    warn(f"Could not extract sub-test #{sub_idx} input precisely ({how}).")
            else:
                info("Sub-test could not be inferred (no leading t or atypical format).")

            # Single console diff style: EXPECTED (left) vs YOUR OUTPUT (right)
            print(c(BOLD+WHT, "\n≣ Side-by-side diff"))
            print(sbs_diff(B, A, mark_ws=True, ignore_case=args.ignore_case))

            # Optional GUI diff
            if args.gui_diff != "none":
                launched, note = open_external_diff(args.gui_diff, ansf, outf)
                if launched: info(note)
                else: warn(note)

            if args.stop_on_fail: break

        if stderr.strip():
            warn("Stderr:")
            print(stderr)

    print()
    if passed == total:
        ok(f"All {passed}/{total} test(s) passed. 🎉")
        if args.cleanup != "none":
            step(f"Cleanup (post-pass): {args.cleanup}")
            cleanup(tdir, binp, args.cleanup)
    else:
        (err if passed == 0 else warn)(f"Summary: {passed}/{total} passed.")
        if args.cleanup != "none":
            warn(
                "Skipping cleanup because not all tests passed. "
                f"To clean anyway run: python {Path(sys.argv[0]).name} -C -c {args.cleanup}"
            )

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        err("Interrupted by user. Bye 👋"); sys.exit(130)
