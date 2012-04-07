#pragma once
#include "engine.h"

class TestEngine :
	public Engine
{
public:
	TestEngine(void);
	~TestEngine(void);
	// will set a load of hardcoded values
	bool initialise();
    bool compute();
	bool menu();

	
};
