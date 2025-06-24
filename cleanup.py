import os
import shutil
import sys
from datetime import datetime

def archive_contest(contest_code):
    dest_dir = contest_code
    os.makedirs(dest_dir, exist_ok=True)

    moved_files = 0
    for file in os.listdir():
        if file.startswith(contest_code) and file.endswith(".cpp"):
            shutil.move(file, os.path.join(dest_dir, file))
            moved_files += 1

    print(f"📦 Archived {moved_files} file(s) into ./{dest_dir}/")

def main():
    if len(sys.argv) < 2:
        print("Usage: python cleanup.py <contest_code>")
        return

    contest_code = sys.argv[1].strip().upper()
    print(f"🧼 Starting cleanup for contest: {contest_code}")
    archive_contest(contest_code)

if __name__ == "__main__":
    main()

# Usage:
# python cleanup.py ABC900
