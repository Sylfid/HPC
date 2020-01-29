# coding: utf-8

import matplotlib.pyplot as plt

m = 100
y = [9.450000, 4.610000, 2.460000, 1.580000, 1.290000, 0.980000, 0.780000, 0.790000,
0.660000, 0.600000, 0.550000, 0.510000, 0.500000, 0.470000, 0.430000, 0.400000, 0.410000,
0.410000, 0.420000, 0.380000, 0.400000, 0.370000, 0.370000, 0.370000, 0.400000, 0.370000,
 0.380000, 0.400000, 0.350000, 0.380000, 0.380000, 0.380000, 0.380000, 0.390000, 0.410000,
  0.400000, 0.410000, 0.430000, 0.420000, 0.420000, 0.450000, 0.460000, 0.440000, 0.470000,
   0.460000, 0.450000, 0.460000, 0.480000, 0.460000, 0.490000, 0.470000, 0.460000, 0.490000,
   0.490000, 0.530000, 0.510000, 0.520000, 0.490000, 0.530000, 0.510000, 0.520000, 0.560000,
   0.550000, 0.560000, 0.560000, 0.540000, 0.540000, 0.550000, 0.560000, 0.570000, 0.630000,
   0.630000, 0.620000, 0.630000, 0.620000, 0.620000, 0.630000, 0.620000, 0.620000, 0.620000,
    0.620000, 0.640000, 0.760000, 0.730000, 0.700000, 0.690000, 0.720000, 0.690000, 0.700000,
    0.690000, 0.700000, 0.710000, 0.710000, 0.710000, 0.710000, 0.710000, 0.720000, 0.730000]


x = range(2, m)
tempsMin = min(y)
limite = [tempsMin for i in range(len(x))]

plt.title("test pour 500 points")
plt.plot(x, y)
plt.plot(x, limite, "r--")
plt.xlabel('nombre de threads')
plt.ylabel('temps')
# plt.xticks(x)
plt.grid(True)
plt.show()
