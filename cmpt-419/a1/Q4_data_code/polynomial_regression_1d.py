#!/usr/bin/env python

import assignment1 as a1
import numpy as np
import matplotlib.pyplot as plt

(countries, features, values) = a1.load_unicef_data()

targets = values[:,1]
x = {}
for i in range(7, 15):
	x[i] = values[:,i:i+1]
# x = values[:,7:8]
# norm_x = a1.normalize_data(x)

N_TRAIN = 100
x_train = {}
x_test = {}
t_train = targets[0:N_TRAIN]
t_test = targets[N_TRAIN:]
for i in range(7, 15):
	x_train[i] = x[i][0:N_TRAIN,:]
	x_test[i] = x[i][N_TRAIN:,:]

# Complete the linear_regression and evaluate_regression functions of the assignment1.py
# Pass the required parameters to these functions

train_err = {}
weights = {}
test_err = {}
reg_vals = {}

for i in range(7, 15):
	weights[i], train_err[i] = a1.linear_regression(x_train[i], t_train, 'polynomial', degree=3, bias=0)
	reg_vals[i], test_err[i] = a1.evaluate_regression(weights[i], x_test[i], t_test, basis='polynomial', degree=3, bias=0)

# Produce a plot of results.
plt.rcParams.update({'font.size': 15})
fig, ax = plt.subplots()
plt.title("RMS per single feature, no bias")
x = np.arange(8)
width = 0.4

rect1 = ax.bar(x-width/2, train_err.values(), width)
rect2 = ax.bar(x+width/2, test_err.values(), width)
ax.set_xticks(x)
ax.set_xticklabels(range(8,16))
ax.legend(['Training error','Testing error'])
plt.xlabel("Feature")
plt.ylabel("RMS")
plt.show()

# for i in range(10, 11):
# 	x_ev = np.linspace(np.asscalar(min(x_train[i])), np.asscalar(max(x_train[i])), num=500)
# 	# x_ev2 = np.linspace(np.asscalar(min(min(x_train[i][:,f]),min(x_test[:,f]))),
# 	#                   	np.asscalar(max(max(x_train[i][:,f]),max(x_test[:,f]))), num=500)
# w, tr_err = a1.linear_regression(x_train[i], t_train, 'polynomial', degree=3)

