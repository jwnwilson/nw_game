#include "StdAfx.h"
#include "Sprite.h"

Sprite::Sprite(void)
{
	rows =1;
	columns =1;
	currentRow =1;
	currentColumn =1;
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
		if( currentColumn < columns)
		{
			currentColumn++;
		}
		else
		{
			currentColumn = 1;
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
	int rectWidth = (width / columns);
	int rectHeight = (height / rows);

	if(rect != NULL)
	{
		rect->left=		( rectWidth* (currentColumn - 1) );
		rect->right=	( rectWidth* currentColumn );
		rect->top=		( rectHeight* (currentRow - 1)  ); 
		rect->bottom=	( rectHeight* currentRow  ); 
	}
	else
	{
		return false;
	}

	return true;
}
