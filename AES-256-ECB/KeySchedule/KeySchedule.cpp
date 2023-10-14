#include <iostream>
#include <iomanip>
#include  <bits/stdc++.h>
using namespace std;
//DELETE ABOVE THIS IS ONLY FOR PRINTING FOR TESTING!!!!

#include "KeySchedule.h"


void KeySchedule::run(std::string masterKey)
{

    int round = 0;

    while (round < 7)
    {
        if (round == 0)
        {
            for (int x = 0; x < 4; x++)
            {
                for (int y = 0; y < 8; y++)
                {
                    
                    // Calculate the index in the string for the current element
                    int index = x * 2 + y * 8;

                    // Extract two hexadecimal characters
                    std::string hexByte = masterKey.substr(index, 2);

                    // Convert the hexadecimal string to an unsigned char
                    expandedKey[x][y][0] = static_cast<unsigned char>(std::stoi(hexByte, nullptr, 16));
                }
            }
        }

        unsigned char temp[4] = { 0x00, 0x00, 0x00, 0x00 };

        if (round == 0)
        {
            temp[0] = expandedKey[0][7][0];
            temp[1] = expandedKey[1][7][0];
            temp[2] = expandedKey[2][7][0];
            temp[3] = expandedKey[3][7][0];
        }
        else
        {
            temp[0] = expandedKey[0][7][round];
            temp[1] = expandedKey[1][7][round];
            temp[2] = expandedKey[2][7][round];
            temp[3] = expandedKey[3][7][round];
        }

        rotWord(temp, round);
        subWord(temp, round);
        rcon(temp, round);

        round++;

        for (int x = 0; x < 4; x++)
        {
            expandedKey[x][0][round] = temp[x] ^ expandedKey[x][0][round - 1];
        }

        for (int y = 1; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                expandedKey[x][y][round] = expandedKey[x][y][round - 1] ^ expandedKey[x][y - 1][round];
            }
        }

        temp[0] = expandedKey[0][3][round];
        temp[1] = expandedKey[1][3][round];
        temp[2] = expandedKey[2][3][round];
        temp[3] = expandedKey[3][3][round];

        subWord(temp, round);

        for (int x = 0; x < 4; x++)
        {
            expandedKey[x][4][round] = temp[x] ^ expandedKey[x][4][round - 1];
        }

        for (int y = 5; y < 8; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                expandedKey[x][y][round] = expandedKey[x][y][round - 1] ^ expandedKey[x][y - 1][round];
            }
        }
    }

    int formatRound = 0;
        int col = 0;
        int counter = 0;

        // Iterate through rows and columns of the 4x6x9 array
        for (int j = 0; j < 8; j++) {
            for (int i = 0; i < 8; i++) {
                for (int row = 0; row < 4; row++) {
                    counter++;
                    if (counter > 240) break;
                    // Copy the value from the 4x6x9 array to the reformatted array
                    roundKey[row][col][formatRound] = expandedKey[row][i][j];
                }
                // Increment the column counter
                col++;

                // When the column reaches 4, reset it to 0
                if (col == 4) {
                    col = 0;
                    formatRound++;
                }
            }
            if (formatRound > 14) {
                break;
            }
        }
}

void KeySchedule::rotWord(unsigned char temp[4], int round)
{

    unsigned char temp2 = temp[0];
    for (int x = 0; x < 4; x++)
    {
        temp[x] = temp[x + 1];
    }
    temp[3] = temp2;

}

void KeySchedule::subWord(unsigned char temp[4], int round)
{

    for (int x = 0; x < 4; x++)
    {
        temp[x] = help.sBox[temp[x]];
    }

}

void KeySchedule::rcon(unsigned char temp[4], int round)
{

    temp[0] = temp[0] ^ RCon[round];

}