#include "BitsetMath.hpp"
using namespace std;

bool BitsetMath::addBits(bool b1, bool b2, bool& carry) {
	// Calculate the sum
	bool sum = (b1 ^ b2) ^ carry;

	// Calculate the carry bit
	carry = (b1 && b2) || (b1 && carry) || (b2 && carry);

	return sum;
}

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
bitset<N> BitsetMath::partialProduct(const bitset<N>& num, int shifts) {
	bitset<N> partialProduct;
	for (int i = shifts; i < N; i++) {
		partialProduct[i] = num[i - shifts];
	}
	return partialProduct;
}

template<unsigned int N>
bitset<N> BitsetMath::multiplyBitset(const bitset<N>& l, const bitset<N>& r) {
	bitset<N> product;

	// Loop through the bitset
	for (int i = 0; i < N; i++) {

		// If the current multiplier is 1
		if (r[i] == 1) {
			// Acumulate the product
			product = addBitset(product, partialProduct(l, i));
		}
	}
	return product;
}

TEST_CASE("addBits 0 + 0 = 0 with 0 carry", "[fullAdder]") {
	bool carry = 0;
	REQUIRE(BitsetMath::addBits(0, 0, carry) == 0);
	REQUIRE(carry == 0);
}

TEST_CASE("addBits 0 + 1 = 1 with 0 carry", "[fullAdder]") {
	bool carry = 0;
	REQUIRE(BitsetMath::addBits(0, 1, carry) == 1);
	REQUIRE(carry == 0);

	carry = 0;
	REQUIRE(BitsetMath::addBits(1, 0, carry) == 1);
	REQUIRE(carry == 0);
}

TEST_CASE("addBits 1 + 1 = 0 with 1 carry", "[fullAdder]") {
	bool carry = 0;
	REQUIRE(BitsetMath::addBits(1, 1, carry) == 0);
	REQUIRE(carry == 1);
}

TEST_CASE("addBits single carry bit addition works", "[fullAdder]") {
	bool carry = 1;
	REQUIRE(BitsetMath::addBits(0, 1, carry) == 0);
	REQUIRE(carry == 1);
	REQUIRE(BitsetMath::addBits(1, 1, carry) == 1);
	REQUIRE(carry == 1);
	REQUIRE(BitsetMath::addBits(0, 0, carry) == 1);
	REQUIRE(carry == 0);
}

TEST_CASE("addBitset returns correct results", "[addBitset]") {
	REQUIRE(BitsetMath::addBitset(bitset<4>{5}, bitset<4>{3}) == bitset<4>{8});
	REQUIRE(BitsetMath::addBitset(bitset<4>{9}, bitset<4>{5}) == bitset<4>{14});
	REQUIRE(BitsetMath::addBitset(bitset<8>{25}, bitset<8>{36}) == bitset<8>{61});
}

TEST_CASE("subtractBitset returns correct results", "[subtractBitset]") {
	bool negative = false;
	REQUIRE(BitsetMath::subtractBitset(bitset<4>{5}, bitset<4>{3}, negative) == bitset<4>{2});
	REQUIRE(negative == false);
	negative = false;
	REQUIRE(BitsetMath::subtractBitset(bitset<4>{3}, bitset<4>{5}, negative) == bitset<4>{2});
	REQUIRE(negative == true);
}

TEST_CASE("partialProduct returns correct results", "[partialProduct]") {
	REQUIRE(BitsetMath::partialProduct(bitset<4>{1}, 1) == bitset<4>{2});
	REQUIRE(BitsetMath::partialProduct(bitset<4>{1}, 2) == bitset<4>{4});
	REQUIRE(BitsetMath::partialProduct(bitset<4>{1}, 3) == bitset<4>{8});
	REQUIRE(BitsetMath::partialProduct(bitset<4>{3}, 2) == bitset<4>{12});
}

TEST_CASE("multiplyBitset returns correct results", "[multiplyBitset]") {
	REQUIRE(BitsetMath::multiplyBitset(bitset<10>{1}, bitset<10>{1}) == bitset<10>{1});
	REQUIRE(BitsetMath::multiplyBitset(bitset<4>{3}, bitset<4>{3}) == bitset<4>{9});
	REQUIRE(BitsetMath::multiplyBitset(bitset<10>{15}, bitset<10>{2}) == bitset<10>{30});
}
