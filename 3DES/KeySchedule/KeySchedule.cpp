#include <iostream>
#include <string>

#include "KeySchedule.h"


// Function to shift a string left n times
std::string KeySchedule::shiftLeft(std::string keyHalf, int amount)
{
    std::string shifted = "";
    for (int i = 0; i < amount; i++)
    {
        for (int j = 1; j < 28; j++)
        {
            shifted += keyHalf[j];
        }
        shifted += keyHalf[0];
        keyHalf = shifted;
        shifted = "";
    }
    return keyHalf;
}

// Function to generate the 16 sub keys
void KeySchedule::generateKeySchedule(std::string key)
{

    // 1. Compressing our 64-bit key down to 56 bits
    std::string permutation1 = "";
    for (int i = 0; i < 56; i++) {
        permutation1 += key[PC1[i] - 1];
    }

    // 2. Split our key into two halves
    std::string left = permutation1.substr(0, 28);
    std::string right = permutation1.substr(28, 28);

    for (int i = 0; i < 16; i++)
    {
        // 3.1. Rounds 1, 2, 9, 16 are shifted left once
        if (i == 0 || i == 1 || i == 8 || i == 15)
        {
            left = shiftLeft(left, 1);
            right = shiftLeft(right, 1);
        }
        // 3.2. All other rounds are shifted left twice
        else
        {
            left = shiftLeft(left, 2);
            right = shiftLeft(right, 2);
        }

        // 4. Combine the two halves
        std::string combined = left + right;
        std::string permutation2 = "";

        // 5. Permute the two halves into 48-bit sub key i
        for (int j = 0; j < 48; j++) {
            permutation2 += combined[PC2[j] - 1];
        }

        tempKeyRounds[i] = permutation2;
    }
}

void KeySchedule::generateAllKeySchedules()
{

    // Generate K1 key schedule
    generateKeySchedule(key1);
    for (int i = 0; i < 16; i++)
    {
        keyRoundsK1[i] = tempKeyRounds[i];
        std::cout << "Key 1 round " << i << " :  " << keyRoundsK1[i] << std::endl;
    }
    std::cout << std::endl;
    // Generate K2 key schedule
    generateKeySchedule(key2);
    for (int i = 0; i < 16; i++)
    {
        keyRoundsK2[i] = tempKeyRounds[i];
        std::cout << "Key 2 round " << i << " :  " << keyRoundsK2[i] << std::endl;
    }
    std::cout << std::endl;
    // Generate K3 key schedule
    generateKeySchedule(key3);
    for (int i = 0; i < 16; i++)
    {
        keyRoundsK3[i] = tempKeyRounds[i];
        std::cout << "Key 3 round " << i << " :  " << keyRoundsK3[i] << std::endl;
    }
    std::cout << std::endl;
}
