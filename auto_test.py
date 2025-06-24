import os
import subprocess
import time
from pathlib import Path
from difflib import unified_diff

exe_name = "a.exe"
input_dir = "tests"
input_prefix = "in"
output_prefix = "out"

def run_test(input_file, output_file, test_id):
    with open(input_file, 'r') as f_in:
        start = time.time()
        result = subprocess.run([exe_name], stdin=f_in, capture_output=True, text=True, timeout=2)
        end = time.time()

    expected_output = Path(output_file).read_text().strip()
    actual_output = result.stdout.strip()

    print(f"\n🧪 Test {test_id}: {'✅ PASS' if actual_output == expected_output else '❌ FAIL'}")
    print(f"⏱️ Time: {(end - start)*1000:.2f} ms")

    if actual_output != expected_output:
        diff = unified_diff(expected_output.splitlines(), actual_output.splitlines(),
                            fromfile='expected', tofile='actual', lineterm='')
        print("\n".join(diff))

def main():
    i = 1
    while True:
        input_file = f"{input_dir}/{input_prefix}{i}.txt"
        output_file = f"{input_dir}/{output_prefix}{i}.txt"
        if not os.path.exists(input_file) or not os.path.exists(output_file):
            break
        run_test(input_file, output_file, i)
        i += 1

    if i == 1:
        print("⚠️ No test cases found.")

if __name__ == "__main__":
    main()
