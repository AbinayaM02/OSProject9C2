#!/bin/bash
gcc MeanCalculation.c MainProgram.c -o calculateMean
gcc Datapreprocessing_modified.c -o preprocessData
make
time ./knn
octaveCommand = source plot_final_trial.m
res=$(octave -q --eval ${octavecommand})
echo "the result is ${res}"
