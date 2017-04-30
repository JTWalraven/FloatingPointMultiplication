#ifndef HEX_CONVERTER
#define HEX_CONVERTER

#include "Float32.hpp"
#include <iostream>

using namespace std;

class HexConverter {
public:
	static const Float32 hexToFloat32(const string);
	static const string hexToBinary(const string);
	static const char * hexDigitToBinary(const char);
};

#endif