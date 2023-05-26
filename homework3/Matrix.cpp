#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include "Matrix.h"


//default constructor 
Matrix::Matrix()
{
	m_row_count = 0;
	m_col_count = 0;
	m_fill = 0;
	matrix = NULL;
}
//copy constructor
//creates the constructor and copies it
Matrix::Matrix(const Matrix& m)
{
	//creating the new matrix
	m_row_count = m.m_row_count;
	m_col_count = m.m_col_count;
	matrix = new double*[m_row_count];
	for (unsigned int i = 0; i < m_row_count; i++)
	{
		matrix[i] = new double[m_col_count];
	}
	for (unsigned int j = 0; j < m_row_count; j++)
	{
		for (unsigned int k = 0; k < m_col_count; k++)
		{
			matrix[j][k] = m_fill;
		}
	}
	//copying the matrix
	for (unsigned int i = 0; i < m_row_count; i++)
	{
		for (unsigned int j = 0; j < m_col_count;j++)
		{
			double numb = 0;
			m.get(i,j,numb);		
			(*this).matrix[i][j] = numb;

		}
	}
}

//the constructor that takes it it. 
Matrix::Matrix(unsigned int row_count, unsigned int col_count, double fill)
{
	m_row_count = row_count;
	m_col_count = col_count;
	m_fill = fill;
	matrix = new double*[m_row_count];
	for (unsigned int i = 0; i < row_count; i++)
	{
		matrix[i] = new double[m_col_count];
	}
	for (unsigned int j = 0; j < row_count; j++)
	{
		for (unsigned int k = 0; k < col_count; k++)
		{
			matrix[j][k] = fill;
		}
	}
	
}

//returns the number of rows in the matrix
//output: row count 
//input: none
unsigned int Matrix::num_rows() const
{
	return m_row_count;
}

//returns the number of cols in the matrix
//output: column count 
//input: none
unsigned int Matrix::num_cols() const
{
	return m_col_count;
}

//returns a boolean based on the value a being in the matrix
//output: boolean 
//input: a row number and a column number and a value
bool Matrix::get(unsigned int row, unsigned int column, double& a) const
{
	if (row < m_row_count && column < m_col_count)
	{
		a = matrix[row][column];
		return true;
	}
	else
	{
		return false;
	}
} 

//sets the matrix values to value
//output: boolean 
//input: a row number and a column number and a value
bool Matrix::set(unsigned int row, unsigned int column, double value)
{
	if (row < m_row_count && column < m_col_count){
		matrix[row][column] = value;
		return true;
	}
	else
	{
		return false;
	}
}

//changes how the operator = behaves in the code; 
//returns a matrix
//output: boolean 
//input: Matrix object
Matrix& Matrix::operator=(const Matrix& m)
{
	if (this != &m)
	{
		if(matrix != NULL)
		{
			clear();
		}
		
		m_row_count = m.m_row_count;
		m_col_count = m.m_col_count;
		if (m_row_count != 0&& m_col_count != 0)
		{
			matrix = new double*[m_row_count];
			for (unsigned int i = 0; i < m_row_count; i++)
			{
				matrix[i] = new double[m_col_count];
				for (unsigned int j = 0; j<m_col_count;j++)
				{
					matrix[i][j] = m.matrix[i][j];
				}
			}

		}
		return *this;
	}
	return *this;
}

//checks if all the values in the matrix are the same and see 
//if the matrixes are equal
//output: boolean 
//input: Matrix object
bool Matrix::operator==(const Matrix& m)
{
	//double temp_value;

	if (m.num_rows() != m_row_count && m.num_cols() != m_col_count)
	{
		return false; 
	}
	else
	{
		for (unsigned int i = 0; i < m_row_count;i++)
		{
			for (unsigned int j = 0; j < m_col_count; j++)
			{
				if (m.matrix[i][j] != (*this).matrix[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}
}

//checks if all the values in the matrix are different and see 
//if the matrixes are not equal
//output: boolean 
//input: Matrix object
bool Matrix::operator!=(const Matrix& m)
{
	//double temp_value;

	if (m.num_rows() != m_row_count && m.num_cols() != m_col_count)
	{
		return true; 
	}
	else
	{
		for (unsigned int i = 0; i < m_row_count;i++)
		{
			for (unsigned int j = 0; j < m_col_count; j++)
			{
				if (m.matrix[i][j] != (*this).matrix[i][j])
				{
					return true;
				}
			}
		}
		return false;
	}
}
//printing out printin operator to print out the matrix
std::ostream& operator<< (std::ostream& out, const Matrix& m)
{
	std::cout<<std::endl;
	std::cout<<m.num_rows()<<" X "<<m.num_cols()<<" matrix:"<<std::endl;
	std::cout<<"[";
	for (unsigned int i = 0; i < m.num_rows(); i++)
	{
		std::cout<<" ";
		for (unsigned int j = 0; j < m.num_cols();j++)
		{	
			//std::cout<<" ";
			double temp = 0;
			if (m.get(i,j,temp))
			{
				std::cout<<temp;
				std::cout<<" ";
			}
		}
		if (i != m.num_rows()-1)
		{
			std::cout<<" ";
			std::cout<<std::endl;
		}
	}
	std::cout<<"]"<<std::endl;
	return out; 
}

//adding each value in a matrix
//output: boolean 
//input: Matrix object
bool Matrix::add(const Matrix& b)
{
	if ((*this).num_rows() != b.num_rows() && (*this).num_cols() != b.num_cols())
	{
		return false;
	}
	else
	{
		for (unsigned int i = 0; i < (*this).num_rows(); i++)
		{
			for(unsigned int j = 0; j < (*this).num_cols(); j++)
			{
				matrix[i][j] += b.matrix[i][j];

			}
		}
	}
	return true;
}
//subtracting each value in both matrices
//output: boolean 
//input: Matrix object
bool Matrix::sub(const Matrix& b)
{
	if ((*this).num_rows() != b.num_rows() && (*this).num_cols() != b.num_cols())
	{
		return false;
	}
	else
	{
		for (unsigned int i = 0; i < (*this).num_rows(); i++)
		{
			for(unsigned int j = 0; j < (*this).num_cols(); j++)
			{
				matrix[i][j] -= b.matrix[i][j];

			}
		}
	}
	return true;
}
//getting the row specified
//output: pointer 
//input: row number
double* Matrix::get_row(unsigned int row)
{
	double* temp;
	if (row >= (*this).num_rows())
	{
		temp = NULL;
	}
	else
	{
		temp = new double[(*this).num_cols()];
		for(unsigned int i = 0; i < m_col_count; i++)
		{
			temp[i] = matrix[row][i];
		}
	}
	return temp;
}
//getting the col specified
//output: pointer 
//input: column number
double* Matrix::get_col(unsigned int col)
{
	double* temp;
	if (col >= (*this).num_cols())
	{
		temp = NULL;
	}
	else
	{
		temp = new double[(*this).num_rows()];
		for(unsigned int i = 0; i < m_row_count; i++)
		{
			temp[i] = matrix[i][col];
		}
	}
	return temp;
}

//swapping the source row and the target row in the given matrix
//output: boolean 
//input: two row numbers
bool Matrix::swap_row(unsigned int source_row, unsigned target_row)
{
	if(source_row > m_row_count || target_row > m_row_count)
	{
		return false; 
	}
	double* temp_row;
	temp_row = matrix[source_row];
	matrix[source_row] = matrix[target_row];
	matrix[target_row] = temp_row;
	return true; 

}
//multiplying all values with a coefficient 
//output: Matrix 
//input: none
void Matrix::multiply_by_coefficient(double coeff)
{
	for (unsigned int i = 0; i < (*this).num_rows(); i++)
	{
		for(unsigned int j = 0; j < (*this).num_cols(); j++)
		{
			matrix[i][j] *= coeff;

		}
	}
}

//switching the rows and columns
//output: none 
//input: none
void Matrix::transpose()
{
	double** temp_matrix = new double*[m_col_count];
	for(unsigned int i = 0; i < m_col_count; i++)
	{
		temp_matrix[i] = new double[m_row_count];
	}

	for (unsigned int i = 0; i < (*this).num_rows(); i++)
	{
		for(unsigned int j = 0; j < (*this).num_cols(); j++)
		{
			temp_matrix[j][i] = matrix[i][j];
		}
	}

	clear();
	int temp = m_row_count;
	m_row_count = m_col_count;
	m_col_count = temp;
	matrix = temp_matrix;
}

//clearing the entire matrix, this is to prevent mempory leaks (this is was annoying but it def worked.)
//output: none 
//input: none
void Matrix::clear()
{
	if(matrix != NULL)
	{
		for (unsigned int i = 0; i < (*this).num_rows(); i++) 
   		{
        	delete[] matrix[i];
    	}
    	delete [] matrix;
	}
}


//making 4 matrices out of the given matrix depending on the number of rows and columns. 
//output: Matrix 
//input: none
Matrix* Matrix::quarter()
{


	int temp_num = 0;
	Matrix *quarter_matrix = new Matrix[4];
	unsigned int mid_row = (m_row_count + 1) /2;
	unsigned int mid_col = (m_col_count + 1)/ 2;
	for (unsigned int i = 0; i< 4; i++)
	{
		quarter_matrix[i] = Matrix(mid_row,mid_col,temp_num);
	}

	//if it's even 
	if ((*this).num_rows() % 2 == 0)
	{
		mid_row = m_row_count/2;
	}
	else if ((*this).num_cols() % 2 == 0)
	{
		mid_col = m_col_count/2;
	}
	//if it's odd
	else if ((*this).num_cols() % 2 != 0)
	{
		mid_col = (m_col_count+ 1) / 2;
	}
	else if ((*this).num_rows() % 2 != 0)
	{
		mid_row = (m_row_count+1) / 2;
	}
	//upper left
	for (unsigned int i = 0; i < mid_row; i++)
		{
			for (unsigned j = 0; j < mid_col; j++)
			{
				quarter_matrix[0].set(i,j,matrix[i][j]);

			}
		}
	//upper right
	for (unsigned int i = 0; i < mid_row; i++)
	{
		for (unsigned j = mid_col ; j < m_col_count; j++)
		{
			quarter_matrix[1].set(i,j-mid_col,matrix[i][j]);
		}
	}
	//lower left
	for (unsigned int i = mid_row -1; i < m_row_count; i++)
	{
		for (unsigned j = 0; j < mid_col; j++)
		{
			quarter_matrix[2].set(i-(mid_row-1),j,matrix[i][j]);
		}
	}
	//lower right
	for (unsigned int i = mid_row-1; i < m_row_count; i++)
	{
		for (unsigned j = mid_col; j <m_col_count; j++)
		{
			quarter_matrix[3].set(i-(mid_row-1),j-mid_col,matrix[i][j]);
		}
	}
	return quarter_matrix; 
}
