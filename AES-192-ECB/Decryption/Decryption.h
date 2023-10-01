#pragma once

#include "KeySchedule.h"
#include "helper.h"

class Decryption
{
public:

	std::string run(unsigned char ciphertext[4][4], unsigned char roundKey[4][4][13]);

private:

	Help help;

	bool debug = false; // BOOL DEBUG ACTIVE

	void invSubByte(unsigned char ciphertext[4][4]);
	void invShiftRows(unsigned char ciphertext[4][4]);
	void invMixColumns(unsigned char ciphertext[4][4]);
	void invAddRoundKey(int round, unsigned char ciphertext[4][4], unsigned char roundKey[4][4][13]);

};
