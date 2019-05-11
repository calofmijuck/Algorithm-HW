import os
from random import shuffle

os.system("g++ check.cpp -o check")

for i in range(1, 5, 1):
    os.system("echo Test " + str(i))
    os.system("./check < tests/in" + str(i))
