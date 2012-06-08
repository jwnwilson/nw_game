#pragma once
#include "World2D.h"
#include "Input.h"
#include "XMLReader.h"
#include <mmsystem.h>

// Struct to hold data read from file
struct  ConfigData {
	bool fullscreen;
};

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
	void setFileIO(FileIO* f){ fileReader = f;}
	void setXMLReader(XMLReader *x){xmlReader = x;}
	int getGameState(){return GAMESTATE;}
	void setGameState(int g){GAMESTATE = g;}
	void setWinHandle(HWND w){winHandle = w;}
	const ConfigData* getConfigData()const {return &configData;}

protected:
	// For error handling
	HWND winHandle;
	// will have full access to world
	int GAMESTATE;
	World *worldPtr;
	Input *engineInput;
	FileIO *fileReader;
	XMLReader *xmlReader;
	ConfigData configData;
};
