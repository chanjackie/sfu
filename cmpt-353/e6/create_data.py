import numpy as np
import pandas as pd
import time
from implementations import all_implementations


def test_implementations(random_array):
	times = []
	for sort in all_implementations:
	    st = time.time()
	    res = sort(random_array)
	    en = time.time()
	    times.append(en-st)
	return times

def main():
	times = []
	for i in range(50):
		array = np.random.randint(low=0, high=100000, size=20000)
		times.append(test_implementations(array))
	data = pd.DataFrame.from_records(times)
	data.columns = ['qs1', 'qs2', 'qs3', 'qs4', 'qs5', 'merge1', 'partition_sort']
	data.to_csv('data.csv', index=False)

if __name__ == '__main__':
    main()