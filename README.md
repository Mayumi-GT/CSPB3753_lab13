# CSPB 3753: Operation Systems
# Lab 13 "Markov Chains: Predictive Paging Algorithm"
## Date: Nov 21, 2024
## Name: Mayumi Shimobe

## Project Overview
* This project implements a Predictive Paging Algorithm using Markov Chains in C. The program reads a sequence of page requests from an input file, constructs a Markov Chain to model the probabilities of transitioning between pages, and predicts future page requests based on the computed probabilities. The goal is to enhance page replacement strategies by predicting which pages are likely to be needed soon, thereby reducing page faults.

## Files Structure
* main.c: Entry point of the program; orchestrates the overall process.
* matrix.h / matrix.c: Functions for matrix allocation, deallocation, and multiplication.
* markov.h / markov.c: Functions related to Markov Chain computations and predictions.
* error_handling.h / error_handling.c: Centralized error handling functions.
* Makefile: Automates the build process and provides targets for testing and cleaning.
* test_input.txt: Sample input file containing a sequence of page requests.
* README.md: Documentation of the project (this file).
