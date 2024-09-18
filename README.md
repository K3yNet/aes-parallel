# AES Paralelo

## Resumo (Português)

Este projeto implementa uma versão paralelizada do algoritmo Advanced Encryption Standard (AES), com o objetivo de melhorar o desempenho criptográfico usando técnicas de computação paralela. A paralelização foi feita utilizando a biblioteca OpenMP, que distribui a carga de trabalho em múltiplos núcleos do processador, trazendo ganhos significativos em termos de eficiência.

### Comparação com AES Tradicional

Nosso algoritmo paralelo oferece uma eficiência muito maior comparado à versão sequencial tradicional do AES. Ao utilizarmos múltiplos threads, a execução é drasticamente mais rápida, conforme demonstrado pelos gráficos de tempo de execução e eficiência. A métrica de Karp-Flat foi usada para avaliar o ganho de desempenho.

### Hardware Utilizado

Os testes foram realizados em dois modelos de notebooks, ambos equipados com processadores Intel Core i5 de 11ª geração com 4 núcleos físicos e 8 GB de memória RAM. Este hardware foi escolhido para fornecer uma base consistente para avaliar o desempenho da paralelização em um ambiente com recursos limitados.

### Gráficos

- **Tempo de Execução**:

  ![image1](https://github.com/user-attachments/assets/2e70ff93-ed6c-4f51-89d2-f660522a1338)

- **SpeedUp**:
  
  ![image2](https://github.com/user-attachments/assets/2fbccb76-e6d4-4d77-9e6c-2611d17bdbb2)

- **Eficiência**:
  
  ![image3](https://github.com/user-attachments/assets/747b1faf-a86a-4aff-989b-91b149cbb0bf)

### Como Usar (Português)

1. Compile o código em "main.cpp" com suporte para OpenMP:

    ```bash
    g++ -fopenmp -o main main.cpp
    ```

2. Execute o programa, fornecendo o número de threads e o arquivo de entrada:

    ```bash
    ./main key_16_characters "input_name_file.txt" "num_threads"
    ```

    O programa gerará a saída criptografada.

---

## Summary (English)

This project implements a parallelized version of the Advanced Encryption Standard (AES) algorithm, aiming to improve cryptographic performance using parallel computing techniques. Parallelization was achieved using the OpenMP library, which distributes the workload across multiple CPU cores, providing significant efficiency gains.

### Comparison with Traditional AES

Our parallel algorithm offers much greater efficiency compared to the traditional sequential version of AES. By utilizing multiple threads, the execution time is drastically faster, as demonstrated by the execution time and efficiency graphs. The Karp-Flat metric was used to assess the performance gains.

### Hardware Used

The tests were conducted on two notebook models, both equipped with 11th-generation Intel Core i5 processors with 4 physical cores and 8 GB of RAM. This hardware was chosen to provide a consistent baseline for evaluating the performance of parallelization in a limited resource environment.

### Graphs

- **Execution Time**:

  ![image1](https://github.com/user-attachments/assets/2e70ff93-ed6c-4f51-89d2-f660522a1338)

- **SpeedUp**:
  
  ![image2](https://github.com/user-attachments/assets/2fbccb76-e6d4-4d77-9e6c-2611d17bdbb2)

- **Efficiency**:
  
  ![image3](https://github.com/user-attachments/assets/747b1faf-a86a-4aff-989b-91b149cbb0bf)

### How to Use (English)

1. Compile the code in "main.cpp" with OpenMP support:

    ```bash
    g++ -fopenmp -o main main.cpp
    ```

2. Run the program, specifying the number of threads and the input file:

    ```bash
    ./main key_16_characters "input_name_file.txt" "num_threads"
    ```

    The program will output the encrypted data.

---

## Autores / Authors:

- Gustavo Soares
- Rafael Brunini
- Enzo Velo

---
