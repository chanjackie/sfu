import sys
from pyspark.sql import SparkSession, functions, types, Column, Row

spark = SparkSession.builder.appName('weather ETL').getOrCreate()
spark.sparkContext.setLogLevel('WARN')

assert sys.version_info >= (3, 5) # make sure we have Python 3.5+
assert spark.version >= '2.4' # make sure we have Spark 2.4+

observation_schema = types.StructType([
    types.StructField('station', types.StringType()),
    types.StructField('date', types.StringType()),
    types.StructField('observation', types.StringType()),
    types.StructField('value', types.IntegerType()),
    types.StructField('mflag', types.StringType()),
    types.StructField('qflag', types.StringType()),
    types.StructField('sflag', types.StringType()),
    types.StructField('obstime', types.StringType()),
])


def main(in_directory, out_directory):

    weather = spark.read.csv(in_directory, schema=observation_schema)

    # TODO: finish here.
    selected_cols = weather.select(
        weather.qflag,
        weather.station,
        weather.observation,
        weather.date,
        weather.value
        )

    filtered_data = selected_cols.filter(selected_cols.qflag.isNull() & selected_cols.station.startswith('CA') & (selected_cols.observation == 'TMAX'))

    tmax_data = filtered_data.withColumn("tmax", filtered_data.value/10)

    cleaned_data = tmax_data.select(
        tmax_data.station,
        tmax_data.date,
        tmax_data.tmax)

    # cleaned_data.show()

    cleaned_data.write.json(out_directory, compression='gzip', mode='overwrite')


if __name__=='__main__':
    in_directory = sys.argv[1]
    out_directory = sys.argv[2]
    main(in_directory, out_directory)
