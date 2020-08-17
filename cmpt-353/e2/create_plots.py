import sys
import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt

filename1 = sys.argv[1]
filename2 = sys.argv[2]

dataset1 = pd.read_csv(filename1, sep=' ', header=None, index_col=1,
	names=['lang', 'page', 'views', 'bytes'])

dataset2 = pd.read_csv(filename2, sep=' ', header=None, index_col=1,
	names=['lang', 'page', 'views', 'bytes'])

sorted_d1 = dataset1.sort_values('views', ascending=False)

joined_data = pd.concat([dataset1['views'], dataset2['views']], axis=1)
columns = joined_data.columns.values
columns[0] = 'views1'
columns[1] = 'views2'
joined_data.columns = columns
print(joined_data)
# print(joined_data)

plt.figure(figsize=(10, 5))
plt.subplot(1, 2, 1)
plt.title('Distribution of page views')
plt.ylabel('# of views')
plt.xlabel('Page ranking')
plt.plot(sorted_d1['views'].values)
plt.subplot(1, 2, 2)
plt.title('Daily views')
plt.ylabel('Day 2 views')
plt.xlabel('Day 1 views')
plt.scatter(joined_data['views1'].values, joined_data['views2'].values)
plt.xscale('log')
plt.yscale('log')
plt.savefig('wikipedia.png')
plt.show()