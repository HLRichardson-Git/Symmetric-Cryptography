#pragma once


class KeySchedule
{
public:

    const int PC1[56] = { 57, 49, 41, 33, 25, 17, 9, 1,
                     58, 50, 42, 34, 26, 18, 10, 2,
                     59, 51, 43, 35, 27, 19, 11, 3,
                     60, 52, 44, 36, 63, 55, 47, 39,
                     31, 23, 15, 7, 62, 54, 46, 38,
                     30, 22, 14, 6, 61, 53, 45, 37,
                     29, 21, 13, 5, 28, 20, 12, 4 };

    const int PC2[48] = { 14, 17, 11, 24, 1, 5, 3, 28,
                          15, 6, 21, 10, 23, 19, 12, 4,
                          26, 8, 16, 7, 27, 20, 13, 2,
                          41, 52, 31, 37, 47, 55, 30, 40,
                          51, 45, 33, 48, 44, 49, 39, 56,
                          34, 53, 46, 42, 50, 36, 29, 32 };

	std::string tempKeyRounds[16];

    std::string keyRoundsK1[16];
    std::string keyRoundsK2[16];
    std::string keyRoundsK3[16];

	std::string shiftLeft(std::string keyHalf, int amount);
	void generateKeySchedule(std::string key);
    void generateAllKeySchedules();

private:

    const std::string key1 = "000010000011111100001001000011001110111011001100111000111000011";
    const std::string key2 = "011110101100001000010110010011101111010100000000000001111001000";
    const std::string key3 = "100110010010010010001100001000011110100111010101011001011100000";

};

