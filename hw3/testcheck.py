f = open("output_adj.txt", "r")
g = open("output_mat.txt", "r")

# for line in f.readlines():
#     n = input()
#     if line[:-1] != str(n):
#         print("Incorrect")
#         exit(0)
#         break
#
# print("Adjacency List: OK")

for line in g.readlines():
    n = input()
    if line[:-1] != str(n):
        print("Incorrect")
        exit(0)
        break

print("Adjacency Matrix: OK")
