import sys
import numpy as np 
import pandas as pd 
import matplotlib.pyplot as plt 
import difflib

file1 = sys.argv[1]
file2 = sys.argv[2]

output_name = sys.argv[3]

movie_list = open(file1).readlines()
movie_list = list(map(str.strip, movie_list))
movie_ratings = pd.read_csv(file2)

# print(movie_list)
# print(movie_ratings)

def get_close_matches(title, title_list):
	match = difflib.get_close_matches(title, title_list, n=1)
	if (len(match) == 0):
		match = ''
	else:
		match = match[0]
	return match

movie_ratings['matched_title'] = movie_ratings['title'].apply(get_close_matches, title_list=movie_list)

movie_ratings = movie_ratings[movie_ratings['matched_title'].str.len()>0]

average_ratings = movie_ratings.groupby('matched_title').mean()

average_ratings['rating'] = average_ratings['rating'].round(2)

average_ratings.index.names = ['title']

print(average_ratings)

average_ratings.to_csv(output_name)