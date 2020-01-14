#!/usr/local/bin/python3
from __future__ import print_function
import sys, random, os
from os.path import dirname, abspath
from platform import system
import argparse


class TheProcess():

	def __init__(self):

		parser = argparse.ArgumentParser(description='Process some strings.')
		parser.add_argument('strings', type=str, nargs='+',
							help='name n_champs [champ_file ...]')
		
		args = parser.parse_args().strings

		print("args.strings -> |{}|".format(args))

		name = args.pop(0)
		
		self.our = name + ".ourdump"
		self.real = name + ".realdump"
		self.diff = name + ".diffdump"

		self.players = " ".join(args)

	def generate_diff(self, dump_nb):
		os.system(" ".join(["./corewar -D", str(dump_nb), self.players, ">", self.our, "&& ../resource/./corewar_res -d", str(dump_nb), self.players, ">", self.real]))
		our_file = ""
		real_file = ""
		with open(self.our, 'r') as file:
			our_file = file.read().split(sep="0x")
		with open(self.real, 'r') as file:
			real_file = file.read().split(sep="0x")
		our_file.pop(0)
		real_file.pop(0)

		with open(self.our, 'w') as file:
			file.write("".join(our_file))
		with open(self.real, 'w') as file:
			file.write("".join(real_file))

		os.system(" ".join(["diff", self.our, self.real, ">", self.diff]))



	def process(self):
		s_c, c_c, e_c, error_c = 1, 10000, 10000, -1
		while (s_c + 1 != e_c and e_c <= 100000):
			self.generate_diff(c_c)
			with open(self.diff, 'r') as file:
				if file.read() == "":
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

		self.generate_diff(e_c)

if __name__ == "__main__":

	the_process = TheProcess()
	
	the_process.process()

	os.system("cat " + the_process.diff + " && rm *dump")
