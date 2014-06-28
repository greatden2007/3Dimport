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
	float tmp;
	int tmp2;
	int counter; // для подсчёта количества линий и добавлении их в матрицу при необходимости
	for (string line; getline(stream, line);) {
		counter = 0;
		istringstream in(line);

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

			// что за хуйня? вынести в функцию три блока ниже
			in >> tmp2;
			line_vector.setElement(0, 0, tmp2);
			in >> tmp2;
			line_vector.setElement(0, 1, tmp2);
			in >> tmp2;
			line_vector.setElement(0, 2, tmp2);
			counter++;
			if (flat_number.size1 < counter){
				flat_number = flat_number.addLine(this->line_vector);
			}
			else {
				flat_number.setVectorToLine(counter - 1, line_vector);
			}

			in >> tmp2;
			line_vector.setElement(0, 0, tmp2);
			in >> tmp2;
			line_vector.setElement(0, 1, tmp2);
			in >> tmp2;
			line_vector.setElement(0, 2, tmp2);
			counter++;
			if (flat_number.size1 < counter){
				flat_number = flat_number.addLine(this->line_vector);
			}
			else {
				flat_number.setVectorToLine(counter - 1, line_vector);
			}

			in >> tmp2;
			line_vector.setElement(0, 0, tmp2);
			in >> tmp2;
			line_vector.setElement(0, 1, tmp2);
			in >> tmp2;
			line_vector.setElement(0, 2, tmp2);
			counter++;
			if (flat_number.size1 < counter){
				flat_number = flat_number.addLine(this->line_vector);
			}
			else {
				flat_number.setVectorToLine(counter - 1, line_vector);
			}

			all_flats_numbers.push_back(flat_number);
		}
	}
}

// создаёт сами поверхности из номеров вертексов
void Reader::createFlatsFromVertexNumber() {
	int i = 0;
	// проходим все матрицы с номерами вертексов на нулевой позиции
	for (Matrix flat_number : all_flats_numbers) {
		// берём все строки очередной матрицы
		for (i = 0; i < flat_number.size1; i++) {
			//если размер матрцы [0] или [3, а нужен 4], то увеличиваем его добавлением вектора
			if (flat.size1 < flat_number.size1) {
				flat = flat.addLine(all_vertexs.at(flat_number.getElement(i, 0) - 1));
			}
			// если размер матрицы подходящий
			else {
				flat.setVectorToLine(i, all_vertexs.at(flat_number.getElement(i, 0) - 1));
			}
			
		}
		all_flats.push_back(flat);
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
