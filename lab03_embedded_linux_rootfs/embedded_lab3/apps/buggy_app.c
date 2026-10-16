#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void array_bug(void)
{
    int arr[5] = {10, 20, 30, 40, 50};

    printf("\n[1] Array out-of-bounds bug:\n");
    for (int i = 0; i <= 5; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
}

void use_after_free_bug(void)
{
    char *ptr = malloc(32);

    if (ptr == NULL) {
        perror("malloc");
        return;
    }

    strcpy(ptr, "Hello from ARM debugging");
    free(ptr);

    printf("\n[2] Use-after-free bug:\n");
    printf("Data: %s\n", ptr);
}

void integer_overflow_bug(void)
{
    volatile int a = INT_MAX;
    volatile int b = 1;
    volatile int result = a + b;

    printf("\n[3] Integer overflow demonstration:\n");
    printf("%d + %d = %d\n", a, b, result);
}

int main(void)
{
    printf("=== LAB03: ARM GDB Debugging ===\n");

    array_bug();
    use_after_free_bug();
    integer_overflow_bug();

    printf("\nProgram finished.\n");
    return 0;
}
