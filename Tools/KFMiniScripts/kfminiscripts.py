##@package KFMiniScripts
# Mini scripts relevant to King's Field (II) reverse engineering

import numpy
import random

## Creates a random number based on a base value.
# Used for randomizing entity gold drop value based on the class declaration's gold base value.
# @param number Base value for the randomization (e.g. 40)
def randomize(number : numpy.int32):
    return (random.randint(0,32767) + random.randint(0,32767) - 32768) * number >> 15