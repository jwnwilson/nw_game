#pragma once
#include "World2D.h"
#include "Input.h"

// Dummy engine class will be used to point to a real engine
class Engine
{
public:
	Engine(void);
	~Engine(void);
	// will set game up
	virtual bool initialise(){return false;}
	// runs the game
	virtual bool compute(){return false;}
	// load menu
	virtual bool menu(){return false;}

	void setWorld(World* w){ worldPtr = w;}
	void setInput(Input* i){ engineInput = i;}
	int getGameState(){return GAMESTATE;}
	void setGameState(int g){GAMESTATE = g;}

protected:

	// will have full access to world
	int GAMESTATE;
	World *worldPtr;
	Input *engineInput;
};
