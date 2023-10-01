#pragma once

#include <string>

#include "helper.h"

class KeySchedule
{
public:
	
	unsigned char roundKey[4][4][11];

	void run(std::string masterKey);

private:
	Help help;

	unsigned char RCon[10] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36 };

	void rotWord(unsigned char temp[4], int round);
	void subWord(unsigned char temp[4], int round);
	void rcon(unsigned char temp[4], int round);

};
