#include "stdafx.h"
#include "Graphics2D.h"
#include <assert.h>
#include <mmsystem.h>
#include <string>
#include <iostream>

// Constructor
Graphics2D::Graphics2D(void): m_d3dObject(0),m_d3dDevice(0)
{
	ppSprite=NULL;

}

// Destructor
Graphics2D::~Graphics2D(void)
{
	// Once we have finished with the Direct3D objects we must release them
	if (m_d3dDevice)
		m_d3dDevice->Release();

	if (m_d3dObject)
		m_d3dObject->Release();
	
	for(int i=0;i<gTexture.size();i++)
	{
		gTexture[i]->Release();
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
	
	for(int i=0;i<gTexture.size();i++)
	{
		gTexture[i]->Release();
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
	// Shits gonna get initialized!!
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

	// A load of params for something directX-y
	D3DPRESENT_PARAMETERS presParams;
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
	//presParams.BackBufferFormat=D3DFMT_UNKNOWN;

	// if full screen
	presParams.BackBufferFormat = D3DFMT_X8R8G8B8;    // set the back buffer format to 32-bit
    presParams.BackBufferWidth = SCREEN_WIDTH;    // set the width of the buffer
    presParams.BackBufferHeight = SCREEN_HEIGHT;    // set the height of the buffer

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
		std::cout<< "error creating sprite\n";
		return false;
	}
	
	// We don't want a z buffer (ask me for explaination) the comment below is a dick

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
	gTexture.resize(world->getObjects().size());
	for(int i=0;i<world->getObjects().size();i++)
	{
		if (FAILED(D3DXCreateTextureFromFile(m_d3dDevice,world->getObjects()[i]->getImage(),&gTexture[i])))
		 {
			std::cout<<"error creating texture\n";
	 		return false;
		}
	}
}

bool Graphics2D::DrawSprites()
{	
	D3DXVECTOR3 pos;

	if(FAILED(ppSprite->Begin(D3DXSPRITE_ALPHABLEND)))
	{
		std::cout<<"error begin\n";
		return false;
	}
	for(int i=0;i<world->getObjects().size();i++)
	{
		pos.x= world->getObjects()[i]->getX();
		pos.y= world->getObjects()[i]->getY();
		pos.z= world->getObjects()[i]->getZ(); 

		if(FAILED(ppSprite->Draw(gTexture[i],world->getObjects()[i]->getAnimation(),NULL,&pos,0xFFFFFFFF)))
		{
			std::cout<<"error drawing "<<world->getObjects()[i]->getImage()<<endl;
			return false;	
		}
	}
	if(FAILED(ppSprite->End()))
	{
		std::cout<<"error end\n";
		return false;

	}
	return true;
}

bool Graphics2D::toogleFullScreen(HWND hWnd)
{
	HMENU hMenu = NULL; 
	// A load of params for something directX-y
	D3DPRESENT_PARAMETERS presParams;
	RECT WindowRect; 
	long WindowStyle;

	GetWindowRect(hWnd, &WindowRect);

	if(fullscreen)
	{
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
                         WindowRect.left, WindowRect.top,
                         (WindowRect.right - WindowRect.left),
                         (WindowRect.bottom - WindowRect.top),
                         SWP_SHOWWINDOW);

            return false;
        }

        fullscreen = false;
	}
	else
	{
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

        // Reset D3D device
        if(FAILED(m_d3dDevice->Reset(&presParams)))
            return false;

        // Set the window position
        SetWindowPos(hWnd, HWND_NOTOPMOST,
                     WindowRect.left, WindowRect.top,
                     (WindowRect.right - WindowRect.left),
                     (WindowRect.bottom - WindowRect.top),
                     SWP_SHOWWINDOW);

        fullscreen = true;
	}
	return false;
}


