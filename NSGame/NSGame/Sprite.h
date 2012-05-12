#pragma once
#include "object.h"

// For sprite animation use simple layout, each row will have all the frames of an animation,
// once a row is set the animation will keep looping that row until another is selected.
class Sprite :
	public Object
{
public:
	Sprite(void);
	Sprite(const int& a,const int& b,const string& c);
	~Sprite(void);

	void setImage(const string &a){image=a;}
	void setHeight(const int& a){animationData.height=a;}
	void setWidth(const int& b){animationData.width=b;}
	int getHeight(){return animationData.height;}
	int getWidth(){return animationData.width;}
	void setAnimation(RECT* r){rect=r;}
	RECT* getAnimation(){return rect;}
	char* getImage(){return &image[0];}
	D3DXMATRIX* getMatrix(){return &matrix;}

	void setRowColumnNumber(const int &row,const int &column){animationData.rows=row; animationData.columns=column;}
	void setRowColumn(const int &row,const int &column){animationData.currentRow=row; animationData.currentColumn=column;}
	SpriteData* getAnimationData(){return &animationData;}
	
	int getCurrentRow(){return animationData.currentRow;}
	int getCurrentColumn(){return animationData.currentColumn;}
	int getRows(){return animationData.rows;}
	int getColumns(){return animationData.columns;}

	bool setNextFrame();
	bool updateAnimation();

	
protected:
	// To manage rect and animation
	SpriteData animationData;
	string image;
	RECT* rect;
	D3DXMATRIX matrix;
};
