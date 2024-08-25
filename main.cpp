#include "src/app.hpp"

int main(int argc, char* argv[]){

    if(argc != 4){
        printf("Uso do programa: ./main.o key_16_characters input_file_name.txt num_threads\n");
        return 1;
    }
    // converter a entrada de char para unsigned char
    byte key[KEY_SIZE];
    for (size_t i = 0; i < KEY_SIZE; ++i) {
        key[i] = static_cast<unsigned char>(argv[1][i]);
    }

    char* fileName = argv[2];

    int numThreads = atoi(argv[3]);

    omp_set_num_threads(numThreads);

    appEncrypt(key, fileName);
    appDecrypt(key, "output.enc");
    
    return 0;
}