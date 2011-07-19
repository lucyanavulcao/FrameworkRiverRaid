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

/*****************************************************************************************/
/*
 * 	Defines do jogo
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

#define	RR_PLAYER_MIN_SPEED			1
#define RR_PLAYER_CRUISE_SPEED	2
#define RR_PLAYER_MAX_SPEED			4

#define RR_START_ENEMY_TILES		48	//! Índice do primeiro tile que indica a posição de um inimigo no mapa

/*****************************************************************************************/
/*
 * Tiles do mapa que indicam as posições dos itens
 */
enum EEnemyTiles {
		FUEL =	RR_START_ENEMY_TILES,
		SHIP_R,
		SHIP_L,
		CHOPPER_R,
		CHOPPER_L,
		JET_R,
		JET_L,
		BRIDGE,
		HOUSE_R,
		HOUSE_L,
};


/*****************************************************************************************/
/*
 *	Máquina de estados do jogo
 */
enum EPlayState {
	STATE_STARTING_GAME,
	STATE_STARTING_LEVEL,	//<	Iniciando uma fase, faz a animação do rio e deixa o player parado
	STATE_PLAYING,				//< Player jogando
	STATE_NULL
};

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
		
		// Métodos da máquina de estados do jogo
		EPlayState GetCurrState(void);
		EPlayState GetPrevState(void);
		void EnterNewState(EPlayState eNewState);
		void ExecuteCurrState();
		void LeaveCurrState();


	protected:
		PlayState() {}
		void CarregaTiles();
		void CarregaSprites();
		void MontaLayer();
		bool TemColisaoSpriteTile(CSprite *sprite, CTilesMap *map);
		void CriaMapDeColisao();
		void MoveRotatingMaps(int nOffset);
		void MapLoadNewSlice(int nMapSliceIdx, int nRiverLevel, int nLevelSlice);
		void MapStartLevel(int nLevel);
		void MapStartLevelResetOffsets(void);
		void TileLineProcess(std::vector<int>* vLine, int nSliceIdx);

		EPlayState m_eCurrState, m_ePrevState;

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
		int m_nLevelSlice;
		int m_nRiverLevel;
		bool m_bnPlayerHasStarted;
		std::vector<int> m_vnSlicesIdxForCollision;

		// Variáveis auxiliares
		int m_nAuxSlice;
		int m_nAuxRolagem;


		Uint8* keystate; // state of all keys (1 means key is pressed)

		int currentFrame;
		bool done;
    bool firstTime;
		string BASE_DIR;
		irrklang::ISoundSource* initSound;

};

#endif
