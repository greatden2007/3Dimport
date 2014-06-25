#include "Drawer.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <algorithm>

Drawer::Drawer(void)
	{
	}

Drawer::~Drawer(void)
	{
	}

void Drawer::drawVertex(Matrix v) {
	glVertex3f(v.getElement(0, 0), v.getElement(0, 1), v.getElement(0, 2));
}

void Drawer::drawTextureVertex(Matrix vt) {
	glTexCoord2f(vt.getElement(0, 0), vt.getElement(0, 1));
}

void Drawer::drawFlat(Matrix flat) {

	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	Matrix vertex(1, 3);
	for (int i = 0; i < flat.size1; i++)  {
		vertex.setElement(0, 0, flat.getElement(i, 0));
		vertex.setElement(0, 1, flat.getElement(i, 1));
		vertex.setElement(0, 2, flat.getElement(i, 2));
		drawVertex(vertex);
		//TODO: drawTextureVertex(texture_vertex);
		// сложность в том, что нужно добавить поля в матрицу flat. но тогда с ней нельзя делать мат. операций.
		// или создать новую матрицу texture_flat;
	}
	glEnd();
}

void Drawer::drawFlats(std::vector<Matrix> flats) {
	for( auto flat:flats) {
		drawFlat(flat);
	}
}

void Drawer::drawFloor(float red, float green, float blue) {
	glColor3f(red, green, blue);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(-10, 0, -10);
	glTexCoord2f(0.0, 1.0);
	glVertex3d(10, 0, -10);
	glTexCoord2f(1.0, 1.0);
	glVertex3d(10, 0, 10);
	glTexCoord2f(1.0, 0.0);
	glVertex3d(-10, 0, +10);
	glEnd();
}