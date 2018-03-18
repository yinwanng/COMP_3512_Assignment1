#include <iostream>
using std::ostream;

class Matrix
{
public:
	// Constructors & destructor
	Matrix();
	~Matrix();
	Matrix(const Matrix &);
	Matrix(int);
	Matrix(double[], int);

	// setters and getters
	void set_value(int, int, double);
	double get_value(int, int) const;
	void clear() const;
	Matrix& set_importance();

	// insertion operator
	friend ostream & operator<<(ostream &, const Matrix &);

	// comparison operators
	friend bool operator==(const Matrix&, const Matrix&);
	friend bool operator!=(const Matrix&, const Matrix&);
	friend bool operator<(const Matrix&, const Matrix&);
	friend bool operator>(const Matrix&, const Matrix&);
	friend bool operator<=(const Matrix&, const Matrix&);
	friend bool operator>=(const Matrix&, const Matrix&);

	// unary increment and decrement operators
	Matrix& operator++();   //prefix increment
	Matrix operator++(int); //postfix increment
	Matrix& operator--();   //prefix decrement
	Matrix operator--(int); //postfix decrement

							// assignment operator using the copy-and-swap algorithm
	friend void swap(Matrix&, Matrix&);
	Matrix& operator=(Matrix);

	// binary arithmetic operators [+=, +, -+, -]
	Matrix& operator+=(const Matrix&);
	friend Matrix operator+(Matrix, const Matrix &);
	Matrix& operator-=(const Matrix &);
	friend Matrix operator-(Matrix, const Matrix &);

	// identity
	Matrix& identity();
private:
	double *matrix;
	int dimensions;
};