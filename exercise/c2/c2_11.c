#include <stdio.h>

void inplace_swap(int *x, int *y) {
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}


void reverse_array(int a[], int cnt) {
    for(size_t first = 0, last = cnt - 1;
            first < last;
            first++, last--) {
        inplace_swap(&a[first], &a[last]);
    }
}


void print_array(int a[], int cnt) {
    for(size_t i = 0; i < cnt; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");
}


int main() {
    int arr[] = {1,2,3,4,5};

    int cnt = sizeof(arr) / sizeof(int);


    printf("Before reverse_array:\n ");
    print_array(arr, cnt);

    printf("After reverse_array:\n ");
    reverse_array(arr, cnt);
    print_array(arr, cnt);
}
