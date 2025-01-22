#include <stdio.h>
#include <stdlib.h>

void add(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int n, int A[n][n], int B[n][n], int C[n][n]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;
    int (*A11)[newSize] = malloc(sizeof(int[newSize][newSize]));
    int (*A12)[newSize] = malloc(sizeof(int[newSize][newSize]));
    int (*A21)[newSize] = malloc(sizeof(int[newSize][newSize]));
    int (*A22)[newSize] = malloc(sizeof(int[newSize][newSize]));
    int (*B11)[newSize] = malloc(sizeof(int[newSize][newSize]));
    int (*B12)[newSize] = malloc(sizeof(int[newSize][newSize]));
    int (*B21)[newSize] = malloc(sizeof(int[newSize][newSize]));
    int (*B22)[newSize] = malloc(sizeof(int[newSize][newSize]));
    int (*M1)[newSize] = malloc(sizeof(int[newSize][newSize]));
    int (*M2)[newSize] = malloc(sizeof(int[newSize][newSize]));
    int (*M3)[newSize] = malloc(sizeof(int[newSize][newSize]));
    int (*M4)[newSize] = malloc(sizeof(int[newSize][newSize]));
    int (*M5)[newSize] = malloc(sizeof(int[newSize][newSize]));
    int (*M6)[newSize] = malloc(sizeof(int[newSize][newSize]));
    int (*M7)[newSize] = malloc(sizeof(int[newSize][newSize]));

    // Divide matrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    int (*temp1)[newSize] = malloc(sizeof(int[newSize][newSize]));
    int (*temp2)[newSize] = malloc(sizeof(int[newSize][newSize]));

    // Calculate M1 to M7
    add(newSize, A11, A22, temp1);
    add(newSize, B11, B22, temp2);
    strassen(newSize, temp1, temp2, M1);

    add(newSize, A21, A22, temp1);
    strassen(newSize, temp1, B11, M2);

    subtract(newSize, B12, B22, temp2);
    strassen(newSize, A11, temp2, M3);

    subtract(newSize, B21, B11, temp2);
    strassen(newSize, A22, temp2, M4);

    add(newSize, A11, A12, temp1);
    strassen(newSize, temp1, B22, M5);

    subtract(newSize, A21, A11, temp1);
    add(newSize, B11, B12, temp2);
    strassen(newSize, temp1, temp2, M6);

    subtract(newSize, A12, A22, temp1);
    add(newSize, B21, B22, temp2);
    strassen(newSize, temp1, temp2, M7);

    // Calculate final C matrix
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + newSize] = M3[i][j] + M5[i][j];
            C[i + newSize][j] = M2[i][j] + M4[i][j];
            C[i + newSize][j + newSize] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }

    // Free allocated memory
    free(A11); free(A12); free(A21); free(A22);
    free(B11); free(B12); free(B21); free(B22);
    free(M1); free(M2); free(M3); free(M4); free(M5); free(M6); free(M7);
    free(temp1); free(temp2);
}

int main() {
    int n;
    printf("Enter the dimension of the matrix (power of 2): ");
    scanf("%d", &n);

    int A[n][n], B[n][n], C[n][n];
    printf("Enter elements of matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    strassen(n, A, B, C);

    printf("Resultant matrix C:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    return 0;
}
