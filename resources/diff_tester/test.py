#!/usr/bin/python
from __future__ import print_function
import sys, random, os
from os.path import dirname, abspath
from platform import system
import argparse

def generate_diff(dump_nb):
	os.system(" ".join(["./corewar -dump", str(dump_nb), p, ">", our, "&& ./resources/vm_champs/corewar -d", str(dump_nb), p, ">", real]))
	our_file = open(our, 'r').read().split(sep="0x")
	real_file = open(real, 'r').read().split(sep="0x")
	our_file.pop(0)
	real_file.pop(0)
	our_file = map(lambda x: x[10:], our_file)
	real_file = map(lambda x: x[10:-2] + '\n', real_file)
	open(our, 'w').write("".join(our_file))
	open(real, 'w').write("".join(real_file))
	os.system(" ".join(["diff", our, real, ">", diff]))

parser = argparse.ArgumentParser(description='Process some strings.')
parser.add_argument('strings', type=str, nargs='+',
                    help='name n_champs [champ_file ...]')
args = parser.parse_args().strings
print("args.strings -> |{}|".format(args))
name = args[0]
n = int(args[1])
p = " ".join([args[i + 2] for i in range(n)])
our = "ourdump_" + name
real = "realdump_" + name
diff = "diffdump_" + name
s_c, c_c, e_c, error_c = 1, 10000, 10000, -1
while (s_c + 1 != e_c and e_c <= 100000):
	generate_diff(c_c)
	if open(diff, 'r').read() == "":
		if error_c > -1:
			c_c, s_c = (e_c - c_c) // 2 + c_c, c_c 
		else:
			s_c = e_c + 1
			e_c += 10000
			c_c = e_c
	else:
		error_c = c_c
		c_c, e_c = (c_c - s_c) // 2 + s_c, c_c
if error_c == -1:
	print(error_c)
else:
	print(e_c)
generate_diff(e_c)
os.system("cat " + diff)