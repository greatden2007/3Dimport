#include "Object.h"
#define DEBUG

Object::Object()
{
}


Object::~Object()
{
}

Object::Object(const char *filename) {
	this->size = 1;
	this->flats = reader.readModel(filename);
	searchFor_Height_Width_Depth_Center();
}

int Object::searchFor_Height_Width_Depth_Center() {
	Matrix tmp(1, 3);
	this->height = 0;
	this->width = 0;
	this->depth = 0;
	this->center = { 0, 0, 0 };
	for (Matrix flat : this->flats) {
		for (int i = 0; i < flat.size1; i++) {
			if (flat.getElement(i, 0) > this->width) {
				this->width = flat.getElement(i, 0);
			}
			if (flat.getElement(i, 1) > this->height) {
				this->height = flat.getElement(i, 1);
			}
			if (flat.getElement(i, 2) > this->depth) {
				this->depth = flat.getElement(i, 2);
			}
		}
	}
	center = { width / 2.0f, height / 2.0f, depth / 2.0f };
	return 0;
}


int Object::draw() {
	drawer.drawFlats(flats);
	return 0;
}

int Object::moveBy(float x, float y, float z) {
	modelMover.move_model_by(x, y, z, flats);
	return 0;
}

int Object::rotateByAxe(Point axePoint1, Point axePoint2, float angle) {
	axePoint1 = this->center;
	axePoint2 = this->center;
	axePoint2.y -= 1;
#ifdef DEBUG
	std::cout << "rotation in points:\n\tp1: " << axePoint1.x << " " << axePoint1.y << " " << axePoint1.z << "\n"
		<< "\tp2:" << axePoint2.x << " " << axePoint2.y << " " << axePoint2.z << "\n"
		<< "by angle: " << angle << "\n"
		<< "center: " << this->center.x << " " << this->center.y << " " << this->center.z << "\n"
		<< "box: " << this->width << " " << this->height << " " << this->depth << "\n";
#endif
	modelMover.rotate_model_in_axe(axePoint1, axePoint2, angle, this->flats);
	return 0;
}

int Object::rotateBySelfAxe(const char *axeName, float angle) {

	return 0;
}

int Object::rotateByCenter(float x, float y, float z) {
	return 0;
}