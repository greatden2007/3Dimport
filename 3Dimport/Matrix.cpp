#include "Matrix.h"


Matrix::Matrix()
{
}

Matrix::Matrix(int size1, int size2) {
	this->size1 = size1;
	this->size2 = size2;
	vector<LINE> A;
	LINE line;
	for (int columns_count = 0; columns_count < size2; columns_count++) {
		line.push_back(0);
	}
	for (int lines_count = 0; lines_count < size1; lines_count++) {
		A.push_back(line);
	}
	this->M = A;
}

Matrix::~Matrix()
{
}

void Matrix::setElement(int index1, int index2, float value){
	this->M.at(index1).at(index2) = value;
}

float Matrix::getElement(int index1, int index2){
	return this->M.at(index1).at(index2); 
}

Matrix Matrix::operator*(Matrix A){
	if (this->size2 != A.size1) {
		//���-�� �������� this != ���-�� ����� A
		return *this;
	}
	else {
		Matrix C(this->size1, A.size2);

		// line_count � column_count -- ��� ���������� ����� � ������������
		int line_count = 0;
		int column_count = 0;
		int tmp = 0;
		float mul1 = 0;
		float mul2 = 0;
		for (int i = 0; i < C.size1; i++) {
			for (int j = 0; j < C.size2; j++){
				while (line_count < this->size1) {
					mul1 = this->getElement(i, line_count);
					mul2 = A.getElement(column_count, j);
					tmp += mul1 * mul2;
					line_count++;
					column_count++;
				}
				C.setElement(i, j, tmp);
				tmp = 0;
				line_count = 0;
				column_count = 0;
			}
		}
		return C;
	}

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
		// �������� ������ �������
		while (!(m_line == M.size1-1 && m_column == M.size2)){

			// ����� ������������� �����/�������� � ������������ � ������� �������
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

			// ����� ������������� ������ ��� �������
			// &&
			// ��������� ������������� ������� ������� ������� � ������� ������� 
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

		// ����������������� ������� �������������� ����������
		Matrix transposed_B = B.transposeMatrix();
		
		Matrix I(transposed_B.size1, transposed_B.size2);
		I = transposed_B * (1 / A.det());

		return I;
	}
	return *this;
}

Matrix Matrix::transposeMatrix() {
	Matrix T(this->size2, this->size1);
	int matrix_column = 0;	// ������� �������� �������� �������
	int matrix_line = 0;	// ������� ����� �������� �������
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