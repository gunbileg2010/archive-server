#include <string>
#include <iostream>
#include <fstream>
#include <openssl/aes.h>

bool aes_encrypt(const std::string& filepath, const std::string& key) {
    std::ifstream input_file(filepath, std::ios::binary);
    std::ofstream output_file(filepath + ".enc", std::ios::binary);
    
    if (!input_file || !output_file) {
        return false;
    }

    AES_KEY encrypt_key;
    AES_set_encrypt_key((const unsigned char*)key.c_str(), 128, &encrypt_key);

    unsigned char indata[AES_BLOCK_SIZE];
    unsigned char outdata[AES_BLOCK_SIZE];
    
    while (!input_file.eof()) {
        input_file.read((char*)indata, AES_BLOCK_SIZE);
        AES_encrypt(indata, outdata, &encrypt_key);
        output_file.write((char*)outdata, AES_BLOCK_SIZE);
    }

    input_file.close();
    output_file.close();
    return true;
}