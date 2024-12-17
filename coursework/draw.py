import numpy as np
import matplotlib.pyplot as plt

data1 = np.loadtxt('jac15000.dat', skiprows=1)
processes1 = data1[:, 0].astype(int)  # Количество процессов
speedup1 = data1[:, 1]  # Ускорение

data2 = np.loadtxt('jac28000.dat', skiprows=1)
processes2 = data2[:, 0].astype(int)  # Количество процессов
speedup2 = data2[:, 1]  # Ускорение

# Построение графика
plt.figure(figsize=(10, 6))

# Первый график
plt.plot(processes1, speedup1, '-o', label="n = 15000", color='red')

# Второй график
plt.plot(processes2, speedup2, '-o', label="n = 28000", color='green')  # Пример с другим цветом и маркером

# Линейное ускорение
plt.plot(processes1, processes1, '-o', label="Линейное ускорение", color='blue')

# Оформление
plt.xlabel("Количество процессов")
plt.ylabel("Ускорение")
plt.xticks(processes1)  # Устанавливаем тики по количеству процессов первого графика
plt.legend()
plt.grid()
plt.savefig("speedup.png", dpi=300)
plt.show()