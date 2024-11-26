///////////////////////////////////////////////////////////////////////////////
// matrix.h
///////////////////////////////////////////////////////////////////////////////
// Author:  Mayumi Shimobe
// Date: Nov 21, 2024
// Editted: Nov 21, 2024
///////////////////////////////////////////////////////////////////////////////
// Description: Provides matrix allocation, deallocation, and multiplication 
//             functions.
// Purpose: To manage matrix operations required for the Markov chain
//            computations.
///////////////////////////////////////////////////////////////////////////////

#ifndef MATRIX_H
#define MATRIX_H

int **allocate_int_matrix(int N);
void free_int_matrix(int **matrix, int N);
double **allocate_double_matrix(int N);
void free_double_matrix(double **matrix, int N);
void multiply_matrices(double **A, double **B, double **result, int N);

#endif