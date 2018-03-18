#include <iostream>
#include <fstream>
#include <string>
#include <Math.h>
#include <vector>
#include <iomanip>
#include "Matrix.h"

#define ASCII_OFFSET      65   
using namespace std;

int main()
{
	
	size_t inputStringLength = 0;
	int dimension = 0;
	vector<double> connectivityValues;

	string filename = "connectivity.txt";
	ifstream input;
	input.open(filename);

	if (!input.is_open()) {
		return 1;
	}

	cout << "Input file contents: \n";
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

	cout << "Dimension count: " << dimension << endl;

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
	// set importance
	sMatrix.set_importance();
	cout << "S Matrix after importance\n" << sMatrix << endl;

	// set randomness
	sMatrix.set_randomness();
	cout << "S Matrix after randomness\n" << sMatrix << endl;
	
	// set up q matrix
	Matrix qMatrix{ dimension, (1.0 / dimension) * 0.15 };
	
	// print q matrix
	cout << "Q Matrix after *0.15\n" << qMatrix << endl;
	
	// created transition matrix
	Matrix mMatrix = sMatrix + qMatrix;

	// print transition matrix
	cout << "Transition Matrix\n" << mMatrix << endl;

	// create column matrix rank
	double *matrixRank = new double[dimension];
	for (int i = 0; i < dimension; i++) {
		matrixRank[i] = 1;
	}

	// markov process
	int index = 0;
	double rank = 0;
	for (int row = 0; row < dimension; row++) {
		for (int col = 0; col < dimension; col++) {
			rank+= mMatrix.get_value(row, col) * matrixRank[index];
		}

		matrixRank[index++] = rank;
		rank = 0;
	} 

	// display check
	cout << "Rank\n";
	for (int i = 0; i < dimension; i++) {
		cout << fixed << setprecision(3) << (char)(i + ASCII_OFFSET) << " = " << matrixRank[i] / dimension << endl;
	}


	// write to file
	ofstream outFile;
	string outputFileName = "Rank.txt";
	outFile.open(outputFileName);
	if (outFile.is_open()) {
		for (int i = 0; i < dimension; i++) {
			outFile << fixed << setprecision(3) << (char)(i + ASCII_OFFSET) << " = " << matrixRank[i] / dimension << endl;
		}
		outFile.close();
	}
	else {
		cout << "Could not create file: " << outputFileName << endl;
	}

	system("pause");
	return 0;
}