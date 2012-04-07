#pragma once
#include "engine.h"
class SpriteEngine :
	public Engine
{
public:
	SpriteEngine(void);
	~SpriteEngine(void);

	bool initialise();
    bool compute();
	bool menu();
};

