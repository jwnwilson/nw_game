#pragma once
#include "Graphics.h"
#include "Input.h"
#include "Sound.h"
#include "World.h"
#include "Engine.h"
#include "FileIO.h"

#define GAME_INIT		0 // the game is initializing
#define GAME_MENU		1// the game is in the menu mode
#define GAME_LOAD		2// the game is about to run
#define GAME_RUN		3// the game is now running
#define GAME_RESTART	4// the game is going to restart
#define GAME_EXIT		5// the game is exiting
#define GAME_SEXY		6// the game is sexy

// Need a clock to sync the game

class Game
{
public:
	Game(void);
	~Game(void);
	bool initialise(HWND hWnd,HINSTANCE hInstance);
	bool menu(HWND hWnd);
	bool load();
	bool save();
	bool run();
	bool exit();
	int getGameState(){return GAMESTATE;}

protected:

	// all pointers to classes that we will create
	int GAMESTATE;
	bool updateSettings;
	Graphics *graphicsEngine;
	Input	 *input;
	Sound	 *sound;
	World	 *world;
	Engine	 *gameEngine;
	FileIO   *fileReader;

};
