import time
import os
import datetime
import json
import traceback
import sys
from typing import Optional
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

TEMPLATE_FILE = "template.cc"
WATCH_FOLDER = "."
CPH_META_DIR = ".cph"

# ---------------- Logging Utility ---------------- #
def log(msg, level="INFO"):
    emojis = {
        "INFO": "ℹ️",
        "SUCCESS": "✅",
        "WARNING": "⚠️",
        "ERROR": "❌"
    }
    colors = {
        "INFO": "\033[94m",      # Blue
        "SUCCESS": "\033[92m",   # Green
        "WARNING": "\033[93m",   # Yellow
        "ERROR": "\033[91m",     # Red
        "ENDC": "\033[0m"
    }
    timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    emoji = emojis.get(level, "")
    print(f"{colors.get(level, '')}[{level}] {emoji} {timestamp}: {msg}{colors['ENDC']}")

# ---------------- Metadata Extraction ---------------- #
def extract_cph_metadata(cpp_filename):
    metadata = {
        "Problem Name": "UNKNOWN",
        "Problem URL": "UNKNOWN",
        "Group": "UNKNOWN",
        "Time Limit": "UNKNOWN",
        "Memory Limit": "UNKNOWN"
    }

    try:
        cpp_basename = os.path.basename(cpp_filename)
        probable_json_prefix = f".{cpp_basename}_"
        json_files = [f for f in os.listdir(CPH_META_DIR) if f.startswith(probable_json_prefix)]

        if not json_files:
            log(f"No matching metadata JSON found for {cpp_basename}", "WARNING")
            return metadata

        json_files.sort(key=lambda x: os.path.getmtime(os.path.join(CPH_META_DIR, x)), reverse=True)
        json_path = os.path.join(CPH_META_DIR, json_files[0])

        with open(json_path, 'r', encoding='utf-8') as f:
            data = json.load(f)
            metadata["Problem Name"] = data.get("name", "UNKNOWN")
            metadata["Problem URL"] = data.get("url", "UNKNOWN")
            metadata["Group"] = data.get("group", "UNKNOWN")
            metadata["Time Limit"] = f"{data.get('timeLimit', 'UNKNOWN')} ms"
            metadata["Memory Limit"] = f"{data.get('memoryLimit', 'UNKNOWN')} MB"

        log(f"Loaded metadata from: {json_path}", "SUCCESS")

    except Exception as e:
        log(f"Failed to extract metadata for {cpp_filename}: {e}", "ERROR")
        traceback.print_exc()

    return metadata

# ---------------- Template Loader ---------------- #
def load_template(metadata):
    try:
        with open(TEMPLATE_FILE, "r", encoding="utf-8") as f:
            lines = f.read().splitlines()
    except Exception as e:
        log(f"Failed to read template file: {TEMPLATE_FILE}. Error: {e}", "ERROR")
        return []

    for i, line in enumerate(lines):
        if "*    Created:" in line:
            lines[i] = f" *    Created: {datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')}"
        elif "*    Group:" in line:
            lines[i] = f" *    Group: {metadata['Group']}"
        elif "*    Problem Name:" in line:
            lines[i] = f" *    Problem Name: {metadata['Problem Name']}"
        elif "*    Problem URL:" in line:
            lines[i] = f" *    Problem URL: {metadata['Problem URL']}"
        elif "*    Time Limit:" in line:
            lines[i] = f" *    Time Limit: {metadata['Time Limit']}"
        elif "*    Memory Limit:" in line:
            lines[i] = f" *    Memory Limit: {metadata['Memory Limit']}"
    return lines

# ---------------- Header Updater ---------------- #
def update_metadata_block(cpp_file):
    metadata = extract_cph_metadata(cpp_file)
    new_header = load_template(metadata)

    try:
        with open(cpp_file, 'r', encoding='utf-8') as f:
            original_lines = f.read().splitlines()

        updated_lines = []
        in_comment_block = False
        header_replaced = False

        i = 0
        n = len(original_lines)

        # Skip existing header comment block if present
        if i < n and original_lines[i].strip().startswith("/*"):
            in_comment_block = True
            while i < n:
                if original_lines[i].strip().endswith("*/"):
                    i += 1
                    break
                i += 1

        # Insert new header
        updated_lines.extend(new_header)
        updated_lines.append("")  # spacing

        # Add the rest of the original content
        updated_lines.extend(original_lines[i:])

        with open(cpp_file, 'w', encoding='utf-8') as f:
            f.write("\n".join(updated_lines) + "\n")

        log(f"Metadata header updated in: {cpp_file}", "SUCCESS")

    except Exception as e:
        log(f"Error updating metadata in {cpp_file}: {e}", "ERROR")
        traceback.print_exc()

# ---------------- CLI Auto-Fallback ---------------- #
def get_latest_cpp_file() -> Optional[str]:
    cpp_files = [f for f in os.listdir(".") if f.endswith(".cpp")]
    if not cpp_files:
        return None
    cpp_files.sort(key=lambda x: os.path.getmtime(x), reverse=True)
    return cpp_files[0]

# ---------------- Watchdog Handler ---------------- #
class CPHHandler(FileSystemEventHandler):
    def on_created(self, event):
        if not event.is_directory and event.src_path.endswith(".cpp"):
            log(f"Detected new C++ file: {event.src_path}", "INFO")
            time.sleep(1.0)
            update_metadata_block(event.src_path)

# ---------------- Main Entry ---------------- #
if __name__ == "__main__":
    if len(sys.argv) == 2:
        # Manual override: CLI mode
        target_file = sys.argv[1]
        if not os.path.isfile(target_file):
            log(f"File not found: {target_file}", "ERROR")
            sys.exit(1)
        update_metadata_block(target_file)
    elif len(sys.argv) == 1:
        # No argument: auto mode + watchdog
        target_file = get_latest_cpp_file()
        if target_file:
            log(f"No file provided. Auto-updating latest C++ file: {target_file}", "INFO")
            update_metadata_block(target_file)

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
    else:
        log("Usage: python gen_cp_template.py [optional_cpp_file]", "ERROR")


# python gen_cp_template.py
# python gen_cp_template.py [optional_cpp_file]