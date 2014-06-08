#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <GL\GLU.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include "Reader.h"
#include "Drawer.h"
#include "ModelMovements.h"
#include "Object.h"
#include <process.h>
#include <thread>

#define MOVEMENT_STEP 0.05
#define PI 3.14159265

typedef struct CAMERA_POSITION {
	float x;
	float y;
	float z;
};

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void init();
bool initGL();
void handleKeys( unsigned char key, int x, int y );
void update();
void draw();
void close();
void handleMouseCoord(SDL_Event e);

SDL_Window* gWindow = NULL;
SDL_GLContext gContext;
SDL_Texture *patrickTexture;
SDL_Renderer *patrickRenderer;
SDL_Surface *patrickSurface;
Reader reader;
Drawer drawer;
ModelMovements modelMover;

Object patrick;

int x = 0, y = 0, prevX=0, prevY=0;

bool gRenderQuad = true;

int deltaX = 0;
CAMERA_POSITION cp;

void init()
{
	patrick = Object("Patrick.obj");

	SDL_Init( SDL_INIT_VIDEO );
	
	//Use OpenGL 2.1
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

	gWindow = SDL_CreateWindow( "Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
	gContext = SDL_GL_CreateContext( gWindow );
	patrickRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	patrickSurface = SDL_LoadBMP("Patrick.bmp");
	patrickTexture = SDL_CreateTextureFromSurface(patrickRenderer, patrickSurface);
	

	//Use Vsync
	SDL_GL_SetSwapInterval(1);

	//Initialize OpenGL
	initGL();
}

bool initGL()
{
	bool success = true;
	cp.x = 2;
	cp.y = 5;
	cp.z = 2;
		//Initialize Projection Matrix
		glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(60, 1.0, 0.0, 7.0);

	//Initialize Modelview Matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluLookAt(cp.x, cp.y, cp.z,
          0.0, 0.0, 0.0,
          0.0, 1.0, 0.0);

	//Initialize clear color
	glClearColor( 0.f, 0.f, 0.f, 1.f );
	glEnable(GL_DEPTH_TEST);
	return success;
}
GLuint texturePatrick, textureChess;
GLuint* init_texture(char* filename) {
	GLuint texture;
	SDL_Surface *surface = IMG_Load(filename);

    if (surface==NULL) { 
        printf("Error: \"%s\"\n",SDL_GetError()); return 0;
    }

    glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w,surface->h, 0, GL_RGB,GL_UNSIGNED_BYTE,surface->pixels);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    SDL_FreeSurface(surface);
	return &texture;
}

void handleKeys( SDL_Scancode key, int x, int y )
{


	if ( key == SDL_SCANCODE_LEFT) {
		patrick.moveBy(-MOVEMENT_STEP, 0, 0);
	}

	if ( key == SDL_SCANCODE_UP) {
		patrick.moveBy(0, 0, MOVEMENT_STEP);
	}

	if ( key == SDL_SCANCODE_DOWN) {
		patrick.moveBy(0, 0, -MOVEMENT_STEP);
	}

	if ( key == SDL_SCANCODE_RIGHT) {
		patrick.moveBy(MOVEMENT_STEP, 0, 0);
	}

	if (key == SDL_SCANCODE_LCTRL) {
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		cp.x+=0.2;
		cp.y+=0.2;
		cp.z+=0.2;
		gluLookAt(cp.x, cp.y, cp.z,
          0.0, 0.0, 0.0,
          0.0, 1.0, 0.0);
	}

	if (key == SDL_SCANCODE_LALT) {
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		cp.x-=0.2;
		cp.y-=0.2;
		cp.z-=0.2;
		if(cp.x < 1 || cp.y <1 || cp.z <1)
			{cp.x=1; cp.y=1; cp.z=1;}
		gluLookAt(cp.x, cp.y, cp.z,
          0.0, 0.0, 0.0,
          0.0, 1.0, 0.0);
	}
}


void close()
{

	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	init();
	
	bool quit = false;

	SDL_Event e;

	SDL_StartTextInput();
	texturePatrick = *init_texture("Patrick1.bmp");
	textureChess = *init_texture("Chessboard.bmp");
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, textureChess);
		glEnable(GL_TEXTURE_2D);
		drawer.drawFloor(1, 1, 1);
		glDisable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D,texturePatrick);
		glEnable(GL_TEXTURE_2D);
		if(patrick.size != 0) {
			patrick.draw();
		}
		glDisable(GL_TEXTURE_2D);
		handleMouseCoord(e);
		SDL_PumpEvents();
		if(SDL_GetMouseState(&x, &y)&SDL_BUTTON(1)) {
			if(prevX!=prevY!=0){
				if(prevX-x > 20) {
					patrick.rotateByAxe({ 0, 0, 0 }, { 0, 0, 0 }, 25);
					//modelMover.rotate_model_in_x((prevX-x)*PI/180/5, patrickModel);
					}
				else if(x-prevX > 20) {
					//modelMover.rotate_model_in_x((prevX-x)*PI/180/5, patrickModel);
				}
				if(prevY-y > 20) {
					//modelMover.rotate_model_in_z((prevY-y)*PI/180/5, patrickModel);
				}
				else if(y-prevY > 20) {
					//modelMover.rotate_model_in_z((prevY-y)*PI/180/5, patrickModel);
				}
			}
		}
		SDL_GL_SwapWindow( gWindow );
	}
		
	SDL_StopTextInput();

	close();

	return 0;
}

//TODO: выполнить отрисовку в отдельном потоке. Как вариант -- библиотека thread из C++11.

void handleMouseCoord( SDL_Event e ) {

	SDL_GetMouseState( &x, &y );
	if( e.key.state == SDL_PRESSED)
		handleKeys( e.key.keysym.scancode, x, y );

	if(e.type == SDL_MOUSEBUTTONDOWN)
       {
          if(e.button.button == SDL_BUTTON_LEFT)
          {
			prevX = x;
			prevY = y;
          }
       }


}
