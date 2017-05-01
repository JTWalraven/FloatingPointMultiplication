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
	sig2[0] = 1;
	result.setSignificand(BitsetMath::multiplyBitset(sig1, sig2));

	// Round the float

	return result;
}

string Float32::getHex() const {
	stringstream result;
	result << hex << uppercase << (*this).to_ulong();
	return result.str();
}

string Float32::getDecimal() const {
	stringstream result;

	cout << (*this) << endl;

	// Print out the sign
	if (!this->isPositive())
		result << "-";

	// Get exponent
	int exponent = (int)(this->getExponent().to_ulong()) - 127;

	// De-Normalize the number
	bitset<FLOAT32_SIGNIFICAND_LENGTH> whole;
	if (exponent < FLOAT32_SIGNIFICAND_LENGTH) {
		whole = BitsetMath::shiftRight(this->getSignificand(), FLOAT32_SIGNIFICAND_LENGTH - exponent);
	}
	else {
		whole = BitsetMath::shiftRight(this->getSignificand(), FLOAT32_SIGNIFICAND_LENGTH);
	}
	if (exponent >= 0 && exponent < FLOAT32_SIGNIFICAND_LENGTH) whole[exponent] = 1;
	int wholeNumber = (int)(whole.to_ulong());

	result << wholeNumber;

	// Print out the radix
	result << ".";

	bitset<FLOAT32_SIGNIFICAND_LENGTH> significand;
	significand = BitsetMath::shiftLeft(this->getSignificand(), 0);
	const int percision = 10;
	long long significandInt = 0;
	for (int i = percision; i > 0; i--) {
		significandInt += significand[i] * pow(5, i) * pow(10, percision - i);
	}

	result << setfill('0') << setw(6) << significandInt;

	result << "e" << exponent;


	// Print out the fraction

	// Print out the exponent
	return result.str();
}

