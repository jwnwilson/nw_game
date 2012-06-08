#include "StdAfx.h"
#include "Input.h"

Input::Input(void)
{
	winHandle = NULL;
	mouse_state.lX =0;
	mouse_state.lY =0;
	mouse_state.lZ =0;
}

Input::~Input(void)
{
}
