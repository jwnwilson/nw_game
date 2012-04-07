#pragma once
#include "World.h"

// Dummy graphics class
class Graphics
{
public:
	Graphics(void);
	~Graphics(void);
	
	// inline functions cos I'm lazy
	virtual bool initialise(HWND hWnd,HINSTANCE hInstance){return false;}
	virtual bool setWorld(const World* worldPtr){return false;}
	virtual bool draw(){return false;}
	virtual bool CreateSprites(){return false;}
	virtual bool release(){return false;}

	virtual bool toogleFullScreen(HWND hWnd){return false;}

protected:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	bool fullscreen;
};


