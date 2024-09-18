# AES Paralelo

## Resumo (Português)

Este projeto implementa uma versão paralelizada do algoritmo Advanced Encryption Standard (AES), com o objetivo de melhorar o desempenho criptográfico usando técnicas de computação paralela. A paralelização foi feita utilizando a biblioteca OpenMP, que distribui a carga de trabalho em múltiplos núcleos do processador, trazendo ganhos significativos em termos de eficiência.

### Comparação com AES Tradicional

Nosso algoritmo paralelo oferece uma eficiência muito maior comparado à versão sequencial tradicional do AES. Ao utilizarmos múltiplos threads, a execução é drasticamente mais rápida, conforme demonstrado pelos gráficos de tempo de execução e eficiência. A métrica de Karp-Flat foi usada para avaliar o ganho de desempenho.

### Gráficos

- **Tempo de Execução**:
  
  (Insira aqui o gráfico de tempo de execução)

- **Eficiência**:
  
  (Insira aqui o gráfico de eficiência)

### Como Usar (Português)

1. Navegue até o diretório `src`.
2. Compile o código com suporte para OpenMP:

    ```bash
    g++ -fopenmp -o aes_parallel aes_parallel.cpp
    ```

3. Execute o programa, fornecendo o número de threads e o arquivo de entrada:

    ```bash
    ./aes_parallel <numero_de_threads> <arquivo_de_entrada>
    ```

    O programa gerará a saída criptografada.

---

## Summary (English)

This project implements a parallelized version of the Advanced Encryption Standard (AES) algorithm, aiming to improve cryptographic performance using parallel computing techniques. Parallelization was achieved using the OpenMP library, which distributes the workload across multiple CPU cores, providing significant efficiency gains.

### Comparison with Traditional AES

Our parallel algorithm offers much greater efficiency compared to the traditional sequential version of AES. By utilizing multiple threads, the execution time is drastically faster, as demonstrated by the execution time and efficiency graphs. The Karp-Flat metric was used to assess the performance gains.

### Graphs

- **Execution Time**:
  
  (Insert execution time graph here)

- **Efficiency**:
  
  (Insert efficiency graph here)

### How to Use (English)

1. Navigate to the `src` directory.
2. Compile the code with OpenMP support:

    ```bash
    g++ -fopenmp -o aes_parallel aes_parallel.cpp
    ```

3. Run the program, specifying the number of threads and the input file:

    ```bash
    ./aes_parallel <number_of_threads> <input_file>
    ```

    The program will output the encrypted data.

---

## Autores / Authors:

- Gustavo Soares
- Rafael Brunini
- Enzo Velo
