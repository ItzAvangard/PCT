#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define M_PI 3.14159265358979323846

double func(double x, double y) {
    return x / (y * y);
}

double getrand(double min, double max, unsigned int *seed) {
    return min + (max - min) * ((double)rand_r(seed) / RAND_MAX); // Генерация числа в диапазоне [0, 1] и [2, 5]
}

int main(int argc, char **argv) {
    const int n_values[2] = {10000000, 100000000}; // n = 10^7 и n = 10^8
    double t_pos =  0.179024;
    double t_pos2 = 1.821060; 
    for (int n_index = 0; n_index < 2; n_index++) { // Перебираем значения n
        const int n = n_values[n_index];
        printf("Численное интегрирование методом Монте-Карло: n = %d\n", n);

        // Цикл по разным количествам потоков
        for (int num_threads = 2; num_threads <= 8; num_threads += 2) {
            omp_set_num_threads(num_threads);
            double t = omp_get_wtime();
            int in = 0;
            double s = 0;
            #pragma omp parallel
            {
                double s_loc = 0;
                int in_loc = 0;
                unsigned int seed = omp_get_thread_num();
                #pragma omp for nowait
                for (int i = 0; i < n; i++) {
                    double x = getrand(0, 1, &seed);
                    double y = getrand(2, 5, &seed); 
                    s_loc += func(x, y);
                    in_loc++;
                }
                #pragma omp atomic
                s += s_loc;
                #pragma omp atomic
                in += in_loc;
            }
            double v = M_PI * in / n;
            double res = v * s / in;
            t = omp_get_wtime() - t;
            double speedup;
            if (n_index == 0)
            {
                speedup = t_pos/t;
            }
            else
            {
                speedup = t_pos2/t;
            }
            printf("Результат: %.12f, n = %d, Количество потоков: %d, Прошедшее время (сек.): %.6f, Speedup: %.4lf\n", res, n, num_threads, t,speedup);
        }
    }

    return 0;
}
