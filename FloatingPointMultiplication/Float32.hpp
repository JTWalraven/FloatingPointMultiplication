#ifndef FLOAT32
#define FLOAT32

#define FLOAT32_SIGN_POS 0
#define FLOAT32_SIGN_LENGTH 1
#define FLOAT32_EXPONENT_POS 1
#define FLOAT32_EXPONENT_LENGTH 8
#define FLOAT32_FRACTION_POS 9
#define FLOAT32_FRACTION_LENGTH 23

#include <bitset>
#include <iostream>
#include "BitsetMath.hpp"
using namespace std;

class Float32 : public bitset<32> {
public:
	void setSign(const bool sign);

	void setExponent(const bitset<FLOAT32_EXPONENT_LENGTH>& exponent);

	void setFraction(const bitset<FLOAT32_FRACTION_LENGTH>& fraction);

	bool getSign() const;

	bool isPositive() const;

	bitset<FLOAT32_EXPONENT_LENGTH> getExponent() const;

	bitset<FLOAT32_FRACTION_LENGTH> getFraction() const;

	Float32 operator*(Float32);

	void printDecimal() const;

};

#endif // !FLOAT32