/*
 *  CGame.h
 *  Main game class
 *
 *  Created by Marcelo Cohen on 04/11.
 *
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#ifndef CGAME_H
#define CGAME_H

#include <SDL.h>
#include <SDL_opengl.h>
#include <stack>

class CGameState;

class CGame
{
    public:

        CGame(int minFrameRate=15, int maxFrameRate=20);
        void init(const char* title, int width, int height, int bpp, bool fullscreen);
        void handleEvents();
        void changeState(CGameState* state);
        void pushState(CGameState* state);
        void popState();
        void update();
        void draw();
        void clean();
        bool isRunning() { return running; }
        void quit()    { running = false; }
        void resize(int w, int h);
        void updateCamera();
        SDL_Surface* getScreen() { return screen; }
        static void printAttributes();
        double getUpdateInterval() { return updateInterval; }

        void setXpan(float xpan);
        void setYpan(float ypan);

        void setZoom(float z);

        float getXpan() { return panX; }
        float getYpan() { return panY; }
        float getZoom() { return zoom; }
        float getWidth();
        float getHeight();

    private:

        SDL_Surface* screen;
        bool running;
        bool fullscreen;
        int bpp; // bits per pixel (screen colour depth)
        int flags; // SDL initialization flags
        std::stack<CGameState*> states;
        float xmin,xmax,ymin,ymax;
        float zoom;
        float panX;
        float panY;
        // Fixed interval time-based animation
        int minFrameRate;
        int maxFrameRate;
        double updateInterval;
        double maxCyclesPerFrame;
        double lastFrameTime;
        double cyclesLeftOver;
};

#endif

