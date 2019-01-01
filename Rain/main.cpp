#include "Game.h"

//Include the standard C++ headers  
#include <stdio.h>  
#include <stdlib.h>  


int main(void)
{	
	Game game;
	game.loop();
	game.cleanup();
}