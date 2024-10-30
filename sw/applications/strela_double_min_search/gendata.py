import sys
import random

data_size = int(sys.argv[1])

X = [int(random.random()*100000.00 - 50000.0) for x in range(data_size)]
Y = [int(0.0) for x in range(4)]
Z = [int(0.0) for x in range(4)]

Z[0] = 127

for i in range(0, data_size):
    if X[i] < Z[0]:
        Z[2] = Z[0]
        Z[3] = Z[1]
        Z[0] = X[i]
        Z[1] = i
    elif X[i] < Z[2]:
        Z[2] = X[i]
        Z[3] = i


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

print_array_interleaved("int32_t", "input", "DATA_SIZE", X)
print_array_interleaved("int32_t", "output", "4", Y)
print_array("int32_t", "expected_result", "4", Z)