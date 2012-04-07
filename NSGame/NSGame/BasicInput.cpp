#include "StdAfx.h"
#include "BasicInput.h"
#define BUFFER_SIZE  16

BasicInput::BasicInput(void)
{
	key=&keys[0];
	mouse=&mouse_state;
	m_diObject=NULL;
	m_diKeyboardDevice=NULL;
	m_diMouse=NULL;
}
BasicInput::BasicInput(HINSTANCE hInstance,HWND hWnd)
{
	initalise(hInstance,hWnd);
	key=&keys[0];
}

BasicInput::~BasicInput(void)
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
bool BasicInput::initalise(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
    IID_IDirectInput8, (void**)&m_diObject, NULL);

	if(FAILED(hr = m_diObject->CreateDevice(GUID_SysKeyboard, &m_diKeyboardDevice, NULL)))
		return false;

	if(FAILED(hr=m_diKeyboardDevice->SetDataFormat( &c_dfDIKeyboard )))
		return false;

	if(FAILED(hr = m_diKeyboardDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		return false;

	if(FAILED(hr = m_diObject->CreateDevice(GUID_SysMouse, &m_diMouse, NULL)))
		return false;

	if(FAILED(hr = m_diMouse->SetDataFormat(&c_dfDIMouse)))
		return false;

	if(FAILED(hr = m_diMouse->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
		return false;

	if (FAILED(m_diMouse->SetDataFormat(&c_dfDIMouse)))
		return false;

	if (FAILED(m_diMouse->Acquire()))
		return false;

	return true;

}

bool BasicInput::updateInput()
{
	// If input is lost then acquire and keep trying until we get it back
	bool error=true;

	HRESULT hr=m_diKeyboardDevice->Acquire();
	while( hr == DIERR_INPUTLOST )
	{     
		hr = m_diKeyboardDevice->Acquire();
	}
	// Now read the state again
	if(!m_diKeyboardDevice->GetDeviceState( sizeof(keys), keys ))
	{
		error=false;
	}

	if (FAILED(m_diMouse->Acquire()))
		if(error==false)
			return false;

	if(FAILED(hr=(m_diMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouse_state))))
		if(error==false)
			return false;

	return true;


}

bool BasicInput::escKey()
{
	if (key[DIK_ESCAPE] & 0x80)
	{
			return true;
	}
	else
	{
		return false;
	}
}

bool BasicInput::Dkey()
{
	if (key[DIK_D] & 0x80)
	{
			return true;
	}
	else
	{
		return false;
	}
}

bool BasicInput::Wkey()
{
	if (key[DIK_W] & 0x80)
	{
			return true;
	}
	else
	{
		return false;
	}
}
bool BasicInput::Akey()
{
	if (key[DIK_A] & 0x80)
	{
			return true;
	}
	else
	{
		return false;
	}
}
bool BasicInput::Skey()
{
	if (key[DIK_S] & 0x80)
	{
			return true;
	}
	else
	{
		return false;
	}
}
bool BasicInput::Spacekey()
{
	if (key[DIK_SPACE] & 0x80)
	{
			return true;
	}
	else
	{
		return false;
	}
}

bool BasicInput::Shiftkey()
{
	if (key[DIK_LSHIFT] & 0x80)
	{
			return true;
	}
	else
	{
		return false;
	}
}

bool BasicInput::mouseR()
{
	if (mouse_state.rgbButtons[1] & 0x80)
	{
			return true;
	}
	else
	{
		return false;
	}
}
bool BasicInput::mouseL()
{
	if (mouse_state.rgbButtons[0] & 0x80)
	{
			return true;
	}
	else
	{
		return false;
	}
}