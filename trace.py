# coding: utf-8

import matplotlib.pyplot as plt

m = 150
y = [115.129997, 49.459999, 25.049999, 17.570000, 14.010000, 7.610000, 6.480000,
 5.290000, 4.250000, 3.980000, 3.260000, 2.940000, 2.730000, 2.560000, 2.360000,
  2.220000, 2.000000, 1.860000, 1.900000, 1.790000, 1.740000, 1.690000, 1.650000,
   1.670000, 1.520000, 1.660000, 1.550000, 1.540000, 1.500000, 1.530000, 1.500000,
    1.480000, 1.480000, 1.500000, 1.420000, 1.440000, 1.400000, 1.460000, 1.460000,
     1.410000, 1.420000, 1.430000, 1.360000, 1.350000, 1.410000, 1.390000,
     1.430000, 1.420000, 1.430000, 1.450000, 1.470000, 1.510000, 1.500000,
     1.510000, 1.540000, 1.510000, 1.540000, 1.610000, 1.580000, 1.580000,
      1.580000, 1.620000, 1.610000, 1.610000, 1.610000, 1.690000, 1.670000,
      1.650000, 1.660000, 1.670000, 1.760000, 1.750000, 1.710000, 1.730000,
       1.750000, 1.870000, 1.870000, 1.820000, 1.810000, 1.810000, 1.830000,
        1.830000, 1.980000, 1.930000, 1.920000, 1.900000, 1.910000, 1.930000,
        1.920000, 2.080000, 2.050000, 2.050000, 2.050000, 2.040000, 2.010000,
         2.010000, 2.040000, 2.060000, 2.040000, 2.220000, 2.230000, 2.200000,
          2.210000, 2.170000, 2.190000, 2.180000, 2.160000, 2.200000, 2.210000,
           2.240000, 2.420000, 2.430000, 2.400000, 2.400000, 2.390000, 2.410000,
            2.380000, 2.370000, 2.360000, 2.380000, 2.400000, 2.410000, 2.400000,
             2.440000, 2.660000, 2.620000, 2.630000, 2.590000, 2.570000, 2.610000,
              2.570000, 2.600000, 2.600000, 2.610000, 2.590000, 2.590000, 2.610000,
               2.610000, 2.630000, 2.630000, 2.630000, 3.200000, 3.170000,
               3.060000, 2.970000, 2.930000, 2.920000, 2.890000]




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
