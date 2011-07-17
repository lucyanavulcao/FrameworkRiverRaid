/*
 *  CRiverMap.cpp
 *
 *  Baseado no código CTilesMap de Isabel Manssour and Márcio Pinho on 05/11.
 *  Criado por Alexandre Ramos Coelho, 07/11.
 *
 * 	Classe para criar um mapa de tiles que possa ser 'rolado' na vertical
 * 	e na horizontal
 */

#include "CMultiImage.h"

#ifndef _RIVER_MAP_H_
#define _RIVER_MAP_H_

class CRiverMap : public CMultiImage {

	private:
		int widthTileMap, heightTileMap;	// largura e altura do mapa de tiles
		std::vector<int> map;	// mapa de tiles (tem indice para o vetor de subbitmaps
		int m_nScrollOffsetX; // Offset horizontal do mapa
		int m_nScrollOffsetY;	// Offset vertical do mapa
		int m_nStartPosX;	// Posição inicial em X
		int m_nStartPosY;	// Posição inicial em Y

	public:
		CRiverMap();
		bool loadMap(const char nomeArq[]);
		bool loadTileMap(const char nomeArq[], int w, int h, int hSpace, int vSpace, int xIni, int yIni,
				int column, int row, int total);
		void draw();
		void printMap();
		int getWidthTileMap() { return widthTileMap; }
		int getHeightTileMap() { return heightTileMap; }
		int getTileNumber(int lin, int col);

		std::vector<int> getTileLine(int nLine);
		int getOffsetY();
		int getOffsetX();
		void setOffsetY(int nOffset);
		void setOffsetX(int nOffset);

		int getStartPosX() { return m_nStartPosX; }
		int getStartPosY() { return m_nStartPosY; }
		void setStartPosX(int nPos);
		void setStartPosY(int nPos);
		void scrambleMap(int nMaxRandom);
		void mapSliceScramble(int nNum);
		bool putTileLine(std::vector<int> vLine, int nLine);
};

#endif
