// ***************************************************************************
// PUCRS/FACIN
// 		Curso de Especialização em Desenvolvimento de Jogos Digitais
// 		Computação Gráfica 2D
// 		Profs.
//    		Isabel Harb Manssour / Márcio Sarroglia Pinho
// ***************************************************************************

#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>

using namespace std;


#ifdef __APPLE__
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#endif

#include "RiverRaidGame.h"
#include "CGame.h"
#include "PlayState.h"
#include "MenuState.h"

int main( int argc, char* args[] ) {

	CGame game(5,30);

	game.init("River Raid Remake",RR_GAME_WINDOW_WIDTH,RR_GAME_WINDOW_HEIGHT,0,false);

	game.changeState(MenuState::instance());

	while(game.isRunning())
	{
		game.handleEvents();
		game.update();
		game.draw();
	}

	// cleanup the engine
	game.clean();

	return 0;

}

