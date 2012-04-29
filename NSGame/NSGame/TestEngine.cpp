#include "StdAfx.h"
#include "TestEngine.h"
#include "Game.h"

TestEngine::TestEngine(void)
{
}

TestEngine::~TestEngine(void)
{
}

// hardcoded test
bool TestEngine::initialise()
{
	Object *backGround = new Object();
	
	backGround->setXY(0,0);
	backGround->setWidth(256);
	backGround->setHeight(256);
	backGround->setImage("background.tga");
	
	worldPtr->addObject( backGround );

	Object *hero = new Object();
	
	hero->setXY(0,0);
	hero->setWidth(64);
	hero->setHeight(64);
	hero->setImage("hero.tga");
	
	worldPtr->setMiddleGround( hero );

	return true;
}
bool TestEngine::compute()
{
	int x,y;
	engineInput->updateInput();

	if(engineInput->Wkey())
	{
		x = worldPtr->getObjects()[1]->getX();
		y = worldPtr->getObjects()[1]->getY();

		y--;
		worldPtr->getObjects()[1]->setXY(x,y);
	}
	if(engineInput->Skey())
	{
		x = worldPtr->getObjects()[1]->getX();
		y = worldPtr->getObjects()[1]->getY();

		y++;
		worldPtr->getObjects()[1]->setXY(x,y);
	}
	if(engineInput->Akey())
	{
		x = worldPtr->getObjects()[1]->getX();
		y = worldPtr->getObjects()[1]->getY();

		x--;
		worldPtr->getObjects()[1]->setXY(x,y);
	}
	if(engineInput->Dkey())
	{
		x = worldPtr->getObjects()[1]->getX();
		y = worldPtr->getObjects()[1]->getY();

		x++;
		worldPtr->getObjects()[1]->setXY(x,y);
	}

	if(engineInput->escKey())
	{
		GAMESTATE = GAME_EXIT;
	}
	else
	{
		GAMESTATE = GAME_RUN;
	}
	return true;
}

bool TestEngine::menu()
{
	if(engineInput->getKBInput()[DIK_1]  & 0x80)
	{
		GAMESTATE = GAME_RUN;
		return true;
	}
	else if(engineInput->getKBInput()[DIK_2]  & 0x80)
	{
		GAMESTATE = GAME_RUN;
		return true;
	}

	if(engineInput->escKey())
	{
		GAMESTATE = GAME_EXIT;
	}

	return false;
}