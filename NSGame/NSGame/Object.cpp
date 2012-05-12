#include "StdAfx.h"
#include "Object.h"

Object::Object(void)
{
	worldSpaceData.posX=0;
	worldSpaceData.posY=0;
	worldSpaceData.posZ=0;
	worldSpaceData.rotX=0;
	worldSpaceData.rotY=0;
	worldSpaceData.rotZ=0;
	worldSpaceData.scaleX=1;
	worldSpaceData.scaleY=1;
	worldSpaceData.scaleZ=1;
	name= "";

}

Object::~Object(void)
{
}