/*
 *  CSprite.cpp
 *  Sprite class
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#include "CSprite.h"
#include <iostream>

using namespace std;

// Construtor
CSprite::CSprite()
{

}

bool CSprite::loadSprite(const char nomeArq[], int w, int h, int hSpace, int vSpace, int xIni, int yIni,
                 int column, int row, int total)
{
    if(!loadMultiImage(nomeArq,w,h,hSpace,vSpace,xIni,yIni,column,row,total))
        return false;

	// Init animation vars
	xspeed = 0;
	yspeed = 0;
	curframe = 0;
    curFrameD = 0;
    firstFrame = 0;
    lastFrame = total-1;
	return true;
}

CSprite::~CSprite()
{
    //dtor
}

// Especifica quantos pixels o sprite ira se mover em x.
void CSprite::setXspeed(double xspeed)
{
	this->xspeed = xspeed;
}

// Especifica quantos pixels a sprite ira se mover em y.
void CSprite::setYspeed(double yspeed)
{
	this->yspeed = yspeed;
}

// Sets the current frame
void CSprite::setCurrentFrame(int c)
{
	if ( c>=0 && c<totalFrames )
		curframe = c;
	else
		curframe = 0;
    curFrameD = curframe;
}

/** @brief setFrameRange
  *
  * @todo: document this function
  */
bool CSprite::setFrameRange(int first, int last)
{
    if(first > last || first < 0 || last >= totalFrames)
        return false;
    firstFrame = first;
    lastFrame = last;
    return true;
}

// Advance to next frame
void CSprite::frameForward()
{
	curframe++;
	if (curframe > lastFrame)
		curframe = firstFrame;
}

// Go back to previous frame
void CSprite::frameBack()
{
	curframe--;
	if (curframe < firstFrame)
		curframe = lastFrame;
}

// Recebe por parametro o valor que sera usado para especificar o atributo
// framedelay, responsavel por diminuir ou aumentar a taxa de animacao.
void CSprite::setAnimRate(int fdelay)
{
	if (fdelay >= 0)
		framedelay = fdelay;
	else
		framedelay = 0;

    // Reset framecount so next draw will work as it should be
    framecount = 0;
}

// Metodo responsavel por fazer as atualizacoes necessarias para a correta
// animacao do sprite.
void CSprite::update(double updateInterval)
{
    // Move sprite according to its speed and the amount of time that has passed
    x += xspeed/1000*updateInterval;
    y += yspeed/1000*updateInterval;

    curFrameD += (double)framedelay/1000*updateInterval;
    curframe = (int) curFrameD;
    if(curframe > lastFrame) {
        curFrameD = firstFrame;
        curframe = firstFrame;
    }
}

// Draw the sprite
void CSprite::draw()
{
	//cout << "Curframe: " << curframe << endl;
    drawFrame(curframe);
}

// Check collision between this and other sprite
// (bounding box collision only)
bool CSprite::bboxCollision(CSprite* other)
{
    float x1 = this->x + this->width;
    float y1 = this->y + this->height;
    
    float x3 = other->x + other->width;
    float y3 = other->y + other->height;
    
    return !(x1<other->x || x3<this->x || y1<other->y || y3<this->y);
}