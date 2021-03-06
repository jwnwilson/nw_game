#include "stdafx.h"
#include "Graphics2D.h"
#include <assert.h>
#include <mmsystem.h>
#include <string>
#include <iostream>
#include "Utilities.h"


// Constructor
Graphics2D::Graphics2D(void): m_d3dObject(0),m_d3dDevice(0)
{
	ppSprite=NULL;
	m_pCursorTexture = NULL;
	cursorScaleX = 0.5;
	cursorScaleY = 0.5;

}

// Destructor
Graphics2D::~Graphics2D(void)
{
	// Once we have finished with the Direct3D objects we must release them
	if (m_d3dDevice)
		m_d3dDevice->Release();

	if (m_d3dObject)
		m_d3dObject->Release();
	
	for( map<string, LPDIRECT3DTEXTURE9>::iterator ii= gTexture.begin(); ii!=gTexture.end(); ++ii)
	{
		(*ii).second->Release();
	}
	ppSprite->Release();
}

bool Graphics2D::release()
{
	// Once we have finished with the Direct3D objects we must release them
	if (m_d3dDevice)
		m_d3dDevice->Release();

	if (m_d3dObject)
		m_d3dObject->Release();
	
	for( map<string, LPDIRECT3DTEXTURE9>::iterator ii= gTexture.begin(); ii!=gTexture.end(); ++ii)
	{
		(*ii).second->Release();
	}
	ppSprite->Release();

	return true;
}

bool Graphics2D::CheckHR(HRESULT hr)
{
	// just checks a HRESULT object from directX contains an error message
	if (SUCCEEDED(hr))
		return true;

	// An error occured so find out what it was and output it to the output pane in Vis
	OutputDebugString("\nDirectX Error Reported:\n");
	OutputDebugString(DXGetErrorString(hr));
	OutputDebugString(" : ");
	OutputDebugString(DXGetErrorDescription(hr));
	OutputDebugString("\n\n");

	return false;
}

bool Graphics2D::initialise(HWND hWnd,HINSTANCE hInstance)
{
	if (!InitialiseDirect3D(hWnd))
		return false;

	return true;
}

bool Graphics2D::InitialiseDirect3D(HWND hWnd)
{
	// Create the main D3D object. It is only used to get a device object.
	m_d3dObject=Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_d3dObject)
		return false;

	GetWindowRect(hWnd, &windowRect);

	// A load of params for something directX-y
	D3DPRESENT_PARAMETERS presParams;

	initParameters(presParams);

	// Creates direct render engine
	HRESULT hr=m_d3dObject->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&presParams, &m_d3dDevice);
	if (FAILED(hr))
	{
		hr=m_d3dObject->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_MIXED_VERTEXPROCESSING,
			&presParams, &m_d3dDevice);
		if (FAILED(hr))
		{
			hr=m_d3dObject->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&presParams, &m_d3dDevice);
			if (FAILED(hr))
				return false;
		}
	}
	// will create sprites
	if (FAILED(D3DXCreateSprite(m_d3dDevice,&ppSprite)))
	{
		GAMEERROR("error creating sprite.",winHandle);
		return false;
	}
	
	// As well as specifying that we want a z buffer (above) we also need to turn it on
	m_d3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return true;
}

bool Graphics2D::draw()
{
	// 1. clear the back buffer to black (0,0,0) and the z buffer to 1
	HRESULT hr=m_d3dDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0,0,0),1.0f,0);
	if (!CheckHR(hr))
		return false;

	// 2. begin the scene
	hr=m_d3dDevice->BeginScene();
	if (!CheckHR(hr))
		return false;

	// 3. draw me some sprites!!
	if (!DrawSprites())
		return false;

	// 4. End the scene and present it
	hr=m_d3dDevice->EndScene();
	if (!CheckHR(hr))
		return false;

	// 5. ...... ta da!
	hr=m_d3dDevice->Present(NULL,NULL,NULL,NULL);
	if (!CheckHR(hr))
		return false;

	return true;
}

bool Graphics2D::CreateSprites()
{
	// Gonna store us some textures
	//gTexture.resize(world->getObjects().size());
	for(int i=0;i<world->getObjects().size();i++)
	{
		// Need to aquire this from config file
		Object *sprite = world->getObjects()[i];
		string path = "Textures/";
		string fileName = sprite->getImage();

		if (FAILED(D3DXCreateTextureFromFile(m_d3dDevice, (path + fileName).c_str() ,&gTexture[sprite->getImage()])))
		{
			if (FAILED(D3DXCreateTextureFromFile(m_d3dDevice, fileName.c_str() ,&gTexture[sprite->getImage()])))
			{
				GAMEERROR("error creating texture.",winHandle);
	 			return false;
			}
		}
	}
	// Create Cusor
	if (FAILED(D3DXCreateTextureFromFile(m_d3dDevice, "Textures/cursor.tga" , &m_pCursorTexture)))
	{
		GAMEERROR("error creating cursor texture.",winHandle);
	 	return false;
	}
	return true;
}

bool Graphics2D::DrawSprites()
{	
	Object *sprite;

	D3DXVECTOR2 spriteCentre;
	D3DXVECTOR2 scaling;
	D3DXVECTOR2 trans;
	D3DXVECTOR3 pos;
	float rotation;

	if(FAILED(ppSprite->Begin(D3DXSPRITE_ALPHABLEND)))
	{
		GAMEERROR("error begining sprites.",winHandle);
		return false;
	}
	for(int i=0;i<world->getObjects().size();i++)
	{
		sprite = world->getObjects()[i];

		// Set center of sprite
		//spriteCentre= D3DXVECTOR2( (sprite->getWidth() / 2), (sprite->getHeight() / 2) );
		spriteCentre= D3DXVECTOR2( (sprite->getPosX() + (sprite->getWidth() / 2)), (sprite->getPosY() + (sprite->getHeight() / 2)) );

		// Screen position of the sprite
		trans= D3DXVECTOR2(sprite->getPosX(),sprite->getPosY());
		//trans = scaleTranslateToScreenSize(trans);

		// Scaling
		scaling = D3DXVECTOR2(sprite->getScaleX(),sprite->getScaleY());

		// Rotate
		rotation= sprite->getRotX();

		// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
		D3DXMatrixTransformation2D(sprite->getMatrix(),NULL,0.0,&scaling,&spriteCentre,rotation,&trans);
		//D3DXMatrixTranslation(sprite->getMatrix(),trans.x,trans.y,sprite->getPosZ());

		ppSprite->SetTransform(sprite->getMatrix());
		if(FAILED(ppSprite->Draw(gTexture[sprite->getImage()],sprite->getAnimation(),NULL,NULL,0xFFFFFFFF)))
		{
			GAMEERROR("error drawing sprites.",winHandle);
			return false;	
		}
	}
	// draw cursor
	if(m_pCursorTexture != NULL)
	{
		// hardcode the shitout of that cursor
		RECT cursorRect;
		cursorRect.bottom = 64;
		cursorRect.top = 0;
		cursorRect.left = 0;
		cursorRect.right = 64;

		spriteCentre= D3DXVECTOR2( (sprite->getPosX() + (sprite->getWidth() / 2)), (sprite->getPosY() + (sprite->getHeight() / 2)) );
		trans= D3DXVECTOR2(inputPtr->getRelativeX(),inputPtr->getRelativeY());
		
		// Scaling
		scaling = D3DXVECTOR2(cursorScaleX,cursorScaleY);

		D3DXMatrixTransformation2D(inputPtr->getMatrix(),NULL,0.0,&scaling,&spriteCentre,NULL,&trans);
		//D3DXMatrixTranslation(inputPtr->getMatrix(),trans.x,trans.y,inputPtr->getRelativeZ());
		ppSprite->SetTransform(inputPtr->getMatrix());

		//pos.x = inputPtr->getRelativeX();
		//pos.y = inputPtr->getRelativeY();
		//pos.z = inputPtr->getRelativeZ();
		if(FAILED(ppSprite->Draw(m_pCursorTexture,&cursorRect,NULL,NULL,0xFFFFFFFF)))
		{
			GAMEERROR("error drawing cursor.",winHandle);
			return false;	
		}
	}
	if(FAILED(ppSprite->End()))
	{
		GAMEERROR("error ending sprites.",winHandle);
		return false;

	}
	return true;
}

bool Graphics2D::toogleFullScreen(HWND hWnd)
{
	HMENU hMenu = NULL; 
	// A load of params for something directX-y
	D3DPRESENT_PARAMETERS presParams;
	long WindowStyle;

	GetWindowRect(hWnd, &windowRect);

	if(! fullscreen)
	{
		fullscreen = true;
		initParameters(presParams);
		// Set the fullscreen mode style, clear menu if attached
        SetWindowLong(hWnd, GWL_STYLE, WS_POPUP|WS_SYSMENU|WS_VISIBLE);
        if(hMenu == NULL)
        {
            hMenu = GetMenu(hWnd);
            SetMenu(hWnd, NULL);
        }

        // Set the Presentation Parameters, specifically
        presParams.Windowed = FALSE;
        presParams.BackBufferWidth = SCREEN_WIDTH;
        presParams.BackBufferHeight = SCREEN_HEIGHT;

		// Need to release assets and recreate
		release();
        // Reset D3D device, any device dependent objects
        if(FAILED(m_d3dDevice->Reset(&presParams)))
        {
            // Couldn't do the change, set things back
            SetWindowLong(hWnd, GWL_STYLE, WindowStyle);
            if(hMenu != NULL)
            {
                SetMenu(hWnd, hMenu);
                hMenu = NULL;
            }

            // Set the window position
            SetWindowPos(hWnd, HWND_NOTOPMOST,
                         windowRect.left, windowRect.top,
                         (windowRect.right - windowRect.left),
                         (windowRect.bottom - windowRect.top),
                         SWP_SHOWWINDOW);

            fullscreen = false;
			return true;
		}
		InitialiseDirect3D(hWnd);
		CreateSprites();
		
	}
	else
	{
		fullscreen = false;
		initParameters(presParams);
		// Set the windowed mode style, reset menu if needed
        SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
        if(hMenu != NULL)
        {
            SetMenu(hWnd, hMenu);
            hMenu = NULL;
        }

        // Set the Presentation Parameters, specifically
        presParams.Windowed = TRUE;
        presParams.BackBufferWidth = SCREEN_WIDTH;
        presParams.BackBufferHeight = SCREEN_HEIGHT;

		release();
        // Reset D3D device
        if(FAILED(m_d3dDevice->Reset(&presParams)))
            return false;

        // Set the window position
        SetWindowPos(hWnd, HWND_NOTOPMOST,
                     windowRect.left, windowRect.top,
                     (windowRect.right - windowRect.left),
                     (windowRect.bottom - windowRect.top),
                     SWP_SHOWWINDOW);
		InitialiseDirect3D(hWnd);
		CreateSprites();
        
	}
	return true;
}


bool Graphics2D::initParameters(D3DPRESENT_PARAMETERS &presParams)
{
	ZeroMemory(&presParams,sizeof(presParams));
	if(fullscreen)
	{
		presParams.Windowed=FALSE;
	}
	else
	{
		presParams.Windowed=TRUE;
	}
	presParams.SwapEffect=D3DSWAPEFFECT_DISCARD;
	presParams.EnableAutoDepthStencil = TRUE;
	presParams.AutoDepthStencilFormat = D3DFMT_D16;

	// if window
	// presParams.BackBufferFormat=D3DFMT_UNKNOWN;

	// if full screen
	presParams.BackBufferFormat = D3DFMT_X8R8G8B8;    // set the back buffer format to 32-bit
    presParams.BackBufferWidth = SCREEN_WIDTH;    // set the width of the buffer
    presParams.BackBufferHeight = SCREEN_HEIGHT;    // set the height of the buffer

	return true;
}


