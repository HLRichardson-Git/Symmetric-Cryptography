
#include <iostream>
#include <iomanip>

#include "Encryption.h"

using namespace std;

std::string Encryption::run(unsigned char plaintext[4][4], unsigned char roundKey[4][4][13])
{

	if (debug)
	{
		//print3dArray(roundKey);
	}

	int round = 0;

	if (debug)
	{
		print2dArray(plaintext);
	}
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			plaintext[x][y] = plaintext[x][y] ^ roundKey[x][y][0];
		}
	}
	round++;

	if (debug)
	{
		print2dArray(plaintext);
	}
	while (round < 12)
	{
		
		subByte(plaintext);
		if (debug)
		{
			cout << "=== ENCRYPTION ROUND: " << round << " ===" << endl;
			cout << "SubByte" << endl;
			print2dArray(plaintext);
		}

		shiftRows(plaintext);
		if (debug)
		{
			cout << "ShiftRows" << endl;
			print2dArray(plaintext);
		}

		mixColumns(plaintext);
		if (debug)
		{
			cout << "MixColumns" << endl;
			print2dArray(plaintext);
		}

		addRoundKey(round, plaintext, roundKey);
		if (debug)
		{
			cout << "AddRoundKey" << endl;
			print2dArray(plaintext);
		}
		round++;

	}

	subByte(plaintext);
	if (debug)
	{
		cout << "=== ENCRYPTION ROUND: " << round << " ===" << endl;
		cout << "SubByte" << endl;
		print2dArray(plaintext);
	}

	shiftRows(plaintext);
	if (debug)
	{
		cout << "ShiftRows" << endl;
		print2dArray(plaintext);
	}

	addRoundKey(round, plaintext, roundKey);
	if (debug)
	{
		cout << "AddRoundKey" << endl;
		print2dArray(plaintext);
	}

	string ciphertext = "";
	for (int col = 0; col < 4; ++col) {
		for (int row = 0; row < 4; ++row) {
			ciphertext += plaintext[row][col];
		}
	}

	return ciphertext;
}

void Encryption::subByte(unsigned char plaintext[4][4])
{

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			plaintext[x][y] = help.sBox[plaintext[x][y]];
		}
	}

}

void Encryption::shiftRows(unsigned char plaintext[4][4])
{

	int shift = 1;

	for (int x = 1; x < 4; x++)
	{
		int index = 1;

		while (index <= shift)
		{
			unsigned char first = plaintext[x][0];

			for (int y = 0; y < 3; y++)
				plaintext[x][y] = plaintext[x][y + 1];

			index++;
			plaintext[x][3] = first;
		}

		shift++;

	}

}

void Encryption::mixColumns(unsigned char plaintext[4][4])
{

	unsigned char temp[4] = { 0x00,0x00,0x00,0x00 };

	unsigned char newState[4][4] = { {0,0,0,0},
									 {0,0,0,0},
									 {0,0,0,0},
									 {0,0,0,0} };

	int rijndaelMatric[4][4] = { {2,3,1,1},
								 {1,2,3,1},
								 {1,1,2,3},
								 {3,1,1,2} };

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
				case 1:
					temp[j] = plaintext[j][y];
					break;
				case 2:
					element = plaintext[j][y];
					temp[j] = multiplyBy2(element);
					break;
				case 3:
					element = plaintext[j][y];
					temp[j] = multiplyBy2(element) ^ element;
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
			plaintext[x][y] = newState[x][y];
		}
	}

}

void Encryption::addRoundKey(int round, unsigned char plaintext[4][4], unsigned char roundKey[4][4][13])
{

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			plaintext[x][y] = plaintext[x][y] ^ roundKey[x][y][round];
		}
	}

}
