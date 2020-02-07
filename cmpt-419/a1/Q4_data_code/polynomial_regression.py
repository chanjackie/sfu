#!/usr/bin/env python

import assignment1 as a1
import numpy as np
import matplotlib.pyplot as plt

(countries, features, values) = a1.load_unicef_data()

targets = values[:,1]
x = values[:,7:]
train_x = values[:99,7:]
train_targets = values[:99,1]
# x = a1.normalize_data(x)
min1990 = float("inf")
index1990 = 0
min2011 = float("inf")
index2011 = 0
valuesArray = np.array(values)
print(valuesArray[0])
for i in range(len(countries)):
	if valuesArray[i][0] < min1990:
		min1990 = valuesArray[i][0]
		index1990 = i
	if valuesArray[i][1] < min2011:
		min2011 = valuesArray[i][1]
		index2011 = i

print(min1990, min2011)
country1990 = countries[index1990]
country2011 = countries[index2011]
print(country1990, country2011)

# N_TRAIN = 100
# x_train = x[0:N_TRAIN,:]
# x_test = x[N_TRAIN:,:]
# t_train = targets[0:N_TRAIN]
# t_test = targets[N_TRAIN:]

# # Complete the linear_regression and evaluate_regression functions of the assignment1.py
# # Pass the required parameters to these functions

# # (w, tr_err) = a1.linear_regression()
# # (t_est, te_err) = a1.evaluate_regression()








# # Produce a plot of results.
# plt.rcParams.update({'font.size': 15})
# # plt.plot(train_err.keys(), train_err.valuesArray())
# # plt.plot(test_err.keys(), test_err.valuesArray())
# plt.ylabel('RMS')
# plt.legend(['Training error','Testing error'])
# plt.title('Fit with polynomials, no regularization')
# plt.xlabel('Polynomial degree')
# plt.show()
