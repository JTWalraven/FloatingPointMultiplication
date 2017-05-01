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
		while (fin >> value1 >> value2) {

			// Convert left value to float
			Float32 leftFloat = HexConverter::hexToFloat32(value1);

			// Print out equivalence
			cout << value1 << " is equivalent to IEEE: " << leftFloat.getDecimal() << endl;

			// Convert right value to float
			Float32 rightFloat = HexConverter::hexToFloat32(value2);

			// Print out equivalence
			cout << value2 << " is equivalent to IEEE: " << rightFloat.getDecimal() << endl;

			try {
				// Multiply float values
				Float32 product = leftFloat * rightFloat;

				// Print product result
				cout << endl
					<< "The product is " << product.getHex()
					<< ", which is equivalent to " << product.getDecimal() << endl << endl;
			}
			catch (std::overflow_error) {	// Catch and report overflow
				cout << endl << "ERROR: Overflow occured in multiplication of floats." << endl << endl;
			}
			catch (std::underflow_error) {	// Catch and report underflow
				cout << endl << "ERROR: Underflow occured in multiplication of floats." << endl << endl;
			}
		}
	}
	fin.close();

	// Pause the program
	cout << "Execution finished. Press any key to continue..." << endl;
	int x;
	cin >> x;
	return 0;
}