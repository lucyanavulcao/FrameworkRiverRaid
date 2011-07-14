/*
 *  MenuState.h
 *  Example "menu" state
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Updated by Isabel Manssour and Márcio Pinho on 05/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#ifdef __APPLE__
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#endif

#include <cstdlib>
#include <iostream>
#include <cstring>
#include "CGameState.h"
#include "CRiverMap.h"
#include "CFont.h"

#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <sstream>


using namespace std;


class MenuState : public CGameState
{
    public:
        void init();
        void cleanup();

        void pause();
        void resume();

        void handleEvents(CGame* game);
        void update(CGame* game);
        void draw(CGame* game);

        // Implement Singleton Pattern
        static MenuState* instance()
        {
            return &m_MenuState;
        }

				// TODO: adicionado para teste
				int m_nLinha;
				bool m_bMoveOutroMapa;
				int m_nSpeedY;
    protected:
        MenuState() {}

    private:
        static MenuState m_MenuState;
        CRiverMap* mapaFundo;
				CRiverMap* mapaTeste;
				CRiverMap* mapaTeste2;
        CFont *fonte;
        string BASE_DIR;

};

#endif

