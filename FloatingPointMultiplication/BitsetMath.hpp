#ifndef BITSET_MATH
#define BITSET_MATH

#include <bitset>
using namespace std;

class BitsetMath {
public:
	static bool addBits(bool b1, bool b2, bool& carry);

	template<unsigned int N>
	static bitset<N> addBitset(const bitset<N>& l, const bitset<N>& r);

	template<unsigned int N>
	static bitset<N> complimentBitset(const bitset<N>& num);

	template<unsigned int N>
	static bitset<N> subtractBitset(const bitset<N>& l, const bitset<N>& r, bool &negative);

	template<unsigned int N>
	static bitset<N> shiftLeft(const bitset<N>& num, int shifts);

	template<unsigned int N>
	static bitset<N> shiftRight(const bitset<N>& num, int shifts);

	template<unsigned int N>
	static bitset<N> multiplyBitset(const bitset<N>& l, const bitset<N>& r);
};

template<unsigned int N>
bitset<N> BitsetMath::addBitset(const bitset<N>& l, const bitset<N>& r) {
	bitset<N> sum;
	bool carry = false;

	// Add the bits
	for (int i = 0; i < N; i++) {
		sum[i] = addBits(l[i], r[i], carry);
	}

	// Overflow
	if (carry) throw std::overflow_error("Overflow on bitset addition.");

	return sum;
}

template<unsigned int N>
bitset<N> BitsetMath::complimentBitset(const bitset<N>& num) {
	bitset<N> compliment;
	for (int i = 0; i < N; i++) {
		// Invert bit
		compliment[i] = !(num[i]);
	}
	return compliment;
}

template<unsigned int N>
bitset<N> BitsetMath::subtractBitset(const bitset<N>& l, const bitset<N>& r, bool &negative) {
	bool carry = false;
	bitset<N> difference;

	// Obtain two's compliment
	bitset<N> twosCompliment = addBitset(complimentBitset(l), bitset<N>{1});

	// Add the bits
	for (int i = 0; i < N; i++) {
		difference[i] = addBits(twosCompliment[i], r[i], carry);
	}

	// Handle underflow 
	// (there are never two positive numbers, since r can only be positive)
	if (carry && negative) throw std::underflow_error("Underflow on bitset subtraction.");

	// Set negative
	negative = carry;

	// Convert back
	if (!negative)
		difference = addBitset(complimentBitset(difference), bitset<N>{1});

	return difference;
}

template<unsigned int N>
bitset<N> BitsetMath::shiftLeft(const bitset<N>& num, int shifts) {
	bitset<N> shiftedBitset;
	for (int i = shifts; i < N; i++) {
		shiftedBitset[i] = num[i - shifts];
	}
	return shiftedBitset;
}

template<unsigned int N>
bitset<N> BitsetMath::shiftRight(const bitset<N>& num, int shifts) {
	bitset<N> shiftedBitset;
	for (int i = shifts; i < N; i++) {
		shiftedBitset[i - shifts] = num[i];
	}
	return shiftedBitset;
}

template<unsigned int N>
bitset<N> BitsetMath::multiplyBitset(const bitset<N>& l, const bitset<N>& r) {
	bitset<N> product;

	// Loop through the bitset
	for (int i = 0; i < N; i++) {

		// If the current multiplier is 1
		if (r[i] == 1) {
			// Acumulate the product
			product = addBitset(product, shiftLeft(l, i));
		}
	}
	return product;
}

#endif
