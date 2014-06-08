#include "Math.h"
# define M_PI 3.14159265358979323846

float findAngle(float cos_in, float sin_in) {
	float angle, angle2;
	angle = acos(cos_in);
	angle2 = asin(sin_in);

	//Округление до второго знака после запятой для нормального сравнения
	angle = floorf(angle * 100 + 0.5) / 100;
	angle2 = floorf(angle2 * 100 + 0.5) / 100;

	float temp_angle1 = acos(cos(M_PI - angle2));
	temp_angle1 = floorf(temp_angle1 * 100 + 0.5) / 100;
	float temp_angle2 = asin(sin(2 * M_PI - angle));
	temp_angle2 = floorf(temp_angle2 * 100 + 0.5) / 100;
	
	if (angle == angle2) {
		return angle;
	}
	else if (temp_angle1 == angle) {
		return angle;
	}
	else if (temp_angle2 == angle2) {
		return angle2;
	}
}