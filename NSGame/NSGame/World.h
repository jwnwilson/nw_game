#pragma once
// vectors are basicly dynamic arrays very useful if I still haven't explained them ask my bitch ass why the hell not
#include <vector>
#include "Object.h"

// Not much thought has been put into this yet is still very dodgy
class World
{
public:
	World(void);
	~World(void);

	virtual vector<Object*> getObjects()const{return objects; }
	virtual bool addObject(Object* obj){objects.push_back(obj); return true;}
	virtual bool clearObjects();

	virtual bool setBackGround(Object* obj){return false;}
	virtual bool setMiddleGround(Object* obj){return false;}
	virtual bool setForeGround(Object* obj){return false;}


protected:
	vector<Object*> objects;
};
