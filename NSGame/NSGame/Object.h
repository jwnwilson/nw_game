#pragma once
#include <string>

#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>

using namespace std;

// Everything in our game will be some kind of object
class Object
{
public:
	Object(void);
	~Object(void);

	
	virtual void setXY(const float& a,const float& b){x=a;y=b;}
	virtual void setXYZ(const float& a,const float& b,const float& c){x=a;y=b;z=c;}
	virtual void setName(const string &a){name=a;}
	virtual float getX(){return x;}
	virtual float getY(){return y;}
	virtual float getZ(){return z;}
	virtual char* getName(){return &name[0];}
	virtual D3DXMATRIX* getMatrix(){return NULL;}

	//sprite animation functions
	virtual void setImage(const string &a){;}
	virtual void setHeight(const int& a){;}
	virtual void setWidth(const int& b){;}
	virtual int getHeight(){return 0;}
	virtual int getWidth(){return 0;}
	virtual void setAnimation(RECT* r){;}
	virtual RECT* getAnimation(){return NULL;}
	virtual char* getImage(){return NULL;}

	virtual void setRowColumnNumber(const int &row,const int &column){;}
	virtual void setRowColumn(const int &row,const int &column){;}
	virtual int getCurrentRow(){return 0;}
	virtual int getCurrentColumn(){return 0;}
	virtual int getRows(){return 0;}
	virtual int getColumns(){return 0;}
	virtual bool setNextFrame(){return false;}
	virtual bool updateAnimation(){return false;}

protected:
	string name;
	float x,y,z;
};
