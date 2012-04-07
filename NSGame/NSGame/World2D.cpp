#include "StdAfx.h"
#include "World2D.h"


World2D::World2D(void)
{
}


World2D::~World2D(void)
{
	upDateObjects();
	for(int i=0; i< objects.size(); i++)
	{
		if( objects [i] != NULL)
		{
			delete objects [i];
		}
	}
}


bool World2D::upDateObjects()
{
	objects.clear();

	for(int i=0; i< backGround.size(); i++)
	{
		objects.push_back(backGround[i]);
	}
	for(int i=0; i< middleGround.size(); i++)
	{
		objects.push_back(middleGround[i]);
	}
	for(int i=0; i< foreGround.size(); i++)
	{
		objects.push_back(foreGround[i]);
	}

	return 1;
}
void World2D::setBackGround(Object* obj)
{
	backGround.push_back(obj);
	upDateObjects();
}
void World2D::setMiddleGround(Object* obj)
{
	middleGround.push_back(obj);
	upDateObjects();
}
void World2D::setForeGround(Object* obj)
{
	foreGround.push_back(obj);
	upDateObjects();
}