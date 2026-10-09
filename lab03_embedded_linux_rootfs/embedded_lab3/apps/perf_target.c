
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARRAY_SIZE 100000
#define ITERATIONS 100

static double heavy_compute(double *arr, int size)
{
    double total = 0.0;

    for (int i = 0; i < size; i++) {
        total += sqrt(arr[i] * arr[i] + 1.0);
    }

    return total;
}

static int linear_search(int *arr, int size, int target)
{
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }

    return -1;
}

static void io_intensive(int lines)
{
    FILE *fp = fopen("/tmp/perf_io_test.txt", "w");

    if (fp == NULL) {
        perror("fopen");
        return;
    }

    for (int i = 0; i < lines; i++) {
        fprintf(fp, "Line %d: Embedded Linux performance test\n", i);
    }

    fclose(fp);
}

int main(void)
{
    double *darr = malloc(sizeof(double) * ARRAY_SIZE);
    int *iarr = malloc(sizeof(int) * ARRAY_SIZE);

    if (darr == NULL || iarr == NULL) {
        perror("malloc");
        free(darr);
        free(iarr);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        darr[i] = (double)i / 100.0;
        iarr[i] = i;
    }

    printf("=== LAB03 Performance Target ===\n");

    printf("[1] Heavy computation (%d iterations)...\n", ITERATIONS);
    double total = 0.0;

    for (int iter = 0; iter < ITERATIONS; iter++) {
        total += heavy_compute(darr, ARRAY_SIZE);
    }

    printf("    Result: %f\n", total);

    printf("[2] Linear search (1000 times)...\n");

    for (int i = 0; i < 1000; i++) {
        linear_search(iarr, ARRAY_SIZE, ARRAY_SIZE - 1);
    }

    printf("[3] I/O intensive (write 10000 lines)...\n");
    io_intensive(10000);

    free(darr);
    free(iarr);

    printf("Done.\n");
    return 0;
}