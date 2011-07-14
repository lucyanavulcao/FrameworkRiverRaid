/*
 *  CLayer.cpp
 *  Layer class
 *
 *  Created by Isabel Manssour / Marcio Pinho on 05/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */
 
 #include "CLayer.h"

void CLayer::add(CImage *i)
{
	spritesAndTiles.push_back(i);
}

bool CLayer::remove(CImage *img)
{
	bool achou = false;
	std::vector<CImage *>::iterator i;

	i=spritesAndTiles.begin();

	while (!achou && i != spritesAndTiles.end())
	{
		if (*i == img)
		{
			spritesAndTiles.erase(i);
			achou = true;
		}
		else
			i++;
	}
	return achou;
}

bool CLayer::contains(CImage *img)
{
	bool achou = false;
	std::vector<CImage *>::iterator i;

	for (i=spritesAndTiles.begin(); i != spritesAndTiles.end() && !achou; i++)
	{
		if (*i == img)
		{
			achou = true;
		}
	}
	return achou;
}

void CLayer::draw()
{
	for (int i=0; i<spritesAndTiles.size(); i++){
  		spritesAndTiles[i]->draw();
	}
}

int CLayer::getTotalElements()
{
	return spritesAndTiles.size();
}

CImage * CLayer::getElement(int i)
{
	if ( i>=0 && i<spritesAndTiles.size() )
		return spritesAndTiles[i];
	else
		return NULL;
}
/*
void CLayer::setOffsetX(int o)
{
	for (int i=0; i<spritesAndTiles.size(); i++)
		spritesAndTiles[i]->setOffsetX(o);
}

void CLayer::setOffsetY(int o)
{
	for (int i=0; i<spritesAndTiles.size(); i++)
		spritesAndTiles[i]->setOffsetY(o);
}
*/