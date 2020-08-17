import sys
from pyspark.sql import SparkSession, functions, types
import string, re

wordbreak = r'[%s\s]+' % (re.escape(string.punctuation),)  # regex that matches spaces and/or punctuation

spark = SparkSession.builder.appName('word count').getOrCreate()
spark.sparkContext.setLogLevel('WARN')

assert sys.version_info >= (3, 5)
assert spark.version >= '2.3'

def get_words(df):
	split_df = df.select(functions.split(df['value'], wordbreak, -1).alias('s'))
	expl_df = split_df.select(functions.explode_outer('s').alias('word'))
	filtered_df = expl_df.where((expl_df['word'].isNotNull()) & (expl_df['word'] != ''))
	return filtered_df.select(functions.lower(filtered_df['word']).alias('word'))


def main(in_directory, out_directory):
	text = spark.read.text(in_directory)
	words_df = get_words(text)
	grouped = words_df.groupBy(words_df['word'])
	count = grouped.agg(functions.count('word').alias('count'))
	sorted_count = count.orderBy(['count', 'word'], ascending=[0, 1])

	sorted_count.write.csv(out_directory, mode='overwrite')



if __name__=='__main__':
	in_directory = sys.argv[1]
	out_directory = sys.argv[2]
	main(in_directory, out_directory)