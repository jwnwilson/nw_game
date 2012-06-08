#pragma once
#include "engine.h"
#include "Vector2D.h"

// Struct to hold data read from file
struct  TextureData {
	Object *objectPtr;
	string image;
	string command;
	double rectLeft,
		rectRight,
		rectTop,
		rectBottom;
	double posX, posY, posZ;
	double width, height;
	double row, column;

	void clear()
	{
		objectPtr =NULL;
		image ="";
		command = "";
		rectLeft = 0,
		rectRight =0,
		rectTop =0,
		rectBottom = 0;
		posX =0; 
		posY =0; 
		posZ =0;
		width =0;
		height =0;
		row=0; 
		column =0;
	}
};

class SpriteEngine :
	public Engine
{
public:
	SpriteEngine(void);
	~SpriteEngine(void);

	bool initialise();
    bool compute();
	bool menu();

private:
	Object* createSprite(const TextureData &textureData);
	bool getTextureData(TextureData &textureData);
	bool collision(const Vector2D &v2, Object* objPtr);
	bool mouseButtonCollision(int &buttonIndex);

	// private variables
	vector<Object*> buttonList;
};

