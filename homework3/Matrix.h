#ifndef __Matrix_h_
#define __Matrix_h_

#include <iostream>
#include <vector>

class Matrix
{

public:

	Matrix();
	Matrix(const Matrix&m);
	Matrix(unsigned int row_count, unsigned int col_count, double fill);
	unsigned int num_rows() const;
	unsigned int num_cols() const;
	bool get(unsigned int row, unsigned int column, double& a) const;
	bool set(unsigned int row, unsigned int column, double value);
	bool operator==(const Matrix& m);
	bool operator!=(const Matrix& m);
	bool add(const Matrix& b);
	bool sub(const Matrix& b);
	double* get_row(unsigned int row);
	double* get_col(unsigned int row);
	bool swap_row(unsigned int source_row, unsigned target_row);
	void multiply_by_coefficient(double coeff);
	~Matrix() { clear();};
	void transpose();
	Matrix* quarter();
	Matrix& operator=(const Matrix& m);



private: 
	void clear();
	unsigned int m_row_count;
	unsigned int m_col_count;
	double m_fill;
	double** matrix;

};
std::ostream& operator<< (std::ostream& out, const Matrix& m);

#endif