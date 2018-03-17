#include "Matrix.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setw;
using std::ostream;
using std::invalid_argument;

// Default constructor : Intializes Matrix 1 x 1 that contains 0.
Matrix::Matrix()
{
	dimensions = 1;
	matrix = new int[dimensions];
	matrix[0] = 0;
}

// Destructor
Matrix::~Matrix()
{
	delete[] matrix;
}

// Copy constructor 
Matrix::Matrix(const Matrix &other)
{
	dimensions = other.dimensions;
	matrix = new int[dimensions * dimensions];
	for (int row = 0; row < dimensions; row++) {
		for (int col = 0; col < dimensions; col++) {
			matrix[row * dimensions + col] = other.matrix[row * dimensions + col];
		}
	}
}

// Constructor that creates a n x n Matrix that contains 0s.
// PRE: Must be a positive integer
// POST: n x n Matrix gets created which contain 0s.
Matrix::Matrix(int n)
{
	dimensions = n;
	matrix = new int[n * n];
	for (int row = 0; row < dimensions; row++) {
		for (int col = 0; col < dimensions; col++) {
			matrix[row * dimensions + col] = 0;
		}
	}
}

// Constructor that creates an n x n Matrix that contains values from
// the array
// PRE: The size of the array must have an integer square root.
// POST: Newly constructed square matrix of the size inputted along with values contained
//		 from array
Matrix::Matrix(int tempArray[], int size)
{
	double sqrtNum = sqrt(size);

	if ((sqrtNum * sqrtNum) == size)
	{
		dimensions = (int)sqrtNum;
		matrix = new int[size];
		for (int row = 0; row < dimensions; row++) {
			for (int col = 0; col < dimensions; col++) {
				matrix[row * dimensions + col] = tempArray[row * dimensions + col];
			}
		}
	}
	else
	{
		//throw invalid_argument("The size must have an integer square root.");
		cout << "The size must have an integer square root." << endl;
	}
}

// Sets a new value at the location specified
// PRE: Specify the row, column, and value
// POST: The new value assigned to specified location
void Matrix::set_value(int row, int col, int value)
{
	matrix[row * dimensions + col] = value;
}

// Gets the value
// PRE: Specify row and column
// POST: Value from the specified location
int Matrix::get_value(int row, int col) const
{
	return matrix[row * dimensions + col];
}

// POST: Sets all values in the Matrix to 0.
void Matrix::clear() const
{
	for (int row = 0; row < dimensions; row++) {
		for (int col = 0; col < dimensions; col++) {
			matrix[row * dimensions + col] = 0;
		}
	}
}

// Prefix: Increments all the values in the Matrix by 1.
Matrix & Matrix::operator++()
{
	for (int row = 0; row < dimensions; row++) {
		for (int col = 0; col < dimensions; col++) {
			matrix[row * dimensions + col] = matrix[row * dimensions + col] + 1;
		}
	}
	return *this;
}

// Postfix: Increments all the values in the Matrix by 1.
Matrix Matrix::operator++(int)
{
	Matrix tmp(*this);
	operator++();
	return tmp;
}

// Prefix: Decrements all the values in the Matrix by 1.
Matrix & Matrix::operator--()
{
	for (int row = 0; row < dimensions; row++) {
		for (int col = 0; col < dimensions; col++) {
			matrix[row * dimensions + col] = matrix[row * dimensions + col] - 1;
		}
	}
	return *this;
}

// Postfix: decrements all values in the Matrix by 1.
Matrix Matrix::operator--(int)
{
	Matrix tmp(*this);
	operator--();
	return tmp;
}

// Prints the Matrix to std::cout or other streams
ostream & operator<<(ostream & out, const Matrix & m)
{
	for (int row = 0; row < m.dimensions; row++) {
		for (int col = 0; col < m.dimensions; col++) {
			out << setw(4) << m.get_value(row, col);
			if (col % m.dimensions == m.dimensions - 1)
			{
				out << "\n";
			}
		}
	}
	return out;
}

// Checks if both the Matrixces are the same.
// PRE: The matrixes must be the same size.
// POST: Returns false if both the Matrices are not the same size or values are not the same.
//   	 Returns true if both the matrices are the same size and all the values inside.
bool operator==(const Matrix &lhs, const Matrix &rhs)
{
	if (lhs.dimensions != rhs.dimensions) {
		return false;
	}
	else
	{
		for (int row = 0; row < lhs.dimensions; row++) {
			for (int col = 0; col < lhs.dimensions; col++) {
				if (lhs.matrix[row * lhs.dimensions + col] != rhs.matrix[row * rhs.dimensions + col]) {
					return false;
				}
			}
		}
		return true;
	}
}

// Checks if the matrices are not the same.
// Returns true if its not the same.
// Returns false if it is the same.
bool operator!=(const Matrix &lhs, const Matrix &rhs)
{
	return !operator==(lhs, rhs);
}

// Checks if the matrix is smaller.
// Returns true if matrix is smaller.
// Returns false if matrix is not smaller.
bool operator<(const Matrix &lhs, const Matrix &rhs)
{
	if (lhs.dimensions < rhs.dimensions) {
		return true;
	}
	return false;
}

// Checks if matrix is bigger.
// Returns true if matrix is bigger.
// Returns false is matrix is not bigger.
bool operator>(const Matrix & lhs, const Matrix &rhs)
{
	return operator< (rhs, lhs);
}

// Checks if matrix is smaller or equal.
// Returns true if matrix is smaller or equal.
// Returns false is matrix is not smaller or equal.
bool operator<=(const Matrix & lhs, const Matrix &rhs)
{
	return !operator> (lhs, rhs);
}

// Checks if matrix is bigger or equal.
// Returns true if it is bigger or equal.
// Returns false if it is not bigger or equal.
bool operator>=(const Matrix & lhs, const Matrix &rhs)
{
	return !operator< (lhs, rhs);
}

// Swaps the data members
void swap(Matrix &first, Matrix &second)
{
	using std::swap;
	swap(first.dimensions, second.dimensions);
	swap(first.matrix, second.matrix);
}

// Adds the rhs matrix values to the lhs matrix .
// Returns the lhs matrix.
Matrix operator+(Matrix lhs, const Matrix &rhs)
{
	lhs += rhs;
	return lhs;
}
// Subtracts the rhs matrix values to the lhs matrix.
Matrix operator-(Matrix lhs, const Matrix &rhs)
{
	lhs -= rhs;
	return lhs;
}

// Tears down the object's old state and builds its 
// new state as a copy of some other objects state
Matrix & Matrix::operator=(Matrix other)
{
	swap(*this, other);
	return *this;
}

// Adds the matrix values
// PRE: Must be the same size.
// POST: rhs matrix values been added to this
Matrix & Matrix::operator+=(const Matrix &rhs)
{
	for (int row = 0; row < rhs.dimensions; row++) {
		for (int col = 0; col < rhs.dimensions; col++) {
			this->matrix[row * this->dimensions + col] = this->matrix[row * this->dimensions + col] + matrix[row * rhs.dimensions + col];
		}
	}
	return *this;
}

// Substracts the matrix values
// PRE: Must be the same size.
// POST: rhs values been subtracted to this
Matrix & Matrix::operator-=(const Matrix &rhs)
{
	for (int row = 0; row < rhs.dimensions; row++) {
		for (int col = 0; col < rhs.dimensions; col++) {
			this->matrix[row * this->dimensions + col] = this->matrix[row * this->dimensions + col] - matrix[row * rhs.dimensions + col];
		}
	}
	return *this;
}

// Creates identity matrix
// PRE: Size must be the same as current
// POST: Identity matrix created
Matrix & Matrix::identity()
{
	for (int row = 0; row < this->dimensions; row++) {
		for (int col = 0; col < this->dimensions; col++) {
			if (row == col) {
				this->matrix[row * this->dimensions + col] = 1;
			}
			else {
				this->matrix[row * this->dimensions + col] = 0;
			}
		}
	}
	return *this;
}