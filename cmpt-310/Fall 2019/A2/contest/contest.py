#!/usr/bin/python3

# Script for CMPT310 SAT contest
# Heng Liu


import time
import subprocess
import os
import signal
import DPLLsat as dp
import sys
from io import StringIO
from functools import reduce
import contextlib

#Redirect output
@contextlib.contextmanager
def stdoutIO(stdout=None):
    old = sys.stdout
    if stdout is None:
        stdout = StringIO()
    sys.stdout = stdout
    yield stdout
    sys.stdout = old

@contextlib.contextmanager
def timeout(time):
    # Register a function to raise a TimeoutError on the signal.
    signal.signal(signal.SIGALRM, raise_timeout)
    # Schedule the signal to be sent after ``time``.
    signal.alarm(time)

    try:
        yield
    except TimeoutError:
        pass
    finally:
        # Unregister the signal so it won't be triggered
        # if the timeout is not reached.
        signal.signal(signal.SIGALRM, signal.SIG_IGN)


def raise_timeout(signum, frame):
    raise TimeoutError


def solve(cnf_file, n):
    f = StringIO()
    with contextlib.redirect_stdout(f):
        dp.main(['-i', cnf_file])
    output = f.getvalue()
    if(output == "SAT\n"):
        return("Pass n={}".format(n))
    else:
        return("Fail")


def seconds_to_str(t):
    return "%d:%02d:%02d.%03d" % \
           reduce(lambda ll, b: divmod(ll[0], b) + ll[1:],
                  [(t * 1000,), 1000, 60, 60])
#Get current working dir
dirpath = os.getcwd()
#Start timer
n = 50
start_time = time.time()
with timeout(300):
    while True:
        my_cmd = ["{}/sgen".format(dirpath), "-n", str(n), "-sat" , "-s", "310"]
        with open('{}/myfile.cnf'.format(dirpath), "w") as outfile:
            subprocess.call(my_cmd, stdout=outfile)
            result = solve('{}/myfile.cnf'.format(dirpath), n)
            if("Pass" in result):
                print(result, "time left", seconds_to_str(300+start_time - time.time()))
                n += 5
            else:
                print (result)
                print("Invalid entry due to incorrect result")
                break
print("Time out!")
print("Largest n = ", n-5)
