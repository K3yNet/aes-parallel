# Parallel AES

## Summary

This project implements a parallelized version of the Advanced Encryption Standard (AES) algorithm, aiming to improve cryptographic performance using parallel computing techniques. Parallelization was achieved using the OpenMP library, which distributes the workload across multiple CPU cores, providing significant efficiency gains.

### Comparison with Traditional AES

Our parallel algorithm offers much greater efficiency compared to the traditional sequential version of AES. By utilizing multiple threads, the execution time is drastically faster, as demonstrated by the execution time and efficiency graphs. The Karp-Flat metric was used to assess the performance gains.

### Hardware Used

The tests were conducted on two notebook models, both equipped with 11th-generation Intel Core i5 processors with 4 physical cores and 8 GB of RAM. This hardware was chosen to provide a consistent baseline for evaluating the performance of parallelization in a limited resource environment.

## Graphs

- **Execution Time**:

  ![image1](https://github.com/user-attachments/assets/2e70ff93-ed6c-4f51-89d2-f660522a1338)

- **SpeedUp**:
  
  ![image2](https://github.com/user-attachments/assets/2fbccb76-e6d4-4d77-9e6c-2611d17bdbb2)

## How to Use

1. Compile the code in "main.cpp" with OpenMP support:

    ```bash
    g++ -fopenmp -o main main.cpp
    ```

2. Run the program, specifying the 16-character key, the input file, and the number of threads:

    ```bash
    ./main key_16_characters "input_name_file.txt" "num_threads"
    ```

    The program will output the encrypted data.

---

## Authors

- Gustavo Soares
- Rafael Brunini
- Enzo Velo