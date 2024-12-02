# CSPB 3753: Operation Systems
# Lab 13 "Markov Chains: Predictive Paging Algorithm"
## Date: Nov 21, 2024
## Name: Mayumi Shimobe

## Project Overview
* This project implements a Predictive Paging Algorithm using Markov Chains in C. The program reads a sequence of page requests from an input file, constructs a Markov Chain to model the probabilities of transitioning between pages, and predicts future page requests based on the computed probabilities. The goal is to enhance page replacement strategies by predicting which pages are likely to be needed soon, thereby reducing page faults.
* Reference: 
  * "Lab 8 Markov Chains" given in CSPB3753 class as an assignment
  * https://web.stanford.edu/class/stat217/New12.pdf

## Files Structure
* main.c: Entry point of the program; orchestrates the overall process.
* matrix.h / matrix.c: Functions for matrix allocation, deallocation, and multiplication.
* markov.h / markov.c: Functions related to Markov Chain computations and predictions.
* error_handling.h / error_handling.c: Centralized error handling functions.
* Makefile: Automates the build process and provides targets for testing and cleaning.
* test_input.txt: Sample input file containing a sequence of page requests.
* README.md: Documentation of the project (this file).


## Answers to Questions from Given pdf File
* Matrix Multiplication
  * Question: "Convince yourself that you essentially already wrote multithreaded code for performing AB. In particular, extend your code to perform AB. What quantity should each thread should be in charge of computing?"
  * My Answer: Each element, $(AB)_{i,j}$ is computed as a dot prduct of i-th row of matrix A and j-th column of matrix B: $(AB)_{i,j} = \sum_{k=1}^{m} a_{i,k} b_{k,j}$. With multithreadede implementation, the computation can be done in parallel by assigning different parts of the task to multiple threads. Each threads computs a subset of the elements in the result matrix AB: each thread should compute one or more elements $(AB)_{i,j}$ of the result matrix.
<br>
<br>
* Walks and Matrix Multiplication
  * Question 1: "What does the (i, j)-entry of $A^2$ compute?"
  * My Answer: In the graph theory, when A is the adjacency matrix of a directed graph G = (V, E), the (i, j)-entry of $A^2$ represents the number of walks of length 2 from vertex i to vertx j, as the multiplying adjacency matrix by itself counts the number of ways to go from i to j. Multiplying the adjacency matrix by itself counts the number of ways to go from vertex i to j via vertex k: $(AB^2)_{i,j} = \sum_{k=1}^{n} a_{i,k} b_{k,j}$. The terms $a_{i,k} b_{k,j}$ would be 1 if there is a path from i to k and from k to j, so the a walk of length 2 from i to j.
<br>
<br>
  * Question 2: "For any positive integer k, what does the (i, j)-entry of $A^k$ compute?"
  * My Answer: Similar to question 1, it would represents the the number of walks of length 𝑘 from vertex i to vertex j in the graph  G.
<br>
<br>
* Markov Chains
  * Question 1: "For any positive integer k, is $M^k$ a Markov chain?"
  * My Answer: Yes, for any positive inter k, $M^k$ is a Markov chain. The product of matrices with non-negative entries will have non-negative entries because M is a probabilities and M has non-negative entries. In addition, resulting matrix also has rows that sum to 1 when multiply matrices where each row sums to 1. With the definition given of Markov chain, " a n × n matrix is a Markov chain if its entries are all non-negative and each row sums to 1."
<br>
<br>
  * Question 2: "What does the (i, j)-entry of $M^k$ compute?"
  * My Answer: According to the reference, fundamental property of Markov chains is $(M^k)_{i, j}$ = P(state j at step k$∣$starting from state i). Therefore, the (i, j)-entry of $M^k$ computes the probabiility of transitioning from state i to state j in k steps.
<br>
<br>
  * Question 3: "think about how you could use a Markov chain as part of a predictive paging algorithm. How do you define M? What are its probabilities? How do we compute them? What do powers of M tell us?"
  * My Answer: 
    * How do you define M?: I would define M as transition probability matrix representing prbabiility of requesting page j after page i. Each state in Markov chain corresponds to a page in memory.
    * What are its probabilities?: Like above, the probabilities are likelihood of transitioning from one page to another.
    * How do we compute them?: It would be calculated by normalzing observed transition counts between pages by fir collect counts of transitions from data then normalize counts to obtain probabilities, ensuring each row sums to 1.
    * What do powers of M tell us?: Silimar to previous questions on the assignment, the powers of M tellss us the probabilities of transitioning between pages over multiple steps. It would predict future page requests several steps ahead and assist making informed decisions for prefetching and page replacement.