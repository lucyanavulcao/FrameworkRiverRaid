/*
 *  CLayerHandler.h
 *  Layer handler class
 *
 *  Created by Isabel Manssour / Marcio Pinho on 05/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#ifndef CLAYERHANDLER_H
#define CLAYERHANDLER_H

#include "CLayer.h"

class CLayerHandler
{
	private:
			CLayer *vet;
			int totalLayers;
	public:
			CLayerHandler(int numLayers);
			bool add(CImage *i, int layer);
			bool remove(CImage *img);
			CLayer getLayer(int n);
			void draw();
			int getTotalLayers();
			bool changeLayerUp(CImage *img);
			bool changeLayerDown(CImage *img);
};

#endif
