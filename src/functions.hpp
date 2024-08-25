#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "utils.hpp"
#include <string>

// ----- Common function declarations -----

void getRoundKey(byte expandedKey[], byte roundKey[]);
void addRoundKey(byte state[], byte roundKey[]);
byte galois_multiplication(byte a, byte b);
void printBytesHexa(byte teste[], int size);
void rotate(byte word[]);
void expandKey(byte key[], byte expandedKey[]);
void core(byte word[], byte iteration);

// ----- Encrypt function declarations -----

void aesCypher(byte input[], byte expandedKey[]);
byte* aesEncrypt(std::string input, byte key[], size_t &inputSize);
void subBytes(byte state[]);
void shiftRow(byte *state, byte nbr);
void shiftRows(byte *state);
void mixColumns(byte state[]);

// ----- Decrypt function declarations -----

void aesDescypher(byte input[], byte expandedKey[]);
void aesDecrypt(byte bInput[], int inputSize, byte key[]);
void invSubBytes(byte state[]);
void invShiftRow(byte *state, byte nbr);
void invShiftRows(byte *state);
void invMixColumn(byte column[]);
void invMixColumns(byte state[]);

// ----- Common function definitions -----

void getRoundKey(byte expandedKey[], byte roundKey[]){
    for(int i=0; i<WORD_SIZE; i++){
        for(int j=0; j<WORD_SIZE; j++){
            roundKey[i + (j * WORD_SIZE)] = expandedKey[((i * WORD_SIZE) + j)];
        }
    }
}

void addRoundKey(byte state[], byte roundKey[]){
    for(int i = 0; i < KEY_SIZE; i++){
        state[i] = state[i] ^ roundKey[i];
    }
}

byte galois_multiplication(byte a, byte b){
    byte p = 0;
    byte hi_bit_set;
    for (byte counter = 0; counter < 8; counter++) {
        if ((b & 1) == 1)
            p ^= a;
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set == 0x80)
            a ^= 0x1b;
        b >>= 1;
    }
    return p;
}

void printBytesHexa(byte teste[], int size){
    printf("\n=============== Print ================\n\n");
    for (int i = 0; i < size; i++){
        printf("%2.2x%c", teste[i], ((i + 1) % 16) ? ' ' : '\n');
    }
    printf("\n=======================================\n");
}

void rotate(byte word[]){
    byte firstByte = word[0];
    for (int i = 0; i < 3; i++){
        word[i] = word[i + 1];
    }
    word[3] = firstByte;
}

void expandKey(byte key[], byte expandedKey[]){
    for(int i=0; i<KEY_SIZE; i++){
        expandedKey[i] = key[i];
    }
    int currentSize = KEY_SIZE;
    byte rcomIterator = 1;
    byte prevWord[WORD_SIZE];
    for(; currentSize < EXPANDED_KEY_SIZE;){
        for(int i=0; i<WORD_SIZE; i++){
            prevWord[i] = expandedKey[(currentSize-WORD_SIZE)+i];
        }
        if(currentSize % KEY_SIZE == 0)
            core(prevWord, rcomIterator++);
        for(int i=0; i<WORD_SIZE; i++){
            expandedKey[currentSize] = expandedKey[currentSize - KEY_SIZE] ^ prevWord[i];
            currentSize++;
        }
    }
}

void core(byte word[], byte iteration){
    rotate(word);
    for (int i = 0; i < 4; ++i){
        word[i] = sbox[word[i]];
    }
    word[0] = word[0] ^ Rcon[iteration];
}

// ----- Encrypt function definitions -----

void aesCypher(byte input[], byte expandedKey[]){
    byte* state = input;
    byte roundKey[KEY_SIZE];
    getRoundKey(expandedKey, roundKey);
    addRoundKey(state,roundKey);
    for(int i=1; i<NUM_ROUNDS; i++){
        getRoundKey(expandedKey + 16 * i, roundKey);
        subBytes(state);
        shiftRows(state);
        mixColumns(state);
        addRoundKey(state,roundKey);
    }
    getRoundKey(expandedKey + 16 * NUM_ROUNDS, roundKey);
    subBytes(state);
    shiftRows(state);
    addRoundKey(state,roundKey);
}

byte* aesEncrypt(std::string input, byte key[], size_t &inputSize){
    const char* cInput = input.c_str();
    inputSize = (input.size()/16 + 1)*16;
    int nBlocks = inputSize/16;

    byte* bInput = new byte[inputSize];
    int i;
    for(i=0; i<input.size(); i++){
        bInput[i] = cInput[i];
    }
    for(; i<inputSize; i++){
        bInput[i] = 0;
    }

    byte expandedKey[EXPANDED_KEY_SIZE];
    expandKey(key, expandedKey);

    double startTime = omp_get_wtime();

    // Paralelização das entradas da criptografia
    #pragma omp parallel for
    for(int i=0; i<nBlocks; i++){
        aesCypher(bInput + 16*i, expandedKey);
    }

    double endTime = omp_get_wtime();

    printf("Tempo: %.6f\n", endTime-startTime);

    return bInput;
}

void subBytes(byte state[]){
    for(int i = 0; i < KEY_SIZE; i++){
        state[i] = sbox[state[i]];
    }
}

void shiftRow(byte *state, byte nbr){
    byte tmp;
    for (int i = 0; i < nbr; i++){
        tmp = state[0];
        for (int j = 0; j < 3; j++)
            state[j] = state[j + 1];
        state[3] = tmp;
    }
}

void shiftRows(byte *state){
    for (int i = 0; i < 4; i++){
        shiftRow(state + i * 4, i);
    }
}

void mixColumns(byte state[]){
    byte column[4];
    byte cpy[4];
    for (int i = 0; i < WORD_SIZE; i++) {
        for (int j = 0; j < WORD_SIZE; j++) {
            column[j] = state[(j * WORD_SIZE) + i];
        }
        for (int k = 0; k < WORD_SIZE; k++) {
            cpy[k] = column[k];
        }
        column[0] = galois_multiplication(cpy[0], 2) ^
                    galois_multiplication(cpy[3], 1) ^
                    galois_multiplication(cpy[2], 1) ^
                    galois_multiplication(cpy[1], 3);

        column[1] = galois_multiplication(cpy[1], 2) ^
                    galois_multiplication(cpy[0], 1) ^
                    galois_multiplication(cpy[3], 1) ^
                    galois_multiplication(cpy[2], 3);

        column[2] = galois_multiplication(cpy[2], 2) ^
                    galois_multiplication(cpy[1], 1) ^
                    galois_multiplication(cpy[0], 1) ^
                    galois_multiplication(cpy[3], 3);

        column[3] = galois_multiplication(cpy[3], 2) ^
                    galois_multiplication(cpy[2], 1) ^
                    galois_multiplication(cpy[1], 1) ^
                    galois_multiplication(cpy[0], 3);

        for (int j = 0; j < WORD_SIZE; j++){
            state[(j * WORD_SIZE) + i] = column[j];
        }
    }
}

// ----- Decrypt function definitions -----

void aesDescypher(byte input[], byte expandedKey[]){
    byte* state = input;

    byte roundKey[KEY_SIZE];
    getRoundKey(expandedKey + 16 * NUM_ROUNDS, roundKey);
    addRoundKey(state,roundKey);
    for(int i = NUM_ROUNDS - 1; i > 0; i--){
        getRoundKey(expandedKey + 16 * i, roundKey);
        invShiftRows(state);
        invSubBytes(state);
        addRoundKey(state, roundKey);
        invMixColumns(state);
    }
    getRoundKey(expandedKey, roundKey);
    invShiftRows(state);
    invSubBytes(state);
    addRoundKey(state, roundKey);
}

void aesDecrypt(byte bInput[], int inputSize, byte key[]){
    int nBlocks = inputSize / 16;

    byte expandedKey[EXPANDED_KEY_SIZE];
    expandKey(key, expandedKey);

    double startTime = omp_get_wtime();

    // Parallelize the decryption process
    #pragma omp parallel for
    for(int i = 0; i < nBlocks; i++){
        aesDescypher(bInput + 16 * i, expandedKey);
    }

    double endTime = omp_get_wtime();
    printf("Tempo: %.6f\n", endTime - startTime);

    for(int i = 0; i < inputSize; i++){
        printf("%c", bInput[i]);
    }
    printf("\n");
}

void invSubBytes(byte state[]) {
    for (int i = 0; i < 16; i++)
        state[i] = rsbox[state[i]];
}

void invShiftRow(byte *state, byte nbr)
{
    byte tmp;
    for (int i = 0; i < nbr; i++){
        tmp = state[3];
        for (int j = 3; j > 0; j--)
            state[j] = state[j - 1];
        state[0] = tmp;
    }
}

void invShiftRows(byte *state)
{
    for (int i = 0; i < 4; i++)
        invShiftRow(state + i * 4, i);
}

void invMixColumn(byte column[])
{
    byte cpy[WORD_SIZE];
    for (int i = 0; i < WORD_SIZE; i++){
        cpy[i] = column[i];
    }

    column[0] = galois_multiplication(cpy[0], 14) ^
                galois_multiplication(cpy[3], 9) ^
                galois_multiplication(cpy[2], 13) ^
                galois_multiplication(cpy[1], 11);
    column[1] = galois_multiplication(cpy[1], 14) ^
                galois_multiplication(cpy[0], 9) ^
                galois_multiplication(cpy[3], 13) ^
                galois_multiplication(cpy[2], 11);
    column[2] = galois_multiplication(cpy[2], 14) ^
                galois_multiplication(cpy[1], 9) ^
                galois_multiplication(cpy[0], 13) ^
                galois_multiplication(cpy[3], 11);
    column[3] = galois_multiplication(cpy[3], 14) ^
                galois_multiplication(cpy[2], 9) ^
                galois_multiplication(cpy[1], 13) ^
                galois_multiplication(cpy[0], 11);
}

void invMixColumns(byte state[])
{
    byte column[WORD_SIZE];

    for (int i = 0; i < WORD_SIZE; i++){
        for (int j = 0; j < WORD_SIZE; j++){
            column[j] = state[(j * WORD_SIZE) + i];
        }

        invMixColumn(column);

        for (int j = 0; j < WORD_SIZE; j++){
            state[(j * WORD_SIZE) + i] = column[j];
        }
    }
}

#endif // FUNCTIONS_HPP