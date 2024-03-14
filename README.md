# Knapsack - SA
Solving Knapsack problem using metaheuristic optimization method - Simulated Annealing

## How it works
#### Comming up with initial solution
Suppose we have $n$ items to be considered. We can think of the solution to be a number with $n$-bit length. The $i$-th bit represents whether we selected
the $i$-th item or not (1 is selected, 0 is not). With this assumption, the **initial solution** is going to be 
anything from $0$ to $2^n - 1$


#### The objective function
In this problem, we have to maximize the total value that be can obtained subject to constraint on weight. So 
the **objective function** is going to return the value we can obtained given a solution (`x`) as a parameter.

```c
int objective_func(int x, int *weight, int *value) {
    int total_value = 0;
    int total_weight = 0;
    for (int i = 0; i < n; i++) {
        if (x & (1 << i)) {
            total_value += value[i];
            total_weight += weight[i];
        }
    }
    return (total_weight > MAX_WEIGHT ? 0 : total_value);
}
```

#### Visiting next solution strategy
Since our solution is a number represented in binary, the next solution can be acquired by taking any $i$-bit 
from $1$ to $n$ and flip it. Let $x_0$ be our current solution and $x_1$ be the next solution. $x_1$ can be acquired 
by

```c
// my_rand() returns a random number between 0 and 1
double my_rand() {
    return (double)rand() / (double)RAND_MAX;
}

int dx = my_rand() * (n - 1); // Randomize the bit to be flipped
int x_1 = x_0 ^ (1 << dx); // Flip the corresponding bit
```

#### Temperature function
> **TODO**
