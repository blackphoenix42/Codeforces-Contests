import subprocess

def run_once():
    subprocess.run(["gen.exe"], stdout=open("input.txt", "w"))
    with open("input.txt", "r") as f:
        out1 = subprocess.run(["a.exe"], stdin=f, capture_output=True, text=True).stdout
    with open("input.txt", "r") as f:
        out2 = subprocess.run(["brute.exe"], stdin=f, capture_output=True, text=True).stdout
    return out1.strip(), out2.strip()

def main():
    for i in range(1, 1001):
        out1, out2 = run_once()
        if out1 != out2:
            print(f"\n❌ Test {i} failed")
            print(f"Input:"); print(open("input.txt").read())
            print(f"Your Output:\n{out1}")
            print(f"Brute Output:\n{out2}")
            return
        else:
            print(f"✅ Test {i} passed")
    print("🎉 All tests passed!")

if __name__ == "__main__":
    main()
