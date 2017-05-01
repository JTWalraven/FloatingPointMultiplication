#ifndef FLOAT32
#define FLOAT32

#define FLOAT32_LENGTH 32
#define FLOAT32_SIGN_POS 0
#define FLOAT32_SIGN_LENGTH 1
#define FLOAT32_EXPONENT_POS 1
#define FLOAT32_EXPONENT_LENGTH 8
#define FLOAT32_SIGNIFICAND_POS 9
#define FLOAT32_SIGNIFICAND_LENGTH 23

#include <bitset>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "BitsetMath.hpp"
using namespace std;

class Float32 : public bitset<32> {
public:
	void setSign(const bool sign);

	void setExponent(const bitset<FLOAT32_EXPONENT_LENGTH>&);

	void setSignificand(const bitset<FLOAT32_SIGNIFICAND_LENGTH>&);

	bool getSign() const;

	bool isPositive() const;

	bitset<FLOAT32_EXPONENT_LENGTH> getExponent() const;

	bitset<FLOAT32_SIGNIFICAND_LENGTH> getSignificand() const;

	Float32 operator*(Float32);

	string getHex() const;

	string getDecimal() const;

};

#endif // !FLOAT32