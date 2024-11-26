///////////////////////////////////////////////////////////////////////////////
// markov.c
///////////////////////////////////////////////////////////////////////////////
// Author:  Mayumi Shimobe
// Date: Nov 26, 2024
///////////////////////////////////////////////////////////////////////////////
// Description: Implements functions related to Markov chain computations 
//              for predictive paging.
///////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include "markov.h"
#include "matrix.h"
#include "error_handling.h"

///////////////////////////////////////////////////////////////////////////////
// read_page_sequence
// Description: Reads a sequence of page requests from a file and updates 
//             the transition counts matrix C.
// Parameters: filename - name of the input file containing the page sequence.
//             C - the transition counts matrix to be updated with int **.
//             N - the number of pages (size of the matrix).
// Returns: void
// Error Processing: if the file cannot be opened, it calls handle_error,
//                  and if a page number is out of range, it calls 
//                  handle_error.
///////////////////////////////////////////////////////////////////////////////
void read_page_sequence(const char *filename, int **C, int N) {
    if (filename == NULL || C == NULL) {
        handle_error("Null pointer passed to read_page_sequence.");
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        handle_error("Failed to open input file.");
    }

    int prev_page = -1;
    int current_page;

    while (fscanf(file, "%d", &current_page) == 1) {
        if (current_page < 0 || current_page >= N) {
            handle_error("Page number out of range in input file.");
        }

        if (prev_page != -1) {
            C[prev_page][current_page]++;
        }

        prev_page = current_page;
    }

    fclose(file);
}



///////////////////////////////////////////////////////////////////////////////
// compute_transition_matrix
// Description: this function processes each row of matrix C, calculates the
//              sum of counts, and then normalizes each count to compute the
//              probability. It ensures that each row of M sums to 1.0. If a 
//             row in C sums to zero (no outgoing transitions), it handles 
//              the division by zero appropriately.
// Parameters: C - int 2D array containing counts of transitions between pages.
//             M - double 2D array where the computed probabilities will be 
//                 stored.
//             N - the number of pages (size of the matrices).
// Returns: void
// Error Processing: if C or M is NULL, it calls handle_error and checks for
//                   division by zero when a row sum is zero.
///////////////////////////////////////////////////////////////////////////////
void compute_transition_matrix(int **C, double **M, int N) {
    if (C == NULL || M == NULL) {
        handle_error("Null pointer passed to compute_transition_matrix.");
    }

    for (int i = 0; i < N; i++) {
        int row_sum = 0;
        for (int j = 0; j < N; j++) {
            row_sum += C[i][j];
        }

        if (row_sum == 0) {
            // Handle zero transitions from this page
            for (int j = 0; j < N; j++) {
                M[i][j] = 0.0;
            }
            M[i][i] = 1.0; // Stay on the same page
        } else {
            for (int j = 0; j < N; j++) {
                M[i][j] = (double)C[i][j] / row_sum;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// compute_matrix_power
// Description: this function compute the k-th power of matrix M and stores 
//              the result in M_power
// Parameter: M, double ** - the input transition probability matrix (double **)
//            M_power, double ** - The matrix where the result will be stored 
//            k - the exponent
//            N - the size of the matrices (they are N x N).
// Return : void
// Error Handling: if M or M_power is NULL, it calls handle_error, and 
//                 if k <= 0, it calls handle_error.
///////////////////////////////////////////////////////////////////////////////
void compute_matrix_power(double **M, double **M_power, int k, int N) {
    if (M == NULL || M_power == NULL) {
        handle_error("Null pointer passed to compute_matrix_power.");
    }
    if (k <= 0) {
        handle_error("Invalid exponent k in compute_matrix_power.");
    }

    // Initialize M_power to M
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            M_power[i][j] = M[i][j];
        }
    }

    double **temp = allocate_double_matrix(N);
    if (temp == NULL) {
        handle_error("Failed to allocate memory for temporary matrix.");
    }

    // Compute M_power = M^k
    for (int step = 1; step < k; step++) {
        multiply_matrices(M_power, M, temp, N);

        // Copy temp to M_power
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                M_power[i][j] = temp[i][j];
            }
        }
    }

    free_double_matrix(temp, N);
}

///////////////////////////////////////////////////////////////////////////////
// predict_pages
// Description:
// Parameters:
// Return: void
// Error Handling:
///////////////////////////////////////////////////////////////////////////////
void predict_pages(double **M_power, int current_page, int N) {
    if (M_power == NULL) {
        handle_error("Null pointer passed to predict_pages.");
    }
    if (current_page < 0 || current_page >= N) {
        handle_error("Current page number out of range in predict_pages.");
    }

    printf("Predicted probabilities after k steps from page %d:\n", current_page);
    for (int j = 0; j < N; j++) {
        printf("Page %d: %.4f\n", j, M_power[current_page][j]);
    }

    // Optionally, identify the page with the highest probability
    double max_prob = 0.0;
    int predicted_page = -1;
    for (int j = 0; j < N; j++) {
        if (M_power[current_page][j] > max_prob) {
            max_prob = M_power[current_page][j];
            predicted_page = j;
        }
    }

    printf("Most likely next page: %d (Probability: %.4f)\n", predicted_page, max_prob);
}