#include "StdAfx.h"
#include "MouseKeyboardInput.h"
#include "Utilities.h"


MouseKeyboardInput::MouseKeyboardInput(void)
{
	key=&keys[0];
	mouse=&mouse_state;
	m_diObject=NULL;
	m_diKeyboardDevice=NULL;
	m_diMouse=NULL;
	m_data.m_fCursorX=0;
	m_data.m_fCursorY=0;
	m_data.m_fCursorZ=0;
}


MouseKeyboardInput::~MouseKeyboardInput(void)
{
	if(m_diKeyboardDevice)
	{
		m_diKeyboardDevice->Unacquire();
		m_diKeyboardDevice->Release();
		m_diKeyboardDevice=NULL;
	}
	
	if(m_diMouse)
	{
		m_diMouse->Unacquire();
		m_diMouse->Release();
		m_diMouse = NULL;
	}
	if(m_diObject)
	{	
		m_diObject->Release();		
	}
}

/*MouseKeyboardInput::MouseKeyboardInput(HINSTANCE hInstance,HWND hWnd, DWORD keyBoard,DWORD mouse)
{
	initalise(hInstance,hWnd,keyBoard,mouse);
	key=&keys[0];
}*/

MouseKeyboardInput::MouseKeyboardInput(HINSTANCE hInstance,HWND hWnd)
{
	winHandle = hWnd;
	initalise(hInstance,hWnd);
	key=&keys[0];
}

float MouseKeyboardInput::getRelativeX()
{
	/*float result;
	float screenAbsoluteWidth = ( windowRect->right - windowRect->left);
	float xRatio = screenWidth / screenAbsoluteWidth;
	result = (m_data.m_fCursorX * xRatio);*/
	//return result;
	return m_data.m_fCursorX;
}
float MouseKeyboardInput::getRelativeY()
{
	/*float result;
	float screenAbsoluteHeight = ( windowRect->right - windowRect->left);
	float yRatio = screenWidth / screenAbsoluteHeight;
	result = (m_data.m_fCursorY * yRatio);*/
	//return result;
	return m_data.m_fCursorY;
}

bool MouseKeyboardInput::initalise(HINSTANCE hInstance,HWND hWnd)
{
	winHandle = hWnd;

	HRESULT hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
    IID_IDirectInput8, (void**)&m_diObject, NULL);

	if(FAILED(m_diObject->CreateDevice(GUID_SysKeyboard, &m_diKeyboardDevice, NULL)))
	{
		GAMEERROR("Unable to create input device object.",winHandle);
		return false;
	}

	if( FAILED( initMouse() ) )
	{
		GAMEERROR("Unable to create mouse initalise mouse.",winHandle);
		return false;
	}

	if( FAILED( initKeyboard() ) )
	{
		GAMEERROR("Unable to create mouse initalise keyboard.",winHandle);
		return false;
	}

	return true;

}

bool MouseKeyboardInput::initMouse(void)
{
	DIDEVCAPS MouseCapabilities; //device capabilities

	if(FAILED(m_diObject->CreateDevice(GUID_SysMouse, &m_diMouse, NULL)))
	{
		GAMEERROR("Unable to create mouse input device object.",winHandle);
		return false;
	}

	if(FAILED(m_diMouse->SetDataFormat(&c_dfDIMouse)))
	{
		GAMEERROR("Unable to set data format for mouse.",winHandle);
		return false;
	}

	if(FAILED(m_diMouse->SetCooperativeLevel(winHandle, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
	{
		GAMEERROR("Unable to set co-operation level for mouse.",winHandle);
		return false;
	}

	m_diMouse->Acquire();

	MouseCapabilities.dwSize = sizeof(MouseCapabilities);
	m_diMouse->GetCapabilities(&MouseCapabilities);

	if(!(MouseCapabilities.dwFlags & DIDC_ATTACHED))
	{
		GAMEERROR("Mouse is currently not attached.",winHandle);
		return false;
	}

	m_data.m_dwAxes = MouseCapabilities.dwAxes;
	m_data.m_dwButtons = MouseCapabilities.dwButtons;
	m_data.m_fSensitivity =1;
	m_data.m_iHotSpotX =0;
	m_data.m_iHotSpotY =0;

	//setCursor("arrow.bmp",0,0,0xffffffff);
	//setAttributes(false,1.0f);

	return true;
 }

bool MouseKeyboardInput::initKeyboard(void)
{
	if(FAILED(m_diKeyboardDevice->SetDataFormat( &c_dfDIKeyboard )))
	{
		GAMEERROR("Unable to set data format for keyboard.",winHandle);
		return false;
	}

	if(FAILED(m_diKeyboardDevice->SetCooperativeLevel(winHandle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		GAMEERROR("Unable to set data format for keyboard.",winHandle);
		return false;
	}

	return true;

}

bool MouseKeyboardInput::updateInput()
{
	m_diKeyboardDevice->Acquire();
	// If input is lost then acquire and keep trying until we get it back
	if(DIERR_INPUTLOST == m_diKeyboardDevice->GetDeviceState( sizeof(keys), keys ))
	{
		if (FAILED(m_diKeyboardDevice->Acquire()))
			return false;
	}

	// update mouse
	m_diMouse->Acquire();
	if(DIERR_INPUTLOST == m_diMouse->GetDeviceState(sizeof(DIMOUSESTATE),
		                                       (LPVOID)&mouse_state))
	{
		if (FAILED(m_diMouse->Acquire()))
			return false;
	}

	// Save data
	m_data.m_fCursorX += mouse->lX;
	m_data.m_fCursorY += mouse->lY;
	m_data.m_fCursorZ += mouse->lZ;

	return true;


}

bool MouseKeyboardInput::mouseButtonDown(int Button)
{
	if(mouse_state.rgbButtons[Button] & 0x80)
	{
		return true;
	}

	return false;
} 

bool MouseKeyboardInput::keyPressed(int keyIndice)
{
	if (key[keyIndice] & 0x80)
	{
			return true;
	}
	else
	{
		return false;
	}
}