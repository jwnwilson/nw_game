#include "StdAfx.h"
#include "Object.h"

Object::Object(void)
{
	x=0;
	y=0;
	z=0;
	image="unkown";
	rect=NULL;
}
Object::Object(const int& a,const int& b,const string& c)
{
	x=a;
	y=b;
	image=c;
	rect=NULL;
}

Object::~Object(void)
{
	if(rect!=NULL)
	{
		delete rect;
	}
}