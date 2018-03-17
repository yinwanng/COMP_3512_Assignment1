class Matrix
{
public:
	Matrix(int n)
	{
		dimension = n;
		matrix = new int[n * n];
		for (int row = 0; row < dimension; row++) {
			for (int col = 0; col < dimension; col++) {
				matrix[row * dimension + col] = 0;
			}
		}
	}
private:
	int *matrix;
	int dimension;
};