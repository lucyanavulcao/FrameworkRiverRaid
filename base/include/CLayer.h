/*
 *  CLayer.h
 *  Layer class
 *
 *  Created by Isabel Manssour / Marcio Pinho on 05/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#ifndef CLAYER_H
#define CLAYER_H

#include <vector>
#include "CSprite.h"

class CLayer
{
	private:
			std::vector<CImage *> spritesAndTiles;
	public:
			void add(CImage *img);
			bool remove(CImage *img);
			bool contains(CImage *img);
			void draw();
			int getTotalElements();
			CImage * getElement(int i);
			//void setOffsetX(int o);
			//void setOffsetY(int o);
			//int getOffsetX() { return spritesAndTiles[0]->getOffsetX(); }
			//int getOffsetY() { return spritesAndTiles[0]->getOffsetY(); }
};

#endif
