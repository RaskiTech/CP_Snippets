import subprocess
import sys
import os
import re

rootdir = "./"
name = sys.argv[1]
regex = re.compile(name + "-test")


COLOR_RED = "\x1b[31m"
COLOR_GREEN = "\x1b[32m"
COLOR_YELLOW = "\x1b[33m"
COLOR_RESET = "\x1b[0m "


def get_correct(data):
    correct = data.partition("Output:")[2]
    if len(correct) == 0:
        correct = data.partition("output:")[2]
    if len(correct) == 0:
        correct = data.partition("Correct:")[2]
    if len(correct) == 0:
        correct = data.partition("correct:")[2]
    if len(correct) == 0:
        correct = data.partition("Result:")[2]
    if len(correct) == 0:
        correct = data.partition("result:")[2]
    if len(correct) == 0:
        correct = data.partition("res:")[2]
    return correct


def print_dif(out_lines, correct_lines):
    i = 0
    j = 0
    print("Your output:")
    while i < len(out_lines):
        if out_lines[i].startswith("DEBUG"):
            print(out_lines[i])
        elif j < len(correct_lines) and out_lines[i] != correct_lines[j]:
            print(COLOR_YELLOW + out_lines[i] + COLOR_RESET)
            j = j + 1
        else:
            print(out_lines[i])
            j = j + 1
        i = i + 1

    i = 0
    j = 0
    print("Correct output:")
    while j < len(correct_lines):
        if i < len(out_lines) and out_lines[i] != correct_lines[j]:
            print(COLOR_YELLOW + correct_lines[j] + COLOR_RESET)
            j = j + 1
        else:
            print(correct_lines[j])
            j = j + 1
        i = i + 1


files_ar = []
for root, dirs, files in os.walk(rootdir):
    for file in files:
        if regex.match(file):
            files_ar.append(file)

files_ar.sort()
passed = 0
for file in files_ar:
    with open(file, "r") as f:
        data = f.read()
        p = subprocess.run(
            [rootdir + name + ".o"], input=data.encode(), capture_output=True
        )
        out = p.stdout
        out = out.decode().strip()

        # Filter debug prints
        out_lines = out.splitlines()
        out_filtered = list(filter(lambda x: not x.startswith("DEBUG"), out_lines))
        out = "\n".join(out_filtered)

        correct = get_correct(data).strip()
        correct_lines = correct.splitlines()
        if out == correct:
            print(COLOR_GREEN + "Test " + file + " passed." + COLOR_RESET)
            passed = passed + 1
        else:
            print(COLOR_RED + "Test " + file + " failed." + COLOR_RESET)
            print_dif(out_lines, correct_lines)
            # If you don't want colorful output
            # print("Program output:")
            # print(out)
            # print("Correct result:")
            # print(correct)

if passed == len(files_ar):
    print(COLOR_GREEN + "All tests passed." + COLOR_RESET)
else:
    print(COLOR_RED + str(passed) + "/" + str(len(files_ar)) + " tests passed.")
