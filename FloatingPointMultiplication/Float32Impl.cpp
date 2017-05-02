#include "Float32.hpp"

void Float32::setSign(const bool sign) {
	(*this)[FLOAT32_SIGN_POS] = sign;
}

void Float32::setExponent(const bitset<FLOAT32_EXPONENT_LENGTH>& exponent) {
	for (int i = 0; i < FLOAT32_EXPONENT_LENGTH; i++) {
		(*this)[FLOAT32_EXPONENT_POS + i] = exponent[i];
	}
}

void Float32::setSignificand(const bitset<FLOAT32_SIGNIFICAND_LENGTH>& fraction) {
	for (int i = 0; i < FLOAT32_SIGNIFICAND_LENGTH; i++) {
		(*this)[FLOAT32_SIGNIFICAND_POS + i] = fraction[i];
	}
}

void Float32::setReverseExponent(const bitset<FLOAT32_EXPONENT_LENGTH>& exponent) {
	for (int i = 0; i < FLOAT32_EXPONENT_LENGTH; i++) {
		(*this)[FLOAT32_EXPONENT_POS + i] = exponent[(FLOAT32_EXPONENT_LENGTH - 1) - i];
	}
}

void Float32::setReverseSignificand(const bitset<FLOAT32_SIGNIFICAND_LENGTH>& fraction) {
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
	if (exponent == 0) exponent = 127;	// Set to 127 if the exponent is 0

	// Check for underflow or overflow
	if (exponent < 127) 
		throw std::underflow_error("Underflow on exponent.");
	else if (exponent > 381) 
		throw std::overflow_error("Overflow on exponent.");

	// Subtract the bias
	exponent -= 127;

	// Set the resulting exponent
	result.setExponent(bitset<FLOAT32_EXPONENT_LENGTH>{exponent});

	/*bitset<FLOAT32_SIGNIFICAND_LENGTH> significand = this->getSignificand();
	significand <<= 1;	// Shift the bitset right
	significand[0] = 1;	// Set the 1 on the bitset
	bitset<FLOAT32_SIGNIFICAND_LENGTH> significand2 = num.getSignificand();
	significand2 <<= 1;	// Shift the bitset right
	significand2[0] = 1;	// Set the 1 on the bitset*/
	bitset<FLOAT32_SIGNIFICAND_LENGTH> sig1 = this->getSignificand();
	bitset<FLOAT32_SIGNIFICAND_LENGTH> sig2 = num.getSignificand();
	sig2 >>= 1;
	sig2[0] = 1;

	// Multiply significands
	result.setSignificand(BitsetMath::multiplyBitset(sig1, sig2));

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

