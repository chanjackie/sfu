import sys
from pyspark.sql import SparkSession, functions, types

spark = SparkSession.builder.appName('reddit averages').getOrCreate()
spark.sparkContext.setLogLevel('WARN')

assert sys.version_info >= (3, 5) # make sure we have Python 3.5+
assert spark.version >= '2.3' # make sure we have Spark 2.3+


page_views_schema = types.StructType([
    types.StructField('language', types.StringType()),
    types.StructField('title', types.StringType()),
    types.StructField('views', types.IntegerType()),
    types.StructField('bytes', types.LongType()),
])

def path_to_date(path):
    f_len = len(path)
    date = path[f_len-18:f_len-7]
    return date


def main(in_directory, out_directory):
    page_views = spark.read.csv(in_directory, schema=page_views_schema, sep=" ").withColumn('filename', functions.input_file_name())

    path_to_hour = functions.udf(path_to_date, returnType=types.StringType())

    page_views_with_hr = page_views.withColumn('hour', path_to_hour(page_views['filename']))
    # page_views_with_hr.show()

    filtered_data = page_views_with_hr.filter((page_views_with_hr['language'] == 'en') & 
        (page_views_with_hr['title'] != 'Main_Page') & 
        ~(page_views_with_hr['title'].startswith('Special:')))
    filtered_data = filtered_data.cache()

    grouped = filtered_data.groupBy(filtered_data['hour'].alias('hour_group'))
    view_grouped = grouped.agg(functions.max('views'))
    # view_grouped.show()

    joined_data = view_grouped.join(filtered_data, on=(view_grouped['max(views)'] == filtered_data['views']) & (view_grouped['hour_group'] == filtered_data['hour']))
    # joined_data.show()

    final_data = joined_data.select(
        joined_data['hour'],
        joined_data['title'],
        joined_data['views']).orderBy('hour', ascending=True)

    # final_data.show()
    final_data.write.csv(out_directory, mode='overwrite')
    

if __name__=='__main__':
    in_directory = sys.argv[1]
    out_directory = sys.argv[2]
    main(in_directory, out_directory)
