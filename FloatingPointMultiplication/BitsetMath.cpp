#include "BitsetMath.hpp"

bool BitsetMath::addBits(bool b1, bool b2, bool& carry) {
	// Calculate the sum
	bool sum = (b1 ^ b2) ^ carry;

	// Calculate the carry bit
	carry = (b1 && b2) || (b1 && carry) || (b2 && carry);

	return sum;
}

