#include "StdAfx.h"
#include "Game.h"
#include "SpriteEngine.h"
#include "Utilities.h"
#include "MouseKeyboardInput.h"

SpriteEngine::SpriteEngine(void)
{
}


SpriteEngine::~SpriteEngine(void)
{
}

bool SpriteEngine::initialise()
{
	vector<string> textures;
	vector<string> buttons;
	TextureData dataFromFile;
	string name;
	string command;

	// Read menu file
	if(! xmlReader->read("menu.xml"))
	{
		GAMEERROR("Error reading menu.xml.",winHandle);
	}

	xmlReader->setRoot("menu.xml");
	
	// Load menu items

	// Get base menu
	if(!xmlReader->findChildElement("Menu", "name", "baseMenu") )
	{
		GAMEERROR("Base menu data not found in menu.xml",winHandle);
	}

	// store base Menu position in file
	TiXmlElement* BaseMenu = xmlReader->getCurrentElement();

	// Load textures
	xmlReader->listElementsWithValue("Texture", "name", &textures);

	for(int i=0;i<textures.size();i++)
	{
		name = textures[i];
		if(!xmlReader->findChildElement("Texture", "name", name) )
		{
			GAMEERROR("Texture data not found",winHandle);
		}

		dataFromFile.clear();
		getTextureData(dataFromFile);
		createSprite(dataFromFile);
		// reset position in XML file
		xmlReader->setCurrentElement(BaseMenu);
	}	
	
	// Load buttons
	xmlReader->listElementsWithValue("Button", "name", &buttons);

	for(int i=0;i<buttons.size();i++)
	{
		name = buttons[i];
		Object *buttonPtr;
		if(!xmlReader->findChildElement("Button", "name", name) )
		{
			GAMEERROR("Texture data not found",winHandle);
		}

		dataFromFile.clear();
		getTextureData(dataFromFile);
		buttonPtr= createSprite(dataFromFile);
		buttonList.push_back(buttonPtr);
		// reset position in XML file
		xmlReader->setCurrentElement(BaseMenu);
	}

	return true;

}
bool SpriteEngine::compute()
{
	float time = timeGetTime();
	engineInput->updateInput();
	
	if(engineInput->keyPressed(ESCKEY))
	{
		GAMESTATE = GAME_EXIT;
	}
	else
	{
		GAMESTATE = GAME_RUN;
	}
	return true;
}

bool SpriteEngine::menu()
{
	float time = timeGetTime();
	engineInput->updateInput();
	// See if button has been pressed
	if(engineInput->mouseButtonDown(DIMOUSE_LEFTBUTTON))
	{
		int buttonIndex;
		// Check for button collision
		if( mouseButtonCollision( buttonIndex ) )
		{
			// Change state or rules as necessary
			if( buttonList[buttonIndex]->getCommand() == "start" )
			{
				GAMESTATE = GAME_RUN;
			}
			else if( buttonList[buttonIndex]->getCommand() == "exit" )
			{
				GAMESTATE = GAME_EXIT;
			}
		}
	}
	if(engineInput->keyPressed(F1KEY))
	{
		if(configData.fullscreen ==  true)
		{
			configData.fullscreen = false;
		}
		else
		{
			configData.fullscreen = true;
		}
		GAMESTATE = GAME_CONFIG;
	}
	else if(engineInput->keyPressed(ESCKEY))
	{
		GAMESTATE = GAME_RUN;
	}
	else
	{
		GAMESTATE = GAME_MENU;
	}

	return true;
}
bool SpriteEngine::collision(const Vector2D &pos, Object* objPtr)
{
	int width = objPtr->getWidth();
	int height = objPtr->getHeight();
	Vector2D objPos(objPtr->getPosX(),objPtr->getPosY());
	Vector2D result;

	result = pos - objPos;

	if(result.x < (width/2) )
	{
		if(result.y < (height/2) )
		{
			return true;
		}
	}
	return false;
}

bool SpriteEngine::mouseButtonCollision(int &buttonIndex)
{
	float x= engineInput->getRelativeX();
	float y= engineInput->getRelativeY();

	for(int i=0; i<buttonList.size(); i++)
	{
		if(collision(Vector2D(x,y), buttonList[i]))
		{
			buttonIndex= i;
			return true;
		}
	}
	return false;
}

bool SpriteEngine::getTextureData(TextureData &dataFromFile)
{
	
	xmlReader->getStringDataFromCurrent("Image", "file", dataFromFile.image);
	xmlReader->getDoubleDataFromCurrent("Rect", "left", dataFromFile.rectLeft);
	xmlReader->getDoubleDataFromCurrent("Rect", "right", dataFromFile.rectRight);
	xmlReader->getDoubleDataFromCurrent("Rect", "top", dataFromFile.rectTop);
	xmlReader->getDoubleDataFromCurrent("Rect", "bottom", dataFromFile.rectBottom);
	xmlReader->getDoubleDataFromCurrent("Position", "x", dataFromFile.posX);
	xmlReader->getDoubleDataFromCurrent("Position", "y", dataFromFile.posY);
	xmlReader->getDoubleDataFromCurrent("Position", "z", dataFromFile.posZ);
	xmlReader->getDoubleDataFromCurrent("Size", "width", dataFromFile.width);
	xmlReader->getDoubleDataFromCurrent("Size", "height", dataFromFile.height);
	xmlReader->getDoubleDataFromCurrent("Animation", "row", dataFromFile.row);
	xmlReader->getDoubleDataFromCurrent("Animation", "column", dataFromFile.column);
	xmlReader->getStringDataFromCurrent("Command", "command", dataFromFile.command);
	return true;
}

Object* SpriteEngine::createSprite(const TextureData &td)
{
	Object *spritePtr = new Sprite();
	RECT *animRec = new RECT;
	animRec->left= td.rectLeft;
	animRec->right= td.rectRight;
	animRec->top= td.rectTop;
	animRec->bottom= td.rectBottom;
	
	spritePtr->setPosXYZ( td.posX , td.posY , td.posZ);
	spritePtr->setWidth( td.width );
	spritePtr->setHeight( td.height );
	spritePtr->setRowColumnNumber( td.row, td.column);
	spritePtr->setImage( td.image );
	spritePtr->setAnimation(animRec);
	spritePtr->setCommand(td.command);

	worldPtr->addObject( spritePtr );
	return spritePtr;
}

