#ifndef BITSET_MATH
#define BITSET_MATH

#include <bitset>
#include "catch.hpp"
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
	static bitset<N> partialProduct(const bitset<N>& num, int shifts);

	template<unsigned int N>
	static bitset<N> multiplyBitset(const bitset<N>& l, const bitset<N>& r);
};

#endif
