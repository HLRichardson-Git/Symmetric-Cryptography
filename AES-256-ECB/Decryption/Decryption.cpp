
#include <iostream>
#include <iomanip>

#include "Decryption.h"

using namespace std;

std::string Decryption::run(unsigned char ciphertext[4][4], unsigned char roundKey[4][4][15])
{

    int round = 14;

    if (debug)
    {
        cout << "KEY" << endl;
        //print3dArray(roundKey);
        cout << "Initial block" << endl;
        print2dArray(ciphertext);
    }

    invAddRoundKey(round, ciphertext, roundKey);
    if (debug)
    {
        cout << "=== DECRYPTION ROUND: " << round << " ===" << endl;
        cout << "Inverse AddRoundKey" << endl;
        print2dArray(ciphertext);
    }

    invShiftRows(ciphertext);
    if (debug)
    {
        cout << "Inverse ShiftRows" << endl;
        print2dArray(ciphertext);
    }

    invSubByte(ciphertext);
    if (debug)
    {
        cout << "Inverse SubByte" << endl;
        print2dArray(ciphertext);
    }

    round--;

    while (round > 0)
    {
        invAddRoundKey(round, ciphertext, roundKey);
        if (debug)
        {
            cout << "=== DECRYPTION ROUND: " << round << " ===" << endl;
            cout << "Inverse AddRoundKey" << endl;
            print2dArray(ciphertext);
        }

        invMixColumns(ciphertext);
        if (debug)
        {
            cout << "Inverse MixColumns" << endl;
            print2dArray(ciphertext);
        }

        invShiftRows(ciphertext);
        if (debug)
        {
            cout << "Inverse ShiftRows" << endl;
            print2dArray(ciphertext);
        }

        invSubByte(ciphertext);
        if (debug)
        {
            cout << "Inverse SubByte" << endl;
            print2dArray(ciphertext);
        }

        round--;

    }

    invAddRoundKey(round, ciphertext, roundKey);
    if (debug)
    {
        cout << "=== DECRYPTION ROUND: " << round << " ===" << endl;
        cout << "Inverse AddRoundKey" << endl;
        print2dArray(ciphertext);
    }

    string plaintext = "";
    for (int col = 0; col < 4; ++col) {
        for (int row = 0; row < 4; ++row) {
            plaintext += ciphertext[row][col];
        }
    }

    return plaintext;

}

void Decryption::invSubByte(unsigned char ciphertext[4][4])
{

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            ciphertext[x][y] = help.InvsBox[ciphertext[x][y]];
        }
    }

}

void Decryption::invShiftRows(unsigned char ciphertext[4][4])
{

    int shift = 1;

    for (int x = 1; x < 4; x++)
    {
        int index = 1;

        while (index <= shift)
        {
            unsigned char last = ciphertext[x][3];

            for (int y = 3; y > 0; y--)
                ciphertext[x][y] = ciphertext[x][y - 1];

            index++;
            ciphertext[x][0] = last;
        }

        shift++;

    }

}

void Decryption::invMixColumns(unsigned char ciphertext[4][4])
{

    unsigned char temp[4] = { 0x00,0x00,0x00,0x00 };

    unsigned char newState[4][4] = { {0,0,0,0},
                                     {0,0,0,0},
                                     {0,0,0,0},
                                     {0,0,0,0} };

    int rijndaelMatric[4][4] = { {14,11,13,9},
                                 {9,14,11,13},
                                 {13,9,14,11},
                                 {11,13,9,14} };

    for (int y = 0; y < 4; y++)
    {
        int z = 0;
        for (int i = 0; i < 4; i++)
        {
            temp[i] = 0x00;
        }
        for (int x = 0; x < 4; x++)
        {
            for (int j = 0; j < 4; j++)
            {
                unsigned char constant = 0x00;
                unsigned char element = 0x00;
                switch (rijndaelMatric[z][j])
                {
                case 9:
                    element = ciphertext[j][y];
                    temp[j] = (multiplyBy2(multiplyBy2(multiplyBy2(element)))) ^ element;
                    break;
                case 11:
                    element = ciphertext[j][y];
                    temp[j] = (multiplyBy2(multiplyBy2(multiplyBy2(element)) ^ element)) ^ element;
                    break;
                case 13:
                    element = ciphertext[j][y];
                    temp[j] = multiplyBy2(multiplyBy2(multiplyBy2(element) ^ element)) ^ element;
                    break;
                case 14:
                    element = ciphertext[j][y];
                    temp[j] = multiplyBy2((multiplyBy2(multiplyBy2(element) ^ element)) ^ element);
                    break;
                }

            }
            newState[x][y] = int(temp[0]) ^ int(temp[1]) ^ int(temp[2]) ^ int(temp[3]);
            z++;
        }

    }

    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            ciphertext[x][y] = newState[x][y];
        }
    }

}

void Decryption::invAddRoundKey(int round, unsigned char ciphertext[4][4], unsigned char roundKey[4][4][15])
{

    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            ciphertext[x][y] = ciphertext[x][y] ^ roundKey[x][y][round];
        }
    }

}