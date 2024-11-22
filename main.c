///////////////////////////////////////////////////////////////////////////////
// main.c
///////////////////////////////////////////////////////////////////////////////
// Author:  Mayumi Shimobe
// Date: Nov 21, 2024
// Editted: Nov 21, 2024
///////////////////////////////////////////////////////////////////////////////
// Description: this is an entry point for the Predictive Paging Algorithm program.
// Purpose: Reads page sequence, constructs the Markov chain, predicts future pages.
///////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "markov.h"
#include "error_handling.h"

#define NUM_PAGES 10  
#define K_STEPS 2    // Number of steps ahead to predict

int main(int argc, char *argv[]) {
    if (argc != 2) {
        handle_error("Usage: ./predictive_paging <input_file>");
    }

    const char *input_file = argv[1];
    int **C = allocate_int_matrix(NUM_PAGES);
    if (C == NULL) {
        handle_error("Failed to allocate memory for transition counts matrix.");
    }

    read_page_sequence(input_file, C, NUM_PAGES);

    double **M = allocate_double_matrix(NUM_PAGES);
    if (M == NULL) {
        handle_error("Failed to allocate memory for transition probability matrix.");
    }

    compute_transition_matrix(C, M, NUM_PAGES);

    double **M_power = allocate_double_matrix(NUM_PAGES);
    if (M_power == NULL) {
        handle_error("Failed to allocate memory for matrix power.");
    }

    compute_matrix_power(M, M_power, K_STEPS, NUM_PAGES);

    int current_page = 0;  // Starting page (can be set dynamically)
    predict_pages(M_power, current_page, NUM_PAGES);

    // Free allocated memory
    free_int_matrix(C, NUM_PAGES);
    free_double_matrix(M, NUM_PAGES);
    free_double_matrix(M_power, NUM_PAGES);

    return 0;
}