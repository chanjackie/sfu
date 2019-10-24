#!/usr/bin/python3
# CMPT310 A2
#####################################################
#####################################################
# Please enter the number of hours you spent on this
# assignment here
"""
num_hours_i_spent_on_this_assignment = 
"""
#
#####################################################
#####################################################

#####################################################
#####################################################
# Give one short piece of feedback about the course so far. What
# have you found most interesting? Is there a topic that you had trouble
# understanding? Are there any changes that could improve the value of the
# course to you? (We will anonymize these before reading them.)
"""
<Your feedback goes here>


"""
#####################################################
#####################################################
import sys, getopt
import copy
import random
import time
import numpy as np
sys.setrecursionlimit(10000)

class SatInstance:
	def __init__(self):
		pass

	def from_file(self, inputfile):
		self.clauses = list()
		self.VARS = set()
		self.p = 0
		self.cnf = 0
		with open(inputfile, "r") as input_file:
			self.clauses.append(list())
			maxvar = 0
			for line in input_file:
				tokens = line.split()
				if len(tokens) != 0 and tokens[0] not in ("p", "c"):
					for tok in tokens:
						lit = int(tok)
						maxvar = max(maxvar, abs(lit))
						if lit == 0:
							self.clauses.append(list())
						else:
							self.clauses[-1].append(lit)
				if tokens[0] == "p":
					self.p = int(tokens[2])
					self.cnf = int(tokens[3])
			assert len(self.clauses[-1]) == 0
			self.clauses.pop()
			if (maxvar > self.p):
				print("Non-standard CNF encoding!")
				sys.exit(5)
		# Variables are numbered from 1 to p
		for i in range(1, self.p + 1):
			self.VARS.add(i)

	def __str__(self):
		s = ""
		for clause in self.clauses:
			s += str(clause)
			s += "\n"
		return s


def main(argv):
	inputfile = ''
	verbosity = False
	inputflag = False
	try:
		opts, args = getopt.getopt(argv, "hi:v", ["ifile="])
	except getopt.GetoptError:
		print('DPLLsat.py -i <inputCNFfile> [-v] ')
		sys.exit(2)
	for opt, arg in opts:
		if opt == '-h':
			print('DPLLsat.py -i <inputCNFfile> [-v]')
			sys.exit()
		##-v sets the verbosity of informational output
		## (set to true for output veriable assignments, defaults to false)
		elif opt == '-v':
			verbosity = True
		elif opt in ("-i", "--ifile"):
			inputfile = arg
			inputflag = True
	if inputflag:
		instance = SatInstance()
		instance.from_file(inputfile)
		#start_time = time.time()
		solve_dpll(instance, verbosity)
		#print("--- %s seconds ---" % (time.time() - start_time))

	else:
		print("You must have an input file!")
		print('DPLLsat.py -i <inputCNFfile> [-v]')


# Finds a satisfying assignment to a SAT instance,
# using the DPLL algorithm.
# Input: a SAT instance and verbosity flag
# Output: print "UNSAT" or
#    "SAT"
#    list of true literals (if verbosity == True)
#
#  You will need to define your own
#  DPLLsat(), DPLL(), pure-elim(), propagate-units(), and
#  any other auxiliary functions
def solve_dpll(instance, verbosity):
	# print(instance)
	# instance.VARS goes 1 to N in a dict
	# print(instance.VARS)
	# print(verbosity)
	###########################################
	# Start your code
	clauses = instance.clauses
	variables = instance.VARS
	# print("----INSTANCE----")
	# print(instance)
	# print("----CLAUSES----")
	# print(instance.clauses)
	# print("----VARS----")
	# print(instance.VARS)
	# print("----VERBOSITY----")
	# print(verbosity)
	ret = DPLL(clauses, variables)
	if not ret:
		print("UNSAT")
	else:
		print("SAT")
		if verbosity:
			trueLiterals = []
			for i in ret:
				if ret[i] == True:
					trueLiterals.append(i)
			print(trueLiterals)






	###########################################

def DPLL(oClauses, oSymbols, oModel={}):
	model = copy.deepcopy(oModel)
	symbols = copy.deepcopy(oSymbols)
	clauses = copy.deepcopy(oClauses)
	sat = DPLLsat(clauses, model)
	if sat == 0:
		return model
	if sat == -1:
		return False
	prop = propagateUnits(clauses)
	# print(prop)
	if (prop[0]):
		model[prop[1]] = prop[2]
		symbols.remove(prop[1])
		return DPLL(clauses, symbols, model)
	P = symbols.pop()
	for value in [True, False]:
		# print(P, value)
		model[P] = value
		ret = DPLL(clauses, symbols, model)
		# print("Ret:", ret, "P:", P)
		if ret is not False and ret is not None:
			return ret

def DPLLsat(clauses, model):
	# print(clauses)
	# print(model)
	for i in model:
		symbol = i
		if not model[i]:
			symbol = -i
		j = 0
		while j != len(clauses):
			if (symbol in clauses[j]):
				clauses.pop(j)
			else:
				j += 1
		for j in range(len(clauses)):
			if (-symbol in clauses[j]):
				clauses[j].remove(-symbol)
	# print("---- AFTER REMOVAL ----")
	# print(clauses)
	if (not clauses):
		return 0
	elif ([] in clauses):
		return -1
	else:
		return 1

def propagateUnits(clauses):
	# clausesCopy = copy.deepcopy(clauses)
	# print(clauses)
	for i in clauses:
		if (len(i) == 1):
			return [True, abs(i[0]), i[0]>0]
	return [False]


if __name__ == "__main__":
	main(sys.argv[1:])