#!/usr/bin/env python

import assignment1 as a1
import numpy as np
import matplotlib.pyplot as plt

(countries, features, values) = a1.load_unicef_data()

targets = values[:,1]
x = values[:,7:]
norm_x = a1.normalize_data(x)

# min1990 = float("inf")
# index1990 = 0
# min2011 = float("inf")
# index2011 = 0
# valuesArray = np.array(values)
# print(valuesArray[0])
# for i in range(len(countries)):
# 	if valuesArray[i][0] < min1990:
# 		min1990 = valuesArray[i][0]
# 		index1990 = i
# 	if valuesArray[i][1] < min2011:
# 		min2011 = valuesArray[i][1]
# 		index2011 = i

# print(min1990, min2011)
# country1990 = countries[index1990]
# country2011 = countries[index2011]
# print(country1990, country2011)

N_TRAIN = 100
x_train = x[0:N_TRAIN,:]
x_test = x[N_TRAIN:,:]
norm_x_train = norm_x[0:N_TRAIN,:]
norm_x_test = norm_x[N_TRAIN:,:]
t_train = targets[0:N_TRAIN]
t_test = targets[N_TRAIN:]

# Complete the linear_regression and evaluate_regression functions of the assignment1.py
# Pass the required parameters to these functions

train_err = {}
norm_train_err = {}
weights = {}
norm_weights = {}
test_err = {}
norm_test_err = {}
reg_vals = {}
norm_reg_vals = {}

for i in range(1,7):
	weights[i], train_err[i] = a1.linear_regression(x_train, t_train, 'polynomial', degree=i, bias=1)
	reg_vals[i], test_err[i] = a1.evaluate_regression(weights[i], x_test, t_test, basis='polynomial', degree=i, bias=1)
	norm_weights[i], norm_train_err[i] = a1.linear_regression(norm_x_train, t_train, 'polynomial', degree=i, bias=1)
	norm_reg_vals[i], norm_test_err[i] = a1.evaluate_regression(norm_weights[i], norm_x_test, t_test, basis='polynomial', degree=i, bias=1)

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
