#!/bin/bash
gcc MeanCalculation.c MainProgram.c -o calculateMean
gcc Datapreprocessing_modified.c -o preprocessData
make
time ./knn
