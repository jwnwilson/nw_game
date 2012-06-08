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

	void setWinHandle(HWND w){winHandle = w;}
	void setInputPointer(Input *iPtr){ inputPtr = iPtr;}
	bool queryFullscreen(){return fullscreen;}

protected:
	// For error handling
	HWND winHandle;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	RECT ClientRect;                // Saved client rectangle
	RECT WindowRect;				// Windowed rectangle
	bool fullscreen;
	// input pointer to draw cusor
	Input *inputPtr;
};


