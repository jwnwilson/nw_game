#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

string intToString(int num)
{
	stringstream ss;
	ss << num;
	return ss.str();
}

