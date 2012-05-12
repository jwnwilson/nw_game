#include "StdAfx.h"
#include "Sprite.h"

Sprite::Sprite(void)
{
	image="unkown";
	rect=NULL;
	animationData.height= 64;
	animationData.width = 64;
	animationData.rows =1;
	animationData.columns =1;
	animationData.currentRow =1;
	animationData.currentColumn =1;
}

Sprite::Sprite(const int& a,const int& b,const string& c)
{
	worldSpaceData.posX=a;
	worldSpaceData.posY=b;
	image=c;
	rect=NULL;
}


Sprite::~Sprite(void)
{
	if(rect != NULL)
	{
		delete rect;
	}
}

bool Sprite::setNextFrame()
{
	if(rect != NULL)
	{
		if( animationData.currentColumn < animationData.columns)
		{
			animationData.currentColumn++;
		}
		else
		{
			animationData.currentColumn = 1;
		}
		updateAnimation();
	}
	else
	{
		return false;
	}

	return true;
}

bool Sprite::updateAnimation()
{
	int rectWidth = (animationData.width / animationData.columns);
	int rectHeight = (animationData.height / animationData.rows);

	if(rect != NULL)
	{
		rect->left=		( rectWidth* (animationData.currentColumn - 1) );
		rect->right=	( rectWidth* animationData.currentColumn );
		rect->top=		( rectHeight* (animationData.currentRow - 1)  ); 
		rect->bottom=	( rectHeight* animationData.currentRow  ); 
	}
	else
	{
		return false;
	}

	return true;
}
