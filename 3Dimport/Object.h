#pragma once
#include "Reader.h"
#include "Drawer.h"
#include "ModelMovements.h"

class Object
{
private:
	std::vector<FLAT> flats;
	Reader reader;
	Drawer drawer;
	ModelMovements modelMover;
	
	int searchFor_Height_Width_Depth_Center();
public:
	Object();
	Object(const char *filename);
	~Object();
	int size;
	float mass;
	float acceleration;
	float height;
	float width;
	float depth;
	Point center;

	int draw();
	int moveBy(float x, float y, float z);
	int rotateByAxe(Point axePoint1, Point axePoint2, float angle);
	int rotateBySelfAxe(const char *axeName, float angle);
	int rotateByCenter(float x, float y, float z);
};

