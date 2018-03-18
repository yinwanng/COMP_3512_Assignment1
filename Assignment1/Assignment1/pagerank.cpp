#include <iostream>
#include <fstream>
#include <string>
#include <Math.h>
#include <vector>
#include "Matrix.h"
using namespace std;
int main()
{
	size_t inputStringLength = 0;
	int dimension = 0;
	vector<double> connectivityValues;
	double p{ 0.85 };

	string filename = "connectivity.txt";
	ifstream input;
	input.open(filename);

	if (!input.is_open()) {
		return 1;
	}

	// count to find Matrix diemsnion
	while (input) {
		string line;	
		getline(input, line, '\r');	
		int value;
		input >> value;
		cout << line << endl;
		inputStringLength += line.length();
	}
	input.close();

	dimension = sqrt((inputStringLength + 1) / 2);

	cout << "dimension count: " << dimension << endl;

	// constructed  connectivity matrix
	Matrix cMatrix{ dimension };

	// retrieve values from connectivity input file
	int value = 0;
	input.open(filename);
	while (input >> value) {
		connectivityValues.push_back(value);
	}
	input.close();


	// assign the values to the connectivity matrix
	int i = 0;
	for (int row = 0; row < dimension; row++) {
		for (int col = 0; col < dimension; col++) {
			cMatrix.set_value(row, col, connectivityValues[i++]);
		}
	}

	// print connectivity matrix
	cout << "\nConnectivity Matrix" << endl;
	cout << cMatrix << endl;

	Matrix sMatrix = cMatrix;
	sMatrix.set_importance();
	

	cout << sMatrix << endl;


	system("pause");
	return 0;
}