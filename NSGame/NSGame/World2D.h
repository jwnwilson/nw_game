#pragma once
#include "world.h"
class World2D :
	public World
{
public:
	World2D(void);
	~World2D(void);

	 //vector<Object*> objects getObjects();
	 bool setBackGround(Object*);
	 bool setMiddleGround(Object*);
	 bool setForeGround(Object*);

	 bool addObject(Object* obj){ setBackGround(obj); return true;}
	 bool clearObjects() {objects.clear(); return true;}

protected:

	bool upDateObjects();

	vector<Object*> backGround;
	vector<Object*> middleGround;
	vector<Object*> foreGround;
};

