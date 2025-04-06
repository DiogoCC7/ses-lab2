import subprocess
import os

SEED_FILE = "./inputs/valid_input.txt"
NUM_MUTATIONS = 1000
BINARY_PATH = "./bin/vuln.o"
RADAMSA_PATH = "radamsa"

def run_input(input_data):
    try:
        result = subprocess.run(
            [BINARY_PATH],
            input=input_data,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            timeout=1
        )
        if b"Segmentation fault" in result.stderr or result.returncode != 0:
            print("[!] Potential crash detected!")
            print("Input:", repr(input_data))
            print("Output:", result.stdout.decode(errors='ignore'))
    except subprocess.TimeoutExpired:
        print("[!] Timeout - possible hang")

def fuzz():
    with open(SEED_FILE, 'rb') as f:
        seed_data = f.read()

    for i in range(NUM_MUTATIONS):
        fuzzed = subprocess.check_output(
            [RADAMSA_PATH, "-n", "1"],
            input=seed_data
        )
        print(f"[{i+1}] Fuzzing with input:", fuzzed.decode(errors='ignore').strip())
        run_input(fuzzed)

if __name__ == "__main__":
    fuzz()
