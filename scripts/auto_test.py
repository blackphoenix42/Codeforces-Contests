import os
import subprocess
import time
import sys
from pathlib import Path
from difflib import unified_diff
from datetime import datetime

# Configs
TIME_LIMIT = 2  # seconds
LOG_FILE = "test_log.txt"
INPUT_DIR = "tests"
INPUT_PREFIX = "in"
OUTPUT_PREFIX = "out"

# Executable from CLI or fallback
exe_name = sys.argv[1] if len(sys.argv) > 1 else "main.exe"

def write_log(content):
    with open(LOG_FILE, "a", encoding="utf-8") as f:
        f.write(content + "\n")

def run_test(input_path, output_path, test_id):
    with open(input_path, 'r') as f:
        input_data = f.read()

    expected_output = Path(output_path).read_text().strip()

    try:
        start = time.time()
        result = subprocess.run(
            [exe_name], input=input_data, text=True,
            capture_output=True, timeout=TIME_LIMIT
        )
        end = time.time()
    except subprocess.TimeoutExpired:
        print(f"\n⏱️ Timeout on Test #{test_id} (> {TIME_LIMIT}s)")
        write_log(f"[FAIL] Test #{test_id} - TIMEOUT")
        return

    actual_output = result.stdout.strip()
    passed = (actual_output == expected_output)

    print(f"\n🧪 Test #{test_id}: {'✅ PASS' if passed else '❌ FAIL'}")
    print(f"⏱️ Time: {(end - start) * 1000:.2f} ms")

    if passed:
        write_log(f"[PASS] Test #{test_id}")
    else:
        diff = "\n".join(unified_diff(
            expected_output.splitlines(),
            actual_output.splitlines(),
            fromfile="expected",
            tofile="actual",
            lineterm=""
        ))

        print("🔍 Diff:\n" + diff)
        write_log(f"\n[FAIL] Test #{test_id} @ {datetime.now().isoformat()}")
        write_log("Input:\n" + input_data)
        write_log("Expected:\n" + expected_output)
        write_log("Actual:\n" + actual_output)
        write_log("Diff:\n" + diff)

def main():
    with open(LOG_FILE, "w", encoding="utf-8") as f:
        f.write(f"=== Auto Test Log Started @ {datetime.now().isoformat()} ===\n\n")

    i = 1
    while True:
        input_path = f"{INPUT_DIR}/{INPUT_PREFIX}{i}.txt"
        output_path = f"{INPUT_DIR}/{OUTPUT_PREFIX}{i}.txt"

        if not os.path.exists(input_path) or not os.path.exists(output_path):
            break

        run_test(input_path, output_path, i)
        i += 1

    if i == 1:
        print("⚠️ No test cases found in ./tests/")
        write_log("No test cases found.")
    else:
        print(f"\n✅ Tested {i-1} case(s)")
        write_log(f"\n✅ Auto-Test Finished ({i-1} test cases)")

if __name__ == "__main__":
    main()

# Usage:
# python auto_test.py main.exe