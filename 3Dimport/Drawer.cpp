#include "Drawer.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <algorithm>
#include <ctime>

Drawer::Drawer(void)
	{
	}

Drawer::~Drawer(void)
	{
	}

void Drawer::drawVertex(Matrix &v) {
	glVertex3f(v.getElement(0, 0), v.getElement(0, 1), v.getElement(0, 2));
}

void Drawer::drawTextureVertex(Matrix &vt) {
	glTexCoord2f(vt.getElement(0, 0), vt.getElement(0, 1));
}

void Drawer::drawFlat(Matrix &flat) {
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < flat.size1; i++)  {
		this->vertex.setElement(0, 0, flat.getElement(i, 0));
		this->vertex.setElement(0, 1, flat.getElement(i, 1));
		this->vertex.setElement(0, 2, flat.getElement(i, 2));
		drawVertex(this->vertex);
		//TODO: drawTextureVertex(texture_vertex);
		// сложность в том, что нужно добавить поля в матрицу flat. но тогда с ней нельзя делать мат. операций.
		// или создать новую матрицу texture_flat;
	}
	glEnd();
}

void Drawer::drawFlats(std::vector<Matrix> &flats) {
	clock_t t = clock();
	for( auto &flat:flats) {
		drawFlat(flat);
	}
	cout << "All flats drawed in " << clock() - t << "ms With FPS:" << (float)(1000.0/(clock()-t)) << "\n";
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