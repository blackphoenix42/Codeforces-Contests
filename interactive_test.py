import subprocess

def run_with_input():
    print("🧪 Enter input (end with empty line):")
    user_input = ""
    while True:
        line = input()
        if not line:
            break
        user_input += line + '\n'

    proc = subprocess.run(["a.exe"], input=user_input, text=True, capture_output=True)
    print("📤 Output:")
    print(proc.stdout)

if __name__ == "__main__":
    while True:
        run_with_input()
        cont = input("🔁 Test again? (y/n): ").strip().lower()
        if cont != 'y':
            break
