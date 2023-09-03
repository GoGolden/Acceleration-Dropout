# distutils: language = c++
# cython: language_level = 3
from cpython cimport array as cparray
import numpy as np
from libc.stdlib cimport malloc

cdef extern from "mydropout.cpp":
    double* dropout(int n, double p, int bit, double *data)
    
cdef mid_dropout(int n, double p, int bit,double* input):
    # Memoryview on a NumPy array
    cdef double [:] input_num = input
    cdef double* data = <double*>malloc(sizeof(double) * n)
    data = &input_num[0]
    cdef double* output = dropout(n, p, bit, data)
    cdef double[:] output_num = <double[:n]> output
    return np.array(output_num)

def fast_dropout(int n, double p, int bit, input):
    return mid_dropout(n, p, bit, input)
