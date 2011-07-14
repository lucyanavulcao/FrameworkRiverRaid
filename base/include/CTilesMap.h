/*
 *  CTilesMap.cpp
 *
 *  Created by Isabel Manssour and Márcio Pinho on 05/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#include "CMultiImage.h"

#ifndef _TILES_MAP_H_
#define _TILES_MAP_H_

class CTilesMap : public CMultiImage {
	private:
		int widthTileMap, heightTileMap;	// largura e altura do mapa de tiles
		std::vector<int> map;	// mapa de tiles (tem indice para o vetor de subbitmaps
		float m_fScrollOffsetX, m_fScrollOffsetY;
	public:
		CTilesMap();
		bool loadMap(const char nomeArq[]);
		bool loadTileMap(const char nomeArq[], int w, int h, int hSpace, int vSpace, int xIni, int yIni,
				int column, int row, int total);
		void draw();
		void printMap();
		int getWidthTileMap() {
			return widthTileMap;
		}
		int getHeightTileMap() {
			return heightTileMap;
		}
		int getTileNumber(int lin, int col);
		std::vector<int> CTilesMap::getTileLine(int nLine);
		void CTilesMap::drawScroll(float fOffsetX, float fOffsetY);
		void setOffsetY(float fOffset);
		float getOffsetY();
};

#endif
