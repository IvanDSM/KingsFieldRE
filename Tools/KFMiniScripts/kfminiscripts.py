# @package KFMiniScripts
# Mini scripts relevant to King's Field (II) reverse engineering

import numpy
import random

## Replica of C-style rand() function
# Replicates the behavior of the C rand() function using Python's random library
def c_rand():
    return random.randint(0, 32767)

## Creates a random number based on a base value.
# Used by the game for randomizing entity gold drop value based on the entity class declaration's gold base value.
# @param number Base value for the randomization (e.g. 40)
def randomize(number : numpy.int32):
    return (c_rand() + c_rand() - 32768) * number >> 15

## Adds random jitter to a given number.
# Used by the game for randomizing entity direction?
# @param number Number to apply jitter to
def randomize2(number : numpy.int32):
    return (c_rand() + c_rand()) * number >> 15
