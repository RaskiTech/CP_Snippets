"""Simple grader for competitive programming tasks by nuhakala.

Takes name of the task as parameter. Then it does the following:
- find all files of form "<name>-test-*" in the current working dir
- run "<name>.o" with every test file as stdin
- Highlight the difs between correct result and tested executable output
  with yellow.

Test files are of format:
    a b
    c d e f
    ...

    Output:
    <correct output>

Everything before line "Output:" is given as input to the executable.
Everything after "Output:" line is considered as correct answer. Alternatives
for "Output:" are:
- "output:"
- "Correct:"
- "correct:"
- "Result:"
- "result:"
- "res:"

PROBLEMS with this script:
- If there are multiple possible correct answers, only the one given in
  test-file is considered as correct.
"""

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


def print_dif(out, correct):
    out_lines = out.splitlines()
    correct_lines = correct.splitlines()
    dif = len(out_lines) - len(correct_lines)
    if dif < 0:
        for i in range(0, abs(dif)):
            out_lines.append("")
    else:
        for i in range(0, dif):
            correct_lines.append("")

    print("Your output:")
    for i in range(0, len(out_lines)):
        if out_lines[i] != correct_lines[i]:
            print(COLOR_YELLOW + out_lines[i] + COLOR_RESET)
        else:
            print(out_lines[i])

    print("Correct output:")
    for i in range(0, len(correct_lines)):
        if out_lines[i] != correct_lines[i]:
            print(COLOR_YELLOW + correct_lines[i] + COLOR_RESET)
        else:
            print(out_lines[i])


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
        out = subprocess.check_output([rootdir + name], input=data.encode())
        out = out.decode().strip()
        correct = get_correct(data).strip()
        if out == correct:
            print(COLOR_GREEN + "Test " + file + " passed." + COLOR_RESET)
            passed = passed + 1
        else:
            print(COLOR_RED + "Test " + file + " failed." + COLOR_RESET)
            print_dif(out, correct)
            # If you don't want colorful output
            # print("Program output:")
            # print(out)
            # print("Correct result:")
            # print(correct)

if passed == len(files_ar):
    print(COLOR_GREEN + "All tests passed." + COLOR_RESET)
else:
    print(COLOR_RED + str(passed) + "/" + str(len(files_ar)) + " tests passed.")
