#define M 12
#define N 12

int sumarrayrows(int a[M][N]) {
    int i, j, sum = 0;

    for (j = 0; j < N; j++) {
        for (i = 0; i < M; i++) {
            sum += a[i][j];
        }
    }
    return sum;
}