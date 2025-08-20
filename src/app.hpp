#ifndef APP_HPP
#define APP_HPP

#include "functions.hpp"

int appEncrypt(byte key[], std::string input){ 
    std::ifstream file(input);
    if(!file){
        printf("Could not open the file. Please create a file named 'input.txt'\n");
        return 1;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string conteudo = buffer.str();
    size_t size;
    byte* encryptedInput = aesEncrypt(conteudo, key, size);

    std::ofstream outFile("output.enc", std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening file for writing." << std::endl;
        return 1;
    }
    outFile.write(reinterpret_cast<const char*>(encryptedInput), size);
    outFile.close();

    std::cout << "Data encrypted and saved to file successfully!" << std::endl;

    delete[] encryptedInput;

    return 0;
}

int appDecrypt(byte key[], std::string output){
    std::ifstream inFile(output, std::ios::binary);

    if (!inFile) {
        std::cerr << "Error opening file for reading." << std::endl;
        return 1;
    }

    inFile.seekg(0, std::ios::end);
    std::streamsize fileSize = inFile.tellg();
    inFile.seekg(0, std::ios::beg);

    byte* data = new byte[fileSize];

    if (!inFile.read(reinterpret_cast<char*>(data), fileSize)) {
        std::cerr << "Error reading data from the file." << std::endl;
        delete[] data;
        return 1;
    }

    inFile.close();

    aesDecrypt(data, fileSize, key);

    delete[] data;

    return 0;
}

#endif // APP_HPP