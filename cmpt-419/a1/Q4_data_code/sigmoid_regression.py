#!/usr/bin/env python

import assignment1 as a1
import numpy as np
import matplotlib.pyplot as plt

(countries, features, values) = a1.load_unicef_data()

targets = values[:,1]
x = values[:,10:11]
# x = values[:,7:8]
# norm_x = a1.normalize_data(x)

N_TRAIN = 100
t_train = targets[0:N_TRAIN]
t_test = targets[N_TRAIN:]

x_train = x[0:N_TRAIN,:]
x_test = x[N_TRAIN:,:]

# Complete the linear_regression and evaluate_regression functions of the assignment1.py
# Pass the required parameters to these functions

train_err = {}
weights = {}
test_err = {}
reg_vals = {}

mu = 100
std = 2000
for i in range(1,3):
	weights[i-1], train_err[i-1] = a1.linear_regression(x_train, t_train, 'sigmoid', degree=3, mu=mu**i, s=std)
	reg_vals[i-1], test_err[i-1] = a1.evaluate_regression(weights[i-1], x_test, t_test, basis='sigmoid', degree=3, mu=mu**i, s=std)
	weights[i+1], train_err[i+1] = a1.linear_regression(x_train, t_train, 'sigmoid', degree=3, mu=mu**i, s=std, bias=1)
	reg_vals[i+1], test_err[i+1] = a1.evaluate_regression(weights[i-1], x_test, t_test, basis='sigmoid', degree=3, mu=mu**i, s=std, bias=1)

# Produce a plot of results.
print("Mu = 100, No Bias")
print("train_err =", train_err[0], "test_err =", test_err[0])
print("Mu = 10000, No Bias")
print("train_err =", train_err[1], "test_err =", test_err[1])
print("Mu = 100, With Bias")
print("train_err =", train_err[2], "test_err =", test_err[2])
print("Mu = 10000, With Bias")
print("train_err =", train_err[3], "test_err =", test_err[3])