#include <stdio.h>

void inplace_swap(int *x, int *y) {
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}


int main() {
    int i1 = 3;
    int i2 = 4;
    int *pi1 = &i1;
    int *pi2 = &i2;

    printf("Before inplace_swap:\n");
    printf("pi1->%d\n", *pi1);
    printf("pi2->%d\n", *pi2);

    inplace_swap(pi1, pi2);

    printf("After inplace_swap:\n");
    printf("pi1->%d\n", *pi1);
    printf("pi2->%d\n", *pi2);
}
