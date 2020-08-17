import sys
from pyspark.sql import SparkSession, functions, types

spark = SparkSession.builder.appName('reddit relative scores').getOrCreate()
spark.sparkContext.setLogLevel('WARN')

assert sys.version_info >= (3, 5) # make sure we have Python 3.5+
assert spark.version >= '2.3' # make sure we have Spark 2.3+

comments_schema = types.StructType([
    types.StructField('archived', types.BooleanType()),
    types.StructField('author', types.StringType()),
    types.StructField('author_flair_css_class', types.StringType()),
    types.StructField('author_flair_text', types.StringType()),
    types.StructField('body', types.StringType()),
    types.StructField('controversiality', types.LongType()),
    types.StructField('created_utc', types.StringType()),
    types.StructField('distinguished', types.StringType()),
    types.StructField('downs', types.LongType()),
    types.StructField('edited', types.StringType()),
    types.StructField('gilded', types.LongType()),
    types.StructField('id', types.StringType()),
    types.StructField('link_id', types.StringType()),
    types.StructField('name', types.StringType()),
    types.StructField('parent_id', types.StringType()),
    types.StructField('retrieved_on', types.LongType()),
    types.StructField('score', types.LongType()),
    types.StructField('score_hidden', types.BooleanType()),
    types.StructField('subreddit', types.StringType()),
    types.StructField('subreddit_id', types.StringType()),
    types.StructField('ups', types.LongType()),
    #types.StructField('year', types.IntegerType()),
    #types.StructField('month', types.IntegerType()),
])


def main(in_directory, out_directory):
    comments = spark.read.json(in_directory, schema=comments_schema)
    comments = comments.cache()
    # TODO
    grouped = comments.groupBy(comments['subreddit'].alias('sub_grouped'))
    averages = grouped.agg(functions.avg(comments['score']))
    averages = averages.filter(averages['avg(score)'] > 0)
    averages = functions.broadcast(averages)
    # averages.show()

    joined_data = comments.join(averages, on=(averages['sub_grouped'] == comments['subreddit']))
    joined_data = joined_data.select(
        joined_data['subreddit'],
        joined_data['author'],
        joined_data['score'],
        joined_data['avg(score)'])

    rel_score_data = joined_data.withColumn('rel_score', joined_data['score']/joined_data['avg(score)'])
    rel_score_data.cache()
    # rel_score_data.show()

    grouped = rel_score_data.groupBy(rel_score_data['subreddit'].alias('max_sub'))
    max_rel_score = grouped.agg(functions.max(rel_score_data['rel_score']))
    max_rel_score = functions.broadcast(max_rel_score)

    best_author = rel_score_data.join(max_rel_score, on=(rel_score_data['rel_score'] == max_rel_score['max(rel_score)']))
    best_author = best_author.select(
        best_author['subreddit'],
        best_author['author'],
        best_author['rel_score'])
    # best_author.show()
    best_author.write.json(out_directory, mode='overwrite')


if __name__=='__main__':
    in_directory = sys.argv[1]
    out_directory = sys.argv[2]
    main(in_directory, out_directory)
