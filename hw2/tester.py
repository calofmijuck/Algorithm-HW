from random import randint

# Select random element from list
def rndselect(list):
    idx = randint(0, len(list) - 1)
    return list[idx]

# Number of lines
N = 75

# Operation set
op_set = ['I']
# op_set = ['I', 'D']
# op_set = ['I', 'D', 'R', 'S']

# Numbers
num = [str(i) for i in range(1, 50)]

# Create input text file
f = open('tests/input', "w")

# Write to test file
f.write(str(N) + "\n")
for i in range(N):
    f.write(rndselect(op_set))
    f.write(' ')
    f.write(rndselect(num))
    f.write('\n')

M = 50
op_set2 = ['R', 'S']

f.write(str(M) + "\n")
for i in range(M):
    f.write(rndselect(op_set2))
    f.write(' ')
    f.write(rndselect(num))
    f.write('\n')

f.close()
