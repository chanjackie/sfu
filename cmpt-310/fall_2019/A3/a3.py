#!/usr/bin/python3

import sys
import os
import random
import math

import numpy as np
import operator

#####################################################
#####################################################
# Please enter the number of hours you spent on this
# assignment here
num_hours_i_spent_on_this_assignment = 15
#####################################################
#####################################################

#####################################################
#####################################################
# Give one short piece of feedback about the course so far. What
# have you found most interesting? Is there a topic that you had trouble
# understanding? Are there any changes that could improve the value of the
# course to you? (We will anonymize these before reading them.)
# <Your feedback goes here>
# For this assignment, I feel like I did not learn anything by implementing posterior. This is mainly because
# i was focused on getting the log_sums to work, rather than understanding the algorithm.
#####################################################
#####################################################



# Outputs a random integer, according to a multinomial
# distribution specified by probs.
def rand_multinomial(probs):
    # Make sure probs sum to 1
    assert(abs(sum(probs) - 1.0) < 1e-5)
    rand = random.random()
    for index, prob in enumerate(probs):
        if rand < prob:
            return index
        else:
            rand -= prob
    return 0

# Outputs a random key, according to a (key,prob)
# iterator. For a probability dictionary
# d = {"A": 0.9, "C": 0.1}
# call using rand_multinomial_iter(d.items())
def rand_multinomial_iter(iterator):
    rand = random.random()
    for key, prob in iterator:
        if rand < prob:
            return key
        else:
            rand -= prob
    return 0


class HMM():

    def __init__(self):
        self.num_states = 2
        self.prior      = np.array([0.5, 0.5])
        self.transition = np.array([[0.999, 0.001], [0.01, 0.99]])
        self.emission   = np.array([{"A": 0.291, "T": 0.291, "C": 0.209, "G": 0.209},
                                    {"A": 0.169, "T": 0.169, "C": 0.331, "G": 0.331}])

    # Generates a sequence of states and characters from
    # the HMM model.
    # - length: Length of output sequence
    def sample(self, length):
        sequence = []
        states = []
        rand = random.random()
        cur_state = rand_multinomial(self.prior)
        for i in range(length):
            states.append(cur_state)
            char = rand_multinomial_iter(self.emission[cur_state].items())
            sequence.append(char)
            cur_state = rand_multinomial(self.transition[cur_state])
        return sequence, states

    # Generates a emission sequence given a sequence of states
    def generate_sequence(self, states):
        sequence = []
        for state in states:
            char = rand_multinomial_iter(self.emission[state].items())
            sequence.append(char)
        return sequence

    # Outputs the most likely sequence of states given an emission sequence
    # - sequence: String with characters [A,C,T,G]
    # return: list of state indices, e.g. [0,0,0,1,1,0,0,...]
    def viterbi(self, sequence):
        ###########################################
        # Start your code
        mProbValues = [{}]
        # Initiate initial values
        mStates = [0,1]
        mLogsum = self.prior[0]*self.emission[0][sequence[0]]
        mProbValues[0][0] = {"p": mLogsum, "pred":None}
        mLogsum = self.prior[1]*self.emission[1][sequence[0]]
        mProbValues[0][1] = {"p": mLogsum, "pred":None}

        mSeqLen = len(sequence)
        for arg in range(1, mSeqLen):
            mProbValues.append({})
            # state == index of state
            for state in mStates:
                mMaxTransP = 0;
                mPrevState = 0;
                if(state == 0):
                    #probabilty of 0 -> 0
                    mPStateTrans0 = mProbValues[arg-1][state]["p"] * self.transition[state][state]
                    #probability of 0 -> 1
                    mPStateTrans1 = mProbValues[arg-1][1]["p"] *self.transition[1][state]
                    mMaxTransP = max(mPStateTrans0,mPStateTrans1)
                    if(mPStateTrans1 == mMaxTransP):
                        mPrevState = 1
                elif(state == 1):
                     #probabilty of 1 -> 1
                    mPStateTrans1 = mProbValues[arg-1][state]["p"] *self.transition[state][state]
                    #probability of 1 -> 0
                    mPStateTrans0 = mProbValues[arg-1][0]["p"] * self.transition[0][state]
                    mMaxTransP = max(mPStateTrans0,mPStateTrans1)
                    if(mPStateTrans1 == mMaxTransP):
                        mPrevState = 1
                mNewProb = mMaxTransP *self.emission[state][sequence[arg]]
                mProbValues[arg][state] = {"p":mNewProb, "pred":mPrevState}

        mPMax = mProbValues[len(mProbValues)-1][0]["p"];
        mPMaxState = 0
        mPrev = 0
        indicies = []
        # Find state with max probabilty
        if(mProbValues[len(mProbValues)-1][1]["p"] > mPMax):
            mPMax = mProbValues[len(mProbValues)-1][1]["p"]
            mPMaxState = 1
            mPrev = 1

        indicies.insert(0,mPMaxState)

        # Backtrack from state with highest probabilty 
        for prev in range(len(mProbValues)-1, 0, -1):
            mBackTrack = mProbValues[prev][mPrev]["pred"]
            indicies.insert(0, mBackTrack)
            mPrev = mBackTrack

        counter = 0
        for i in indicies:
            if(i == 1):
                counter+=1

        return indicies

        # End your code
        ###########################################


    def log_sum(self, factors):
        if abs(min(factors)) > abs(max(factors)):
            a = min(factors)
        else:
            a = max(factors)

        total = 0
        for x in factors:
            total += math.exp(x - a)
        return a + math.log(total)

    # - sequence: String with characters [A,C,T,G]
    # return: posterior distribution. shape should be (len(sequence), 2)
    # Please use log_sum() in posterior computations.

    # self.transition = np.array([[0.999, 0.001], [0.01, 0.99]])
    # self.emission   = np.array([{"A": 0.291, "T": 0.291, "C": 0.209, "G": 0.209},
                                # {"A": 0.169, "T": 0.169, "C": 0.331, "G": 0.331}])
    def posterior(self, sequence):
        ###########################################
        # Start your code
        mFwdSums = np.zeros((len(sequence),2))
        states = [0,1]

        # Forwards Initial state
        mInitSum0 = self.prior[0]
        mInitSum1 = self.prior[1]
        mInitSeq = sequence[0]
        mFwdSums[0][0] = math.log(self.emission[0][mInitSeq]) + math.log(mInitSum0)
        mFwdSums[0][1] = math.log(self.emission[1][mInitSeq]) + math.log(mInitSum0)

        # Iterate starting from 2nd sequence argument
        i = 1;
        for arg in sequence[1:]:
            for state in states:
                factors = []
                for prev in states:
                    factors.append(math.log(self.transition[prev][state]) + mFwdSums[i-1][prev])
                mFwdSums[i][state] = (self.log_sum(factors) + math.log(self.emission[state][arg]))
            i+=1
       
        #Backwards initial state
        mBckSums = np.zeros((len(sequence),2))
        mLastSeq = sequence[len(sequence) - 1]
        mBckSums[len(sequence)-1][0] = 0
        mBckSums[len(sequence)-1][1] = 0


        i = len(sequence) - 2
        # Start from second last element to the first element
        for arg in reversed(sequence[1:]):
            for state in states:
                factors = []
                for prev in states:
                    w = math.log(self.transition[state][prev]) + math.log(self.emission[prev][arg]) + mBckSums[i+1][prev]
                    factors.append(w)
                mBckSums[i][state] = self.log_sum(factors)
            i-=1


        mPost = np.zeros((len(sequence),2))
        a = 1/self.log_sum(mFwdSums[:,-1])
        #Generate output 

        for x in range (len(sequence)):
            for state in states:
                mPost[x][state] = mFwdSums[x][state]*mBckSums[x][state]*a

        return mPost


        # End your code
        ###########################################


    # Output the most likely state for each symbol in an emmision sequence
    # - sequence: posterior probabilities received from posterior()
    # return: list of state indices, e.g. [0,0,0,1,1,0,0,...]
    def posterior_decode(self, sequence):
        nSamples  = len(sequence)
        post = self.posterior(sequence)
        best_path = np.zeros(nSamples)
        for t in range(nSamples):
            best_path[t], _ = max(enumerate(post[t]), key=operator.itemgetter(1))
        return list(best_path.astype(int))


def read_sequences(filename):
    inputs = []
    with open(filename, "r") as f:
        for line in f:
            inputs.append(line.strip())
    return inputs

def write_sequence(filename, sequence):
    with open(filename, "w") as f:
        f.write("".join(sequence))

def write_output(filename, viterbi, posterior):
    vit_file_name = filename[:-4]+'_viterbi_output.txt' 
    with open(vit_file_name, "a") as f:
        for state in range(2):
            f.write(str(viterbi.count(state)))
            f.write("\n")
        f.write(" ".join(map(str, viterbi)))
        f.write("\n")

    pos_file_name = filename[:-4]+'_posteri_output.txt' 
    with open(pos_file_name, "a") as f:
        for state in range(2):
            f.write(str(posterior.count(state)))
            f.write("\n")
        f.write(" ".join(map(str, posterior)))
        f.write("\n")


def truncate_files(filename):
    vit_file_name = file[:-4]+'_viterbi_output.txt'
    pos_file_name = file[:-4]+'_posteri_output.txt' 
    if os.path.isfile(vit_file_name):
        open(vit_file_name, 'w')
    if os.path.isfile(pos_file_name):
        open(pos_file_name, 'w')


if __name__ == '__main__':

    hmm = HMM()

    file = sys.argv[1]
    truncate_files(file)
    
    sequences  = read_sequences(file)
    for sequence in sequences:
        viterbi   = hmm.viterbi(sequence)
        posterior = hmm.posterior_decode(sequence)
        write_output(file, viterbi, posterior)


