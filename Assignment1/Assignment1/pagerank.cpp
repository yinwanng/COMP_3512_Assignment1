#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
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
	}


	system("pause");
	return 0;
}