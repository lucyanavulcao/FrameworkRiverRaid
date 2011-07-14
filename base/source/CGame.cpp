/*
 *  CGame.cpp
 *  Main game class
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#include "CGame.h"
#include "CGameState.h"

#include <iostream>
#include <assert.h>
#include <cmath>
#include <irrKlang.h>

using namespace std;

// Construtor
CGame::CGame(int minFrameRate, int maxFrameRate)
{
    this->minFrameRate = minFrameRate;
    this->maxFrameRate = maxFrameRate;
    updateInterval = 1.0 / maxFrameRate*1000;
    cout << "Update interval: " << updateInterval << endl;
    maxCyclesPerFrame = (double) maxFrameRate / minFrameRate;
    lastFrameTime = 0;
    cyclesLeftOver = 0;
    panX = panY = 0; // camera panning
}

void CGame::init(const char* title, int width, int height, int bpp, bool fullscreen)
{
    flags = SDL_OPENGL | SDL_RESIZABLE;
    this->bpp = bpp;

	// initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// set the title bar text
	SDL_WM_SetCaption(title, title);

	if ( fullscreen ) {
		flags |= SDL_FULLSCREEN;
	}

    // Request double-buffered OpenGL
    SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);

    // Request 16 bit depth buffer - not used
    //value = 16;
    //SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, value);

	// create the screen surface
	screen = SDL_SetVideoMode(width, height, bpp, flags);

    // Enable transparency through blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    xmin = 0;
    xmax = width;
    ymin = 0;
    ymax = height;
    zoom = 1;
    updateCamera();

	this->fullscreen = fullscreen;

	running = true;

    printAttributes();
	audioEngine = irrklang::createIrrKlangDevice();
	printf("Game Initialised Succesfully\n");
}


void CGame::printAttributes ()
{
    int nAttr;
    int i;

    SDL_GLattr attr[] = { SDL_GL_RED_SIZE, SDL_GL_BLUE_SIZE, SDL_GL_GREEN_SIZE,
                    SDL_GL_ALPHA_SIZE, SDL_GL_BUFFER_SIZE, SDL_GL_DEPTH_SIZE };

    const char *desc[] = { "Red size: %d bits\n", "Blue size: %d bits\n", "Green size: %d bits\n",
                     "Alpha size: %d bits\n", "Color buffer size: %d bits\n",
                     "Depth bufer size: %d bits\n" };

    nAttr = sizeof(attr) / sizeof(int);

    for (i = 0; i < nAttr; i++) {

        int value;
        SDL_GL_GetAttribute (attr[i], &value);
        printf (desc[i], value);
    }
}

void CGame::handleEvents()
{
    states.top()->handleEvents(this);
}

/** @brief setXpan
  *
  * @todo: document this function
  */
void CGame::setXpan(float xpan)
{
    panX = xpan;
}

/** @brief setYpan
  *
  * @todo: document this function
  */
void CGame::setYpan(float ypan)
{
    panY = ypan;
}

/** @brief setZoom
  *
  * @todo: document this function
  */
void CGame::setZoom(float z)
{
    zoom = z;
}

void CGame::updateCamera()
{
		// FIXME: corrigir para fazer o pan somente em Y, e não em X
    // Setup 2D projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    float xwidth = (xmax-xmin)/2;
    float ywidth = (ymax-ymin)/2;
    float xcentre = (xmin+xmax)/2;
    float ycentre = (ymin+ymax)/2;
		// Trava o pan
    //xcentre += panX;
    ycentre += panY;
    float aspect = screen->w/(float)screen->h;
    xwidth -= zoom*aspect; //ceil(xwidth/zoom);
    ywidth -= zoom; //ceil(ywidth/zoom);
    glOrtho(xcentre-xwidth, xcentre+xwidth, ycentre+ywidth, ycentre-ywidth, -1.0f, 1.0f);

    // Setup viewport
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glViewport(0,0,screen->w,screen->h);
}

float CGame::getWidth()
{
    float xwidth = (xmax-xmin);
    return xwidth-zoom; //ceil(xwidth/zoom);
}

float CGame::getHeight()
{
    float ywidth = (ymax-ymin);
    return ywidth - zoom; //ceil(ywidth/zoom);
}

void CGame::resize(int w, int h)
{
    screen = SDL_SetVideoMode(w, h, bpp, flags);
    assert(screen != NULL);
    updateCamera();
}

void CGame::changeState(CGameState* state)
{
    // cleanup the current state
    if ( !states.empty() ) {
        states.top()->cleanup();
        states.pop();
    }

    // store and init the new state
    states.push(state);
    states.top()->init();
}

void CGame::pushState(CGameState* state)
{
	// pause current state
	if ( !states.empty() ) {
		states.top()->pause();
	}

	// store and init the new state
	states.push(state);
	states.top()->init();
}

void CGame::popState()
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.top()->cleanup();
		states.pop();
	}

	// resume previous state
	if ( !states.empty() ) {
		states.top()->resume();
	}
}

void CGame::update()
{
    double currentTime, updateIterations;

    currentTime = SDL_GetTicks();
    updateIterations = ((currentTime - lastFrameTime) + cyclesLeftOver);

    if (updateIterations > maxCyclesPerFrame * updateInterval) {
        updateIterations = maxCyclesPerFrame * updateInterval;
    }

    // int cont = 1;
    while(updateIterations > updateInterval) {
        updateIterations -= updateInterval;
        //cout << "updating " << cont++ << endl;
        if ( !states.empty() )
            states.top()->update(this);
    }
    cyclesLeftOver = updateIterations;
    lastFrameTime = currentTime;
}

void CGame::draw()
{
    // let the state draw the screen
	states.top()->draw(this);
    //cout << "draw" << endl;
    //SDL_GL_SwapBuffers();
}

void CGame::clean()
{
    while ( !states.empty() ) {
		states.top()->cleanup();
		states.pop();
	}
    SDL_Quit();

}
