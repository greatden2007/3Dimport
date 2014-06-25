#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Matrix.h""

using namespace std;
class Reader
	{
	public:
		Reader(void);
		~Reader(void);
		void readVertexsFromModelFile(ifstream &stream);
		void createFlatsFromVertexNumber();
		vector<Matrix> readModel(const char* modelFileName);

	private:
		Matrix vertex = *new Matrix(1, 3);
		Matrix texture_vertex = *new Matrix(1, 2);
		
		std::vector<Matrix> all_flats;
		std::vector<Matrix> all_flats_numbers;
		std::vector<Matrix> all_vertexs;
		std::vector<Matrix> all_texture_vertexes;
		Matrix flat_number = *new Matrix(0,3);
		Matrix flat = *new Matrix(0, 3);
		int lines;
		int percents;
	};

