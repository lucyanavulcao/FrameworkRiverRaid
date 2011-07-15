/*
 *  PlayState.cpp
 *  Normal "play" state
 *
 *  Created by Isabel Manssour and Márcio Pinho on 05/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#include "CGame.h"
#include "PlayState.h"
#include "PauseState.h"
#include "CRiverMap.h"

PlayState PlayState::m_PlayState;

using namespace std;
//alteracao no inicio para testar
/*****************************************************************************************/
void PlayState::CarregaTiles() {
	bool ret;
	// Carrega o mapa de teste
	string nomeArq = BASE_DIR + "data/maps/river_raid_base.txt";

	// Comentando o antigo mapFundo...
	/*
	mapFundo = new CTilesMap();
	ret = mapFundo->loadMap(nomeArq.c_str());
	if (!ret) {
		cout << "Arquivo de mapa ("<< nomeArq << ") n�o existe." ;
		return;
	}

	nomeArq = BASE_DIR + "data/maps/river_raid_tiles.png";
	ret = mapFundo->loadTileMap(nomeArq.c_str(),
	                            32, 32,		// int w, int h,
	                            0, 0, 		// int hSpace, int vSpace,
	                            0, 0, 		// int xIni, int yIni,
	                            8, 4, 	// int column, int row,
	                            32);		// int total

	if (!ret) {
		cout << "Arquivo de tiles ("<< nomeArq << ") n�o existe." ;
		return;
	}
*/


	// TODO: testando se conseguimos criar um array de mapas :P
	{
		for(int nIdx = 0; nIdx < RR_NUM_ROTATING_MAPS; nIdx++) {
			// 1 - Arquivo com a descri��o do mapa de tiles
			nomeArq = BASE_DIR + "data/maps/river_raid_base.txt";

			mapLevel[nIdx] = new CRiverMap();
			// Carrega o mapa
			ret = mapLevel[nIdx]->loadMap(nomeArq.c_str());
			if (!ret) {
				cout << "Arquivo de mapa ("<< nomeArq << ") n�o existe." ;
				return;
			}

			// 2 - arquivo com o conjunto de figuras 
			nomeArq = BASE_DIR + "data/maps/river_raid_tiles.png";
			ret = mapLevel[nIdx]->loadTileMap(nomeArq.c_str(),
					32, 32,		// int w, int h,
					0, 0, 		// int hSpace, int vSpace,
					0, 0, 		// int xIni, int yIni,
					8, 4, 	// int column, int row,
					32);		// int total

			if (!ret) {
				cout << "Arquivo de tiles ("<< nomeArq << ") n�o existe." ;
				return;
			}
		}
	}

}


/*****************************************************************************************/
/*
 * @brief		Fun��o que cuida de fazer o scroll e rotacionar os mapas de cen�rio
 * @param		nOffset		Deslocamento para todos os mapas
 * @return	void
 */
void PlayState::MoveRotatingMaps(int nOffset) {

	int nOffsetNow[RR_NUM_ROTATING_MAPS];

	// Primeiro, obt�m os valores de offset de cada um dos mapas
	for(int nIdx = 0; nIdx < RR_NUM_ROTATING_MAPS; nIdx++) {
		nOffsetNow[nIdx] = mapLevel[nIdx]->getOffsetY();
	}

	// Processa os offsets, verificando se algum dos mapas saiu da janela. Se saiu, faz a devida rota��o
	// FIXME: ALERTA DE TOSQUICE!!! Melhor esse c�digo, usar o define RR_NUM_ROTATING_MAPS
	if(nOffsetNow[0] >= RR_RIVER_LEVEL_LENGTH) { // Level saiu da janela...
		nOffsetNow[0] = 0;
		nOffsetNow[1] = -RR_RIVER_LEVEL_LENGTH;
		nOffsetNow[2] = -RR_RIVER_LEVEL_LENGTH * 2;
	} else
	if(nOffsetNow[1] >= RR_RIVER_LEVEL_LENGTH) { // Level saiu da janela...
		nOffsetNow[1] = 0;
		nOffsetNow[2] = -RR_RIVER_LEVEL_LENGTH;
		nOffsetNow[0] = -RR_RIVER_LEVEL_LENGTH * 2;
	} else
	if(nOffsetNow[2] >= RR_RIVER_LEVEL_LENGTH) { // Level saiu da janela...
		nOffsetNow[2] = 0;
		nOffsetNow[0] = -RR_RIVER_LEVEL_LENGTH;
		nOffsetNow[1] = -RR_RIVER_LEVEL_LENGTH * 2;
	} 
	
	// Faz a movimenta��o dos mapas
	for(int nIdx = 0; nIdx < RR_NUM_ROTATING_MAPS; nIdx++) {

		mapLevel[nIdx]->setOffsetY(nOffsetNow[nIdx] + nOffset);
	}
}

/*****************************************************************************************/
/*
 * @brief		Faz o carregamento dos sprites do jogo, que devem estar na pasta bin/data/img/
 * @param		void
 * @return	void
 */
void PlayState::CarregaSprites() {

	// Carrega o sprite do jogador
	string nomeArq = BASE_DIR + "data/img/aviao.png";
	m_spritePlayer = new CSprite();
	m_spritePlayer->loadSprite(nomeArq.c_str(), 32, 32, 0, 0, 0, 0, 1, 1, 1);
	m_spritePlayer->setScale(1);
	m_spritePlayer->setAnimRate(8); // taxa de animação em frames por segundo(troca dos frames dele)
	m_spritePlayer->setScale(1.0);
	m_spritePlayer->setPosition(RR_PLAYER_INIT_POS_X, RR_PLAYER_INIT_POS_Y); // FIXME
	// FIXME: adicionar sprite do player com anima��es

	{
		// TODO: testando um layer com nuvens	
		nomeArq = BASE_DIR + "data/img/rr_clouds.png";
		m_spriteNuvem = new CSprite();
		m_spriteNuvem->loadSprite(nomeArq.c_str(), 128, 128, 0, 0, 0, 0, 1, 1, 1);
		m_spriteNuvem->setScale(1);

		m_spriteNuvem->setPosition(160-16,320);

		m_spriteNuvem->setAnimRate(8); // taxa de animação em frames por segundo(troca dos frames dele)
		m_spriteNuvem->setScale(1.0);
	}

	// Carrega os sprites dos inimigos
	// TODO: s� um sprite por inimigo?
	// TODO: fazer as anima��es e carreg�-las aqui
	
	// Carrega o sprite com o barco - 32x8
	nomeArq = BASE_DIR + "data/img/rr_e_ship.png";
	m_spriteShip = new CSprite();
	m_spriteShip->loadSprite(nomeArq.c_str(), 32, 8, 0, 0, 0, 0, 1, 1, 1);
	m_spriteShip->setScale(1);
	m_spriteShip->setAnimRate(8); // taxa de animação em frames por segundo(troca dos frames dele)
	m_spriteShip->setScale(1.0);
	m_spriteShip->setPosition(160,160);	// FIXME

	// Carrega o sprite com o helic�ptero 16x16
	nomeArq = BASE_DIR + "data/img/rr_e_chopper.png";
	m_spriteChopper = new CSprite();
	m_spriteChopper->loadSprite(nomeArq.c_str(), 16, 16, 0, 0, 0, 0, 2, 1, 2);
	m_spriteChopper->setScale(1);
	m_spriteChopper->setAnimRate(8); // taxa de animação em frames por segundo(troca dos frames dele)
	m_spriteChopper->setScale(1.0);
	m_spriteChopper->setPosition(120,400);	// FIXME

	// Carrega o sprite com o barco - 16x8
	nomeArq = BASE_DIR + "data/img/rr_e_jetplane.png";
	m_spriteJetplane = new CSprite();
	m_spriteJetplane->loadSprite(nomeArq.c_str(), 16, 8, 0, 0, 0, 0, 1, 1, 1);
	m_spriteJetplane->setScale(1);
	m_spriteJetplane->setAnimRate(8); // taxa de animação em frames por segundo(troca dos frames dele)
	m_spriteJetplane->setScale(1.0);
	m_spriteJetplane->setPosition(200,500);	// FIXME

}

/*****************************************************************************************/
/*
 * @brief		Faz o desenho de cada um dos layers do jogo. Layers com �ndice maior s�o
 * 					desenhadas sobre os layers de �ndice menor
 * @param		void
 * @return	void
 */
void PlayState::MontaLayer() {
	cout << "Monta Layers....";
	layers = new CLayerHandler(5);
//	layers->add(mapFundo,0);
	
	for(int nIdx = 0; nIdx < RR_NUM_ROTATING_MAPS; nIdx++)
		layers->add(mapLevel[nIdx],0);

	// FIXME: est� com erro no draw do mapa de colis�o
//	layers->add(mapColisao,1);
	layers->add(m_spritePlayer,2);

	layers->add(m_spriteShip,1);	// Adiciona o sprite do barco aos layers
	layers->add(m_spriteChopper,1);	// Adiciona o sprite do helic�ptero aos layers
	layers->add(m_spriteJetplane,1);	// Adiciona o sprite do avi�o inimigo aos layers
	layers->add(m_spriteNuvem,3);
}

/*****************************************************************************************/
void PlayState::init() {

#ifdef __APPLE__
	BASE_DIR = "../../../bin/"; // Codelite
#endif

#ifdef _MSC_VER
	BASE_DIR = "../../../../bin/"; // Visual Studio
#endif
  firstTime = true;
	CarregaTiles();
	CarregaSprites();
	MontaLayer();

	// SDL_GetTicks() tells how many milliseconds have past since an arbitrary point in the past.

	keystate = SDL_GetKeyState(NULL); // get array of key states

	currentFrame = 0;

	// Inicializa a posi��o dos mapas
	for(int nIdx = 0; nIdx < RR_NUM_ROTATING_MAPS; nIdx++) {

		mapLevel[nIdx]->setStartPosX(0);
		mapLevel[nIdx]->setStartPosY(0); // Todos os mapas s�o iniciados na origem...
		mapLevel[nIdx]->setOffsetY(RR_RIVER_LEVEL_LENGTH-(RR_RIVER_LEVEL_LENGTH*nIdx)); // ... mas com offsets diferentes. Assim ficam em fila
	}

	// Inicializa as vari�veis do jogo
	m_lnPlayerScore = 0;
	m_nLevel = 0;	// Primeira fase
	m_nPlayerSpeed = 1; // FIXME: a velocidade inicial do avi�o n�o ser� controlada assim...

	cout << "PlayState Init Successful" << endl;
}

/*****************************************************************************************/
void PlayState::cleanup() {
	delete m_spritePlayer;
	delete m_spriteNuvem;
	
	// FIXME: aqui estamos removendo somente um sprite. O correto ser� remover v�rios
	delete m_spriteShip;	// Remove o sprite do barco
	delete m_spriteChopper;	// Remove o sprite do helic�ptero
	delete m_spriteJetplane;	// Remove o sprite do avi�o inimigo
	cout << "PlayState Clean Successful" << endl;
}

/*****************************************************************************************/
void PlayState::pause() {
	cout << "PlayState Paused" << endl;
}

/*****************************************************************************************/
void PlayState::resume() {
	cout << "PlayState Resumed" << endl;
}

/*****************************************************************************************/
bool PlayState::TemColisaoSpriteTile(CSprite *sprite, CTilesMap *map) {
	return false;
}

/*****************************************************************************************/
void PlayState::handleEvents(CGame* game) {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		// check for messages
		switch (event.type) {
		

		case SDL_QUIT:
			game->quit();
			break;
			// check for keypresses
		case SDL_KEYDOWN:
			// exit if ESCAPE is pressed
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				game->getAudioEngine()->stopAllSounds();
				done = true;
				game->quit();
				break;
			} else if (event.key.keysym.sym == SDLK_p)
				game->pushState(PauseState::instance());
			else if (event.key.keysym.sym == SDLK_a) {

			}
			break;
			// SDL_APPACTIVE: When the application is either minimized/iconified
			// (gain=0) or restored ('gain'=1) this type of activation event occurs
		case SDL_APPACTIVE:
			if (event.active.gain==0) {
			}
			break;
		case SDL_VIDEORESIZE:
			game->resize(event.resize.w, event.resize.h);
			break;
		} // end switch
	}// end of message processing

	if (keystate[SDLK_UP]==1) {

		m_nPlayerSpeed += 2;

		if(m_nPlayerSpeed > RR_PLAYER_MAX_SPEED)
			m_nPlayerSpeed = RR_PLAYER_MAX_SPEED;

		// Movimenta o avi�o e faz o pan da c�mera, movendo tamb�m o cen�rio
		//m_spritePlayer->setY(m_spritePlayer->getY()-m_nPlayerSpeed);
		//game->setYpan(game->getYpan()-2);
		//game->updateCamera();

		/*game->setZoom(game->getZoom()+1);
			game->updateCamera();*/
	}

	if (keystate[SDLK_DOWN]==1) {

		// FIXME: corrigir, a parte de velocidade n�o � t�o simples assim
		m_nPlayerSpeed -= 2;
		if(m_nPlayerSpeed <=1)
			m_nPlayerSpeed = 1;

		// FIXME: n�o fazer mais o pan de c�mera e sim diminuir a velocidade do avi�o
		// Movimenta o avi�o e faz o pan da c�mera, movendo tamb�m o cen�rio
		//m_spritePlayer->setY(m_spritePlayer->getY()+2);
		//game->setYpan(game->getYpan()+2);
		//game->updateCamera();
		/*game->setZoom(game->getZoom()-1);
		game->updateCamera();*/
	}

	if (keystate[SDLK_RIGHT]==1) {
		// FIXME: est� fazendo pan
//		if (!TemColisaoSpriteTile(m_spritePlayer,mapColisao))
			m_spritePlayer->setX(m_spritePlayer->getX()+1);
		/*game->setXpan(game->getXpan()+1);
		game->updateCamera();*/
	}

	if (keystate[SDLK_LEFT]==1) {
	//	if (!TemColisaoSpriteTile(m_spritePlayer,mapColisao))
			m_spritePlayer->setX(m_spritePlayer->getX()-1);
		/*game->setXpan(game->getXpan()-1);
		game->updateCamera();*/
	}

	if(keystate[SDLK_l]==1) {
	}    

	if(keystate[SDLK_k]==1) {
	}

	if(keystate[SDLK_SPACE]==1) {
	}


}

/*****************************************************************************************/
void PlayState::update(CGame* game) {

	if(firstTime){
		firstTime = false;
		string nomeArqSom = BASE_DIR + "data/audio/AM_Countryside.mp3";
		initSound = game->getAudioEngine()->addSoundSourceFromFile(nomeArqSom.c_str());
		game->getAudioEngine()->play2D(initSound,true);
	}

	m_spritePlayer->update(game->getUpdateInterval());

	// Faz a anima��o dos sprites na tela
	m_spriteChopper->update(game->getUpdateInterval());


	//game->setXpan(m_spritePlayer->getX() - game->getWidth()/2);
	//game->updateCamera();
	
	// Move os mapas
	MoveRotatingMaps(m_nPlayerSpeed);

	
	// Chama a fun��o de desenho de cada layer
	layers->draw();

}

/*****************************************************************************************/
void PlayState::draw(CGame* game) {
//	glClearColor(0.59, 0.84, 0.91, 0);
//	Define a cor de fundo do jogo
	glClearColor(0, 0, 0, 0);

	glEnable(GL_TEXTURE_2D); // isto é necessário quando se deseja desenhar com texturas

	// Enable transparency through blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	layers->draw();

	glDisable(GL_TEXTURE_2D); // isto é necessário quando se deseja desenhar SEM texturas
	glColor3f(0,0,0);
	glPointSize(5);

	glColor3f(1,1,1);

	SDL_GL_SwapBuffers();
}

/*****************************************************************************************/
// Cria objetos de colisão a partir de um 'mapa de tiles'
void PlayState::CriaMapDeColisao() {
	float x,y; // usadas para calcular a posição de cada "tile"
	x = 0;
	y = 0;
//	int identificador = BOLA + 5; // identificador para cada tile
	float width = mapColisao->getWidth();
	float height = mapColisao->getHeight();
	float difX = width/2;
	float difY = height/2;

	for(int lin=0; lin < mapColisao->getHeightTileMap(); lin++) {
		for (int col=0; col< mapColisao->getWidthTileMap(); col++) {
			//cout <<  "   "  << mapColisao->getTileNumber(col,lin);
			if (mapColisao->getTileNumber(col,lin) != 192) { // se não é um "tile" do fundo
				// faz manualmente o ajuste entre o (0,0) do "tile" e o (0,0) da Box2D
//				CriaCaixa(identificador, x+difX,y+difY, width, height);
				//identificador ++;
				cout << "["<< col << "," << lin << "]  --  X = "<< x << " Y = " << y << endl;
			}
			//else cout << "["<< col << "," << lin << "] --" << endl;
			x += mapColisao->getWidth();
		}
		//cout << endl;
		x = 0;
		y += mapColisao->getHeight();
	}

}
