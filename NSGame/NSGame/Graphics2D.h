#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include <vector>
#include <map>
#include "World.h"
#include "Graphics.h"

using namespace std;

class Graphics2D :
	public Graphics
{
public:
	Graphics2D(void);
	~Graphics2D(void);

	bool initialise(HWND hWnd,HINSTANCE hInstance);
	bool setWorld(const World* worldPtr){world = worldPtr; return true;}
	bool CreateSprites();
	bool draw();
	bool release();

	bool toogleFullScreen(HWND hWnd);
    void drawCursor(void);

private:
	bool initParameters(D3DPRESENT_PARAMETERS &presParams);
	// Direct3D Objects these are directX classes
	LPDIRECT3D9 m_d3dObject;
	LPDIRECT3DDEVICE9 m_d3dDevice;

	//LPDIRECT3DVERTEXBUFFER9 m_vertexBuffer;
	//LPDIRECT3DINDEXBUFFER9  m_indexBuffer;

	LPDIRECT3DTEXTURE9   m_pCursorTexture;
	float	cursorScaleX,
			cursorScaleY;
	map<string, LPDIRECT3DTEXTURE9> gTexture;
	LPD3DXSPRITE ppSprite;
	const World* world;

	bool InitialiseDirect3D(HWND hWnd);
	bool CheckHR(HRESULT hr);
	bool DrawSprites();

};

