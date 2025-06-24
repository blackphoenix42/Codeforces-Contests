import time
import os
import datetime
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

TEMPLATE_FILE = "template.cc"
WATCH_FOLDER = "."  # Set this to your cph folder path

def load_template():
    with open(TEMPLATE_FILE, "r", encoding="utf-8") as f:
        lines = f.read().splitlines()
    for i, line in enumerate(lines):
        if "*    Created:" in line:
            lines[i] = f" *    Created: {datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')}"
            break
    return "\n".join(lines)

class CPHHandler(FileSystemEventHandler):
    def on_created(self, event):
        if not event.is_directory and event.src_path.endswith(".cpp"):
            time.sleep(1.0)  # Give CPH time to finish writing

            try:
                with open(event.src_path, 'w', encoding='utf-8') as f:
                    f.write(load_template())
                print(f"✅ Forcefully injected template into: {event.src_path}")
            except Exception as e:
                print(f"❌ Error writing to {event.src_path}: {e}")

if __name__ == "__main__":
    observer = Observer()
    observer.schedule(CPHHandler(), WATCH_FOLDER, recursive=False)
    observer.start()
    print(f"Watching folder: {WATCH_FOLDER}")
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        observer.stop()
    observer.join()

# python gen_cp_template.py