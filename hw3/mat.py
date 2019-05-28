import numpy as np

# A is fixed
a = np.array([
    [250**2, 600, 1], [500**2, 1200, 1], [750**2, 1800, 1], [1000**2, 2400, 1]
])

# Running Time
b = np.array([
    [3545], [12780], [30825], [63320]
])

# Moore-Penrose Inverse
aplus = np.linalg.pinv(a)

# Calculate least-square minimum length solution
xplus = np.matmul(aplus, b)

print(xplus)

# Calculate R^2 value
bbar = np.mean(b)
sstot = np.linalg.norm(b - bbar) ** 2
ssres = np.linalg.norm(np.matmul(a, xplus) - b) ** 2
r2 = 1 - ssres/sstot
print(r2)
