#include "StdAfx.h"
#include "Game.h"
#include "Graphics2D.h"
#include "BasicInput.h"
#include "TestEngine.h"
#include "SpriteEngine.h"
#include "World2D.h"
#include "XMLReader.h"
#include "Utilities.h"

Game::Game(void)
{
	GAMESTATE = GAME_INIT;
	graphicsEngine = NULL;
	input = NULL;
	sound = NULL;
	world = NULL;
	gameEngine = NULL;
	updateSettings= false;
	winHandle = NULL;
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
	winHandle = hWnd;
	input		   = new BasicInput;
	fileReader     = new XMLReader;

	// not implemented yet
	sound		   = NULL;

	////////////////////////////////
	// Game Engine
	////////////////////////////////

	// Read a config file to load game
	if(! fileReader->read("config.xml"))
	{
		GAMEERROR("Config file not loaded during initialization");
	}

	string graphicsType;
	string engineType;
	string worldType;

	fileReader->getStringData("config.xml","graphicsEngine","NSGame","type",graphicsType);
	fileReader->getStringData("config.xml","gameEngine","NSGame","type",engineType);
	fileReader->getStringData("config.xml","world","NSGame","type",worldType);

	// Set Graphics
	if(graphicsType == "Graphics2D")
	{
		graphicsEngine = new Graphics2D;
	}
	else
	{
		graphicsEngine = new Graphics2D;
	}

	// Set Game engine
	if( engineType == "TestEngine")
	{
		gameEngine = new TestEngine;
	}
	else if( engineType == "SpriteEngine")
	{
		gameEngine = new SpriteEngine;
	}
	else
	{
		gameEngine = new TestEngine;
	}

	// Set World type
	if( worldType == "World")
	{
		world = new World;
	}
	else if( worldType == "World2D")
	{
		world = new World2D;
	}
	else
	{
		world = new World2D;
	}

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
		if( !graphicsEngine->initialise(hWnd,hInstance) )
		{
			GAMEERROR("Error initialising graphics engine.");
			return false;
		}
		// allow the graphics engine to see the world
		graphicsEngine->setWorld(world);
		// creates sprites should probably be moved from here
		if( !graphicsEngine->CreateSprites() )
		{
			GAMEERROR("Error initialising sprites.");
			return false;
		}
		// initialise my direct X
		if( ! input->initalise(hInstance,hWnd))
		{
			GAMEERROR("Error initialising input.");
			return false;
		}

		gameEngine->setInput(input);
	}

	return true;
}

bool Game::menu(HWND hWnd)
{
	if(! graphicsEngine->draw())
	{
		return false;
	}
	if(! gameEngine->compute())
	{
		return false;
	}
	GAMESTATE = gameEngine->getGameState();

	//check config changed
	if(updateSettings)
	{
		if(! graphicsEngine->toogleFullScreen(hWnd))
		{
			GAMEERROR("Error changing screen resolution.");
		}
	}

	return true;
}
bool Game::load()
{
	if(! graphicsEngine->draw())
	{
		return false;
	}
	if(! gameEngine->compute())
	{
		return false;
	}
	GAMESTATE = gameEngine->getGameState();
}
bool Game::save()
{
	return true;
}
bool Game::run()
{
	if(! graphicsEngine->draw())
	{
		GAMEERROR("Graphics Engine draw() failure.");
		return false;
	}
	if(! gameEngine->compute())
	{
		GAMEERROR("Graphics Engine compute() failure.");
		return false;
	}
	GAMESTATE = gameEngine->getGameState();
	return true;
}

bool Game::exit()
{
	return true;
}

bool Game::error(string errorMsg, string fileName, int lineNumber)
{
	string output = ("Error message:	" + errorMsg + "\n" + "File name:	" + fileName + "\n" + "Line number:\t" + intToString(lineNumber) );
	if(! MessageBox(winHandle, &output[0], "Error!", MB_ICONSTOP ))
	{
		return false;
	}
	return true;
}

bool Game::warning(string warningMsg, string fileName, int lineNumber)
{
	string output = ("Warning message:	" + warningMsg + "\n" + "File name:		" + fileName + "\n" + "Line number:\t" + intToString(lineNumber) );
	if(! MessageBox(winHandle, &output[0], "Warning", MB_ICONQUESTION ))
	{
		return false;
	}
	return true;
}