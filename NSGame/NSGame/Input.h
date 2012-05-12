#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>

#define ESCKEY DIK_ESCAPE
#define WKEY DIK_W
#define SKEY DIK_S
#define AKEY DIK_A
#define DKEY DIK_D
#define SPACEKEY DIK_SPACE
#define SHIFTKEY DIK_LSHIFT

struct MouseCusorData
{
    float                m_fSensitivity,        //mouse sensitivity
                         m_fCursorX,            //cursor position 
                         m_fCursorY,
						 m_fCursorZ;			//middle mosue scroll
    int                  m_iHotSpotX,           //cursor hot spot 
                         m_iHotSpotY;
    DWORD                m_dwAxes,              //number of axes 
                         m_dwButtons,           //number of buttons 
                         m_dwCursorColor;       //cursor color 
};

// Dummy input class
class Input
{
public:
	Input(void);
	~Input(void);

	virtual bool initalise(HINSTANCE hInstance,HWND hWnd){return 0;}
	virtual bool initalise(HINSTANCE hInstance,HWND hWnd, DWORD keyBoard,DWORD mouse){return 0;}
	// updates keyboard and mouse
	virtual bool updateInput(){return 0;}
	// checks key from keyboard
	virtual bool keyPressed(int){return false;}
	// 0 = left mouse 1 = right mouse
	virtual bool mouseButtonDown(int){return false;}
	// get mouse cursor data
	virtual const MouseCusorData* getMouseCursorData()const{return NULL;}

	//set new cursor position
	virtual void setCursorPosition(float a,float b){;}

    //get relative movement
	virtual float getRelativeX(void){return mouse_state.lX;}
    virtual float getRelativeY(void){return mouse_state.lY;}
	//get wheel movement (NEW)
    virtual float getRelativeZ(void){return mouse_state.lZ;}
	// mouse matrix
	virtual D3DXMATRIX* getMatrix(){return NULL;}

	void setWinHandle(HWND w){winHandle = w;}

protected:
	// These may be removed
	// direct access to keyboard input.
	virtual BYTE* getKBInput(){return key;}
	// direct access to mouse input.
	virtual DIMOUSESTATE* getMInput(){return mouse;}

	// For error handling
	HWND winHandle;
	// Some typeDef of unsigned char
	BYTE keys[256];
	BYTE* key;
	DIMOUSESTATE mouse_state;
	DIMOUSESTATE* mouse;
	// The main DirectInput object pointer
	LPDIRECTINPUT8 m_diObject;
	// A DirectInput device object for the keyboard. If you want to handle other devices you need one of these for each.
	LPDIRECTINPUTDEVICE8	m_diKeyboardDevice,
							m_diMouse ;
};
