# main.py
# L I T B I T A E S T H E T I C

import numpy as np
import matplotlib.pyplot as plt
import math
from itertools import groupby
import csv
with open('steplog.csv', 'rb') as csvfile:
    reader = csv.reader(csvfile)
    next(reader)    # skip Putty log info
    next(reader)
    accel = [r for r in reader]
    accel = accel[:-1]      # remove last element in case it is ruined when serial connection
                            # is lost

# force numpy to print out entire arrays in terminal
np.set_printoptions(threshold=np.nan)

def mag(x):
    return math.sqrt(sum(float(i)*float(i) for i in x))

magnitude = []
step_count = 0

for i in range(len(accel)):
    magnitude.append(mag(accel[i]) - 1)

# apply a ten sample moving filter
smoothed_magnitude = np.convolve(magnitude, np.ones((10))/10, mode='valid')

# plt.plot(magnitude)
# plt.ylabel("Magnitude (Gs)")
# plt.xlabel("Sample Number")
plt.plot(smoothed_magnitude)
plt.ylabel("Magnitude (Gs) smoothed")
plt.xlabel("Sample Number")
plt.show()

# Hysteresis threshold detection
hyst_thres_pos = 0.05       # positive and negative threshold in Gs
hyst_thres_neg = -0.05

a = np.zeros_like(smoothed_magnitude)           # array of zeros, same length as smoothed_magnitude
a[ smoothed_magnitude < hyst_thres_neg] = -1    # set values less than negative threshold = -1
a[ smoothed_magnitude > hyst_thres_pos] = +1    # set values greater than positive threshold = 1
indices = np.nonzero(a)                         # find indices where a is nonzero
b = a[indices]                                  # extract the non-zero indices

threshold_crossings = [i for i,j in groupby(b) if i!=0]         # remove consecutive duplicate values
print "Number of steps is: " + str(len(threshold_crossings)/2)  # Steps represented by a crossing from one threshold to another and then back again


