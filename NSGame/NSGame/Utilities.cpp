#include "StdAfx.h"
#include "Utilities.h"

bool utilError(string errorMsg, HWND winHandle, string fileName, int lineNumber)
{
	string output = ("Error message:	" + errorMsg + "\n" + "File name:	" + fileName + "\n" + "Line number:\t" + intToString(lineNumber) );
	if(! MessageBox(winHandle, &output[0], "Error!", MB_ICONSTOP ))
	{
		return false;
	}
	return true;
}

bool utilWarning(string warningMsg, HWND winHandle, string fileName, int lineNumber)
{
	string output = ("Warning message:	" + warningMsg + "\n" + "File name:		" + fileName + "\n" + "Line number:\t" + intToString(lineNumber) );
	if(! MessageBox(winHandle, &output[0], "Warning", MB_ICONQUESTION ))
	{
		return false;
	}
	return true;
}

string intToString(int num)
{
	stringstream ss;
	ss << num;
	return ss.str();
}