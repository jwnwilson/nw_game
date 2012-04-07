#pragma once
#include "object.h"

class Sprite :
	public Object
{
public:
	Sprite(void);
	~Sprite(void);

	void setImage(const string &a){image=a;}
	void setXY(const float& a,const float& b){x=a;y=b;}
	void setHeight(const int& a){height=a;}
	void setWidth(const int& b){width=b;}
	float getX(){return x;}
	float getY(){return y;}
	int getHeight(){return height;}
	int getWidth(){return width;}
	void setAnimation(RECT* r){rect=r;}
	RECT* getAnimation(){return rect;}
	char* getImage(){return &image[0];}
	
protected:
	float x,y;
	int height,width;
	string image;
	RECT* rect;
};
