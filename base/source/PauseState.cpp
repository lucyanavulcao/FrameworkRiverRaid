/*
 *  PauseState.cpp
 *  Example "pause" state
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */


#include "PauseState.h"

PauseState PauseState::m_PauseState;

using namespace std;


void PauseState::init()
{
	// Visual Studio 
	BASE_DIR = "../../../../bin/";
 	//BASE_DIR = "../../../bin/";
	
    bool ret;
	pauseSprite = new CImage();
	string nomeArq = BASE_DIR + "data/img/paused.png";
	pauseSprite->loadImage(nomeArq.c_str());
    pauseSprite->setPosition(150,150);
    pauseFont = new CFont();
	nomeArq = BASE_DIR + "data/fonts/lucida12.png";
    pauseFont->loadFont(nomeArq.c_str(), 112, 208);
    cout << "PauseState Init Successful" << endl;
}

void PauseState::cleanup()
{
    delete pauseSprite;
	cout << "PauseState Clean Successful" << endl;
}

void PauseState::resume() {}

void PauseState::pause() {}

void PauseState::handleEvents(CGame* game)
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->quit();
				break;

            case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
                    case SDLK_p:
                        game->popState();
                        break;
                    case SDLK_ESCAPE:
                        game->quit();
                        break;
				}
		}
	}
}

void PauseState::update(CGame* game)
{
}

void PauseState::draw(CGame* game)
{
    glClearColor(0,0,1,1); // blue
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    pauseSprite->setScale(1);
    pauseSprite->draw();
    glLoadIdentity();
    pauseFont->draw(250,300,"Press P to resume game");
    SDL_GL_SwapBuffers();
}

