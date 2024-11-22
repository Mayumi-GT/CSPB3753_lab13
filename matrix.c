///////////////////////////////////////////////////////////////////////////////
// matrix.c
///////////////////////////////////////////////////////////////////////////////
// Author:  Mayumi Shimobe
// Date: Nov 21, 2024
// Editted: Nov 21, 2024
///////////////////////////////////////////////////////////////////////////////
// Description: PImplements matrix allocation, deallocation, and multiplication functions.
// Purpose: To provide basic matrix operations for integers and doubles.
///////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "error_handling.h"

int **allocate_int_matrix(int N) {
    int **matrix = (int **)malloc(N * sizeof(int *));
    if (matrix == NULL) {
        handle_error("Failed to allocate memory for int matrix rows.");
    }
    for (int i = 0; i < N; i++) {
        matrix[i] = (int *)calloc(N, sizeof(int));
        if (matrix[i] == NULL) {
            handle_error("Failed to allocate memory for int matrix columns.");
        }
    }
    return matrix;
}

void free_int_matrix(int **matrix, int N) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

double **allocate_double_matrix(int N) {
    double **matrix = (double **)malloc(N * sizeof(double *));
    if (matrix == NULL) {
        handle_error("Failed to allocate memory for double matrix rows.");
    }
    for (int i = 0; i < N; i++) {
        matrix[i] = (double *)calloc(N, sizeof(double));
        if (matrix[i] == NULL) {
            handle_error("Failed to allocate memory for double matrix columns.");
        }
    }
    return matrix;
}

void free_double_matrix(double **matrix, int N) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}