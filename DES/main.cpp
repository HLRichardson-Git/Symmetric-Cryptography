/*
    By: Hunter Richardson
    Date: 9/1/2023

    For the purpose of education
*/

#include <iostream>
#include <cmath>
#include <string>
#include <bits/stdc++.h>

#include <chrono>

#include "KeySchedule.h"
#include "DES.h"

using namespace std::chrono;

std::string TextToBinaryString(std::string words) {
    std::string binaryString = "";
    for (char& _char : words) {
        binaryString += std::bitset<8>(_char).to_string();
    }
    return binaryString;
}

int binaryToDecimal(std::string n)
{
    std::string num = n;

    // Stores the decimal value
    int dec_value = 0;

    // Initializing base value to 1
    int base = 1;

    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {

        // If the current bit is 1
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }

    // Return answer
    return dec_value;
}

std::string setStringtoASCII(std::string str)
{
    // To store size of s
    int N = int(str.size());

    // If given string is not a
    // valid string
    if (N % 8 != 0) {
        return "Not Possible!";
    }

    // To store final answer
    std::string res = "";

    // Loop to iterate through string
    for (int i = 0; i < N; i += 8) {
        int decimal_value = binaryToDecimal((str.substr(i, 8)));

        // Apprend the ASCII character
        // equivalent to current value
        res += char(decimal_value);
    }

    // Return Answer
    return res;
}


int main()
{
    // Generate full key schedule
    KeySchedule Key;
    Key.generateKeySchedule();
    
    std::fstream f("plain.txt", std::fstream::in);
    std::string s{ std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>() };
    f.close();

    std::string plaintextBinary = TextToBinaryString(s);

    int plaintextLength = plaintextBinary.length();
    int numberOfBlocks = ceil((float)plaintextLength / 64); // Use ceil to account for padding.

    int padding = 0;
    if (plaintextLength % 64 != 0)
    {
        padding = 64 - (plaintextLength % 64); // Calculate the required padding.
    }

    // Add padding if needed
    for (int i = 0; i < padding; i++)
    {
        plaintextBinary += '0';
    }

    auto start = high_resolution_clock::now();

    std::string ciphertext = "";
    for (int i = 0; i < numberOfBlocks; i++)
    {
        std::string plainBlock = plaintextBinary.substr(i * 64, 64);
        std::string cipherBlock = DES::algorithm(true, plainBlock, Key.keyRounds);
        ciphertext.append(cipherBlock);
    }
    
    std::cout << "Ciphertext: " << ciphertext << std::endl;

    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    std::cout << "Time taken to encrypt: " << duration.count() << " microseconds" << std::endl;

    start = high_resolution_clock::now();

    std::string decryptedCiphertext = "";
    for (int i = 0; i < numberOfBlocks; i++)
    {
        std::string cipherBlock = ciphertext.substr(i * 64, 64);
        std::string plainBlock = DES::algorithm(false, cipherBlock, Key.keyRounds);
        decryptedCiphertext.append(plainBlock);
    }

    std::string test = setStringtoASCII(decryptedCiphertext);
    std::cout << "Plaintext: " << test << std::endl;

    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    std::cout << "Time taken to decrypt: " << duration.count() << " microseconds" << std::endl;

    if (decryptedCiphertext == plaintextBinary)
        std::cout << "SUCCESS: Decryption completed succesfully!" << std::endl;
    else
        std::cout << "FAILED: Decryption failed!" << std::endl;

    return 0;
}




