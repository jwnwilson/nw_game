#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

//#define WHEREARG			__FILE__, __LINE__
#ifndef GAMEERROR
#define GAMEERROR(msg,winHandle)	utilError(msg,winHandle, __FILE__, __LINE__)	
#endif
#ifndef GAMEWARNING
#define GAMEWARNING(msg,winHandle)	utilWarning(msg,winHandle, __FILE__, __LINE__)	
#endif
#ifndef intToString
string intToString(int num);
#endif
#ifndef utilError
bool utilError(string errorMsg, HWND winHandle, string fileName, int lineNumber);
#endif
#ifndef utilWarning
bool utilWarning(string warningMsg, HWND winHandle, string fileName, int lineNumber);
#endif


