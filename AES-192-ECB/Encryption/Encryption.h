#pragma once

#include "KeySchedule.h"
#include "helper.h"

class Encryption
{
public:

	std::string run(unsigned char plaintext[4][4], unsigned char roundKey[4][4][13]);

private:

	Help help;

	bool debug = false; // BOOL DEBUG ACTIVE

	void subByte(unsigned char plaintext[4][4]);
	void shiftRows(unsigned char plaintext[4][4]);
	void mixColumns(unsigned char plaintext[4][4]);
	void addRoundKey(int round, unsigned char plaintext[4][4], unsigned char roundKey[4][4][13]);

};
