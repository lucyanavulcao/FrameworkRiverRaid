/*
 *  PauseState.h
 *  Example "pause" state
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#ifndef PAUSE_STATE_H_
#define PAUSE_STATE_H_

#ifdef __APPLE__
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#endif

#include "CGameState.h"
#include "CImage.h"
#include "CSprite.h"
#include "CLayerHandler.h"
#include "CTilesMap.h"
#include "CFont.h"
#include "CTiro.h"

#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

using namespace std;


class PauseState : public CGameState
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
        static PauseState* instance()
        {
            return &m_PauseState;
        }

    protected:
        PauseState() {}

    private:
        static PauseState m_PauseState;
        CImage* pauseSprite;
        CFont*  pauseFont;
        string BASE_DIR;
};

#endif
