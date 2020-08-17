import sys
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy import stats
from statsmodels.stats.multicomp import pairwise_tukeyhsd

def main():
	file = sys.argv[1]
	data = pd.read_csv(file)
	anova = stats.f_oneway(data['qs1'], data['qs2'], data['qs3'], data['qs4'], data['qs5'], data['merge1'], data['partition_sort'])
	print(anova)
	melt_data = pd.melt(data)
	# print(melt_data)
	posthoc = pairwise_tukeyhsd(melt_data['value'], melt_data['variable'], alpha=0.05)
	print(posthoc)
	fig = posthoc.plot_simultaneous()
	# plt.show()
	print('----Mean sorting time of each sorting algorithm----')
	print('partition_sort:', data['partition_sort'].mean())
	print('qs1:', data['qs1'].mean())
	print('qs2:', data['qs2'].mean())
	print('qs3:', data['qs3'].mean())
	print('qs4:', data['qs4'].mean())
	print('qs5:', data['qs5'].mean())
	print('merge1:', data['merge1'].mean())


if __name__ == '__main__':
    main()