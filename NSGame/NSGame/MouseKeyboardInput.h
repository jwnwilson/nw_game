#pragma once
#include "input.h"

// Mouse constants
#define DIMOUSE_LEFTBUTTON   0
#define DIMOUSE_RIGHTBUTTON  1
#define DIMOUSE_MIDDLEBUTTON 2
#define DIMOUSE_4BUTTON      3
#define DIMOUSE_5BUTTON      4
#define DIMOUSE_6BUTTON      5
#define DIMOUSE_7BUTTON      6
#define DIMOUSE_8BUTTON      7

// vertex format for cursor
#define D3DFVF_CURSORVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

class MouseKeyboardInput :
	public Input
{
public:
	MouseKeyboardInput(void);
	MouseKeyboardInput(HINSTANCE hInstance,HWND hWnd);
	//MouseKeyboardInput(HINSTANCE hInstance,HWND hWnd, DWORD keyBoard,DWORD mouse);
	~MouseKeyboardInput(void);

	bool initalise(HINSTANCE hInstance,HWND hWnd);
	bool initDirectInput(void); //init DirectInput
    bool initKeyboard(void);    //init keyboard
    bool initMouse(void);       //init mouse (NEW)
    bool updateInput(void);          //update device state

    bool keyPressed(int);       //check for key
	//check for mouse button 0 = left 1 = right
    bool mouseButtonDown(int);
	const MouseCusorData* getMouseCursorData(){return (&m_data);}

    //set new cursor position
	void setCursorPosition(float a,float b){m_data.m_iHotSpotX = a;m_data.m_iHotSpotY = b;}

    //get relative movement
	float getRelativeX(void){return m_data.m_fCursorX;}
    float getRelativeY(void){return m_data.m_fCursorY;}
    //get wheel movement (NEW)
    float getRelativeZ(void){return m_data.m_fCursorZ;}
    //get cursor position (NEW)
    float                getAbsoluteX(void){return 0;}
    float                getAbsoluteY(void){return 0;}
    D3DXMATRIX* getMatrix(){return &matrix;}

private:
	D3DXMATRIX			 matrix;
	MouseCusorData		 m_data;
	bool                 m_bInverted;           //inverted y axis 
    DWORD                m_dwScreenWidth,       //screen width 
                         m_dwScreenHeight;      //screen height 
                         

};

