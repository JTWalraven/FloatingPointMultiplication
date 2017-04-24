#include "catch.hpp"
#include <iostream>
using namespace std;

// Declare methods
const int binaryToDecimal(const string&);
const string binaryFloatToDecFloat(const string);
bool isBinaryFloatNegative(const string&);

const int binaryToDecimal(const string &number) {
	int decimal = 0;
	int exponent = 0;
	for (int i = number.length()-1; i >= 0; i--) {
		// If it is a one
		if (number[i] == '1') {
			// Add the power to the number
			decimal += (int) pow(2, exponent);
		}
		// Increment the exponent
		++exponent;
	}
	return decimal;
}

const string binaryFloatToDecFloat(const string number) {
	string decimal = "";

	if (isBinaryFloatNegative(number)) {
		// Add negation symbol
		decimal += '-';
	}

	// Do all the stuff ;)
	int exponent = binaryToDecimal(number.substr(1, 8)) - 127;
	string newNum = "1" + number.substr(9, 32).insert(exponent, ".");
	decimal += newNum;

	return decimal;
}

bool isBinaryFloatNegative(const string &number) {
	return number[0] == '1';
}

TEST_CASE("Binary number is converted to decimal number", "[binaryToDec]") {
	REQUIRE(binaryToDecimal("0") == 0);
	REQUIRE(binaryToDecimal("1") == 1);
	REQUIRE(binaryToDecimal("10") == 2);
	REQUIRE(binaryToDecimal("10111010") == 186);
	REQUIRE(binaryToDecimal("1010011") == 83);
}

TEST_CASE("Binary float is converted to decimal float", "[binaryToDec]") {
	REQUIRE(binaryFloatToDecFloat("11000000101000000000000000000000") == "-5.000000e+000");
	REQUIRE(binaryFloatToDecFloat("00111111100000000000000000000000") == "1.000000e+000");
}
