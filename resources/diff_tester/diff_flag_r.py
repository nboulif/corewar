#!/usr/bin/python
from __future__ import print_function
import sys, random, os
from os.path import dirname, abspath
from platform import system
import argparse
import math

def abs(n):
    if n < 0:
        n = -n
    return n

parser = argparse.ArgumentParser(description='Process some strings.')
parser.add_argument('strings', type=str, nargs='+',
                    help='our_vm vm_origin champs')
args = parser.parse_args().strings

print("args.strings -> |{}|".format(args))

os.system("./{} {} -r > diff_tester_our".format(args[0], args[2]))
os.system("./{} {} -v 4 > diff_tester_origin".format(args[1], args[2]))

file1 = open("diff_tester_our", 'r').read().split(sep="\n")
file2 = open("diff_tester_origin", 'r').read().split(sep="\n")

del file1[-1]
del file2[-1]
# file1.pop(file1[len(file1) - 1])
# file2.pop(file2[len(file2) - 1])
# print(file1)
# print(file2)
len1 = len(file1)
len2 = len(file2)

if (len1 > len2):
    max_len = len1
else:
    max_len = len2
if (len1 != len2):
    print("length of files are differents -> {}.\n".format(abs(len2 - len1)))
for i in range(max_len):
    if (file1[i] != file2[i]):
        # if file1[i][0:1] != 'P':
        #     file1[i] = file1[i - 1] + '\n' + file1[i]
        # if file2[i][0:1] != 'P':
        #     file2[i] = file2[i - 1] + '\n' + file2[i]
        print("first line with diff is {} :\n{}:\n{}\n{}:\n{}".format(i + 1, args[0], "\n".join(file1[i-5:i+10]), args[1], "\n".join(file2[i-10:i+10])))
        break
