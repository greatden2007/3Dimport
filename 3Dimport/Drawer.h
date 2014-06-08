#pragma once
#include <vector>
#include "Reader.h"
class Drawer
	{
	public:
		Drawer(void);
		~Drawer(void);
		void drawFlats(std::vector<FLAT> flats);
		void drawFloor(float red, float green, float blue);
	private:
		void drawVertex(VERTEX v);
		void drawTextureVertex(TEXTURE_VERTEX vt);
		void drawFlat(FLAT flat);
	};

