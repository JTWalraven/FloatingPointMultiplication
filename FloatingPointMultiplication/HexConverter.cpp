#include "catch.hpp"
#include <iostream>
using namespace std;

// Declare methods
const string hexToBinary(const string);
const char * hexDigitToBinary(const char);

// Create the hexedecimal conversion table
const char * const hexQuads[16] = {"0000", "0001", "0010", "0011", "0100", "0101", 
"0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};

const string hexToBinary(const string number) {
	string binary = "";

	// Loop through digits
	for (int i = 0; number[i] != '\0'; i++) {

		// Convert the digit to binary
		const char * digit = hexDigitToBinary(number[i]);

		// If not a valid digit
		if (digit != "-1") {

			// Add digit to binary number
			binary += digit;
		}
	}
	return binary;
}

const char * hexDigitToBinary(const char number) {
	// If the number is 0 through 9 return the value in the array
	if (number >= '0' && number <= '9') 
		return hexQuads[number - '0'];

	// If the number is a through f return the value in the array
	if (number >= 'a' && number <= 'f')
		return hexQuads[10 + number - 'a'];

	// If the number is A through F (uppercase return the value in the array
	if (number >= 'A' && number <= 'F')
		return hexQuads[10 + number - 'A'];

	// Invalid number
	return "-1";
}

TEST_CASE("Hexidecimal number is converted to binary", "[hexToBinary]") {
	REQUIRE(hexToBinary("C0A00000") == "11000000101000000000000000000000");
	REQUIRE(hexToBinary("3f800000") == "00111111100000000000000000000000");
}

TEST_CASE("Hexidecimal digits are converted to binary", "[hexDigitToBinary]") {
	REQUIRE(hexDigitToBinary('0') == "0000");
	REQUIRE(hexDigitToBinary('1') == "0001");
	REQUIRE(hexDigitToBinary('2') == "0010");
	REQUIRE(hexDigitToBinary('3') == "0011");
	REQUIRE(hexDigitToBinary('4') == "0100");
	REQUIRE(hexDigitToBinary('5') == "0101");
	REQUIRE(hexDigitToBinary('6') == "0110");
	REQUIRE(hexDigitToBinary('7') == "0111");
	REQUIRE(hexDigitToBinary('8') == "1000");
	REQUIRE(hexDigitToBinary('9') == "1001");
	REQUIRE(hexDigitToBinary('A') == "1010");
	REQUIRE(hexDigitToBinary('B') == "1011");
	REQUIRE(hexDigitToBinary('C') == "1100");
	REQUIRE(hexDigitToBinary('D') == "1101");
	REQUIRE(hexDigitToBinary('E') == "1110");
	REQUIRE(hexDigitToBinary('F') == "1111");
}