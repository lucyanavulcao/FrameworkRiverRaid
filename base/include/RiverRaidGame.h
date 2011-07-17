#ifndef RIVER_RAID_H
#define RIVER_RAID_H

#include <stdio.h>

#include "CGame.h"
#include "PlayState.h"
#include "MenuState.h"

#define DEBUG
#ifdef DEBUG
	#define debug(fmt, ...)\
	{\
		printf("[%s@%d]", __FUNCTION__, __LINE__);\
		(void)( printf(fmt, __VA_ARGS__));\
		printf("\n");\
	}
#else
	#define debug(fmt, ...) 	{ }		
#endif


#endif
