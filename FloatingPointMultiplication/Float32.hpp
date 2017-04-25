#ifndef FLOAT32
#define FLOAT32

#define FLOAT32_SIGN_POS 0
#define FLOAT32_SIGN_LENGTH 1
#define FLOAT32_EXPONENT_POS 1
#define FLOAT32_EXPONENT_LENGTH 8
#define FLOAT32_FRACTION_POS 9
#define FLOAT32_FRACTION_LENGTH 23

#include <bitset>
#include "BitsetMath.hpp"
using namespace std;

class Float32 : public bitset<32> {
public:
	void setSign(const bool sign) {
		(*this)[FLOAT32_SIGN_POS] = sign;
	}

	void setExponent(const bitset<FLOAT32_EXPONENT_LENGTH>& exponent) {
		for (int i = 0; i < FLOAT32_EXPONENT_LENGTH; i++) {
			(*this)[FLOAT32_EXPONENT_POS + i] = exponent[i];
		}
	}

	void setFraction(const bitset<FLOAT32_FRACTION_LENGTH>& fraction) {
		for (int i = 0; i < FLOAT32_FRACTION_LENGTH; i++) {
			(*this)[FLOAT32_FRACTION_POS + i] = fraction[i];
		}
	}

	bool getSign() {
		return (*this)[FLOAT32_SIGN_POS];
	}

	bool isPositive() {
		return !getSign();
	}

	bitset<FLOAT32_EXPONENT_LENGTH> getExponent() const;
	bitset<FLOAT32_EXPONENT_LENGTH> const getExponent() {
		bitset<FLOAT32_EXPONENT_LENGTH> exponent;
		for (int i = 0; i < FLOAT32_EXPONENT_LENGTH; i++) {
			exponent[i] = (*this)[FLOAT32_EXPONENT_POS + i];
		}
		return exponent;
	}

	bitset<FLOAT32_FRACTION_LENGTH> getFraction() const;
	bitset<FLOAT32_FRACTION_LENGTH> getFraction() {
		bitset<FLOAT32_FRACTION_LENGTH> fraction;
		for (int i = 0; i < FLOAT32_FRACTION_LENGTH; i++) {
			fraction[i] = (*this)[FLOAT32_FRACTION_POS + i];
		}
		return fraction;
	}
};

// Overload the multiplication operator
inline Float32 operator*(Float32 lhs, const Float32& rhs)
{
	// Add exponents
	bitset<FLOAT32_EXPONENT_LENGTH> exponent;
	exponent = BitsetMath::addBitset(lhs.getExponent(), rhs.getExponent());

	// Subtract bias
	bool negative = false;
	exponent = BitsetMath::subtractBitset(exponent, bitset<FLOAT32_EXPONENT_LENGTH>{127}, negative);

	// Multiply significands
	bitset<FLOAT32_FRACTION_LENGTH> fraction;
	fraction = BitsetMath::multiplyBitset(lhs.getFraction(), rhs.getFraction());

	return lhs;
}
#endif // !FLOAT32