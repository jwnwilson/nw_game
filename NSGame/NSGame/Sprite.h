#pragma once
#include "object.h"

// For sprite animation use simple layout, each row will have all the frames of an animation,
// once a row is set the animation will keep looping that row until another is selected.

class Sprite :
	public Object
{
public:
	Sprite(void);
	~Sprite(void);

	// Already covered in Object

	/*void setImage(const string &a){image=a;}
	void setXY(const float& a,const float& b){x=a;y=b;}
	void setHeight(const int& a){height=a;}
	void setWidth(const int& b){width=b;}
	float getX(){return x;}
	float getY(){return y;}
	int getHeight(){return height;}
	int getWidth(){return width;}
	void setAnimation(RECT* r){rect=r;}
	RECT* getAnimation(){return rect;}
	char* getImage(){return &image[0];}*/

	void setRowColumnNumber(const int &row,const int &column){rows=row; columns=column;}
	void setRowColumn(const int &row,const int &column){currentRow=row; currentColumn=column;}
	int getCurrentRow(){return currentRow;}
	int getCurrentColumn(){return currentColumn;}
	int getRows(){return rows;}
	int getColumns(){return columns;}
	bool setNextFrame();
	bool updateAnimation();

	
protected:
	//float x,y;
	//int height,width;
	// To manage rect and animation
	int rows, columns, currentRow, currentColumn;
	/*string image;
	RECT* rect;*/
};
