#include "StdAfx.h"
#include "TestEngine.h"
#include "Game.h"
#include <iostream>
#include <assert.h>
#include <mmsystem.h>

TestEngine::TestEngine(void)
{
}

TestEngine::~TestEngine(void)
{
}

// hardcoded test
bool TestEngine::initialise()
{
	Object *backGround = new Sprite();
	
	backGround->setPosXY(0,0);
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
	
	hero->setPosXY(0,0);
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
	float time = timeGetTime();
	engineInput->updateInput();
	SpriteData* animData = worldPtr->getObjects()[1]->getAnimationData();

	if(engineInput->keyPressed(WKEY))
	{
		x = worldPtr->getObjects()[1]->getPosX();
		y = worldPtr->getObjects()[1]->getPosY();

		y--;
		worldPtr->getObjects()[1]->setPosXY(x,y);

		updateAnim = true;
	}
	if(engineInput->keyPressed(SKEY))
	{
		x = worldPtr->getObjects()[1]->getPosX();
		y = worldPtr->getObjects()[1]->getPosY();

		y++;
		worldPtr->getObjects()[1]->setPosXY(x,y);

		updateAnim = true;
	}
	if(engineInput->keyPressed(AKEY))
	{
		x = worldPtr->getObjects()[1]->getPosX();
		y = worldPtr->getObjects()[1]->getPosY();

		x--;
		worldPtr->getObjects()[1]->setPosXY(x,y);

		if(worldPtr->getObjects()[1]->getCurrentRow() == 1)
		{
			worldPtr->getObjects()[1]->setRowColumn(2,1);
		}
		updateAnim = true;
	}
	if(engineInput->keyPressed(DKEY))
	{
		x = worldPtr->getObjects()[1]->getPosX();
		y = worldPtr->getObjects()[1]->getPosY();

		x++;
		worldPtr->getObjects()[1]->setPosXY(x,y);

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
	
	if(engineInput->keyPressed(ESCKEY))
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
	if(engineInput->keyPressed(DIK_1))
	{
		GAMESTATE = GAME_RUN;
		return true;
	}
	else if(engineInput->keyPressed(DIK_1))
	{
		GAMESTATE = GAME_RUN;
		return true;
	}

	if(engineInput->keyPressed(ESCKEY))
	{
		GAMESTATE = GAME_EXIT;
	}

	return false;
}