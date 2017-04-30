/*#include "catch.hpp"
#include "Float32.hpp"
#include "HexConverter.hpp"
#include "BitsetMath.hpp"



TEST_CASE("Hexidecimal C0A00000 is converted to Float32", "[hexToFloat32]") {
	bitset<32> compareFloat("00000000000000000000010100000011");
	REQUIRE(HexConverter::hexToFloat32("C0A00000") == compareFloat);
}

TEST_CASE("Hexidecimal number is converted to binary", "[hexToBinary]") {
	REQUIRE(HexConverter::hexToBinary("C0A00000") == "11000000101000000000000000000000");
	REQUIRE(HexConverter::hexToBinary("3f800000") == "00111111100000000000000000000000");
}

TEST_CASE("Hexidecimal digits are converted to binary", "[hexDigitToBinary]") {
	REQUIRE(HexConverter::hexDigitToBinary('0') == "0000");
	REQUIRE(HexConverter::hexDigitToBinary('1') == "0001");
	REQUIRE(HexConverter::hexDigitToBinary('2') == "0010");
	REQUIRE(HexConverter::hexDigitToBinary('3') == "0011");
	REQUIRE(HexConverter::hexDigitToBinary('4') == "0100");
	REQUIRE(HexConverter::hexDigitToBinary('5') == "0101");
	REQUIRE(HexConverter::hexDigitToBinary('6') == "0110");
	REQUIRE(HexConverter::hexDigitToBinary('7') == "0111");
	REQUIRE(HexConverter::hexDigitToBinary('8') == "1000");
	REQUIRE(HexConverter::hexDigitToBinary('9') == "1001");
	REQUIRE(HexConverter::hexDigitToBinary('A') == "1010");
	REQUIRE(HexConverter::hexDigitToBinary('B') == "1011");
	REQUIRE(HexConverter::hexDigitToBinary('C') == "1100");
	REQUIRE(HexConverter::hexDigitToBinary('D') == "1101");
	REQUIRE(HexConverter::hexDigitToBinary('E') == "1110");
	REQUIRE(HexConverter::hexDigitToBinary('F') == "1111");
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

TEST_CASE("shiftLeft returns correct results", "[shiftLeft]") {
	REQUIRE(BitsetMath::shiftLeft(bitset<4>{1}, 1) == bitset<4>{2});
	REQUIRE(BitsetMath::shiftLeft(bitset<4>{1}, 2) == bitset<4>{4});
	REQUIRE(BitsetMath::shiftLeft(bitset<4>{1}, 3) == bitset<4>{8});
	REQUIRE(BitsetMath::shiftLeft(bitset<4>{3}, 2) == bitset<4>{12});
}

TEST_CASE("shiftRight returns correct results", "[shiftRight]") {
	REQUIRE(BitsetMath::shiftRight(bitset<4>{1}, 1) == bitset<4>{0});
	REQUIRE(BitsetMath::shiftRight(bitset<4>{2}, 1) == bitset<4>{1});
	REQUIRE(BitsetMath::shiftRight(bitset<4>{4}, 2) == bitset<4>{1});
	REQUIRE(BitsetMath::shiftRight(bitset<4>{8}, 1) == bitset<4>{4});
}

TEST_CASE("multiplyBitset returns correct results", "[multiplyBitset]") {
	REQUIRE(BitsetMath::multiplyBitset(bitset<10>{1}, bitset<10>{1}) == bitset<10>{1});
	REQUIRE(BitsetMath::multiplyBitset(bitset<4>{3}, bitset<4>{3}) == bitset<4>{9});
	REQUIRE(BitsetMath::multiplyBitset(bitset<10>{15}, bitset<10>{2}) == bitset<10>{30});
}*/