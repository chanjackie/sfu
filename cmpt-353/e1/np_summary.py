import numpy as np 

data = np.load('monthdata.npz')
totals = data['totals']
counts = data['counts']

# print(totals)
# print(counts)

lowest_total = np.argmin(np.sum(totals, axis=1))

print("Row number of city with lowest total precipitation:")
print(lowest_total)

average_precip = np.sum(totals, axis=0)/np.sum(counts, axis=0)

print("Average precipitation in each month:")
print(average_precip)

average_precip_per_city = np.sum(totals, axis=1)/np.sum(counts, axis=1)

print("Average precipitation in each city:")
print(average_precip_per_city)

reshaped = np.sum(np.reshape(totals, (np.size(totals, 0)*4, 3)), axis=1)
quarterly_precip_totals = np.reshape(reshaped, (np.size(totals, 0), 4))

print("Quarterly precipitation totals:")
print(quarterly_precip_totals)