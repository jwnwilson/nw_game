#pragma once
#include <string>

#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>

using namespace std;

struct ObjectData
{
float posX,
      posY,
      posZ,
      rotX,
	  rotY,
	  rotZ,
	  scaleX,
	  scaleY,
	  scaleZ;
};

struct SpriteData
{
	int rows, 
		columns, 
		currentRow, 
		currentColumn,
		height,
		width;
};


// Everything in our game will be some kind of object
class Object
{
public:
	Object(void);
	~Object(void);

	// Specifically for 2D objects
	virtual void setPosXY(const float& a,const float& b){worldSpaceData.posX=a;worldSpaceData.posY=b;}
	virtual void setRotX(const float& a){worldSpaceData.rotX=a;}
	// For 3D objects
	virtual void setPosXYZ(const float& a,const float& b,const float& c){worldSpaceData.posX=a;worldSpaceData.posY=b;worldSpaceData.posZ=c;}
	virtual void setRotXYZ(const float& a,const float& b,const float& c){worldSpaceData.rotX=a;worldSpaceData.rotY=b;worldSpaceData.rotZ=c;}
	virtual void setScaleXYZ(const float& a,const float& b,const float& c){worldSpaceData.scaleX=a;worldSpaceData.scaleY=b;worldSpaceData.scaleZ=c;}
	virtual void setName(const string &a){name=a;}
	virtual void setCommand(const string &a){command=a;}

	// Can manipulate object world space
	virtual ObjectData* getWorldSpaceData(){return &worldSpaceData;}	
	virtual char* getName(){return &name[0];}
	virtual D3DXMATRIX* getMatrix(){return NULL;}
	virtual char* getCommand(){return &command[0];}

	// These can be phased out
	virtual float getPosX(){return worldSpaceData.posX;}
	virtual float getPosY(){return worldSpaceData.posY;}
	virtual float getPosZ(){return worldSpaceData.posZ;}
	virtual float getRotX(){return worldSpaceData.rotX;}
	virtual float getRotY(){return worldSpaceData.rotY;}
	virtual float getRotZ(){return worldSpaceData.rotZ;}
	virtual float getScaleX(){return worldSpaceData.scaleX;}
	virtual float getScaleY(){return worldSpaceData.scaleY;}
	virtual float getScaleZ(){return worldSpaceData.scaleZ;}

	//sprite animation functions
	virtual void setImage(const string &a){;}
	virtual void setHeight(const int& a){;}
	virtual void setWidth(const int& b){;}
	virtual void setAnimation(RECT* r){;}
	virtual RECT* getAnimation(){return NULL;}
	virtual char* getImage(){return NULL;}

	virtual void setRowColumnNumber(const int &row,const int &column){;}
	virtual void setRowColumn(const int &row,const int &column){;}
	virtual SpriteData* getAnimationData(){return NULL;}

	virtual bool setNextFrame(){return false;}
	virtual bool updateAnimation(){return false;}

	// These can be phased out
	virtual int getCurrentRow(){return 0;}
	virtual int getCurrentColumn(){return 0;}
	virtual int getRows(){return 0;}
	virtual int getColumns(){return 0;}
	virtual int getHeight(){return 0;}
	virtual int getWidth(){return 0;}
	

protected:
	string name;
	string command;
	// Contains world space data
	ObjectData worldSpaceData;
	/*float posX,posY,posZ;
	float rotX,rotY,rotZ;
	float scaleX,scaleY,scaleZ;*/
};
