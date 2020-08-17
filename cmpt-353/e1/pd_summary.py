import pandas as pd 

totals = pd.read_csv('totals.csv').set_index(keys=['name'])
counts = pd.read_csv('counts.csv').set_index(keys=['name'])

lowest_total = pd.Series.argmin(pd.DataFrame.sum(totals, axis=1))

print("City with lowest total precipitation:")
print(totals.index.values[lowest_total])

average_precip = pd.DataFrame.sum(totals, axis=0)/pd.DataFrame.sum(counts, axis=0)

print("Average precipitation in each month:")
print(average_precip)

average_precip_per_city = pd.DataFrame.sum(totals, axis=1)/pd.DataFrame.sum(counts, axis=1)

print("Average precipitation in each city:")
print(average_precip_per_city)