import sys
import random

size = int(sys.argv[1])
data_size = size * size

def relu(x):
    return max(0.0, x)

X = [int(random.random()*100.00 - 50.0) for x in range(data_size)]
Y = [int(0.0) for x in range(data_size)]
Z = [int(relu(X[x])) for x in range(data_size)]

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
print_array_interleaved("int32_t", "output", "DATA_SIZE", Y)
print_array("int32_t", "expected_result", "DATA_SIZE", Z)