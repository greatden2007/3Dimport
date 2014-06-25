#include "Reader.h"
#include <regex>
#include <boost\regex.hpp>

typedef match_results<const char*> cmatch;

Reader::Reader(void)
	{
	}


Reader::~Reader(void)
	{
	}

void Reader::readVertexsFromModelFile(ifstream &stream) {
	for (string line; getline(stream, line);) {

		istringstream in(line);
		float tmp;
		int tmp2;
		Matrix line_vector = *new Matrix(1, 3);

		string type;
		in >> type;

		if (type.compare("v") == 0) {
			in >> tmp;
			vertex.setElement(0, 0, tmp);
			in >> tmp;
			vertex.setElement(0, 1, tmp);
			in >> tmp;
			vertex.setElement(0, 2, tmp);
			all_vertexs.push_back(vertex);
		}
		else if (type.compare("vt") == 0) {
			in >> tmp;
			texture_vertex.setElement(0, 0, tmp);
			in >> tmp;
			texture_vertex.setElement(0, 1, tmp);
			all_texture_vertexes.push_back(texture_vertex);
		}
		else if (type.compare("f") == 0) {
			// f
			// |	v1.x	v1.y	v1.z	|
			// |	v2.x	v2.y	v2.z	|
			// |	v3.x	v3.y	v3.z	|
			flat_number = *new Matrix(0, 3);

			in >> tmp2;
			line_vector.setElement(0, 0, tmp2);
			in >> tmp2;
			line_vector.setElement(0, 1, tmp2);
			in >> tmp2;
			line_vector.setElement(0, 2, tmp2);
			flat_number = flat_number.addLine(line_vector);

			in >> tmp2;
			line_vector.setElement(0, 0, tmp2);
			in >> tmp2;
			line_vector.setElement(0, 1, tmp2);
			in >> tmp2;
			line_vector.setElement(0, 2, tmp2);
			flat_number = flat_number.addLine(line_vector);

			in >> tmp2;
			line_vector.setElement(0, 0, tmp2);
			in >> tmp2;
			line_vector.setElement(0, 1, tmp2);
			in >> tmp2;
			line_vector.setElement(0, 2, tmp2);
			flat_number = flat_number.addLine(line_vector);

			all_flats_numbers.push_back(flat_number);
			
		}
	}
}

// создаёт сами поверхности из номеров вертексов
void Reader::createFlatsFromVertexNumber() {
	for (Matrix flat_number : all_flats_numbers) {
		for (int i = 0; i < flat_number.size1; i++) {
			flat = flat.addLine(all_vertexs.at(flat_number.getElement(i, 0)-1));
		}
		all_flats.push_back(flat);
		flat = *new Matrix(0, 3);
	}
}

vector<Matrix> Reader::readModel(const char* modelFileName) {
	clock_t t = clock();
	ifstream ModelFile(modelFileName, ifstream::binary);
	readVertexsFromModelFile(ModelFile);
	createFlatsFromVertexNumber();
	cout << "Overall  time:" << clock() - t << "ms\n";
	return all_flats;
}
