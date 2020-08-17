import sys
from pyspark.sql import SparkSession, functions, types, Row
import re
import math

spark = SparkSession.builder.appName('correlate logs').getOrCreate()
spark.sparkContext.setLogLevel('WARN')

assert sys.version_info >= (3, 5) # make sure we have Python 3.5+
assert spark.version >= '2.3' # make sure we have Spark 2.3+

line_re = re.compile(r"^(\S+) - - \[\S+ [+-]\d+\] \"[A-Z]+ \S+ HTTP/\d\.\d\" \d+ (\d+)$")


def line_to_row(line):
    """
    Take a logfile line and return a Row object with hostname and bytes transferred. Return None if regex doesn't match.
    """
    m = line_re.match(line)
    if m:
        # TODO
        host, tail = line.split(' - - ')
        data, end = tail.split('HTTP/')
        http_type, code_byte = end.split('\" ')
        code, byte = code_byte.split(' ')
        return Row(host=host, bytes=int(byte))
    else:
        return None


def not_none(row):
    """
    Is this None? Hint: .filter() with it.
    """
    return row is not None


def create_row_rdd(in_directory):
    log_lines = spark.sparkContext.textFile(in_directory)
    # TODO: return an RDD of Row() objects
    row_rdd = log_lines.map(line_to_row)
    row_rdd = row_rdd.filter(not_none)

    return row_rdd



def main(in_directory):
    logs = spark.createDataFrame(create_row_rdd(in_directory))

    # TODO: calculate r.
    # logs.show()
    grouped = logs.groupBy(logs['host'])
    counts = grouped.agg(
        functions.count(logs['bytes']).alias('count_requests'),
        functions.sum(logs['bytes']).alias('sum_request_bytes'))

    counts = counts.cache()
    counts = counts.withColumn('x^2', counts['count_requests']**2)
    counts = counts.withColumn('y^2', counts['sum_request_bytes']**2)
    counts = counts.withColumn('xy', counts['count_requests']*counts['sum_request_bytes'])

    n = counts.count()
    # counts.show()

    grouped = counts.groupBy().sum()

    vals = grouped.first()
    r = (n*vals[4] - vals[0]*vals[1])/(math.sqrt(n*vals[2]-(vals[0])**2)*math.sqrt(n*vals[3]-(vals[1])**2))

    print("r = %g\nr^2 = %g" % (r, r**2))


if __name__=='__main__':
    in_directory = sys.argv[1]
    main(in_directory)
