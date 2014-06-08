#include "ModelMovements.h"
#define DEGREES_IN_RADIAN 57.2957795


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


	Matrix A(3, 4), B(4, 3);
	A.setElement(0, 0, 1);
	A.setElement(0, 1, 2);
	A.setElement(0, 2, 3);
	A.setElement(0, 3, 4);
	A.setElement(1, 0, 5);
	A.setElement(1, 1, 6);
	A.setElement(1, 2, 7);
	A.setElement(1, 3, 8);
	A.setElement(2, 0, 9);
	A.setElement(2, 1, 10);
	A.setElement(2, 2, 11);
	A.setElement(2, 3, 12);

	B.setElement(0, 0, 12);
	B.setElement(0, 1, 11);
	B.setElement(0, 2, 10);
	B.setElement(1, 0, 9);
	B.setElement(1, 1, 8);
	B.setElement(1, 2, 7);
	B.setElement(2, 0, 6);
	B.setElement(2, 1, 5);
	B.setElement(2, 2, 4);
	B.setElement(3, 0, 3);
	B.setElement(3, 1, 2);
	B.setElement(3, 2, 1);

	Matrix Z(3, 3);
	Z = A*B;

	Matrix T(4, 4), M(4, 4), Rx(4, 4), Ry(4, 4), Rd(4, 4), inv_T(4, 4), inv_Rx(4, 4), inv_Ry(4, 4), C(1, 3);

	//c
	float devider = sqrt(pow((p1.x - p0.x), 2) + pow((p1.y - p0.y), 2) + pow((p1.z - p0.z), 2));
	C.setElement(0, 0, (p1.x - p0.x) / devider);
	C.setElement(0, 1, (p1.y - p0.y) / devider);
	C.setElement(0, 2, (p1.z - p0.z) / devider);

	//d
	float d = sqrt(pow(C.getElement(0, 1), 2) + pow(C.getElement(0, 2), 2));

	//alpha & betta
	float alpha = acos(C.getElement(0, 2) / d) * DEGREES_IN_RADIAN;
	float betta = acos(d) * DEGREES_IN_RADIAN;

	//Rd
	Rd.setElement(0, 0, -cos(angle));
	Rd.setElement(0, 1, sin(angle));
	Rd.setElement(1, 0, -sin(angle));
	Rd.setElement(1, 1, cos(angle));

	//Rx
	Rx.setElement(0, 0, 1);
	Rx.setElement(3, 3, 1);
	Rx.setElement(1, 1, cos(alpha));
	Rx.setElement(1, 2, sin(alpha));
	Rx.setElement(2, 1, -sin(alpha));
	Rx.setElement(2, 2, cos(alpha));

	//Ry
	Ry.setElement(0, 0, d);
	Ry.setElement(0, 2, C.getElement(0, 0));
	Ry.setElement(1, 1, 1);
	Ry.setElement(2, 0, -C.getElement(0, 0));
	Ry.setElement(2, 2, d);
	Ry.setElement(3, 3, 1);

	//T
	T.setElement(0, 0, 1);
	T.setElement(1, 1, 1);
	T.setElement(2, 2, 1);
	T.setElement(3, 3, 1);
	T.setElement(3, 0, p1.x);
	T.setElement(3, 1, p1.y);
	T.setElement(3, 2, p1.z);

	inv_T = T.inverseMatrix();
	inv_Rx = Rx.inverseMatrix();
	inv_Ry = Ry.inverseMatrix();

	M = T*Rx*Ry*Rd*inv_Ry*inv_Rx*inv_T;

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

			//X = M*X;

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

			//X = M*X;
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

			//X = M*X;
		}
	}

	/*
	matrix<float> T(4, 4), M(4, 4), Rx(4, 4), Ry(4, 4), Rd(4, 4), inv_T(4, 4), inv_Rx(4, 4), inv_Ry(4, 4);
	boost::numeric::ublas::vector<float> c(3);

	//c
	float devider = sqrt(pow((p1.x - p0.x), 2) + pow((p1.y - p0.y), 2) + pow((p1.z - p0.z), 2));
	c(0) = (p1.x - p0.x) / devider;
	c(1) = (p1.y - p0.y) / devider;
	c(2) = (p1.z - p0.z) / devider;

	//d
	float d = sqrt( pow(c(1), 2) + pow(c(2), 2) );
	
	//alpha & betta
	float alpha = acos(c(2) / d);
	float betta = acos(d);

	//Rd
	Rd(0, 0) = -cos(angle);
	Rd(0, 1) = sin(angle);
	Rd(1, 0) = -sin(angle);
	Rd(1, 1) = cos(angle);

	//Rx
	Rx(0, 0) = 1;
	Rx(3, 3) = 1;
	Rx(1, 1) = cos(alpha);
	Rx(1, 2) = sin(alpha);
	Rx(2, 1) = -sin(alpha);
	Rx(2, 2) = cos(alpha);
	
	//Ry
	Ry(0, 0) = d;
	Ry(0, 2) = c(0);
	Ry(1, 1) = 1;
	Ry(2, 0) = -c(0);
	Ry(2, 2) = d;
	Ry(3, 3) = 1;

	//T
	T(0, 0) = 1;
	T(1, 1) = 1;
	T(2, 2) = 1;
	T(3, 3) = 1;
	T(3, 0) = p1.x;
	T(3, 1) = p1.y;
	T(3, 2) = p1.z;

	InvertMatrix(T, inv_T);
	InvertMatrix(Rx, inv_Rx);
	InvertMatrix(Ry, inv_Ry);

	M = prod(prod(Ry, inv_Ry), Ry);

	for (auto &flat : flats) {
		if (flat.is2) {
			matrix<float> X(2, 4);
			X(0, 0) = flat.v[0].x;
			X(0, 1) = flat.v[0].y;
			X(0, 2) = flat.v[0].z;
			X(0, 3) = 1;

			X(1, 0) = flat.v[1].x;
			X(1, 1) = flat.v[1].y;
			X(1, 2) = flat.v[1].z;
			X(1, 3) = 1;

			X = prod(M, X);

		}
		else if (flat.is3) {
			matrix<float> X(3, 4);
			X(0, 0) = flat.v[0].x;
			X(0, 1) = flat.v[0].y;
			X(0, 2) = flat.v[0].z;
			X(0, 3) = 1;

			X(1, 0) = flat.v[1].x;
			X(1, 1) = flat.v[1].y;
			X(1, 2) = flat.v[1].z;
			X(1, 3) = 1;

			X(2, 0) = flat.v[2].x;
			X(2, 1) = flat.v[2].y;
			X(2, 2) = flat.v[2].z;
			X(2, 3) = 1;

			//X = prod(M, X);
		}
		else if (flat.is4) {
			matrix<float> X(4, 4);
			X(0, 0) = flat.v[0].x;
			X(0, 1) = flat.v[0].y;
			X(0, 2) = flat.v[0].z;
			X(0, 3) = 1;

			X(1, 0) = flat.v[1].x;
			X(1, 1) = flat.v[1].y;
			X(1, 2) = flat.v[1].z;
			X(1, 3) = 1;

			X(2, 0) = flat.v[2].x;
			X(2, 1) = flat.v[2].y;
			X(2, 2) = flat.v[2].z;
			X(2, 3) = 1;

			X(3, 0) = flat.v[3].x;
			X(3, 1) = flat.v[3].y;
			X(3, 2) = flat.v[3].z;
			X(3, 3) = 1;

			//X = prod(M, X);
		}
	}
	*/
}
