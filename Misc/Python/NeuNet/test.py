import numpy as np

X = np.random.randn(20,2)
Y = []
for x in X:
    Y.append(x[0] * x[1])
Y = np.array(Y)

print X
print Y

Yh = np.random.randn(20)

print -np.sum(np.abs(Y-Yh))
