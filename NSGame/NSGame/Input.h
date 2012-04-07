#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

// Dummy input class
class Input
{
public:
	Input(void);
	~Input(void);

	virtual bool initalise(HINSTANCE hInstance,HWND hWnd){return 0;}
	virtual bool updateInput(){return 0;}

	// direct access to keyboard input.
	virtual BYTE* getKBInput(){return key;}
	// direct access to mouse input.
	virtual DIMOUSESTATE* getMInput(){return mouse;}

	virtual bool escKey(){return 0;}
	virtual bool Akey(){return 0;}
	virtual bool Dkey(){return 0;}
	virtual bool Skey(){return 0;}
	virtual bool Wkey(){return 0;}
	virtual bool Spacekey(){return 0;}
	virtual bool Shiftkey(){return 0;}  //note is only LEFT shift key
	virtual bool mouseR(){return 0;}
	virtual bool mouseL(){return 0;}

protected:
	// I think this is some typeDef of unsigned char, dunno why they can't use char nob ends
	BYTE keys[256];
	DIMOUSESTATE mouse_state;
	BYTE* key;
	DIMOUSESTATE* mouse;
	// The main DirectInput object pointer
	LPDIRECTINPUT8 m_diObject;
	// A DirectInput device object for the keyboard. If you want to handle other devices you need one of these for each.
	LPDIRECTINPUTDEVICE8 m_diKeyboardDevice,m_diMouse ;
};
