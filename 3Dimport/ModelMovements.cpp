#include "ModelMovements.h"
#define DEGREES_IN_RADIAN 57.2957795
#define RADIANS_IN_DEGREES 0.017444


ModelMovements::ModelMovements(void)
	{
	}


ModelMovements::~ModelMovements(void)
	{
	}

void ModelMovements::move_model_by(float x, float y, float z, std::vector<FLAT> &flats) {
	for (auto &flat : flats) {

		if (flat.is2) {
			flat.v[0].x += x; flat.v[0].y += y; flat.v[0].z += z;
			flat.v[1].x += x; flat.v[1].y += y; flat.v[1].z += z;
		}

		if (flat.is3) {
			flat.v[0].x += x; flat.v[0].y += y; flat.v[0].z += z;
			flat.v[1].x += x; flat.v[1].y += y; flat.v[1].z += z;
			flat.v[2].x += x; flat.v[2].y += y; flat.v[2].z += z;
		}

		if (flat.is4) {
			flat.v[0].x += x; flat.v[0].y += y; flat.v[0].z += z;
			flat.v[1].x += x; flat.v[1].y += y; flat.v[1].z += z;
			flat.v[2].x += x; flat.v[2].y += y; flat.v[2].z += z;
			flat.v[3].x += x; flat.v[3].y += y; flat.v[3].z += z;
		}

	}
}

void ModelMovements::rotate_model_in_z(float angle, std::vector<FLAT> &flats){
	for(auto &flat:flats) {
		float originalX;
		if(flat.is2) {
			originalX = flat.v[0].x;
			flat.v[0].x = originalX*cos(angle) - flat.v[0].y*sin(angle);
			flat.v[0].y = originalX*sin(angle) + flat.v[0].y*cos(angle);
			originalX = flat.v[1].x;
			flat.v[1].x = originalX*cos(angle) - flat.v[1].y*sin(angle);
			flat.v[1].y = originalX*sin(angle) + flat.v[1].y*cos(angle);
		}

		if(flat.is3) {
			originalX = flat.v[0].x;
			flat.v[0].x = originalX*cos(angle) - flat.v[0].y*sin(angle);
			flat.v[0].y = originalX*sin(angle) + flat.v[0].y*cos(angle);
			originalX = flat.v[1].x;
			flat.v[1].x = originalX*cos(angle) - flat.v[1].y*sin(angle);
			flat.v[1].y = originalX*sin(angle) + flat.v[1].y*cos(angle);
			originalX = flat.v[2].x;
			flat.v[2].x = originalX*cos(angle) - flat.v[2].y*sin(angle);
			flat.v[2].y = originalX*sin(angle) + flat.v[2].y*cos(angle);
		}

		if(flat.is4) {
			originalX = flat.v[0].x;
			flat.v[0].x = originalX*cos(angle) - flat.v[0].y*sin(angle);
			flat.v[0].y = originalX*sin(angle) + flat.v[0].y*cos(angle);
			originalX = flat.v[1].x;
			flat.v[1].x = originalX*cos(angle) - flat.v[1].y*sin(angle);
			flat.v[1].y = originalX*sin(angle) + flat.v[1].y*cos(angle);
			originalX = flat.v[2].x;
			flat.v[2].x = originalX*cos(angle) - flat.v[2].y*sin(angle);
			flat.v[2].y = originalX*sin(angle) + flat.v[2].y*cos(angle);
			originalX = flat.v[3].x;
			flat.v[3].x = originalX*cos(angle) - flat.v[3].y*sin(angle);
			flat.v[3].y = originalX*sin(angle) + flat.v[3].y*cos(angle);
		}
	}
}

void ModelMovements::rotate_model_in_x(float angle, std::vector<FLAT> &flats){
	for(auto &flat:flats) {
		float originalY;
		if(flat.is2) {
			originalY = flat.v[0].y;
			flat.v[0].y = originalY*cos(angle) - flat.v[0].z*sin(angle);
			flat.v[0].z = originalY*sin(angle) + flat.v[0].z*cos(angle);
			originalY = flat.v[1].y;
			flat.v[1].y = originalY*cos(angle) - flat.v[1].z*sin(angle);
			flat.v[1].z = originalY*sin(angle) + flat.v[1].z*cos(angle);
		}

		if(flat.is3) {
			originalY = flat.v[0].y;
			flat.v[0].y = originalY*cos(angle) - flat.v[0].z*sin(angle);
			flat.v[0].z = originalY*sin(angle) + flat.v[0].z*cos(angle);
			originalY = flat.v[1].y;
			flat.v[1].y = originalY*cos(angle) - flat.v[1].z*sin(angle);
			flat.v[1].z = originalY*sin(angle) + flat.v[1].z*cos(angle);
			originalY = flat.v[2].y;
			flat.v[2].y = originalY*cos(angle) - flat.v[2].z*sin(angle);
			flat.v[2].z = originalY*sin(angle) + flat.v[2].z*cos(angle);
		}

		if(flat.is4) {
			originalY = flat.v[0].y;
			flat.v[0].y = originalY*cos(angle) - flat.v[0].z*sin(angle);
			flat.v[0].z = originalY*sin(angle) + flat.v[0].z*cos(angle);
			originalY = flat.v[1].y;
			flat.v[1].y = originalY*cos(angle) - flat.v[1].z*sin(angle);
			flat.v[1].z = originalY*sin(angle) + flat.v[1].z*cos(angle);
			originalY = flat.v[2].y;
			flat.v[2].y = originalY*cos(angle) - flat.v[2].z*sin(angle);
			flat.v[2].z = originalY*sin(angle) + flat.v[2].z*cos(angle);
			originalY = flat.v[3].y;
			flat.v[3].y = originalY*cos(angle) - flat.v[3].z*sin(angle);
			flat.v[3].z = originalY*sin(angle) + flat.v[3].z*cos(angle);
		}
	}
}


void ModelMovements::rotate_model_in_axe(Point p0, Point p1, float angle, std::vector<FLAT> &flats) {
	angle = angle*RADIANS_IN_DEGREES;
	Matrix T(4, 4), M(4, 4), Rx(4, 4), Ry(4, 4), Rd(4, 4), inv_T(4, 4), inv_Rx(4, 4), inv_Ry(4, 4), C(1, 3);

	//c
	float devider = sqrt(pow((p1.x - p0.x), 2) + pow((p1.y - p0.y), 2) + pow((p1.z - p0.z), 2));
	C.setElement(0, 0, (p1.x - p0.x) / devider);
	C.setElement(0, 1, (p1.y - p0.y) / devider);
	C.setElement(0, 2, (p1.z - p0.z) / devider);

	//d
	float d = sqrt(pow(C.getElement(0, 1), 2) + pow(C.getElement(0, 2), 2));

	//Rd
	printf("Rd\n");
	Rd.setElement(0, 0, -cos(angle));	//angle -- grad
	Rd.setElement(0, 1, sin(angle));
	Rd.setElement(1, 0, -sin(angle));
	Rd.setElement(1, 1, cos(angle));
	Rd.setElement(2, 2, 1);
	Rd.setElement(3, 3, 1);
	Rd.print();

	//Rx
	printf("Rx\n");
	Rx.setElement(0, 0, 1);
	Rx.setElement(3, 3, 1);
	Rx.setElement(1, 1, C.getElement(0, 2)/d);
	Rx.setElement(1, 2, C.getElement(0, 1) / d);
	Rx.setElement(2, 1, -C.getElement(0, 1) / d);
	Rx.setElement(2, 2, C.getElement(0, 2) / d);
	Rx.print();

	//Ry
	printf("Ry\n");
	Ry.setElement(0, 0, d);
	Ry.setElement(0, 2, C.getElement(0, 0));
	Ry.setElement(1, 1, 1);
	Ry.setElement(2, 0, -C.getElement(0, 0));
	Ry.setElement(2, 2, d);
	Ry.setElement(3, 3, 1);
	Ry.print();

	//T
	printf("T\n");
	T.setElement(0, 0, 1);
	T.setElement(1, 1, 1);
	T.setElement(2, 2, 1);
	T.setElement(3, 3, 1);
	T.setElement(3, 0, -p1.x);
	T.setElement(3, 1, -p1.y);
	T.setElement(3, 2, -p1.z);
	T.print();

	printf("M\n");
	M = T * Rx;
	M.print();
	M = M * Ry;
	M.print();

	for (auto &flat : flats) {
		if (flat.is2) {
			Matrix X(2, 4);
			X.setElement(0, 0, flat.v[0].x);
			X.setElement(0, 1, flat.v[0].y);
			X.setElement(0, 2, flat.v[0].z);
			X.setElement(0, 3, 1);

			X.setElement(1, 0, flat.v[1].x);
			X.setElement(1, 1, flat.v[1].y);
			X.setElement(1, 2, flat.v[1].z);
			X.setElement(1, 3, 1);

			X = X*M*Rd*M.inverseMatrix();

			flat.v[0].x = X.getElement(0, 0);
			flat.v[0].y = X.getElement(0, 1);
			flat.v[0].z = X.getElement(0, 2);

			flat.v[1].x = X.getElement(1, 0);
			flat.v[1].y = X.getElement(1, 1);
			flat.v[1].z = X.getElement(1, 2);

		}
		else if (flat.is3) {
			Matrix X(3, 4);
			X.setElement(0, 0, flat.v[0].x);
			X.setElement(0, 1, flat.v[0].y);
			X.setElement(0, 2, flat.v[0].z);
			X.setElement(0, 3, 1);

			X.setElement(1, 0, flat.v[1].x);
			X.setElement(1, 1, flat.v[1].y);
			X.setElement(1, 2, flat.v[1].z);
			X.setElement(1, 3, 1);

			X.setElement(2, 0, flat.v[2].x);
			X.setElement(2, 1, flat.v[2].y);
			X.setElement(2, 2, flat.v[2].z);
			X.setElement(2, 3, 1);

			X = X*M*Rd*M.inverseMatrix();

			flat.v[0].x = X.getElement(0, 0);
			flat.v[0].y = X.getElement(0, 1);
			flat.v[0].z = X.getElement(0, 2);

			flat.v[1].x = X.getElement(1, 0);
			flat.v[1].y = X.getElement(1, 1);
			flat.v[1].z = X.getElement(1, 2);

			flat.v[2].x = X.getElement(2, 0);
			flat.v[2].y = X.getElement(2, 1);
			flat.v[2].z = X.getElement(2, 2);
		}
		else if (flat.is4) {
			Matrix X(4, 4);
			X.setElement(0, 0, flat.v[0].x);
			X.setElement(0, 1, flat.v[0].y);
			X.setElement(0, 2, flat.v[0].z);
			X.setElement(0, 3, 1);

			X.setElement(1, 0, flat.v[1].x);
			X.setElement(1, 1, flat.v[1].y);
			X.setElement(1, 2, flat.v[1].z);
			X.setElement(1, 3, 1);

			X.setElement(2, 0, flat.v[2].x);
			X.setElement(2, 1, flat.v[2].y);
			X.setElement(2, 2, flat.v[2].z);
			X.setElement(2, 3, 1);

			X.setElement(3, 0, flat.v[3].x);
			X.setElement(3, 1, flat.v[3].y);
			X.setElement(3, 2, flat.v[3].z);
			X.setElement(3, 3, 1);

			X = X*M*Rd*M.inverseMatrix();

			flat.v[0].x = X.getElement(0, 0);
			flat.v[0].y = X.getElement(0, 1);
			flat.v[0].z = X.getElement(0, 2);

			flat.v[1].x = X.getElement(1, 0);
			flat.v[1].y = X.getElement(1, 1);
			flat.v[1].z = X.getElement(1, 2);

			flat.v[2].x = X.getElement(2, 0);
			flat.v[2].y = X.getElement(2, 1);
			flat.v[2].z = X.getElement(2, 2);

			flat.v[3].x = X.getElement(3, 0);
			flat.v[3].y = X.getElement(3, 1);
			flat.v[3].z = X.getElement(3, 2);
		}
	}
	cout << "\nrotation done at angle " << angle;
}
