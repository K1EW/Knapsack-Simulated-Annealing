#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_WEIGHT 300
#define ITEMS 20
#define BEST_VALUE 381 // BEST_VALUE can be obtained by a simple dp approach

int objective_func(int x, int *weight, int *value) {
    int total_value = 0;
    int total_weight = 0;
    for (int i = 0; i < ITEMS; i++) {
        if (x & (1 << i)) {
            total_value += value[i];
            total_weight += weight[i];
        }
    }
    return (total_weight > MAX_WEIGHT ? 0 : total_value);
}

double my_rand() {
    return (double)rand() / (double)RAND_MAX;
}

double temperature_func(int iter) {
    return 1e7 - 2 * iter;
}

int search() {
    int weight[] = {2, 3, 6, 7, 8, 12, 18, 30, 32, 35, 37, 44, 48, 50, 61, 79, 74, 84, 89, 95};
    int value[] = {5, 6, 16, 7, 8, 13, 29, 42, 36, 47, 42, 47, 49, 57, 64, 74, 85, 89, 96, 109};

    int x0 = my_rand() * ((1 << (ITEMS + 1)) - 1);

    int best = objective_func(x0, weight, value);
    int best_x = x0;

    int iter = 0;
    double T = temperature_func(iter);

    while (T > 0) {
        int dx = my_rand() * (ITEMS - 1);
        
        int x1 = x0 ^ (1 << dx);
        double delta = objective_func(x0, weight, value) - objective_func(x1, weight, value);
        
        if (delta < 0) {
            x0 = x1;
        } else {
            double P = my_rand();
            if (P < exp(-delta/T)) {
                x0 = x1;
                if (best < objective_func(x0, weight, value)) {
                    best = objective_func(x0, weight, value);
                    best_x = x0;
                }
            }
        }

        iter++;
        T = temperature_func(iter);
    }

    printf("Best total value = %d\n", best);
    printf("By select the follwing items:");
    for (int i = 0; i < ITEMS; i++) {
        if (best_x & (1 << i)) printf(" %d", i + 1);
    }
    printf("\n");
    return best;
}

int main(int argc, char *argv[])
{
    srand(time(0));
    int iteration;
    if (argc == 1) iteration = 1;
    else iteration = atoi(argv[1]);

    double mse = 0;
    for (int i = 1; i <= iteration; i++) {
        printf("======= %d-th iteration =======\n", i);
        int error = search() - BEST_VALUE;
        mse += error * error;
    }
    mse /= iteration;
    printf("======= Mean Squared Error =======\n%lf\n", mse);

    return 0;
}
