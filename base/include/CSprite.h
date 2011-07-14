/*
 *  CSprite.cpp
 *  Sprite class
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#ifndef CSPRITE_H
#define CSPRITE_H

#include <vector>
#include "CMultiImage.h"
#include "TexRect.h"

class CSprite : public CMultiImage
{
    public:
        CSprite();
        virtual ~CSprite();
        bool loadSprite(const char nomeArq[], int w, int h, int hSpace, int vSpace, int xIni, int yIni,
                int column, int row, int total);
        void setXspeed(double xspeed);
        void setYspeed(double yspeed);
        void setCurrentFrame(int c);
        bool setFrameRange(int first, int last);
        void frameForward();
        void frameBack();
        void setAnimRate(int fdelay);
        void update(double updateInterval);
        void draw();
        double getXspeed() { return xspeed; }
        double getYspeed() { return yspeed; }
        int getCurrentFrame() { return curframe; }
        int getTotalFrames() { return totalFrames; }
				bool bboxCollision(CSprite* other);
    private:
        double xspeed,yspeed;       // speed in pixels/s
        int updateCount;            // current count of updates
        int firstFrame, lastFrame; // frame range
        int curframe;		        // current frame
        double curFrameD;           // the current frame as double
		int framecount,framedelay;  // slow down the frame animation
};

#endif // CSPRITE_H
