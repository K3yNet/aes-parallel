#include "src/app.hpp"

byte key [KEY_SIZE] = {'k', 'k', 'k', 'k', 'e', 'e', 'e', 'e', 'y', 'y', 'y', 'y', '.', '.', '.', '.'};

int main(){

    appEncrypt(key, "input.txt");
    appDecrypt(key, "output.enc");
    
}