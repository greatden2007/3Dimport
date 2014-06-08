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

void Drawer::drawVertex(VERTEX v) {
	glVertex3f(v.x, v.y, v.z);
}

void Drawer::drawTextureVertex(TEXTURE_VERTEX vt) {
	glTexCoord2f(vt.x, vt.y);
}

void Drawer::drawFlat(FLAT flat) {

	glColor3f(1, 1, 1);
	if( flat.is2) {
	glBegin( GL_LINES );
	drawTextureVertex(flat.vt[0]);
	drawVertex(flat.v[0]);
	drawTextureVertex(flat.vt[1]);
	drawVertex(flat.v[1]);
	glEnd();

	//glColor3f(0.0f, 0.0f, 0.0f);
	//glBegin(GL_LINES);
	//drawVertex(flat.v[0]);
	//drawVertex(flat.v[1]);
	//glEnd();
	}

	else if (flat.is3) {
	glColor3f(1, 1, 1);
	glBegin( GL_TRIANGLES );
	drawTextureVertex(flat.vt[0]);
	drawVertex(flat.v[0]);
	drawTextureVertex(flat.vt[1]);
	drawVertex(flat.v[1]);
	drawTextureVertex(flat.vt[2]);
	drawVertex(flat.v[2]);
	glEnd();

	//glColor3f(0.0f, 0.0f, 0.0f);
	//glBegin(GL_LINES);
	//drawVertex(flat.v[0]);
	//drawVertex(flat.v[1]);
	//drawVertex(flat.v[1]);
	//drawVertex(flat.v[2]);
	//drawVertex(flat.v[2]);
	//drawVertex(flat.v[0]);
	//glEnd();
	}

	else if (flat.is4) {
	glColor3f(1, 1, 1);
	glBegin( GL_QUADS );
	drawTextureVertex(flat.vt[0]);
	drawVertex(flat.v[0]);
	drawTextureVertex(flat.vt[1]);
	drawVertex(flat.v[1]);
	drawTextureVertex(flat.vt[2]);
	drawVertex(flat.v[2]);
	drawTextureVertex(flat.vt[3]);
	drawVertex(flat.v[3]);
	glEnd();

	//glColor3f(0.0f, 0.0f, 0.0f);
	//glBegin(GL_LINES);
	//drawVertex(flat.v[0]);
	//drawVertex(flat.v[1]);
	//drawVertex(flat.v[1]);
	//drawVertex(flat.v[2]);
	//drawVertex(flat.v[2]);
	//drawVertex(flat.v[3]);
	//drawVertex(flat.v[3]);
	//drawVertex(flat.v[0]);
	//glEnd();
	}

	else std::cout << " I dont know how to draw this flat, sorry.";
}

void Drawer::drawFlats(std::vector<FLAT> flats) {
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