/*
 *  MenuState.cpp
 *  Example "menu" state
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Updated by Isabel Manssour and MÃ¡rcio Pinho on 05/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */


#include <iostream>
#include "CGame.h"
#include "MenuState.h"
#include "PlayState.h"
#include "CRiverMap.h"
#include "CParticleSystem.h"

MenuState MenuState::m_MenuState;

using namespace std;

void MenuState::init()
{

#ifdef __APPLE__
	BASE_DIR = "../../../bin/"; // Codelite
#else
	BASE_DIR = "../../../../bin/"; // Visual Studio
#endif

    bool ret;
	string nomeArq = BASE_DIR + "data/maps/menuEntrada.txt";

	mapaFundo = new CRiverMap();
	ret = mapaFundo->loadMap(nomeArq.c_str());
	if (!ret) {
		cout << "Arquivo de mapa ("<< nomeArq << ") nÃ£o existe." ;
		return;
	}
	else cout << "Leitura OK !" << endl;

	nomeArq = BASE_DIR + "data/maps/blocks1.png";
	ret = mapaFundo->loadTileMap(nomeArq.c_str(),
	                       32, 32,		// int w, int h,
	                       2, 2, 		// int hSpace, int vSpace,
	                       2, 2, 		// int xIni, int yIni,
	                       18, 11, 	// int column, int row,
	                       196);		// int total

	if (!ret) {
		cout << "Arquivo de tiles ("<< nomeArq << ") nÃ£o existe." ;
		return;
	}

	// FIXME: arrumar isso
	mapaFundo->setStartPosX(0);
	mapaFundo->setStartPosY(0);
	m_nLinha = 0;
	m_nSpeedY = 2;

//
	nomeArq = BASE_DIR + "data/maps/menuEntrada.txt";
	mapaTeste = new CRiverMap();
	ret = mapaTeste->loadMap(nomeArq.c_str());
	if (!ret) {
		cout << "Arquivo de mapa ("<< nomeArq << ") nÃ£o existe." ;
		return;
	}
	else cout << "Leitura OK !" << endl;

	nomeArq = BASE_DIR + "data/maps/blocks1_red.png";
	ret = mapaTeste->loadTileMap(nomeArq.c_str(),
	                       32, 32,		// int w, int h,
	                       2, 2, 		// int hSpace, int vSpace,
	                       2, 2, 		// int xIni, int yIni,
	                       18, 11, 	// int column, int row,
	                       196);		// int total

	if (!ret) {
		cout << "Arquivo de tiles ("<< nomeArq << ") nÃ£o existe." ;
		return;
	}

	nomeArq = BASE_DIR + "data/maps/menuEntrada.txt";
	mapaTeste2 = new CRiverMap();
	ret = mapaTeste2->loadMap(nomeArq.c_str());
	if (!ret) {
		cout << "Arquivo de mapa ("<< nomeArq << ") nÃ£o existe." ;
		return;
	}
	else cout << "Leitura OK !" << endl;

	nomeArq = BASE_DIR + "data/maps/blocks1.png";
	ret = mapaTeste2->loadTileMap(nomeArq.c_str(),
	                       32, 32,		// int w, int h,
	                       2, 2, 		// int hSpace, int vSpace,
	                       2, 2, 		// int xIni, int yIni,
	                       18, 11, 	// int column, int row,
	                       196);		// int total

	if (!ret) {
		cout << "Arquivo de tiles ("<< nomeArq << ") nÃ£o existe." ;
		return;
	}
	mapaTeste2->scrambleMap(192);

	// FIXME: arrumar isso
	mapaTeste->setStartPosX(0);
	mapaTeste->setStartPosY(0);
	mapaTeste->setOffsetY(-384);
	mapaTeste2->setStartPosX(0);
	mapaTeste2->setStartPosY(0);
	mapaTeste2->setOffsetY(-384*2);
	m_nLinha = 0;
	m_bMoveOutroMapa = true;

	nomeArq = BASE_DIR + "data/fonts/lucida12.png";
	fonte = new CFont();
	fonte->loadFont(nomeArq.c_str(), 112, 208);
	fonte->setPosition(0,250);
	fonte->setText("Pressione espaco para comecar");


	// Teste
	testeParticulas = new CParticleSystem();
	testeParticulas->setStartPos(120,50);

	cout << "MenuState Init Successful" << endl;
}

void MenuState::cleanup()
{
    delete mapaFundo;
    delete fonte;
		// FIXME
		delete mapaTeste;
		delete mapaTeste2;
	cout << "MenuState Cleanup Successful" << endl;
}

void MenuState::pause()
{
	cout << "MenuState Paused" << endl;
}

void MenuState::resume()
{
	cout << "MenuState Resumed" << endl;
}

void MenuState::handleEvents(CGame* game)
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->quit();
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {

					case SDLK_SPACE:
						game->getAudioEngine()->stopAllSounds();
						game->changeState(PlayState::instance());
						break;
					case SDLK_ESCAPE:
						game->quit();
						break;
					case SDLK_EQUALS:
						m_nSpeedY++;
						break;
					case SDLK_MINUS:
						m_nSpeedY--;
						if(m_nSpeedY < 0)
							m_nSpeedY = 0;
						break;
				}
		}
	}
}

void MenuState::update(CGame* game)
{

	if(firstTime){
		firstTime = false;
		string nomeArqSom = BASE_DIR + "data/audio/AM_Boss2.mp3";
		initSound = game->getAudioEngine()->addSoundSourceFromFile(nomeArqSom.c_str());
		game->getAudioEngine()->play2D(initSound,true);
	}
	// Faz um teste de animação usando as funções novas
	// FIXME: remover isto
	//
	{
		int nOffset = mapaFundo->getOffsetY();
		int nOffsetTeste = mapaTeste->getOffsetY();
		int nOffsetTeste2 = mapaTeste2->getOffsetY();


		//printf("%d - %d - %d\n", nOffset, nOffsetTeste, m_nSpeedY);
		if(nOffset >= 384) { //Chegou ao limite de um dos mapas 
			printf("Vou trocar com nOff %d, Teste %d, Teste2 %d\n",
					nOffset, nOffsetTeste, nOffsetTeste2);
			// O primeiro mapa passou pelo fim da tela? Então alteramos a ordem para:
			// mapa2 -> mapa3 -> mapa1
			nOffsetTeste = 0;
			nOffsetTeste2 = -384;
			nOffset = -384 * 2;
		} else
		if(nOffsetTeste >= 384) {
			// O segundo mapa passou pelo fim da tela? Então alteramos a ordem para:
			// mapa3 -> mapa1 -> mapa2
			nOffsetTeste2 = 0;
			nOffset = -384;
			nOffsetTeste = -384*2;
		} else
		if(nOffsetTeste2 >= 384) {
			// O terceiro mapa passou pelo fim da tela? Então voltamos para a ordem original:
			// mapa1 -> mapa2 -> mapa3
			printf("Vou trocar com nOff %d, Teste %d, Teste2 %d\n",
					nOffset, nOffsetTeste, nOffsetTeste2);

			nOffset = 0;
			nOffsetTeste2 = -384;
			nOffsetTeste2 = -384*2;
		}

		// Um assert bem vagabundo
		//if(abs(nOffset) + abs(nOffsetTeste) != 384)
		//	printf("Erro de diferença!\n");

		
		mapaFundo->setOffsetY(nOffset + m_nSpeedY);
		mapaTeste->setOffsetY(nOffsetTeste + m_nSpeedY);
		mapaTeste2->setOffsetY(nOffsetTeste2 + m_nSpeedY);
	}

	// Teste tosco para mover o sistema de partículas
	testeParticulas->moveParticleSystem(0, m_nSpeedY);
	//testeParticulas->moveOriginParticleSystem(testeParticulas->getX(), 
	//		testeParticulas->getY()+m_nSpeedY);

}

void MenuState::draw(CGame* game)
{
	glClearColor(0.3, 0.3, 0.3, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, game->getWidth(), game->getHeight(), 0, 1, -1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0, 0, game->getWidth(), game->getHeight());

	glEnable(GL_TEXTURE_2D); // isto Ã© necessÃ¡rio quando se deseja desenhar com texturas

	// Enable transparency through blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mapaFundo->draw();
	fonte->draw();
	// FIXME
	mapaTeste->draw();
	mapaTeste2->draw();

	// 
	testeParticulas->draw();

	SDL_GL_SwapBuffers();
}

