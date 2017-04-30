#include "Float32.hpp"

void Float32::setSign(const bool sign) {
	(*this)[FLOAT32_SIGN_POS] = sign;
}

void Float32::setExponent(const bitset<FLOAT32_EXPONENT_LENGTH>& exponent) {
	for (int i = 0; i < FLOAT32_EXPONENT_LENGTH; i++) {
		(*this)[FLOAT32_EXPONENT_POS + i] = exponent[(FLOAT32_EXPONENT_LENGTH - 1) - i];
	}
}

void Float32::setFraction(const bitset<FLOAT32_FRACTION_LENGTH>& fraction) {
	for (int i = 0; i < FLOAT32_FRACTION_LENGTH; i++) {
		(*this)[FLOAT32_FRACTION_POS + i] = fraction[(FLOAT32_FRACTION_LENGTH - 1) - i];
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

Float32 Float32::operator*(Float32 num) {
	// Add exponents
	bitset<FLOAT32_EXPONENT_LENGTH> exponent;
	//exponent = BitsetMath::addBitset(this->getExponent(), num.getExponent());
	exponent = BitsetMath::addBitset(bitset<8>{5}, bitset<8>{5});

	// Subtract bias
	bool negativeExp = false;
	exponent = BitsetMath::subtractBitset(exponent, bitset<FLOAT32_EXPONENT_LENGTH>{127}, negativeExp);

	// Multiply significands
	bitset<FLOAT32_FRACTION_LENGTH> fraction;
	fraction = BitsetMath::multiplyBitset(this->getFraction(), num.getFraction());

	// Normalize the float
	int intExponent = (int)(exponent.to_ulong());
	if (negativeExp) { // Check which direction to shift
		// Shift left by the exponent
		fraction = BitsetMath::shiftLeft(fraction, intExponent);
	}
	else {
		// Shift right by the exponent
		fraction = BitsetMath::shiftRight(fraction, intExponent);
	}

	// Round the float

	return (*this);
}

void Float32::printDecimal() const {
	cout << "Hello" << endl;
}

