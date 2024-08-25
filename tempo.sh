#!/bin/bash
saida_omp="dados-omp.csv"
if [ -f $saida_omp ]; then
	rm $saida_omp
fi

g++ -fopenmp main.cpp -o main.o
g++ -fopenmp decrypt.cpp -o decrypt.o

# Cabeçalho
echo 'NumThreads tempo1 tempo2 tempo3 tempo4 tempo5 tempo6 tempo7 tempo8 tempo9 tempo10' >> $saida_omp

for nThreads in 1 2 4 8 16; do
    echo -n $nThreads >> $saida_omp
    for i in 1 2 3 4 5 6 7 8 9 10; do
        ./main.o $nThreads >> $saida_omp
    done
    echo '' >> $saida_omp
done
