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
	static bitset<N> multiplyBitset(const bitset<N>& l, const bitset<N>& r, bool& increment);
};

template<unsigned int N>
bitset<N> BitsetMath::addBitset(const bitset<N>& l, const bitset<N>& r) {
	bitset<N> sum;
	bool carry = false;

	// Add the bits
	for (int i = 0; i < N; i++) {
		sum[i] = addBits(l[i], r[i], carry);
	}

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
	shiftedBitset = num << shifts;
	return shiftedBitset;
}

template<unsigned int N>
bitset<N> BitsetMath::shiftRight(const bitset<N>& num, int shifts) {
	bitset<N> shiftedBitset;
	shiftedBitset = num >> shifts;
	return shiftedBitset;
}

template<unsigned int N>
bitset<N> BitsetMath::multiplyBitset(const bitset<N>& l, const bitset<N>& r, bool& increment) {
	bitset<N * 3> product;
	bitset<N * 3> ld(l.to_ulong());
	int offset = 0;

	cout << endl << "Multiplication: " << endl;
	cout << "    " << l << endl;
	cout << "   x" << r << endl;
	cout << "----------------------" << endl;

	// Loop through the bitset
	for (int i = 0; i < N; i++) {
		// If the current multiplier is 1
		if (r.test(i)) {
			// Acumulate the product
			product = addBitset(product, shiftLeft(ld, i));

			// Calculate the offset
			offset = (i + N) - 1;
		}
	}

	// Set the increment to true
	if (product.test(offset + 1))
		increment = true;

	// Get the result of the multiplication
	bitset<N> result;
	cout << "Offset: " << offset << endl;
	for (int i = 0; i < N && offset - i > 0; i++) {
		result[(N - 1) - i] = product[offset - i];
	}

	cout << "Left: " << ld << endl;
	cout << "Product: " << product << endl;
	cout << "Result: " << result << endl;

	// Round up the result
	if (result[0] == 1)
		result = BitsetMath::addBitset(result, bitset<N>{1});

	return result;
}

#endif
