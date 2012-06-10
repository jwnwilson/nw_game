#include "StdAfx.h"
#include "Graphics.h"

Graphics::Graphics(void)
{
	SCREEN_WIDTH = 800;
	SCREEN_HEIGHT = 600;
	fullscreen = FALSE;
	winHandle = NULL;
	inputPtr = NULL;
}

Graphics::~Graphics(void)
{
}


D3DXVECTOR2 Graphics::scaleTranslateToScreenSize(D3DXVECTOR2 &position)
{
	D3DXVECTOR2 result;
	float screenWidth = ( windowRect.right - windowRect.left);
	float screenHeight = (windowRect.bottom - windowRect.top);
	float xRatio =  screenWidth / SCREEN_WIDTH;
	float yRatio =  screenHeight / SCREEN_HEIGHT;
	result.x = position.x * xRatio;
	result.y = position.y * yRatio;
	return result;
}
