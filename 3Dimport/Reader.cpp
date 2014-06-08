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

void Reader::readVertexsFromModelFile(const char* modelFileName) {

	ifstream ModelFile (modelFileName, ifstream::binary);
	int permamentPercents = 0;
	std::cout <<"Reading Vertexes:  0%" ;

	for(string line; getline(ModelFile, line); ) {

		istringstream in(line);  

		string type;
		in >> type;      

		// first part.
		// if get VERTEX line in file
		if(type.compare("v") == 0) {
			in >> vertex.x >> vertex.y >> vertex.z;  
			all_vertexs.push_back(vertex);
			permamentPercents = (all_vertexs.size()+all_texture_vertexes.size()) * 100 / lines ;
			if(permamentPercents - this->percents > 0) {
				this->percents = permamentPercents;
				if(this->percents < 10)
					std::cout << "\b\b" << this->percents << "\%";
				else
					std::cout << "\b\b\b" << this->percents << "\%";
			}
		}

		if(type.compare("vt") == 0) {
			in >> texture_vertex.x >> texture_vertex.y;
			all_texture_vertexes.push_back(texture_vertex);
			permamentPercents = (all_vertexs.size()+all_texture_vertexes.size()) * 100 / lines  ;
			if(permamentPercents - this->percents > 0) {
				this->percents = permamentPercents;
				if(this->percents < 10)
					std::cout << "\b\b" << this->percents << "\%";
				else
					std::cout << "\b\b\b" << this->percents << "\%";
			}
		}

	}
	ModelFile.close();
	ofstream logFile ("log.txt",ios::ate);
	logFile << "\nEnd reading vertexs \n";
	std::cout << "\nEnd reading vertexs \n";
	logFile.close();

}


void Reader::make_FLAT_from_VERTEX(const char* modelFileName) {
	ifstream ModelFile (modelFileName, ifstream::binary);
	std::string error;
	std::cout << "Reading flats:  0%";
	int permamentPercents = 0;

	int vertex_in_flat_counter = 0;
	for(string line; getline(ModelFile, line); ) {
		istringstream in(line); 
		string type;
		in >> type; 

		// second part.
		// if get FLAT line in file
		if(type.compare("f") == 0) {
			vertex_in_flat_counter = 0;
			std::regex rgx("\\s(\\d+)");
			std::smatch match;
			std::smatch match_for_textures;
			string bufferString(line);
			string bufferstring_for_textures(line);
			while (std::regex_search(bufferString, match, rgx)) {
				bufferString = match.suffix().str();
				vertex_in_flat_counter++;
			}

			int i = 0;
			int vtNumber = 0;
			boost::regex regex_for_textures("(?:\/)(\\d+)(?:\/)");
			boost::smatch xResults;
			std::string::const_iterator xItStart = bufferstring_for_textures.begin();
			std::string::const_iterator xItEnd = bufferstring_for_textures.end();
			while( boost::regex_search(xItStart, xItEnd, xResults, regex_for_textures) )
			{
			  std::string str = xResults[1];
			  xItStart = xResults[1].second;
			  vtNumber = atoi(str.c_str())-1; 
			  	switch (vertex_in_flat_counter)
					{
					case 2:
						flat.is2 = true;
						swapTextureVertexs(flat.vt[i], all_texture_vertexes[vtNumber]);
						i++;
						break;
					case 3:
						flat.is3 = true;
						swapTextureVertexs(flat.vt[i], all_texture_vertexes[vtNumber]);
						i++;
						break;
					case 4:
						flat.is4 = true;
						swapTextureVertexs(flat.vt[i], all_texture_vertexes[vtNumber]);
						i++;
						break;
					default:
						error = "unrecognized flat! \n";
						break;
					}
			}
			i=0;
			while (std::regex_search(line, match, rgx)) {
				string floatString(match[0]);
				int f = ::atof(floatString.c_str());
				//cout << " " << f;
				f--;
				line = match.suffix().str();

				switch (vertex_in_flat_counter)
					{
					case 2:
						flat.is2 = true;
						swapVertexs(flat.v[i], all_vertexs[f]);
						//cout << "vertex: " << all_vertexs[f].x << " " << all_vertexs[f].y << " " << all_vertexs[f].z << endl;
						i++;
						break;
					case 3:
						flat.is3 = true;
						swapVertexs(flat.v[i], all_vertexs[f]);
						//cout << "vertex: " << all_vertexs[f].x << " " << all_vertexs[f].y << " " << all_vertexs[f].z << endl;
						i++;
						break;
					case 4:
						flat.is4 = true;
						swapVertexs(flat.v[i], all_vertexs[f]);
						//cout << "vertex: " << all_vertexs[f].x << " " << all_vertexs[f].y << " " << all_vertexs[f].z << endl;
						i++;
						break;
					default:
						error = "unrecognized flat! \n";
						break;
					}
			}
			all_flats.push_back(flat);
			permamentPercents = (all_vertexs.size()+all_flats.size()+all_texture_vertexes.size()) * 100 / lines ;
			if(permamentPercents - this->percents > 0) {
				this->percents = permamentPercents;
				if(this->percents > 99) percents = 99;
				if(this->percents < 10)
					std::cout << "\b\b" << this->percents << "\%";
				else
					std::cout << "\b\b\b" << this->percents << "\%";
			}
		}
	}
	ModelFile.close();
	ofstream logFile ("log.txt",ios::ate);
	logFile << "\nEnd reading flats with errors: \n" << error;
	std::cout << "\nEnd reading flats with errors: \n" << error;
	logFile.close();
}

//TODO: перегрузка оператора "=" для вертексов -- !!! возможно только при создании класса VERTEX и в нём изменении оператора "=".
void Reader::swapVertexs (VERTEX &v1, VERTEX &v2) {
	v1.x = v2.x;
	v1.y = v2.y;
	v1.z = v2.z;
}

void Reader::swapTextureVertexs (TEXTURE_VERTEX &vt1, TEXTURE_VERTEX &vt2) {
	vt1.x = vt2.x;
	vt1.y = vt2.y;
}

vector<FLAT> Reader::getFlats(const char* modelFileName) {
	// Следующий код подсчитывает количество строк в файле. Исходя из того, что в каждой строке
	// примерно 31 символов =))
	clock_t t1,t2;
    t1=clock();

	ifstream ModelFile (modelFileName, ios::binary | ios::ate);
	int filesize = ModelFile.tellg();
	lines = filesize/31;
	std::cout << "file size: " << lines << " lines" << endl;
	ModelFile.close();

	this->readVertexsFromModelFile(modelFileName);
	this->make_FLAT_from_VERTEX(modelFileName);

	t2 = clock();
	float loadingModelTime = (float)t2 - (float)t1;
	std::cout << "Time for Loading model: " << loadingModelTime/1000 << "seconds. All vertexes: " << all_vertexs.size()+all_texture_vertexes.size() << "(including texture vertexes: " 
		<< all_texture_vertexes.size() << "). All flats: " << all_flats.size() << std::endl;
	return all_flats;
}


