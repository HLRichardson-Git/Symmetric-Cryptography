/*
    By: Hunter Richardson
    Date: 7/23/2023

    For the purpose of education
*/

#include <iostream>
#include <cmath>
#include <string>
#include <bits/stdc++.h>

#include "KeySchedule.h"
#include "DES.h"

const std::string Plaintext = "1010101111001101111001101010101111001101000100110010010100110110";

const std::string checkEncryption = "1001111000100110100111110101101011111010010011011011101101110000";

int main()
{

    KeySchedule Key;
    Key.generateKeySchedule();
    
    std::cout << "Plaintext:  " << Plaintext << std::endl;

    std::string ciphertext = DES::algorithm(true, Plaintext, Key.keyRounds);
    std::cout << "Ciphertext: " << ciphertext;
    if (ciphertext != checkEncryption)
        std::cout << "    |  ERROR: Encryption check failed, either changed key or plaintext." << std::endl;
    else
        std::cout << std::endl;

    std::string decryptedText = DES::algorithm(false, ciphertext, Key.keyRounds);
    std::cout << "Decryption: " << decryptedText;
    if (Plaintext != decryptedText)
        std::cout << "    |  ERROR: Decryption failed." << std::endl;
    else
        std::cout << std::endl;

}


