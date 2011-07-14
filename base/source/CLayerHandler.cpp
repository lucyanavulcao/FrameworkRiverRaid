/*
 *  CLayerHandler.cpp
 *  Layer handler class
 *
 *  Created by Isabel Manssour / Marcio Pinho on 05/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#include "CLayerHandler.h"

CLayerHandler::CLayerHandler(int numLayers)
{
	if (numLayers > 0 && numLayers < 100)
	{
		totalLayers = numLayers;
		vet = new CLayer[totalLayers];
	}
	else
	{
		totalLayers = 4;
		vet = new CLayer[totalLayers];
	}
}

bool CLayerHandler::add(CImage *i, int layer)
{
	bool ehValido = false;

	if (layer>=0 && layer<totalLayers)
	{
		ehValido = true;
		vet[layer].add(i);
	}

	return ehValido;
}

bool CLayerHandler::remove(CImage *img)
{
	bool achou = false;

	for(int i=0; i<totalLayers && !achou; i++)
	{
		if (vet[i].remove(img) )
		{
			achou = true;
		}
	}
	return achou;
}

CLayer CLayerHandler::getLayer(int n)
{
	if (n < totalLayers)
		return vet[n];
	else
		return vet[0];
}

void CLayerHandler::draw()
{
	for(int i=0; i<totalLayers; i++)
	{
		vet[i].draw();
	}
}

int CLayerHandler::getTotalLayers()
{
	return totalLayers;
}

bool CLayerHandler::changeLayerUp(CImage *img)
{
	bool ehPossivel = false;

	for(int i=0; i<totalLayers && !ehPossivel; i++)
	{
		if ( vet[i].contains(img) )
		{
			if (i < totalLayers-1)
			{
				ehPossivel = true;
				vet[i].remove(img);
				vet[i+1].add(img);
			}
		}
	}

	return ehPossivel;
}

bool CLayerHandler::changeLayerDown(CImage *img)
{
	bool ehPossivel = false;

	for(int i=0; i<totalLayers && !ehPossivel; i++)
	{
		if ( vet[i].contains(img) )
		{
			if (i > 0)
			{
				ehPossivel = true;
				vet[i].remove(img);
				vet[i-1].add(img);
			}
		}
	}

	return ehPossivel;
}
