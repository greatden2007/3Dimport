#pragma once
#include "Reader.h"
#include <math.h>
#include "Math.h""
#include "Matrix.h"

struct Point {
	float x;
	float y;
	float z;
};

class ModelMovements
	{
	public:
		ModelMovements(void);
		~ModelMovements(void);
		void move_model_by(float x, float y, float z, std::vector<Matrix> &flats);
		void rotate_model_in_axe(Point x0, Point x1, float angle, std::vector<Matrix> &flats);
		void rotate_model_in_z(float angle, std::vector<Matrix> &flats);
		void rotate_model_in_x(float angle, std::vector<Matrix> &flats);
	};

