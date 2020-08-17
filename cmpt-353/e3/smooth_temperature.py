import sys
import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt
from statsmodels.nonparametric.smoothers_lowess import lowess
from pykalman import KalmanFilter

filename = sys.argv[1]

cpu_data = pd.read_csv(filename, parse_dates=[0])

fig = plt.figure(figsize=(12,4))
plt.plot(cpu_data['timestamp'], cpu_data['temperature'], 'b.', alpha=0.5)

# plt.plot(cpu_data['timestamp'], cpu_data['cpu_percent'], 'b.', alpha=0.5)
# plt.show()
# plt.clf()

# plt.plot(cpu_data['timestamp'], cpu_data['sys_load_1'], 'b.', alpha=0.5)
# plt.show()
# plt.clf()

# plt.plot(cpu_data['timestamp'], cpu_data['fan_rpm'], 'b.', alpha=0.5)
# plt.show()
# plt.clf()

loess_smoothed = lowess(cpu_data['temperature'], cpu_data['timestamp'], frac=0.015)
plt.plot(cpu_data['timestamp'], loess_smoothed[:, 1], 'r-')

kalman_data = cpu_data[['temperature', 'cpu_percent', 'sys_load_1', 'fan_rpm']]

initial_state = kalman_data.iloc[0]
observation_covariance = np.diag([2, 5, 0.5, 50]) ** 2 # TODO: shouldn't be zero
transition_covariance = np.diag([0.2, 0.6, 0.05, 5]) ** 2 # TODO: shouldn't be zero
transition = [[0.97,0.5,0.2,-0.001], [0.1,0.4,2.2,0], [0,0,0.95,0], [0,0,0,1]] # TODO: shouldn't (all) be zero

kf = KalmanFilter(
	initial_state_mean=initial_state,
	initial_state_covariance=observation_covariance,
	observation_covariance=observation_covariance,
	transition_covariance=transition_covariance,
	transition_matrices=transition
	)
kalman_smoothed, _ = kf.smooth(kalman_data)
plt.plot(cpu_data['timestamp'], kalman_smoothed[:, 0], 'g-')
plt.legend(['CPU Data', 'LOESS Data', 'Kalman Data'])
plt.xlabel('Date')
plt.ylabel('Temperature')
fig.tight_layout()
# plt.show()
plt.savefig('cpu.svg')