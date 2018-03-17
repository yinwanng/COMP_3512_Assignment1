#include <iostream>
#include <fstream>
#include <string>
#include <Math.h>
#include "Matrix.h"
using namespace std;

int main()
{
	int inputStringLength = 0;
	int dimension = 0;

	string filename = "connectivity.txt";
	ifstream input;
	input.open(filename);

	if (!input.is_open()) {
		return 1;
	}

	while (input) {
		string line;
	
		getline(input, line, '\r');
		
		int value;

		input >> value;

		cout << line << endl;
		inputStringLength += line.length();
	}
	dimension = sqrt((inputStringLength + 1) / 2);

	cout << "dimension count: " << dimension << endl;


	system("pause");
	return 0;
}