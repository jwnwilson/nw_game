#include "StdAfx.h"
#include "Engine.h"
#include "Game.h"

Engine::Engine(void)
{
	GAMESTATE = GAME_INIT;
	worldPtr = NULL;
	engineInput = NULL;
	winHandle = NULL;
}

Engine::~Engine(void)
{
}
