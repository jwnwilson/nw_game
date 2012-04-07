#pragma once
#include "fileio.h"

class TestImporter :
	public FileIO
{
public:
	TestImporter(void);
	~TestImporter(void);
	bool initialise();
    bool read(string file);
	bool write(string file,string newFile);
};
