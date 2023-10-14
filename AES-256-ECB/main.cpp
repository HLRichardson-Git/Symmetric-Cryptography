/*
    By: Hunter Richardson
    Date: 9/16/2023

    For the purpose of education

    This implementation is tested using NIST standards:
    Key = "c47b0294dbbbee0fec4757f22ffeee3587ca4730c3d33b691df38bab076bc558"
    IV = "00000000000000000000000000000000"
    Plaintext = "00000000000000000000000000000000"
    Expected Ciphertext = "46f2fb342d6f0ab477476fc501242c5fb1aad7f42738127aded5e41a344ef682"

    To use tested values uncomment masterkey and plaintext variables below
    and comment the respective above variables.

    This implementation also includes a debug for both encryption and 
    decryption. See header files for boolean debug (true = active).
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include <bits/stdc++.h>

#include "helper.h"
#include "KeySchedule.h"
#include "Encryption.h"
#include "Decryption.h"


// Function to convert a character to its hexadecimal representation
std::string StringToHex(unsigned char c) {
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    return ss.str();
}

int main()
{

    std::string masterKey = "c47b0294dbbbee0fec4757f22ffeee3587ca4730c3d33b691df38bab076bc558";    // COMMENT FOR DEBUG
    //std::string masterKey = "0000000000000000000000000000000000000000000000000000000000000000";  // UNCOMMENT FOR DEBUG

    Encryption encrypt;
    Decryption decrypt;
    KeySchedule key;
    key.run(masterKey);

    printExpandedKey(key.expandedKey);
    print3dArray(key.roundKey);

    // Read the plaintext from a file as binary data
    //std::ifstream f("plain.txt", std::ios::binary);  // COMMENT FOR DEBUG
    //std::vector<unsigned char> plaintext(std::istreambuf_iterator<char>(f), {});  // COMMENT FOR DEBUG
    std::vector<unsigned char> plaintext(16, 0x00);  // UNCOMMENT FOR DEBUG

    int elementsInLastBlock = 16 - (plaintext.size() % 16);
    unsigned char paddingValue = static_cast<unsigned char>(elementsInLastBlock);


    // Define the block size for AES (16 bytes for AES-128)
    const int blockSize = 16;
    std::vector<unsigned char> ciphertext;

    int numBlocks = (plaintext.size() + elementsInLastBlock) / 16;

    std::string encryptedPlaintext = "";
    // Loop through the plaintext in blocks
    for (int blockIndex = 0; blockIndex < numBlocks; blockIndex++) {
        // Create a 4x4 unsigned char array for the current block
        unsigned char encryptionBlock[4][4];

        // Fill the block with data from the plaintext
        for (int col = 0; col < 4; ++col) {
            for (int row = 0; row < 4; ++row) {
                //int index = col * 4 + row + i;
                int index = blockIndex * 16 + col * 4 + row;
                if (index < plaintext.size()) {
                    encryptionBlock[row][col] = plaintext[index];
                }
                else {
                    // pad remaining elements with num of padding need based on PKCS#7
                    encryptionBlock[row][col] = paddingValue;
                }
            }
        }

        // Perform encryption on the block using AES encryption function
        encryptedPlaintext += encrypt.run(encryptionBlock, key.roundKey);

        for (int col = 0; col < 4; ++col) 
        {
            for (int row = 0; row < 4; ++row) 
            {
                ciphertext.push_back(encryptionBlock[row][col]);
            }
        }
    }
    
    // Convert binary ciphertext to hexadecimal
    std::string hexCiphertext;
    for (unsigned char c : ciphertext) {
        hexCiphertext += StringToHex(c);
    }

    // Print the entire encrypted plaintext (hexadecimal)
    std::cout << "Encrypted Plaintext: " << hexCiphertext << std::endl;
    
    std::string decryptedCiphertext = "";
    std::vector<unsigned char> decryptedVectorCiphertext;

    for (int i = 0; i < ciphertext.size(); i += blockSize) {
        // Create a 4x4 block for decryption
        unsigned char decryptionBlock[4][4];

        // Fill the decryption block with data from the ciphertext vector
        for (int col = 0; col < 4; ++col) {
            for (int row = 0; row < 4; ++row) {
                int index = col * 4 + row + i;
                if (index < ciphertext.size()) {
                    decryptionBlock[row][col] = ciphertext[index];
                }
                else {
                    // If there are no more bytes, pad with zeros
                    decryptionBlock[row][col] = 0;
                }
            }
        }

        // Perform decryption on the decryptionBlock using AES decryption function
        decryptedCiphertext += decrypt.run(decryptionBlock, key.roundKey);

        for (int col = 0; col < 4; ++col)
        {
            for (int row = 0; row < 4; ++row)
            {
                decryptedVectorCiphertext.push_back(decryptionBlock[row][col]);
            }
        }
    }

    // Convert binary ciphertext to hexadecimal
    std::string hexPlaintext;
    for (unsigned char c : decryptedVectorCiphertext) {
        hexPlaintext += StringToHex(c);
    }

    // Print the entire decrypted ciphertext (hexadecimal)
    std::cout << "Hex Decrypted Ciphertext: " << hexPlaintext << std::endl;
    int lastPaddingHexToInt = stoi(hexPlaintext.substr(hexPlaintext.length() - 2), 0, 16);
    std::string hexPlaintextPaddingRemoved = hexPlaintext.erase(hexPlaintext.length() - lastPaddingHexToInt * 2);
    std::cout << "Hex Decrypted Ciphertext Without Padding: " << hexPlaintextPaddingRemoved << std::endl;

    // Print the entire decrypted ciphertext (ASCII)
    std::string asciiPlaintextPaddingRemoved = decryptedCiphertext.erase(decryptedCiphertext.length() - lastPaddingHexToInt);
    asciiPlaintextPaddingRemoved += "==END==";
    std::cout << "Decrypted Ciphertext: " << asciiPlaintextPaddingRemoved << std::endl;

    return 0;
}


