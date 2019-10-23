#!/usr/bin/python3
# CMPT310 A2 Sample solution

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
#    list of false literals (if verbosity == True)
#
#  You will need to define your own
#  solve(VARS, F), pure-elim(F), propagate-units(F), and
#  any other auxiliary functions

def propagate_units(F,model):
    unitClauses = []
    newUnitClauses = False
    for clause in F:
        if (len(clause) == 1):
            if(clause[0]*-1 not in unitClauses):
                unitClauses.append(clause[0])
    # for each unit clause [x]
    # remove all unit clauses containing x
    for unit_clause in unitClauses:
        F[:] = [clause for clause in F if not (unit_clause in clause)]
    # for each unit clause [x]
    # remove all -x
    # And add x to model
    for unit_clause in unitClauses:
        model[abs(unit_clause)] = unit_clause / abs(unit_clause)
        for clause in F:
            if (-1 * unit_clause) in clause:
                clause.remove(-1 * unit_clause)
                if (len(clause) == 1):
                    newUnitClauses = True

    if (newUnitClauses):
        propagate_units(F,model)
    return F


def printer(model):
    true = []
    for x, i in enumerate(model):
        if i > 0 and x>0:
            true.append(x)
    print(true)
    #print("list of false literals: " + str(false))


# x = flatten(propagate_units(F))

def stats(data):
    import seaborn as sns
    import numpy as np
    import pandas as pd
    import matplotlib.pyplot as plt

    sqr = np.array(data)
    d = {'time': sqr}
    pdnumsqr = pd.DataFrame(d)
    sns.set(style='darkgrid')
    sns.distplot(pdnumsqr)
    plt.figtext(0.1, 0.5, pdnumsqr.describe().to_string())
    plt.show()


def pure_elim(F,model):
    # Get all literals
    literals = []
    for clause in F:
        for literal in clause:
            if not literal in literals:
                literals.append(literal)
    # for each literals x
    # if x is pure in F and [x] not in F then add [x] to F
    for x in literals:
        isPure = True
        for clause in F:
            if -x in clause:
                isPure = False
                break
        if isPure and [x] not in F:
            model[abs(x)] = x / abs(x)
            F.append([x])




# Pick the first literal from a random nonUnit clause.
def pick_a_variable(model):
    unassigned = [var for var,x in enumerate(model) if var>0 and x ==0]
    if (len(unassigned) > 0):
        #return random.choice(unassigned)
        return unassigned[0]
    else:
        return 0;


def solve(VARS, F, model):
    propagate_units(F,model)
    pure_elim(F,model)
    sat_result = check_sat(F, model)
    if (sat_result and model[0] ==1):
        return model
    elif (not sat_result):
        #print("not sat",model)
        return []
    x = pick_a_variable(model)
    # If x==0, no more x can be choosen and there are no empty clauses in F
    # So we have some "Don't care" variables
    # Return F as is
    #if (x == 0):
    #    return []
    tmpF1 = copy.deepcopy(F)
    model1 = copy.deepcopy(model)
    model1[abs(x)] = 1
    tmpF2 = copy.deepcopy(F)
    model2 = copy.deepcopy(model)
    model2[abs(x)] = -1
    sol = solve(VARS, tmpF1+[[abs(x)]],model1)
    if not sol == []:
        return sol  # works to have +x
    else:
        return solve(VARS, tmpF2+[[abs(x)*-1]], model2)  # check -x


def check_sat(F, model):
#    print("Checking", model)
    counter =0
    for clauses in F:
        neg_counter =0
        for lit in clauses:
            sat_lit = (lit/abs(lit)) * model[abs(lit)]
        #    print("sat_lit =",sat_lit)
            if(sat_lit ==1):
                counter += 1
                break;
            elif(sat_lit == -1):
                neg_counter +=1
        #print("cheing ", clauses, "neg_counter", neg_counter)
        if(neg_counter == len(clauses)):
            return False;
    model[0] = 1 if counter == len(F) else 0
    return True;

def solve_dpll(instance, verbosity):
    # print(instance)
    # instance.VARS goes 1 to N in a dict
    # print(instance.VARS)
    # print(verbosity)
    ###########################################
    # Start your code

    clauses = instance.clauses
    variables = instance.VARS
    model = np.zeros(instance.p+1, dtype = int)

    result = solve(variables, clauses, model)
    if (result == []):
        print("UNSAT")
    else:
        print("SAT")
        if verbosity == True:
            printer(result)

    # End your code
    return True
    ###########################################


if __name__ == "__main__":
    main(sys.argv[1:])
