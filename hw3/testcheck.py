f = open("output.txt", "r")

for line in f.readlines():
    n = input()
    if line[:-1] != str(n):
        print("Incorrect")
        exit(0)
        break

print("OK")
