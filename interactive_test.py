import subprocess
import threading
import sys
import os
from datetime import datetime

TIME_LIMIT = 2  # seconds
LOG_FILE = "interactive_log.txt"

def log(msg):
    with open(LOG_FILE, "a", encoding="utf-8") as f:
        f.write(msg + "\n")

def run_interactive(solution, interactor, input_file=None):
    log(f"\n=== Interactive Test Started @ {datetime.now().isoformat()} ===")
    if not os.path.exists(solution) or not os.path.exists(interactor):
        print("❌ One or both executables not found.")
        log("Missing executables.")
        return

    # Setup pipes
    sol_proc = subprocess.Popen(
        [solution],
        stdin=subprocess.PIPE, stdout=subprocess.PIPE,
        stderr=subprocess.PIPE, text=True
    )
    interactor_proc = subprocess.Popen(
        [interactor],
        stdin=subprocess.PIPE, stdout=subprocess.PIPE,
        stderr=subprocess.PIPE, text=True
    )

    if input_file and os.path.exists(input_file):
        with open(input_file, 'r') as f:
            init_input = f.read()
            interactor_proc.stdin.write(init_input)
            interactor_proc.stdin.flush()

    def pipe(src, dst, label_from, label_to):
        while True:
            line = src.stdout.readline()
            if not line:
                break
            dst.stdin.write(line)
            dst.stdin.flush()
            log(f"[{label_from} → {label_to}]: {line.strip()}")

    t1 = threading.Thread(target=pipe, args=(sol_proc, interactor_proc, "sol", "int"))
    t2 = threading.Thread(target=pipe, args=(interactor_proc, sol_proc, "int", "sol"))

    t1.start()
    t2.start()

    try:
        sol_proc.wait(timeout=TIME_LIMIT)
        interactor_proc.wait(timeout=TIME_LIMIT)
    except subprocess.TimeoutExpired:
        sol_proc.kill()
        interactor_proc.kill()
        print("⏱️ Timeout reached.")
        log("❌ TIMEOUT")
        return

    t1.join()
    t2.join()

    sol_code = sol_proc.returncode
    interactor_code = interactor_proc.returncode

    print(f"\n✅ Finished. Solver RC={sol_code}, Interactor RC={interactor_code}")
    log(f"Solver return code: {sol_code}")
    log(f"Interactor return code: {interactor_code}")

    if interactor_code == 0:
        print("✅ Accepted")
        log("✅ Accepted")
    else:
        print("❌ Wrong Answer / Interactor Error")
        log("❌ WA or interactor issue")

def main():
    args = sys.argv
    if len(args) < 3:
        print("Usage: python interactive_test.py <solution.exe> <interactor.exe> [input.txt]")
        return
    solution = args[1]
    interactor = args[2]
    input_file = args[3] if len(args) >= 4 else None
    run_interactive(solution, interactor, input_file)

if __name__ == "__main__":
    main()

# Usage:
# python interactive_test.py main.exe interactor.exe <input.txt>
