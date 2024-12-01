import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('pgc.dat', skiprows=1)
processes = data[:, 0]
speedup = data[:, 1]

plt.figure(figsize=(10, 6))
plt.plot(processes, speedup, '-o', label="n=10000", color='red')
plt.plot(processes, processes, '-o', label="Линейное ускорение", color='blue')
plt.xlabel("Количество процессов")
plt.ylabel("Ускорение")
plt.legend()
plt.grid()
plt.savefig("speedup_10000.png", dpi=300)
plt.show()
