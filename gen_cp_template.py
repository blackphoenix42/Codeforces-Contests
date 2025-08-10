#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
gen_cp_template.py (v2.1.1)
---------------------------
Auto-inserts a rich metadata header into C++ files and injects a fresh,
tech/competitive-programming related quote each run.

Modes:
  • CLI (single file):     python gen_cp_template.py path/to/file.cpp
  • Auto + Watch (default):python gen_cp_template.py

Key features:
  • Pulls quotes from the internet (multiple sources, no API keys).
  • Tight time budget with retries; graceful offline fallback.
  • LRU cache with TTL, file-locked writes, and a cooldown circuit breaker.
  • Idempotent header replacement (no sentinels; smart detection).
  • Atomic writes, debounced watcher, pretty banner, emoji/color logs.
  • Optional JSON logs (--json-logs) and --no-banner for CI.

Environment variables (optional):
  TEMPLATE_FILE, WATCH_FOLDER, CPH_META_DIR
  QUOTE_TIMEOUT_SEC, QUOTE_RETRIES, QUOTE_TOTAL_BUDGET_MS
  QUOTE_CACHE_FILE, QUOTE_CACHE_SIZE, QUOTE_CACHE_TTL_HOURS
  QUOTE_COOLDOWN_MINUTES
  WATCH_DEBOUNCE_MS, META_WAIT_MS
  LOG_FORMAT (pretty|json), DISABLE_COLOR (0|1)
"""

import os
import sys
import time
import json
import datetime
import random
import hashlib
import traceback
import textwrap
import argparse
import re
from typing import Optional, List, Dict, Any, Tuple

# Watchdog for auto mode
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

# Optional requests; we fall back to urllib if unavailable
try:
    import requests  # type: ignore
except Exception:
    requests = None
import urllib.request
import urllib.error

# ---------------- Version & Config ---------------- #
VERSION = "2.1.1"

def _env_str(name: str, default: str) -> str:
    v = os.getenv(name)
    return v if v not in (None, "") else default

def _env_int(name: str, default: int) -> int:
    try:
        return int(_env_str(name, str(default)))
    except Exception:
        return default

def _env_bool(name: str, default: bool) -> bool:
    v = _env_str(name, "1" if default else "0").strip().lower()
    return v in ("1", "true", "t", "yes", "y", "on")

TEMPLATE_FILE      = _env_str("TEMPLATE_FILE", "template.cc")
WATCH_FOLDER       = _env_str("WATCH_FOLDER", ".")
CPH_META_DIR       = _env_str("CPH_META_DIR", ".cph")

# Make it snappy by default
QUOTE_TIMEOUT      = float(_env_int("QUOTE_TIMEOUT_SEC", 2))
QUOTE_RETRIES      = _env_int("QUOTE_RETRIES", 1)
QUOTE_TOTAL_BUDGET = _env_int("QUOTE_TOTAL_BUDGET_MS", 1200)

# Default cache path requested: scripts/.quote_cache.json
DEFAULT_CACHE_PATH = os.path.join("scripts", ".quote_cache.json")
QUOTE_CACHE_FILE   = _env_str("QUOTE_CACHE_FILE", DEFAULT_CACHE_PATH)
QUOTE_CACHE_SIZE   = _env_int("QUOTE_CACHE_SIZE", 64)
QUOTE_CACHE_TTL    = datetime.timedelta(hours=_env_int("QUOTE_CACHE_TTL_HOURS", 168))  # 7 days
QUOTE_COOLDOWN_MIN = _env_int("QUOTE_COOLDOWN_MINUTES", 10)  # circuit-breaker cool-off

WATCH_DEBOUNCE_MS  = _env_int("WATCH_DEBOUNCE_MS", 250)  # faster
META_WAIT_MS       = _env_int("META_WAIT_MS", 900)       # brief wait for CPH JSON if needed

BACKUP_ON_WRITE    = False  # no backups requested

# ---------------- CLI args (logging/banners) ---------------- #
def parse_args():
    p = argparse.ArgumentParser(add_help=False)
    p.add_argument("file", nargs="?", help=".cpp file to update (optional)")
    p.add_argument("--json-logs", action="store_true", help="Print logs in JSON (CI-friendly)")
    p.add_argument("--no-banner", action="store_true", help="Suppress the startup banner")
    p.add_argument("--no-color", action="store_true", help="Disable ANSI colors")
    p.add_argument("-h", "--help", action="store_true", help="Show help and exit")
    args = p.parse_args()

    # Env overrides (env takes precedence only if CLI flag not supplied)
    log_fmt_env = _env_str("LOG_FORMAT", "pretty").lower()
    args.json_logs = args.json_logs or (log_fmt_env == "json")
    args.no_color = args.no_color or _env_bool("DISABLE_COLOR", False)
    return args

ARGS = parse_args()

# ---------------- Logging Utility (Emoji/Color or JSON) ---------------- #
def _supports_color() -> bool:
    if ARGS.no_color:
        return False
    try:
        return sys.stdout.isatty()
    except Exception:
        return False

_USE_COLOR = _supports_color()

def _c(code: str) -> str:
    return code if _USE_COLOR else ""

# Palette
C_BLUE   = _c("\033[94m"); C_GREEN  = _c("\033[92m"); C_YELLOW = _c("\033[93m")
C_RED    = _c("\033[91m"); C_CYAN   = _c("\033[96m"); C_BOLD   = _c("\033[1m")
C_DIM    = _c("\033[2m");  C_END    = _c("\033[0m")

def _now_iso_tz() -> str:
    return datetime.datetime.now().astimezone().isoformat(timespec="seconds")

def log(msg: str, level: str = "INFO"):
    if ARGS.json_logs:
        obj = {"ts": _now_iso_tz(), "level": level, "msg": msg,
               "module": "gen_cp_template", "version": VERSION}
        print(json.dumps(obj, ensure_ascii=False))
        return
    emojis = {"INFO": "ℹ️", "SUCCESS": "✅", "WARNING": "⚠️", "ERROR": "❌"}
    colors = {"INFO": C_BLUE, "SUCCESS": C_GREEN, "WARNING": C_YELLOW, "ERROR": C_RED, "ENDC": C_END}
    ts = _now_iso_tz()
    emoji = emojis.get(level, "")
    print(f"{colors.get(level, '')}[{level}] {emoji} {ts}: {msg}{colors['ENDC']}")

# ---------------- Banner (ANSI-safe width + separate env lines + how-to-set) ---------------- #
ANSI_RE = re.compile(r"\x1b\[[0-9;]*m")

def _visible_len(s: str) -> int:
    return len(ANSI_RE.sub("", s))

def _ljust_visual(s: str, width: int) -> str:
    pad = max(0, width - _visible_len(s))
    return s + (" " * pad)

def _box(lines: List[str], pad: int = 2, min_width: int = 62, max_width: int = 100) -> str:
    width = max(min_width - 2, *( _visible_len(ln) for ln in lines )) if lines else (min_width - 2)
    width = min(width, max_width - 2)
    top = f"{C_CYAN}┌{'─' * (width + 2 * pad)}┐{C_END}"
    bot = f"{C_CYAN}└{'─' * (width + 2 * pad)}┘{C_END}"
    body = [f"{C_CYAN}│{C_END}{' ' * pad}{_ljust_visual(ln, width)}{' ' * pad}{C_CYAN}│{C_END}" for ln in lines]
    return "\n".join([top] + body + [bot])

def banner(mode: str):
    if ARGS.no_banner and not ARGS.help:
        return
    title = f"{C_BOLD}CP Header & Tech Quote Injector{C_END}  v{VERSION}"
    lines = [
        f"{title}",
        f"{C_DIM}Mode:{C_END} {mode}",
        "",
        f"{C_BOLD}What it does{C_END}",
        "• Inserts/refreshes a metadata header at the top of .cpp files.",
        "• Fills it with CPH metadata, time/memory limits, and a fresh tech/CP quote.",
        "",
        f"{C_BOLD}How to use{C_END}",
        "• CLI (single file):     python gen_cp_template.py path/to/file.cpp",
        "• Auto + Watch (default):python gen_cp_template.py",
        "",
        f"{C_BOLD}Config (env){C_END}",
        f"TEMPLATE_FILE={TEMPLATE_FILE}",
        f"WATCH_FOLDER={os.path.abspath(WATCH_FOLDER)}",
        f"CPH_META_DIR={CPH_META_DIR}",
        f"QUOTE_TIMEOUT_SEC={int(QUOTE_TIMEOUT)}",
        f"QUOTE_RETRIES={QUOTE_RETRIES}",
        f"QUOTE_TOTAL_BUDGET_MS={QUOTE_TOTAL_BUDGET}",
        f"QUOTE_CACHE_FILE={os.path.abspath(QUOTE_CACHE_FILE)}",
        f"QUOTE_CACHE_SIZE={QUOTE_CACHE_SIZE}",
        f"QUOTE_CACHE_TTL_HOURS={int(QUOTE_CACHE_TTL.total_seconds()//3600)}",
        f"QUOTE_COOLDOWN_MINUTES={QUOTE_COOLDOWN_MIN}",
        f"WATCH_DEBOUNCE_MS={WATCH_DEBOUNCE_MS}",
        f"META_WAIT_MS={META_WAIT_MS}",
        f"LOG_FORMAT={'json' if ARGS.json_logs else 'pretty'}",
        f"DISABLE_COLOR={'1' if ARGS.no_color else '0'}",
        "",
        f"{C_BOLD}Set env (quick){C_END}",
        "• Windows PowerShell : $env:NAME='value'",
        "• Windows cmd        : set NAME=value",
        "• macOS/Linux (bash) : export NAME=value",
    ]
    print(_box(lines, pad=2, min_width=62, max_width=100))

# ---------------- Quote Cache (LRU + TTL + Cooldown) ---------------- #
def _ensure_parent_dir(path: str):
    d = os.path.dirname(path)
    if d:
        os.makedirs(d, exist_ok=True)

CACHE_LOCK_PATH = QUOTE_CACHE_FILE + ".lock"

def _acquire_lock(path: str, timeout: float = 1.5, interval: float = 0.03) -> bool:
    end = time.time() + timeout
    _ensure_parent_dir(path)
    while time.time() < end:
        try:
            fd = os.open(path, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
            try:
                os.write(fd, str(os.getpid()).encode("utf-8"))
            finally:
                os.close(fd)
            return True
        except FileExistsError:
            time.sleep(interval)
        except Exception:
            return False
    return False

def _release_lock(path: str):
    try:
        if os.path.exists(path):
            os.remove(path)
    except Exception:
        pass

def _load_cache_state_unlocked() -> Dict[str, Any]:
    try:
        if not os.path.isfile(QUOTE_CACHE_FILE):
            return {"entries": [], "cooldown_until": None}
        with open(QUOTE_CACHE_FILE, "r", encoding="utf-8") as f:
            data = json.load(f)
        if isinstance(data, list):  # legacy
            return {"entries": data, "cooldown_until": None}
        if not isinstance(data, dict):
            return {"entries": [], "cooldown_until": None}
        return {"entries": data.get("entries", []), "cooldown_until": data.get("cooldown_until")}
    except Exception:
        return {"entries": [], "cooldown_until": None}

def _save_cache_state_locked(state: Dict[str, Any]) -> None:
    _ensure_parent_dir(QUOTE_CACHE_FILE)
    tmp = QUOTE_CACHE_FILE + ".tmp"
    with open(tmp, "w", encoding="utf-8") as f:
        json.dump(state, f, ensure_ascii=False, indent=0)
    os.replace(tmp, QUOTE_CACHE_FILE)

def _trim_and_prune(entries: List[Dict[str, Any]]) -> List[Dict[str, Any]]:
    out: List[Dict[str, Any]] = []
    now = datetime.datetime.now(datetime.timezone.utc)
    for e in (entries if isinstance(entries, list) else []):
        try:
            h = str(e.get("h", ""))
            t_raw = e.get("t", "")
            t = datetime.datetime.fromisoformat(t_raw)
            if t.tzinfo is None:
                t = t.replace(tzinfo=datetime.timezone.utc)
            if h and (now - t) <= QUOTE_CACHE_TTL:
                out.append({"h": h, "t": t.isoformat()})
        except Exception:
            continue
    return out[-QUOTE_CACHE_SIZE:]

def _load_cache_state() -> Dict[str, Any]:
    state = _load_cache_state_unlocked()
    state["entries"] = _trim_and_prune(state.get("entries", []))
    return state

def _persist_cache_state(mutator):
    if not _acquire_lock(CACHE_LOCK_PATH):
        return
    try:
        state = _load_cache_state_unlocked()
        state["entries"] = _trim_and_prune(state.get("entries", []))
        mutator(state)
        _save_cache_state_locked(state)
    except Exception as e:
        log(f"Could not persist cache: {e}", "WARNING")
    finally:
        _release_lock(CACHE_LOCK_PATH)

def _remember_quote_hash(h: str) -> None:
    def mutate(state):
        entries = state.get("entries", [])
        entries.append({"h": h, "t": datetime.datetime.now(datetime.timezone.utc).isoformat()})
        state["entries"] = _trim_and_prune(entries)
    _persist_cache_state(mutate)

def _recent_hashes() -> set:
    return {e["h"] for e in _load_cache_state().get("entries", [])}

def _in_cooldown() -> bool:
    state = _load_cache_state()
    cu = state.get("cooldown_until")
    if not cu:
        return False
    try:
        t = datetime.datetime.fromisoformat(cu)
        if t.tzinfo is None:
            t = t.replace(tzinfo=datetime.timezone.utc)
        return datetime.datetime.now(datetime.timezone.utc) < t
    except Exception:
        return False

def _set_cooldown(minutes: int):
    until = (datetime.datetime.now(datetime.timezone.utc) +
             datetime.timedelta(minutes=max(1, minutes)))
    def mutate(state):
        state["cooldown_until"] = until.isoformat()
    _persist_cache_state(mutate)

# ---------------- HTTP helpers with retry/timeout & budget ---------------- #
def _http_get_json(url: str, headers: Optional[dict] = None, timeout: float = QUOTE_TIMEOUT) -> Any:
    if requests:
        r = requests.get(url, headers=headers or {}, timeout=timeout)
        r.raise_for_status()
        return r.json()
    req = urllib.request.Request(url, headers=headers or {})
    with urllib.request.urlopen(req, timeout=timeout) as resp:
        data = resp.read()
    return json.loads(data.decode("utf-8"))

def _http_get_text(url: str, headers: Optional[dict] = None, timeout: float = QUOTE_TIMEOUT) -> str:
    if requests:
        r = requests.get(url, headers=headers or {}, timeout=timeout)
        r.raise_for_status()
        return r.text
    req = urllib.request.Request(url, headers=headers or {})
    with urllib.request.urlopen(req, timeout=timeout) as resp:
        return resp.read().decode("utf-8")

def _with_retries(fn, retries: int = QUOTE_RETRIES) -> Any:
    delay = 0.2
    last_exc = None
    for attempt in range(retries + 1):
        try:
            return fn()
        except Exception as e:
            last_exc = e
            if attempt < retries:
                time.sleep(delay)
                delay *= 1.8
    raise last_exc if last_exc else RuntimeError("Unknown error")

# ---------------- Online quote sources (fastest first) ---------------- #
def _src_github_zen() -> str:
    # Do NOT prefix with "GitHub Zen:"
    return _http_get_text("https://api.github.com/zen", headers={"User-Agent": "cp-template/1.0"}).strip()

def _src_stormconsultancy() -> str:
    j = _http_get_json("https://quotes.stormconsultancy.co.uk/random.json")
    q = j.get("quote") or j.get("text") or ""
    a = j.get("author") or "Unknown"
    return f"“{q}” — {a}"

def _src_programming_quotes_vercel() -> str:
    j = _http_get_json("https://programming-quotes-api.vercel.app/api/random")
    q = j.get("en") or j.get("quote") or j.get("content") or ""
    a = j.get("author") or "Unknown"
    return f"“{q}” — {a}"

def _src_quotable() -> str:
    j = _http_get_json("https://api.quotable.io/random?tags=technology|computers|science")
    q = j.get("content") or j.get("quote") or ""
    a = j.get("author") or "Unknown"
    return f"“{q}” — {a}"

_ONLINE_SOURCES = [_src_github_zen, _src_stormconsultancy, _src_programming_quotes_vercel, _src_quotable]

# ---------------- Built-in fallback pool (tech + CP) ---------------- #
_BUILTIN_QUOTES = [
    "AC first. Optimize second.",
    "WA teaches more than AC—once.",
    "If it’s O(1) in your head but O(n^2) on paper, the judge believes the paper.",
    "Debugging: where assumptions go to die.",
    "Think DP; code iteratively; test mercilessly.",
    "Greedy is great—when you can prove it.",
    "Edge cases aren’t edges; they’re cliffs.",
    "Premature optimization is TLE in disguise.",
    "Brute force is a baseline, not a plan.",
    "Binary search is a state of mind.",
    "When in doubt, draw the graph.",
    "Two pointers: because n^2 hurts.",
    "Read the constraints; they’re the problem’s love language.",
    "Proof first, code second, AC third.",
]

def _sanitize_one_line(s: str, max_len: int = 240) -> str:
    s = " ".join(s.split())
    s = s.replace("*/", "*∕")
    if len(s) > max_len:
        s = s[:max_len - 1].rstrip() + "…"
    return s.strip()

def _hash_quote(q: str) -> str:
    return hashlib.sha256(q.strip().encode("utf-8")).hexdigest()

def get_fresh_quote() -> str:
    """
    Fast quote fetch with total time budget.
    """
    start = time.monotonic()

    def under_budget() -> bool:
        return (time.monotonic() - start) * 1000.0 < QUOTE_TOTAL_BUDGET

    if _in_cooldown():
        log("Quote sources in cooldown; using fallback list for now.", "WARNING")
        return random.choice(_BUILTIN_QUOTES)

    recent = _recent_hashes()

    for src in _ONLINE_SOURCES:
        if not under_budget():
            break
        try:
            def attempt():
                return src()
            q = _with_retries(attempt, retries=QUOTE_RETRIES)
            q = _sanitize_one_line(q)
            if not q:
                continue
            h = _hash_quote(q)
            if h not in recent:
                _remember_quote_hash(h)
                log(f"Picked online quote from {src.__name__}", "INFO")
                return q
        except Exception as e:
            log(f"Quote source failed ({src.__name__}): {e}", "WARNING")
            continue

    _set_cooldown(QUOTE_COOLDOWN_MIN)

    for _ in range(4):
        q = _sanitize_one_line(random.choice(_BUILTIN_QUOTES))
        h = _hash_quote(q)
        if h not in recent:
            _remember_quote_hash(h)
            log("Picked quote from built-in list (offline fallback)", "INFO")
            return q
    return "Keep it simple. Make it fast. Prove it correct."

# ---------------- Metadata Extraction (CPH) ---------------- #
def extract_cph_metadata_once(cpp_filename: str) -> Dict[str, str]:
    metadata = {
        "Problem Name": "UNKNOWN",
        "Problem URL": "UNKNOWN",
        "Group": "UNKNOWN",
        "Time Limit": "UNKNOWN",
        "Memory Limit": "UNKNOWN",
    }

    try:
        cpp_basename = os.path.basename(cpp_filename)
        probable_json_prefix = f".{cpp_basename}_"
        if not os.path.isdir(CPH_META_DIR):
            return metadata

        json_files = [f for f in os.listdir(CPH_META_DIR) if f.startswith(probable_json_prefix)]
        if not json_files:
            return metadata

        json_files.sort(key=lambda x: os.path.getmtime(os.path.join(CPH_META_DIR, x)), reverse=True)
        json_path = os.path.join(CPH_META_DIR, json_files[0])

        with open(json_path, 'r', encoding='utf-8') as f:
            data = json.load(f)
            metadata["Problem Name"] = str(data.get("name", "UNKNOWN"))
            metadata["Problem URL"] = str(data.get("url", "UNKNOWN"))
            metadata["Group"] = str(data.get("group", "UNKNOWN"))
            tl = data.get('timeLimit', 'UNKNOWN')
            ml = data.get('memoryLimit', 'UNKNOWN')
            metadata["Time Limit"] = f"{tl} ms" if isinstance(tl, (int, float)) or str(tl).isdigit() else str(tl)
            metadata["Memory Limit"] = f"{ml} MB" if isinstance(ml, (int, float)) or str(ml).isdigit() else str(ml)
    except Exception:
        pass

    return metadata

def extract_cph_metadata(cpp_filename: str, wait_ms: int = META_WAIT_MS) -> Dict[str, str]:
    md = extract_cph_metadata_once(cpp_filename)
    if md["Problem Name"] != "UNKNOWN" or wait_ms <= 0:
        if md["Problem Name"] != "UNKNOWN":
            log("Loaded CPH metadata.", "SUCCESS")
        else:
            log("CPH metadata not found; proceeding with UNKNOWN fields.", "WARNING")
        return md

    deadline = time.monotonic() + (wait_ms / 1000.0)
    while time.monotonic() < deadline:
        time.sleep(0.12)
        md = extract_cph_metadata_once(cpp_filename)
        if md["Problem Name"] != "UNKNOWN":
            log("Loaded CPH metadata (after brief wait).", "SUCCESS")
            return md
    log("CPH metadata still unavailable; proceeding with UNKNOWN fields.", "WARNING")
    return md

# ---------------- Template Handling ---------------- #
_DEFAULT_TEMPLATE = """/**
 *    Author: BinaryPhoenix10
 *    Created:
 *    Profile: https://codeforces.com/profile/BinaryPhoenix10
 *    Quote:
 *    Group:
 *    Problem Name:
 *    Problem URL:
 *    Time Limit:
 *    Memory Limit:
 **/"""

def _read_template_lines() -> List[str]:
    try:
        with open(TEMPLATE_FILE, "r", encoding="utf-8") as f:
            return f.read().splitlines()
    except Exception as e:
        log(f"Template missing/unreadable ({TEMPLATE_FILE}); using built-in default. ({e})", "WARNING")
        return _DEFAULT_TEMPLATE.splitlines()

def _extract_comment_block(lines: List[str]) -> Tuple[List[str], int, int]:
    start, end = -1, -1
    for i, ln in enumerate(lines):
        if ln.strip().startswith("/*"):
            start = i
            break
    if start == -1:
        return [], -1, -1
    for j in range(start, len(lines)):
        if lines[j].strip().endswith("*/"):
            end = j + 1
            break
    if end == -1:
        return [], -1, -1
    return lines[start:end], start, end

def _ensure_quote_line(block: List[str]) -> List[str]:
    if any("Quote:" in ln for ln in block):
        return block
    insert_after = -1
    for idx, ln in enumerate(block):
        if any(k in ln for k in ("Profile:", "Created:", "Author:")):
            insert_after = idx
    quote_line = " *    Quote:"
    if insert_after != -1 and insert_after + 1 < len(block):
        return block[:insert_after + 1] + [quote_line] + block[insert_after + 1:]
    if len(block) >= 2:
        return block[:-1] + [quote_line] + [block[-1]]
    return block + [quote_line]

def _is_cp_header_block(block_lines: List[str]) -> bool:
    joined = "\n".join(block_lines)
    must_have = ["Author:", "Profile:", "Problem Name:", "Problem URL:", "Time Limit:", "Memory Limit:"]
    return all(k in joined for k in must_have)

def load_template(metadata: Dict[str, str]) -> List[str]:
    lines = _read_template_lines()
    block, start, end = _extract_comment_block(lines)
    if start == -1:
        block = _DEFAULT_TEMPLATE.splitlines()

    block = _ensure_quote_line(block)

    created_iso = datetime.datetime.now().astimezone().isoformat(timespec="seconds")
    quote_text = get_fresh_quote()
    out = []
    for ln in block:
        if "*    Created:" in ln:
            ln = f" *    Created: {created_iso}"
        elif "*    Group:" in ln:
            ln = f" *    Group: {metadata.get('Group','UNKNOWN')}"
        elif "*    Problem Name:" in ln:
            ln = f" *    Problem Name: {metadata.get('Problem Name','UNKNOWN')}"
        elif "*    Problem URL:" in ln:
            ln = f" *    Problem URL: {metadata.get('Problem URL','UNKNOWN')}"
        elif "*    Time Limit:" in ln:
            ln = f" *    Time Limit: {metadata.get('Time Limit','UNKNOWN')}"
        elif "*    Memory Limit:" in ln:
            ln = f" *    Memory Limit: {metadata.get('Memory Limit','UNKNOWN')}"
        elif "*    Quote:" in ln:
            ln = f" *    Quote: {quote_text}"
        out.append(ln)
    return out

# ---------------- File Update Logic ---------------- #
def _debounce_until_stable(path: str, timeout_s: float = 2.0, interval_s: float = 0.10) -> bool:
    end_by = time.time() + timeout_s
    last_size = -1
    while time.time() < end_by:
        try:
            size = os.path.getsize(path)
        except Exception:
            time.sleep(interval_s)
            continue
        if size == last_size and size > 0:
            return True
        last_size = size
        time.sleep(interval_s)
    return False

def _find_top_block_comment_region(lines: List[str]) -> Tuple[int, int]:
    """Return [start,end) for the first top-of-file /*...*/ block, or (-1,-1) if none."""
    if not lines or not lines[0].strip().startswith("/*"):
        return -1, -1
    for j in range(len(lines)):
        if lines[j].strip().endswith("*/"):
            return 0, j + 1
    return -1, -1

def update_metadata_block(cpp_file: str) -> None:
    """
    Replace (or insert) the header into `cpp_file` (no sentinels).
    Priority:
      1) If the very first block is our CP header → replace it.
      2) If a different license block exists → insert AFTER it.
      3) Else insert at the very top.
    """
    try:
        if not os.path.isfile(cpp_file):
            log(f"File not found: {cpp_file}", "ERROR")
            return

        _debounce_until_stable(cpp_file, timeout_s=WATCH_DEBOUNCE_MS/1000.0)

        metadata = extract_cph_metadata(cpp_file, wait_ms=META_WAIT_MS)
        new_header = load_template(metadata)
        if not new_header:
            log("Template header not loaded; aborting update.", "ERROR")
            return

        with open(cpp_file, 'r', encoding='utf-8') as f:
            original_lines = f.read().splitlines()

        b_s, b_e = _find_top_block_comment_region(original_lines)
        updated: List[str] = []
        write_mode = ""

        if b_s == 0 and b_e != -1:
            top_block = original_lines[b_s:b_e]
            if _is_cp_header_block(top_block):
                # Replace existing CP header
                updated.extend(new_header)
                if b_e < len(original_lines) and original_lines[b_e].strip() != "":
                    updated.append("")
                updated.extend(original_lines[b_e:])
                write_mode = "replace-cp-header"
            else:
                # Insert after license block
                updated.extend(original_lines[:b_e])
                if b_e < len(original_lines) and original_lines[b_e].strip() != "":
                    updated.append("")
                updated.extend(new_header)
                updated.append("")
                updated.extend(original_lines[b_e:])
                write_mode = "insert-after-license"
        else:
            # Insert at top
            updated.extend(new_header)
            updated.append("")
            updated.extend(original_lines)
            write_mode = "insert-top"

        new_text = "\n".join(updated) + "\n"
        old_text = "\n".join(original_lines) + "\n"
        if new_text == old_text:
            log(f"No changes needed in: {cpp_file} (mode={write_mode})", "SUCCESS")
            return

        tmp_path = f"{cpp_file}.tmp_write"
        with open(tmp_path, 'w', encoding='utf-8') as f:
            f.write(new_text)
        os.replace(tmp_path, cpp_file)

        log(f"Metadata header updated in: {cpp_file} (mode={write_mode})", "SUCCESS")

    except Exception as e:
        log(f"Error updating metadata in {cpp_file}: {e}", "ERROR")
        traceback.print_exc()

# ---------------- CLI Auto-Fallback ---------------- #
def get_latest_cpp_file() -> Optional[str]:
    try:
        cpp_files = [f for f in os.listdir(".") if f.endswith(".cpp") and os.path.isfile(f)]
        if not cpp_files:
            return None
        cpp_files.sort(key=lambda x: os.path.getmtime(x), reverse=True)
        return cpp_files[0]
    except Exception as e:
        log(f"Failed to scan for .cpp files: {e}", "ERROR")
        return None

# ---------------- Watchdog Handler (dedupe events) ---------------- #
class CPHHandler(FileSystemEventHandler):
    """
    Watches for newly created .cpp files and updates their headers.
    De-dupes near-duplicate create events (Windows/macOS can double-fire).
    """
    def __init__(self):
        super().__init__()
        self._seen: Dict[str, Tuple[float, float]] = {}  # path -> (last_wall_time, last_mtime)

    def on_created(self, event):
        try:
            if event.is_directory or not event.src_path.endswith(".cpp"):
                return
            path = event.src_path
            now = time.time()
            try:
                mtime = os.path.getmtime(path)
            except Exception:
                mtime = 0.0

            last = self._seen.get(path)
            if last and ((now - last[0]) < 1.0 or (mtime and mtime == last[1])):
                log(f"Deduped duplicate create event for {path}", "WARNING")
                return

            self._seen[path] = (now, mtime)
            log(f"Detected new C++ file: {path}", "INFO")
            time.sleep(max(0.05, WATCH_DEBOUNCE_MS / 1000.0))
            update_metadata_block(path)
        except Exception as e:
            log(f"Watcher failed on_created: {e}", "ERROR")

# ---------------- Main Entry ---------------- #
def _print_help_and_exit():
    banner("Help")
    print()
    print("Usage:")
    print("  python gen_cp_template.py               # Auto + Watch mode")
    print("  python gen_cp_template.py file.cpp      # Single file mode")
    print()
    print("Flags:")
    print("  --json-logs     Output logs as JSON (CI-friendly)")
    print("  --no-banner     Suppress the startup banner")
    print("  --no-color      Disable ANSI colors")
    print("  -h, --help      Show this help")
    sys.exit(0)

if __name__ == "__main__":
    try:
        if ARGS.help:
            _print_help_and_exit()

        if ARGS.file:
            banner("CLI (single file)")
            print()
            target_file = ARGS.file
            if not os.path.isfile(target_file):
                log(f"File not found: {target_file}", "ERROR")
                sys.exit(1)
            update_metadata_block(target_file)
        else:
            banner("Auto + Watch")
            print()

            target_file = get_latest_cpp_file()
            if target_file:
                log(f"No file provided. Auto-updating latest C++ file: {target_file}", "INFO")
                update_metadata_block(target_file)
            else:
                log("No .cpp file found for initial update. Waiting for new files...", "WARNING")

            observer = Observer()
            observer.schedule(CPHHandler(), WATCH_FOLDER, recursive=False)
            observer.start()
            log(f"Watching folder: {os.path.abspath(WATCH_FOLDER)}", "INFO")

            try:
                while True:
                    time.sleep(1)
            except KeyboardInterrupt:
                observer.stop()
                log("Interrupted. Stopping observer...", "INFO")
            observer.join()
            log("Observer stopped. Exiting.", "INFO")
    except Exception as e:
        log(f"Fatal error: {e}", "ERROR")
        traceback.print_exc()
        sys.exit(1)
