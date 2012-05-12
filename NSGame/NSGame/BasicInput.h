#pragma once
//#define DIRECTINPUT_VERSION 0x0800
//#include <dinput.h>
#include "Input.h"

class BasicInput :
	public Input
{
public:
	BasicInput();
	BasicInput(HINSTANCE hInstance,HWND hWnd);
	~BasicInput();

	bool initalise(HINSTANCE hInstance,HWND hWnd);
	bool updateInput();

	// direct access to keyboard input.
	BYTE* getKBInput(){return key;}
	// direct access to mouse input.
	DIMOUSESTATE* getMInput(){return mouse;}

	bool keyPressed(int);       //check for key

	/*bool escKey();
	bool Akey();
	bool Dkey();
	bool Skey();
	bool Wkey();
	bool Spacekey();
	bool Shiftkey();  //note is only LEFT shift key
	bool mouseR();
	bool mouseL();*/
};

