#include "StdAfx.h"
#include "TestEngine.h"
#include "Game.h"
#include <iostream>

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

	Object *hero = new Sprite();
	RECT* animRec = new RECT;
	animRec->left=0;
	animRec->right=64;
	animRec->top=0;
	animRec->bottom=64;
	
	hero->setXY(0,0);
	hero->setWidth(256);
	hero->setHeight(256);
	hero->setRowColumnNumber(4,4);
	hero->setImage("heroSprite.tga");
	hero->setAnimation(animRec);
	
	worldPtr->setMiddleGround( hero );

	return true;
}
bool TestEngine::compute()
{
	int x,y;
	bool updateAnim = false;
	engineInput->updateInput();

	if(engineInput->Wkey())
	{
		x = worldPtr->getObjects()[1]->getX();
		y = worldPtr->getObjects()[1]->getY();

		y--;
		worldPtr->getObjects()[1]->setXY(x,y);

		updateAnim = true;
	}
	if(engineInput->Skey())
	{
		x = worldPtr->getObjects()[1]->getX();
		y = worldPtr->getObjects()[1]->getY();

		y++;
		worldPtr->getObjects()[1]->setXY(x,y);

		updateAnim = true;
	}
	if(engineInput->Akey())
	{
		x = worldPtr->getObjects()[1]->getX();
		y = worldPtr->getObjects()[1]->getY();

		x--;
		worldPtr->getObjects()[1]->setXY(x,y);

		if(worldPtr->getObjects()[1]->getCurrentRow() == 1)
		{
			worldPtr->getObjects()[1]->setRowColumn(2,1);
		}
		updateAnim = true;
	}
	if(engineInput->Dkey())
	{
		x = worldPtr->getObjects()[1]->getX();
		y = worldPtr->getObjects()[1]->getY();

		x++;
		worldPtr->getObjects()[1]->setXY(x,y);

		if(worldPtr->getObjects()[1]->getCurrentRow() == 2)
		{
			worldPtr->getObjects()[1]->setRowColumn(1,1);
		}
		updateAnim = true;
	}

	if(worldPtr->getObjects()[1]->getAnimation() != NULL && updateAnim == true)
	{
		if(FAILED(worldPtr->getObjects()[1]->setNextFrame()))
		{
			std::cout<<"error getting animation RECT from sprite"<<endl;
			return false;	
		}
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