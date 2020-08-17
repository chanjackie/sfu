import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import pandas._testing as tm
import math

# tm.N = 3


# def unpivot(frame):
#     N, K = frame.shape
#     data = {'value': frame.to_numpy().ravel('F'),
#             'variable': np.asarray(frame.columns).repeat(N),
#             'date': np.tile(np.asarray(frame.index), K)}
#     return pd.DataFrame(data, columns=['date', 'variable', 'value'])


# df = unpivot(tm.makeTimeDataFrame())

# # d1 = np.ones((5))
# # d2 = np.arange(5)
# # data = np.concatenate([np.ones((5)), np.arange(5)])

# # print(data)

# def reshape(df):
# 	df = df.pivot(index='date', columns='variable', values='value')
# 	print(df)
# 	return df

# new = reshape(df)
# print(new)

# def filter(df):
#   df = df[df['A'] > -1]
#   return df

# # new = filter(new)
# print(new)
# new['B'] = abs(new['B'])
# print(new)

# def draw(df):
# 	df['B'] = df['B']**(1/2)
# 	print(df)
# 	plt.scatter(df['A'], df['B'])
# 	plt.show()

# draw(new)

