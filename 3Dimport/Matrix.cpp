#include "Matrix.h"
#include <ctime>
Matrix::Matrix()
{
}

Matrix::Matrix(int lines, int columns) {
	this->size1 = lines;
	this->size2 = columns;
	vector<LINE> A;
	LINE line;
	for (int columns_count = 0; columns_count < columns; columns_count++) {
		line.push_back(0);
	}
	for (int lines_count = 0; lines_count < lines; lines_count++) {
		A.push_back(line);
	}
	this->M = A;
}

Matrix::~Matrix()
{
}


void Matrix::setElement(int index1, int index2, float value){
	//this->M.at(index1).at(index2) = value;
	this->M[index1][index2] = value;
}

float Matrix::getElement(int index1, int index2){
	return this->M.at(index1).at(index2); 
}

void Matrix::print() {
	std::cout << endl;
	for (int i = 0; i < this->size1; i++) {
		for (int j = 0; j < this->size2; j++) {
			std::cout << this->M.at(i).at(j) << "\t";
		}
		std::cout << endl;
	}
}

Matrix Matrix::operator*(Matrix B) {
	Matrix A = *this;
	Matrix C(A.size1, B.size2);
	if (A.size2 != B.size1) {
		cerr << "dim A!= dim B";
	}
	for (int row = 0; row < C.size1; row++) {
		for (int col = 0; col < C.size2; col++) {
			// Multiply the row of A by the column of B to get the row, column of product.
			for (int inner = 0; inner < A.size2; inner++) {
				//product[row][col] += aMatrix[row][inner] * bMatrix[inner][col];
				C.setElement(row, col, C.getElement(row, col) + A.getElement(row, inner)*B.getElement(inner, col));
			}
		}
	}
	return C;
}


Matrix Matrix::operator*(float m){
	for (int i = 0; i < this->size1; i++) {
		for (int j = 0; j < this->size2; j++) {
			this->setElement(i, j, this->getElement(i, j)*m);
		}
	}
	return *this;
}

// use for 4x4, 3x3 or 2x2 Matrix only
float Matrix::det() {
	float det;
	Matrix A = *this;
	//4x4
	if(A.size1 == A.size2 && A.size1 == 4) {
		det = A.getElement(0, 0)*(A.getElement(1, 1)*A.getElement(2, 2)*A.getElement(3, 3) - A.getElement(1, 1)*A.getElement(2, 3)*A.getElement(3, 2) - A.getElement(1, 2)*A.getElement(2, 1)*A.getElement(3, 3) + A.getElement(1, 2)*A.getElement(2, 3)*A.getElement(3, 1) + A.getElement(1, 3)*A.getElement(2, 1)*A.getElement(3, 2) - A.getElement(1, 3)*A.getElement(2, 2)*A.getElement(3, 1)) -
			A.getElement(0, 1)*(A.getElement(1, 0)*A.getElement(2, 2)*A.getElement(3, 3) - A.getElement(1, 0)*A.getElement(2, 3)*A.getElement(3, 2) - A.getElement(1, 2)*A.getElement(2, 0)*A.getElement(3, 3) + A.getElement(1, 2)*A.getElement(2, 3)*A.getElement(3, 0) + A.getElement(1, 3)*A.getElement(2, 0)*A.getElement(3, 2) - A.getElement(1, 3)*A.getElement(2, 2)*A.getElement(3, 0)) +
			A.getElement(0, 2)*(A.getElement(1, 0)*A.getElement(2, 1)*A.getElement(3, 3) - A.getElement(1, 0)*A.getElement(2, 3)*A.getElement(3, 1) - A.getElement(1, 1)*A.getElement(2, 0)*A.getElement(3, 3) + A.getElement(1, 1)*A.getElement(2, 3)*A.getElement(3, 0) + A.getElement(1, 3)*A.getElement(2, 0)*A.getElement(3, 1) - A.getElement(1, 3)*A.getElement(2, 1)*A.getElement(3, 0)) -
			A.getElement(0, 3)*(A.getElement(1, 0)*A.getElement(2, 1)*A.getElement(3, 2) - A.getElement(1, 0)*A.getElement(2, 2)*A.getElement(3, 1) - A.getElement(1, 1)*A.getElement(2, 0)*A.getElement(3, 2) + A.getElement(1, 1)*A.getElement(2, 2)*A.getElement(3, 0) + A.getElement(1, 2)*A.getElement(2, 0)*A.getElement(3, 1) - A.getElement(1, 2)*A.getElement(2, 1)*A.getElement(3, 0));
	}
	//2x2
	else if (A.size1 == A.size2 && A.size1 == 2) {
		det = A.getElement(0, 0)*A.getElement(1, 1) - A.getElement(0, 1)*A.getElement(1, 0);
	}
	else if (A.size1 == A.size2 && A.size1 == 3) {
		det = A.getElement(0, 0)*(A.getElement(1, 1)*A.getElement(2, 2) - A.getElement(1, 2)*A.getElement(2, 1)) -
			A.getElement(0, 1)*(A.getElement(1, 0)*A.getElement(2, 2) - A.getElement(1, 2)*A.getElement(2, 0)) +
			A.getElement(0, 2)*(A.getElement(1, 0)*A.getElement(2, 1) - A.getElement(1, 1)*A.getElement(2, 0));
	}
	return det;
}

// use for 4x4 Matrix only
Matrix Matrix::inverseMatrix() {
	Matrix A = *this;	//input Matrix
	Matrix M(4, 4);	//Minors Matrix

	if (A.det() != 0) {
		// getting minors matrix
		Matrix TEMP(3, 3);
		int current_column = 0;
		int current_line = 0;
		int temp_line = 0;
		int temp_column = 0;
		int m_line = 0;
		int m_column = 0;
		// Создание матриц миноров
		while (!(m_line == M.size1-1 && m_column == M.size2)){

			// Связь вычёркивыемых строк/столбцов с добавляемыми в Матрицу Миноров
			current_column = m_column;
			current_line = m_line;
			if (current_column == M.size1) {
				current_column = 0;
				current_line++;
			}
			//

			temp_line = 0;
			temp_column = 0;
			for (int i = 0; i < A.size1; i++) {
				for (int j = 0; j < A.size2; j++) {
					if (i != current_line && j != current_column) {

						TEMP.setElement(temp_line, temp_column, A.getElement(i, j));
						temp_column++;

						if (temp_column == TEMP.size2) {
							temp_column = 0;
							temp_line++;
						}
					}
				}
			}

			// Смена вычёркиваемой строки или колонки
			// &&
			// Занесение определителей миноров входной матрицы в матрицу Миноров 
			if (m_column == M.size2 && m_line == M.size1 - 1) {
				m_line++;
			}
			else if(m_column == M.size2 && m_line != M.size1-1) {
				m_column = 0;
				m_line++;
				M.setElement(m_line, m_column, TEMP.det());
			}
			else {
				M.setElement(m_line, m_column, TEMP.det());
				m_column++;
			}

		}

		Matrix B(4, 4); // alg addition
		B = M;
		B.setElement(0, 1, -B.getElement(0, 1));
		B.setElement(0, 3, -B.getElement(0, 3));
		B.setElement(1, 0, -B.getElement(1, 0));
		B.setElement(1, 2, -B.getElement(1, 2));
		B.setElement(2, 1, -B.getElement(2, 1));
		B.setElement(2, 3, -B.getElement(2, 3));
		B.setElement(3, 0, -B.getElement(3, 0));
		B.setElement(3, 2, -B.getElement(3, 2));

		// транспонированная матрица алгебраических дополнений
		Matrix transposed_B = B.transposeMatrix();
		
		Matrix I(transposed_B.size1, transposed_B.size2);
		I = transposed_B * (1 / A.det());

		return I;
	}
	std::cout << endl << "Error: matrix det = 0" << endl;
	return *this;
}

Matrix Matrix::transposeMatrix() {
	Matrix T(this->size2, this->size1);
	int matrix_column = 0;	// счётчик столбцов исходной матрицы
	int matrix_line = 0;	// счётчик строк исходной матрицы
	for (int i = 0; i < T.size1; i++) {
		matrix_line = 0;
		for (int j = 0; j < T.size2; j++) {
			T.setElement(i, j, this->getElement(matrix_line, matrix_column));
			matrix_line++;
			if (matrix_line == this->size1) {
				matrix_line = 0;
				matrix_column++;
			}
		}
	}
	return T;
}

Matrix Matrix::addLine(Matrix &M) {
	// O(A.size1 * A.size2)
	// M.size1 must be eq to 1
	//M.size2 must be eq to A.size2
	Matrix A = *this;
	Matrix C(A.size1 + 1, M.size2);
	
	for (int i = 0; i < A.size1; i++) {
		for (int j = 0; j < A.size2; j++) {
			C.setElement(i, j, A.getElement(i, j));
		}
	}

	for (int i = 0; i < M.size2; i++) {
		C.setElement(A.size1, i, M.getElement(0, i));
	}
	return C;
}

void Matrix::setVectorToLine(int line, Matrix &A) {
	for (int i = 0; i < A.size2; i++) {
		this->setElement(line, i, A.getElement(0, i));
	}
}