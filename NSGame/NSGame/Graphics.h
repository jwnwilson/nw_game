#pragma once
#include "World.h"
#include "Input.h"

// Dummy graphics class
class Graphics
{
public:
	Graphics(void);
	~Graphics(void);
	
	virtual bool initialise(HWND hWnd,HINSTANCE hInstance){return false;}
	virtual bool setWorld(const World* worldPtr){return false;}
	virtual bool draw(){return false;}
	virtual bool CreateSprites(){return false;}
	virtual bool release(){return false;}

	virtual bool toogleFullScreen(HWND hWnd){return false;}

	void setScreenWidth(int w){SCREEN_WIDTH =w;}
	void setScreenHeight(int h){SCREEN_HEIGHT =h;}
	int getScreenWidth(){return SCREEN_WIDTH;}
	int getScreenHeight(){return SCREEN_HEIGHT;}

	void setWinHandle(HWND w){winHandle = w;}
	void setInputPointer(Input *iPtr){ inputPtr = iPtr;}
	bool queryFullscreen(){return fullscreen;}
	RECT const* getWindowRect()const{return &windowRect;}

protected:
	// Scale position to match screen size
	D3DXVECTOR2 scaleTranslateToScreenSize(D3DXVECTOR2 &position);
	// For error handling
	HWND winHandle;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	RECT clientRect;                // Saved client rectangle
	RECT windowRect;				// Windowed rectangle
	bool fullscreen;
	// input pointer to draw cusor
	Input *inputPtr;
};


