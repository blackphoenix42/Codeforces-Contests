import os
import shutil

def archive_contest(contest_code):
    os.makedirs(contest_code, exist_ok=True)
    for file in os.listdir():
        if file.startswith(contest_code) and file.endswith(".cpp"):
            shutil.move(file, os.path.join(contest_code, file))
    print(f"📁 Moved all {contest_code} problems into {contest_code}/")

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Usage: python cleanup.py <contest_code>")
    else:
        archive_contest(sys.argv[1])
