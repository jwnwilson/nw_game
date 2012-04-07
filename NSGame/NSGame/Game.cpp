#include "StdAfx.h"
#include "Game.h"
#include "Graphics2D.h"
#include "BasicInput.h"
#include "TestEngine.h"
#include "SpriteEngine.h"
#include "World.h"
#include "XMLReader.h"

Game::Game(void)
{
	GAMESTATE = GAME_INIT;
	graphicsEngine = NULL;
	input = NULL;
	sound = NULL;
	world = NULL;
	gameEngine = NULL;
	updateSettings= false;
}
// This is a deconstructor if you don't know what it does ask me,
// just incase it always runs before the object is deleted, so here we 
// ALWAYS clean up data that we are managing before the object is deleted.
Game::~Game(void)
{
	// check to see if pointer is pointing at anything
	if ( graphicsEngine != NULL)
	{
		// delete it's sorry ass if so
		graphicsEngine->release();
		delete graphicsEngine ;
	}
	if ( input != NULL)
	{
		delete input ;
	}
	if ( sound != NULL)
	{
		delete sound ;
	}
	if ( world != NULL)
	{
		delete world ;
	}
	if ( gameEngine != NULL)
	{
		delete gameEngine ;
	}
	if ( fileReader != NULL)
	{
		delete fileReader ;
	}
	if ( sound != NULL)
	{
		delete sound ;
	}
}


bool Game::initialise(HWND hWnd,HINSTANCE hInstance)
{
	graphicsEngine = new Graphics2D;
	input		   = new BasicInput;
	gameEngine     = new TestEngine;
	//gameEngine     = new SpriteEngine;
	world		   = new World;
	fileReader     = new XMLReader;

	// not implemented yet
	sound		   = NULL;

	////////////////////////////////
	// Game Engine
	////////////////////////////////

	// Read a config file to load game
	if(! fileReader->read("config.xml"))
	{
		cerr<< "Config file not read.";
	}

	/*double test;
	fileReader->read("default.xml");
	fileReader->setData("default.xml","test","NSGame","tValue",10);
	fileReader->getData("default.xml","test","NSGame","tValue",test);
	fileReader->write("default.xml","default.xml");*/

	// give the game engine access to the world
	gameEngine->setGameState(GAME_INIT);
	gameEngine->setWorld(world);
	// will initalise engine
	gameEngine->initialise();
	
	////////////////////////////////
	// Graphics Engine
	////////////////////////////////

	// graphics rely on the game engine to be running or at least exist
	if( gameEngine != NULL)
	{
		// pass windows instance and handle to directX stuff in graphics
		graphicsEngine->initialise(hWnd,hInstance);
		// allow the graphics engine to see the world
		graphicsEngine->setWorld(world);
		// creates sprites should probably be moved from here
		graphicsEngine->CreateSprites();
		// initialise my direct X
		input->initalise(hInstance,hWnd);

		gameEngine->setInput(input);
	}

	return true;
}

bool Game::menu(HWND hWnd)
{
	graphicsEngine->draw();
	updateSettings = gameEngine->menu();
	GAMESTATE = gameEngine->getGameState();

	//check config changed
	if(updateSettings)
	{
		graphicsEngine->toogleFullScreen(hWnd);
	}

	return true;
}
bool Game::load()
{
	return true;
}
bool Game::save()
{
	return true;
}
bool Game::run()
{
	graphicsEngine->draw();
	gameEngine->compute();
	GAMESTATE = gameEngine->getGameState();
	return true;
}
bool Game::exit()
{
	return true;
}