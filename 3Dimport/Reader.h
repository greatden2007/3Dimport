#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

typedef struct VERTEX {
	float x;
	float y;
	float z;
};

typedef struct TEXTURE_VERTEX {
	float x;
	float y;
};

typedef struct FLAT {
	bool is2;
	bool is3;
	bool is4;
	VERTEX v[4];
	TEXTURE_VERTEX vt[4];
};

using namespace std;
class Reader
	{
	public:
		Reader(void);
		~Reader(void);
		void readVertexsFromModelFile(const char* modelFileName);
		void readFlatsFromModelFile(const char* modelFileName);
		std::vector<FLAT> getFlats(const char* modelFileName);

	private:
		void swapVertexs (VERTEX &v1, VERTEX &v2);
		void swapTextureVertexs (TEXTURE_VERTEX &vt1, TEXTURE_VERTEX &vt2);
		virtual virtual void make_FLAT_from_VERTEX(const char* modelFileName);
		std::vector<FLAT> all_flats;
		std::vector<VERTEX> all_vertexs;
		std::vector<TEXTURE_VERTEX> all_texture_vertexes;
		TEXTURE_VERTEX texture_vertex;
		VERTEX vertex;
		FLAT flat;
		int lines;
		int percents;
		
	};

