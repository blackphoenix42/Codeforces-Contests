import subprocess
import sys
import os
import difflib
from datetime import datetime

# Configurable
TIME_LIMIT = 2  # seconds
LOG_FILE = "stress_log.txt"

# Executable names
exe = sys.argv[1] if len(sys.argv) > 1 else "main.exe"
brute = "brute.exe"
gen = "gen.exe"

def check_files_exist():
    missing = [f for f in [exe, brute, gen] if not os.path.exists(f)]
    if missing:
        print("❌ Required files not found:")
        for f in missing:
            print(f"  - {f}")
        sys.exit(1)

def write_log(content):
    with open(LOG_FILE, "a") as f:
        f.write(content + "\n")

def run_once(test_id):
    # 1. Generate input
    with open("input.txt", "w") as f:
        subprocess.run([gen], stdout=f)

    with open("input.txt", "r") as f:
        input_data = f.read()

    # 2. Run optimized with timeout
    try:
        opt_result = subprocess.run([exe], input=input_data, text=True,
                                    capture_output=True, timeout=TIME_LIMIT)
        opt_out = opt_result.stdout.strip()
    except subprocess.TimeoutExpired:
        print(f"\n⏱️ Timeout: {exe} exceeded {TIME_LIMIT}s on test #{test_id}")
        write_log(f"[FAIL] Test #{test_id} - TIMEOUT in optimized solution")
        sys.exit(1)

    # 3. Run brute with timeout
    try:
        brute_result = subprocess.run([brute], input=input_data, text=True,
                                      capture_output=True, timeout=TIME_LIMIT)
        brute_out = brute_result.stdout.strip()
    except subprocess.TimeoutExpired:
        print(f"\n⏱️ Timeout: {brute} exceeded {TIME_LIMIT}s on test #{test_id}")
        write_log(f"[FAIL] Test #{test_id} - TIMEOUT in brute solution")
        sys.exit(1)

    # 4. Compare
    if opt_out != brute_out:
        print(f"\n❌ Mismatch on test #{test_id}")
        print("📥 Input:")
        print(input_data)
        print("\n📤 Optimized Output:")
        print(opt_out)
        print("\n🐢 Brute Output:")
        print(brute_out)
        print("\n🔍 Diff:")
        diff = "\n".join(difflib.unified_diff(
            brute_out.splitlines(),
            opt_out.splitlines(),
            fromfile="brute",
            tofile="optimized",
            lineterm=""
        ))
        print(diff)

        # Log mismatch
        write_log(f"\n[FAIL] Test #{test_id} @ {datetime.now().isoformat()}")
        write_log("Input:\n" + input_data)
        write_log("Brute:\n" + brute_out)
        write_log("Optimized:\n" + opt_out)
        write_log("Diff:\n" + diff)
        sys.exit(1)
    else:
        print(f"✅ Test #{test_id} passed")
        write_log(f"[PASS] Test #{test_id}")

def main():
    # Clear previous log
    with open(LOG_FILE, "w") as f:
        f.write(f"=== Stress Test Log Started @ {datetime.now().isoformat()} ===\n\n")

    check_files_exist()
    for i in range(1, 10001):
        run_once(i)
    print("\n🎉 All tests passed successfully.")
    write_log("\n🎉 ALL TESTS PASSED")

if __name__ == "__main__":
    main()


# How to run (compile these first):
# g++ -std=c++23 main.cpp -o main.exe
# g++ -std=c++23 brute.cpp -o brute.exe
# g++ -std=c++23 gen.cpp -o gen.exe

# Then run the stress test script:
# python stress_test.py main.exe
