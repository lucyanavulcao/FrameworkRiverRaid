/*
 *  CGameState.h
 *  Abstract class to represent game states
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "CGame.h"

class CGameState
{
    public:

    virtual void init() = 0;
    virtual void cleanup() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handleEvents(CGame* game) = 0;
    virtual void update(CGame* game) = 0;
    virtual void draw(CGame* game) = 0;

    void changeState(CGame* game, CGameState* state) {
        game->changeState(state);
    }

    protected:

    CGameState() { }
};

#endif

