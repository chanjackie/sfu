#!/usr/bin/env python

import assignment1 as a1
import numpy as np
import matplotlib.pyplot as plt

(countries, features, values) = a1.load_unicef_data()

targets = values[:,1]
x = {}
for i in range(10, 13):
	x[i] = values[:,i:i+1]
# x = values[:,7:8]
# norm_x = a1.normalize_data(x)

N_TRAIN = 100
x_train = {}
x_test = {}
t_train = targets[0:N_TRAIN]
t_test = targets[N_TRAIN:]
for i in range(10, 13):
	x_train[i] = x[i][0:N_TRAIN,:]
	x_test[i] = x[i][N_TRAIN:,:]

# Complete the linear_regression and evaluate_regression functions of the assignment1.py
# Pass the required parameters to these functions

train_err = {}
weights = {}
test_err = {}
reg_vals = {}

# for i in range(10, 13):
# 	weights[i], train_err[i] = a1.linear_regression(x_train[i], t_train, 'polynomial', degree=3)
# 	reg_vals[i], test_err[i] = a1.evaluate_regression(weights[i], x_test[i], t_test, basis='polynomial', degree=3)

# Plot a curve showing learned function.
# Use linspace to get a set of samples on which to evaluate
# x1_ev = np.linspace(np.asscalar(min(x_train[10])), np.asscalar(max(x_train[10])), num=500)
# x1_ev = np.linspace(np.asscalar(min(min(x_train[10][:,f]),min(x_test[10][:,f]))),
#                   np.asscalar(max(max(x_train[10][:,f]),max(x_test[10][:,f]))), num=500)
# x1_ev = np.linspace(0, 10, num=500)
# x2_ev = np.linspace(0, 10, num=50)
for i in range(10, 13):
	weights[i], train_err[i] = a1.linear_regression(x_train[i], t_train, 'polynomial', degree=3)
	reg_vals[i], test_err[i] = a1.evaluate_regression(weights[i], x_test[i], t_test, basis='polynomial', degree=3)

x = np.arange(len(reg_vals[10]))

# TO DO::
# Perform regression on the linspace samples.
# Put your regression estimate here in place of y_ev.
# y1_ev = np.random.random_sample(x1_ev.shape)
# y2_ev = np.random.random_sample(x2_ev.shape)
# y1_ev = 100*np.sin(x1_ev)
# y2_ev = 100*np.sin(x2_ev)
# print(reg_vals[10])
plt.plot(reg_vals[10], list(x),'bo')
# plt.plot(x2_ev,y2_ev,'bo')
plt.title('Visualization of a function and some data points')
plt.show()