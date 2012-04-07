#include "StdAfx.h"
#include "World.h"

World::World(void)
{
}

World::~World(void)
{
	clearObjects();
}

bool World::clearObjects()
{
	for(int i=0; i< objects.size(); i++)
	{
		if( objects [i] != NULL)
		{
			delete objects [i];
		}
	}

	return true;
}
