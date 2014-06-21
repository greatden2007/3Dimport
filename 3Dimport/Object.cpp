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
	this->flats = reader.getFlats(filename);
	searchFor_Height_Width_Depth_Center();
	
}

int Object::searchFor_Height_Width_Depth_Center() {
	VERTEX tmp;
	this->height = 0;
	this->width = 0;
	this->depth = 0;
	this->center = { 0, 0, 0 };
	for (auto &flat : this->flats) {
		if (flat.is2) {
			if (flat.v[0].x > this->width) {
				this->width = flat.v[0].x;
			}
			if (flat.v[0].y > this->height) {
				this->height = flat.v[0].y;
			}
			if (flat.v[0].z > this->depth) {
				this->depth = flat.v[0].z;
			}
			if (flat.v[1].x > this->width) {
				this->width = flat.v[1].x;
			}
			if (flat.v[1].y > this->height) {
				this->height = flat.v[1].y;
			}
			if (flat.v[1].z > this->depth) {
				this->depth = flat.v[1].z;
			}
		}
		else if (flat.is3) {
			if (flat.v[0].x > this->width) {
				this->width = flat.v[0].x;
			}
			if (flat.v[0].y > this->height) {
				this->height = flat.v[0].y;
			}
			if (flat.v[0].z > this->depth) {
				this->depth = flat.v[0].z;
			}
			if (flat.v[1].x > this->width) {
				this->width = flat.v[1].x;
			}
			if (flat.v[1].y > this->height) {
				this->height = flat.v[1].y;
			}
			if (flat.v[1].z > this->depth) {
				this->depth = flat.v[1].z;
			}
			if (flat.v[2].x > this->width) {
				this->width = flat.v[1].x;
			}
			if (flat.v[2].y > this->height) {
				this->height = flat.v[1].y;
			}
			if (flat.v[2].z > this->depth) {
				this->depth = flat.v[1].z;
			}
		}
		else if (flat.is4) {
			if (flat.v[0].x > this->width) {
				this->width = flat.v[0].x;
			}
			if (flat.v[0].y > this->height) {
				this->height = flat.v[0].y;
			}
			if (flat.v[0].z > this->depth) {
				this->depth = flat.v[0].z;
			}
			if (flat.v[1].x > this->width) {
				this->width = flat.v[1].x;
			}
			if (flat.v[1].y > this->height) {
				this->height = flat.v[1].y;
			}
			if (flat.v[1].z > this->depth) {
				this->depth = flat.v[1].z;
			}
			if (flat.v[2].x > this->width) {
				this->width = flat.v[1].x;
			}
			if (flat.v[2].y > this->height) {
				this->height = flat.v[1].y;
			}
			if (flat.v[2].z > this->depth) {
				this->depth = flat.v[1].z;
			}
			if (flat.v[3].x > this->width) {
				this->width = flat.v[1].x;
			}
			if (flat.v[3].y > this->height) {
				this->height = flat.v[1].y;
			}
			if (flat.v[4].z > this->depth) {
				this->depth = flat.v[1].z;
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