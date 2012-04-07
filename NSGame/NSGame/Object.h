#pragma once
#include <string>

using namespace std;

// Everything in our game will be some kind of object (specially women)
class Object
{
public:
	Object(void);
	Object(const int& a,const int& b,const string& c);
	~Object(void);

	virtual void setImage(const string &a){image=a;}
	virtual void setXY(const float& a,const float& b){x=a;y=b;}
	virtual void setXYZ(const float& a,const float& b,const float& c){x=a;y=b;z=c;}
	virtual void setHeight(const int& a){height=a;}
	virtual void setWidth(const int& b){width=b;}
	virtual float getX(){return x;}
	virtual float getY(){return y;}
	virtual float getZ(){return z;}
	virtual int getHeight(){return height;}
	virtual int getWidth(){return width;}
	virtual void setAnimation(RECT* r){rect=r;}
	virtual RECT* getAnimation(){return rect;}
	virtual char* getImage(){return &image[0];}

protected:
	float x,y,z;
	int height,width;
	string image;
	RECT* rect;
};
