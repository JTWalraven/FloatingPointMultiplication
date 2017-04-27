#include "Float32.hpp"

void Float32::setSign(const bool sign) {
	(*this)[FLOAT32_SIGN_POS] = sign;
}

void Float32::setExponent(const bitset<FLOAT32_EXPONENT_LENGTH>& exponent) {
	for (int i = 0; i < FLOAT32_EXPONENT_LENGTH; i++) {
		(*this)[FLOAT32_EXPONENT_POS + i] = exponent[i];
	}
}

void Float32::setFraction(const bitset<FLOAT32_FRACTION_LENGTH>& fraction) {
	for (int i = 0; i < FLOAT32_FRACTION_LENGTH; i++) {
		(*this)[FLOAT32_FRACTION_POS + i] = fraction[i];
	}
}

bool Float32::getSign() const {
	return (*this)[FLOAT32_SIGN_POS];
}

bool Float32::isPositive() const {
	return !getSign();
}

bitset<FLOAT32_EXPONENT_LENGTH> Float32::getExponent() const {
	bitset<FLOAT32_EXPONENT_LENGTH> exponent;
	for (int i = 0; i < FLOAT32_EXPONENT_LENGTH; i++) {
		exponent[i] = (*this)[FLOAT32_EXPONENT_POS + i];
	}
	return exponent;
}

bitset<FLOAT32_FRACTION_LENGTH> Float32::getFraction() const {
	bitset<FLOAT32_FRACTION_LENGTH> fraction;
	for (int i = 0; i < FLOAT32_FRACTION_LENGTH; i++) {
		fraction[i] = (*this)[FLOAT32_FRACTION_POS + i];
	}
	return fraction;
}

// Overload the multiplication operator
inline Float32 operator*(Float32 leftFloat, const Float32& rightFloat)
{
	// Add exponents
	bitset<FLOAT32_EXPONENT_LENGTH> exponent;
	exponent = BitsetMath::addBitset(leftFloat.getExponent(), rightFloat.getExponent());

	// Subtract bias
	bool negative = false;
	exponent = BitsetMath::subtractBitset(exponent, bitset<FLOAT32_EXPONENT_LENGTH>{127}, negative);

	// Multiply significands
	bitset<FLOAT32_FRACTION_LENGTH> fraction;
	fraction = BitsetMath::multiplyBitset(leftFloat.getFraction(), rightFloat.getFraction());

	// Normalize the float


	return leftFloat;
}
