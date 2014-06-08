#pragma once
#include <vector>
#include <iostream>
using namespace std;
typedef vector<float> LINE;
typedef vector<LINE> MATRIX;

class Matrix{
private:
	MATRIX M;
public:
	Matrix();
	Matrix(int size1, int size2);
	int size1;
	int size2;
	~Matrix();

	void setElement(int index1, int index2, float value);
	float getElement(int index1, int index2);

	Matrix operator*(Matrix A);
	Matrix operator*(float m);
	Matrix inverseMatrix();
	Matrix transposeMatrix();
	float det();
};

