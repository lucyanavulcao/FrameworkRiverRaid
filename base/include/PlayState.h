/*
 *  PlayState.h
 *  Normal "play" state
 *
 *  Created by Isabel Manssour and MÃ¡rcio Pinho on 05/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */


#ifndef PLAY_STATE_H_
#define PLAY_STATE_H_

#ifdef __APPLE__
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#endif

#define	PLAYER_INIT_POS_X			160-16	//FIXME
#define	PLAYER_INIT_POS_Y			276			//FIXME


#include "CGameState.h"
#include "CImage.h"
#include "CSprite.h"
#include "CLayerHandler.h"
#include "CTilesMap.h"
#include "CFont.h"
#include "CTiro.h"
#include "CRiverMap.h"

#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

class PlayState : public CGameState
{
	public:

		void init();
		void cleanup();

		void pause();
		void resume();

		void handleEvents(CGame* game);
		void update(CGame* game);
		void draw(CGame* game);

		// Implement Singleton Pattern
		static PlayState* instance()
		{
			return &m_PlayState;
		}


	protected:
		PlayState() {}
		void CarregaTiles();
		void CarregaSprites();
		void MontaLayer();
		bool TemColisaoSpriteTile(CSprite *sprite, CTilesMap *map);
		void CriaMapDeColisao();

	private:
		static PlayState m_PlayState;
		CLayerHandler *layers;
		CTilesMap *mapFundo;
		CTilesMap *mapColisao;
		CRiverMap *mapLevel[3];

		// Sprites
		CSprite *m_spritePlayer;	// Sprite com o avião do jogador
		CSprite *m_spriteNuvem;
		CSprite *m_spriteShip;	// Sprite com o barco
		CSprite *m_spriteChopper;	// Sprite com o helicóptero
		CSprite *m_spriteJetplane;	// Sprite com o helicóptero

		// Variáveis do jogador
		int	m_nPlayerSpeed;
		long m_lnPlayerScore;

		Uint8* keystate; // state of all keys (1 means key is pressed)

		int currentFrame;
		bool done;

		string BASE_DIR;


};

#endif
