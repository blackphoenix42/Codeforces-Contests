# ===== Minimal constants & helpers (needed by sbs_diff) ========================
import re, shutil, difflib, sys

RESET = "\033[0m"; BOLD = "\033[1m"; DIM = "\033[2m"
RED   = "\033[31m"; GRN  = "\033[32m"; WHT = "\033[37m"
FG_BLK= "\033[30m"; FG_WHT="\033[97m"
BG_RED= "\033[41m"; BG_GRN="\033[42m"

def supports_color() -> bool:
    return sys.stdout.isatty()

def c(color: str, s: str) -> str:
    return (color + s + RESET) if supports_color() else s

ANSI_RE = re.compile(r"\x1b\[[0-?]*[ -/]*[@-~]")

def strip_ansi(s: str) -> str:
    return ANSI_RE.sub("", s)

def vlen(s: str) -> int:
    """Visible length (ignoring ANSI codes)."""
    return len(strip_ansi(s))

def pad_visible(s: str, width: int) -> str:
    """Right-pad to visible width (ANSI-safe)."""
    return s + " " * max(0, width - vlen(s))

def trim_to_visible(s: str, maxw: int) -> str:
    """Trim to visible width, preserving ANSI codes."""
    if vlen(s) <= maxw:
        return s
    out, vis, i = [], 0, 0
    while i < len(s) and vis < maxw:
        m = ANSI_RE.match(s, i)
        if m:
            out.append(m.group(0)); i = m.end(); continue
        out.append(s[i]); vis += 1; i += 1
    return "".join(out)

def term_width(default=120) -> int:
    try:
        return shutil.get_terminal_size((default, 30)).columns
    except Exception:
        return default

# ===== Inline char-level highlighting (used by sbs_diff) ======================
def inline_highlight(a: str, b: str, show_ws: bool,
                     left_changed_color: str = RED + BOLD,
                     right_changed_color: str = GRN + BOLD,
                     ignore_case: bool = False):
    """
    Color per-character differences between strings a (left) and b (right).
    left_changed_color applies to replace/delete on the left,
    right_changed_color to insert/replace on the right.
    If ignore_case is True, matching is case-insensitive but original text is shown.
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
        a_seg, b_seg = a[i1:i2], b[j1:j2]
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

# ===== Side-by-side diff =======================================================
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
        f"{'':>{numw}} {pad_visible(c(BOLD+WHT,'File A'), colw)}{gutter}"
        f"{'':>{numw}} {c(BOLD+WHT,'File B')}"
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


print(sbs_diff("ayus", "abs", mark_ws=True, ignore_case=False))
