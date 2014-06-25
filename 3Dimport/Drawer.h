#pragma once
#include <vector>
#include "Reader.h"
class Drawer
	{
	public:
		Drawer(void);
		~Drawer(void);
		void drawFlats(std::vector<Matrix> flats);
		void drawFloor(float red, float green, float blue);
	private:
		void drawVertex(Matrix v);
		void drawTextureVertex(Matrix vt);
		void drawFlat(Matrix flat);
	};

