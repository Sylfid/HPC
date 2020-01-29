# coding: utf-8

import matplotlib.pyplot as plt


m = 10
y = [0.000000, 0.010000, 0.010000, 0.000000, 0.010000, 0.000000, 0.000000, 0.010000]

x = range(2, m)
tempsMin = min(y)
limite = [tempsMin for i in range(len(x))]

plt.title("test pour 50 points")
plt.plot(x, y)
plt.plot(x, limite, "r--")
plt.xlabel('nombre de threads')
plt.ylabel('temps')
# plt.xticks(x)
plt.grid(True)
plt.show()
