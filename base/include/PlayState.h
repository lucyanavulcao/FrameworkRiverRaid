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

/*****************************************************************************************/
/*
 * Defines do jogo
 */
/*****************************************************************************************/
#define	RR_TILE_WIDTH						32	// Largura de cada tile que compõe o cenário
#define	RR_TILE_HEIGHT					32	// Altura de cada tile que compõe o cenário
#define RR_RIVER_WIDTH					10	// Número de tiles na largura do rio
#define RR_RIVER_HEIGHT					32	// Número de tiles na altura do rio
#define RR_RIVER_VISIBLE_HEIGHT	8	// Número de tiles adiante visíveis no rio
#define RR_RIVER_LEVEL_LENGTH		RR_TILE_HEIGHT*RR_RIVER_HEIGHT	// Para ajudar no posicionamento dos mapas
#define	RR_GAME_WINDOW_WIDTH		RR_TILE_WIDTH*RR_RIVER_WIDTH
#define	RR_GAME_WINDOW_HEIGHT		RR_TILE_HEIGHT*RR_RIVER_VISIBLE_HEIGHT
#define	RR_PLAYER_INIT_POS_X		RR_GAME_WINDOW_WIDTH/2-16	//FIXME
#define	RR_PLAYER_INIT_POS_Y		RR_GAME_WINDOW_HEIGHT-(2*RR_TILE_HEIGHT)			//FIXME
#define RR_NUM_ROTATING_MAPS		3		
#define RR_RIVER_SCREEN_SLICES	RR_RIVER_VISIBLE_HEIGHT + 2	//! Número de 'fatias' do mapa que são rotacionadas

#define RR_PLAYER_MAX_SPEED			10

#include "CGameState.h"
#include "CImage.h"
#include "CSprite.h"
#include "CLayerHandler.h"
#include "CTilesMap.h"
#include "CFont.h"
#include "CTiro.h"
#include "CRiverMap.h"
#include <irrKlang.h>

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
		void MoveRotatingMaps(int nOffset);

	private:
		static PlayState m_PlayState;
		CLayerHandler *layers;
		CTilesMap *mapFundo;
		CTilesMap *mapColisao;
		CRiverMap *mapSlice[RR_RIVER_SCREEN_SLICES];
		CRiverMap *mapLevel[RR_NUM_ROTATING_MAPS];

		// Sprites
		CSprite *m_spritePlayer;	//! Sprite com o avião do jogador
		CSprite *m_spriteNuvem;
		CSprite *m_spriteShip;	//! Sprite com o barco
		CSprite *m_spriteChopper;	//! Sprite com o helicóptero
		CSprite *m_spriteJetplane;	//! Sprite com o helicóptero

		// Variáveis do jogador
		int	m_nPlayerSpeed;
		long m_lnPlayerScore;
		int m_nLevel;		//!	Fase atual em que o jogador se encontra

		Uint8* keystate; // state of all keys (1 means key is pressed)

		int currentFrame;
		bool done;
    bool firstTime;
		string BASE_DIR;
		irrklang::ISoundSource* initSound;

};

#endif
