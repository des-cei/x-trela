import sys
import random

size = int(sys.argv[1])
data_size = size / 2
G = data_size / 2

X = [int(random.random()*255.00 - 128) for x in range(data_size)]
Y = [int(random.random()*255.00 - 128) for x in range(data_size)]
Z = [int(0.0) for x in range(data_size)]
T = [int(0.0) for x in range(data_size)]

Wr = 7
Wi = -3

for i in range(0, G):
    t_r = Wr*X[i+G] - Wi*Y[i+G]
    t_i = Wi*X[i+G] + Wr*Y[i+G]
    Z[i+G] = X[i] - t_r
    Z[i] = X[i] + t_r
    T[i+G] = Y[i] - t_i
    T[i] = Y[i] + t_i

def print_array_interleaved(array_type, array_name, array_sz, pyarr):
    print "volatile {} {}[{}] __attribute__((section(\".xheep_data_interleaved\"))) = ".format(array_type, array_name, array_sz)
    print "{"
    print ", ".join(map(str, pyarr))
    print "};"

def print_array(array_type, array_name, array_sz, pyarr):
    print "volatile {} {}[{}] = ".format(array_type, array_name, array_sz)
    print "{"
    print ", ".join(map(str, pyarr))
    print "};"

def print_scalar(scalar_type, scalar_name, pyscalar):
    print "{} {} = {};".format(scalar_type, scalar_name, pyscalar)


print "#include <stdint.h>"
print "#define DATA_SIZE {}".format(data_size)

print_array_interleaved("int32_t", "real", "DATA_SIZE", X)
print_array_interleaved("int32_t", "imag", "DATA_SIZE", Y)
print_array("int32_t", "expected_real", "DATA_SIZE", Z)
print_array("int32_t", "expected_imag", "DATA_SIZE", T)