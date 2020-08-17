#!/usr/bin/env python

import assignment1 as a1
import numpy as np
import matplotlib.pyplot as plt

(countries, features, values) = a1.load_unicef_data()

targets = values[:,1]
x = values[:,7:]
x = a1.normalize_data(x)

N_TRAIN = 100
x_train = x[0:N_TRAIN,:]
x_test = x[N_TRAIN:,:]
t_train = targets[0:N_TRAIN]
t_test = targets[N_TRAIN:]

# Complete the linear_regression and evaluate_regression functions of the assignment1.py
# Pass the required parameters to these functions

train_err = {}
weights = {}
test_err = {}
reg_vals = {}

lambdas = [0, 0.01, 0.1, 1, 10, 100, 1000, 10000]

for i in range(8):
	weights[i], train_err[i] = a1.linear_regression(x_train, t_train, 'polynomial', degree=2, bias=1, reg_lambda=lambdas[i])
	reg_vals[i], test_err[i] = a1.evaluate_regression(weights[i], x_test, t_test, basis='polynomial', degree=2, bias=1)

# Produce a plot of results.
plt.rcParams.update({'font.size': 15})
plt.plot(list(range(1,7)), list(train_err.values()))
plt.plot(list(range(1,7)), list(test_err.values()))
plt.ylabel('RMS')
plt.legend(['Training error','Testing error'])
plt.title('Fit with polynomials, no regularization, not normalized')
plt.xlabel('Polynomial degree')
plt.show()

plt.rcParams.update({'font.size': 15})
plt.plot(list(range(1,7)), list(norm_train_err.values()))
plt.plot(list(range(1,7)), list(norm_test_err.values()))
plt.ylabel('RMS')
plt.legend(['Training error','Testing error'])
plt.title('Fit with polynomials, no regularization, normalized')
plt.xlabel('Polynomial degree')
plt.show()
