#pragma once
#include "world.h"
class World2D :
	public World
{
public:
	World2D(void);
	~World2D(void);

	 //vector<Object*> objects getObjects();
	 void setBackGround(Object*);
	 void setMiddleGround(Object*);
	 void setForeGround(Object*);

	 bool addObject(Object* obj){ setBackGround(obj); return true;}
	 bool clearObjects() {objects.clear(); return true;}

protected:

	bool upDateObjects();

	vector<Object*> backGround;
	vector<Object*> middleGround;
	vector<Object*> foreGround;
};

