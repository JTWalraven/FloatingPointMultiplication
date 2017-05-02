#include "Float32.hpp"

void Float32::setSign(const bool sign) {
	(*this)[FLOAT32_SIGN_POS] = sign;
}

void Float32::setExponent(const bitset<FLOAT32_EXPONENT_LENGTH>& exponent) {
	for (int i = 0; i < FLOAT32_EXPONENT_LENGTH; i++) {
		(*this)[FLOAT32_EXPONENT_POS + i] = exponent[(FLOAT32_EXPONENT_LENGTH - 1) - i];
	}
}

void Float32::setSignificand(const bitset<FLOAT32_SIGNIFICAND_LENGTH>& fraction) {
	for (int i = 0; i < FLOAT32_SIGNIFICAND_LENGTH; i++) {
		(*this)[FLOAT32_SIGNIFICAND_POS + i] = fraction[(FLOAT32_SIGNIFICAND_LENGTH - 1) - i];
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

bitset<FLOAT32_SIGNIFICAND_LENGTH> Float32::getSignificand() const {
	bitset<FLOAT32_SIGNIFICAND_LENGTH> result;
	for (int i = 0; i < FLOAT32_SIGNIFICAND_LENGTH; i++) {
		result[i] = (*this)[FLOAT32_SIGNIFICAND_POS + i];
	}
	return result;
}

Float32 Float32::operator*(Float32 num) {
	Float32 result;

	// Set the sign
	result.setSign(this->getSign() != num.getSign());

	// Add exponents
	unsigned int exponent = (int)this->getExponent().to_ulong() + (int)num.getExponent().to_ulong();

	// Subtract the bias
	if (exponent > 0)
		exponent -= 127;

	// Set the resulting exponent
	result.setExponent(bitset<FLOAT32_EXPONENT_LENGTH>{exponent});

	// Multiply significands
	bitset<FLOAT32_SIGNIFICAND_LENGTH> sig1 = this->getSignificand();
	bitset<FLOAT32_SIGNIFICAND_LENGTH> sig2 = num.getSignificand();
	sig2[FLOAT32_SIGNIFICAND_POS] = 1;
	result.setSignificand(BitsetMath::multiplyBitset(sig1, sig2));

	// Round the float
	// If the last digit is a one, add one

	return result;
}

float Float32::getFloat() const {
	// Copy the binary to a float using a pointer cast
	bitset<FLOAT32_LENGTH> f = (*this);
	return * reinterpret_cast<float*>(&f);
}

string Float32::getHex() const {
	stringstream result;

	// Get the float
	float fl = this->getFloat();

	// Print out the result to a sstream
	result << hex << *((int*)&fl);

	return result.str();
}

string Float32::getDecimal() const {
	stringstream result;

	cout << *this << endl;

	// Print out the scientific result to a sstream
	result << scientific << this->getFloat();

	return result.str();
}

