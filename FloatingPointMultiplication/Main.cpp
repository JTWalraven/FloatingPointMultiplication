#include <string>
#include <fstream>
#include "Float32.hpp"
#include "HexConverter.hpp"
using namespace std;

int main() {
	string value1, value2;

	// Open file
	ifstream fin;
	fin.open("input.txt", ifstream::in);
	if (fin.good()) {
		// Read in values
		fin >> value1 >> value2;

		// Convert values to floats
		Float32 leftFloat = HexConverter::hexToFloat32(value1);
		Float32 rightFloat = HexConverter::hexToFloat32(value2);

		// Multiply float values
		Float32 product = leftFloat * rightFloat;

		// Print out decimal
		product.printDecimal();
	}
	fin.close();

	// Pause the program
	int x = 0;
	cin >> x;
	return 0;
}