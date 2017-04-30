#include "HexConverter.hpp"

// Create the hexedecimal conversion table
static const char * const hexQuads[16] = {"0000", "0001", "0010", "0011", "0100", "0101", 
"0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};

const Float32 HexConverter::hexToFloat32(const string number) {
	Float32 float32;

	// Convert hex to binary string
	string binary = hexToBinary(number);

	// Convert sign
	string sign = binary.substr(FLOAT32_SIGN_POS, FLOAT32_SIGN_LENGTH);
	float32.setSign(sign[0] == '1');

	// Convert the exponent
	string exponent = binary.substr(FLOAT32_EXPONENT_POS, FLOAT32_EXPONENT_LENGTH);
	float32.setExponent(bitset<FLOAT32_EXPONENT_LENGTH>(exponent));

	// Convert the fraction
	string fraction = binary.substr(FLOAT32_FRACTION_POS, FLOAT32_FRACTION_LENGTH);
	float32.setFraction(bitset<FLOAT32_FRACTION_LENGTH>(fraction));

	return float32;
}

const string HexConverter::hexToBinary(const string number) {
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

const char * HexConverter::hexDigitToBinary(const char number) {
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
