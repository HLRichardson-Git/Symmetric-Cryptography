/*
    By: Hunter Richardson
    Data: 7/23/2023

    For the purpose of education
*/

#include <iostream>
#include <cmath>
#include <string>
#include <bits/stdc++.h>

#include "KeySchedule.h";
#include "DES.h";

const std::string Plaintext = "0111001101110100011000010110111001100100011000010111001001100100";

const std::string checkEncryption = "1010001100101010111010001101011110111100011001110001100001111111";

int main()
{

    KeySchedule Key;
    Key.generateKeySchedule();
    
    std::cout << "Plaintext:  " << Plaintext << std::endl;

    std::string ciphertext = DES::algorithm(true, Plaintext, Key.keyRounds);
    std::cout << "Ciphertext: " << ciphertext;
    if (ciphertext != checkEncryption)
        std::cout << "    |  ERROR: Encryption failed." << std::endl;
    else
        std::cout << std::endl;

    std::string decryptedText = DES::algorithm(false, ciphertext, Key.keyRounds);
    std::cout << "Decryption: " << decryptedText;
    if (Plaintext != decryptedText)
        std::cout << "    |  ERROR: Decryption failed." << std::endl;
    else
        std::cout << std::endl;

}

