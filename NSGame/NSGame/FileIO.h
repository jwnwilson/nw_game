#pragma once
#include <string>

using namespace std;

// Dummy file open close class
class FileIO
{
public:
	FileIO(void);
	~FileIO(void);
	virtual bool initialise(){return false;}
	virtual bool read(string file){return false;}
	virtual bool write(string file, string newFile){return false;}

	//virtual bool createFile(string file){return false;}
	virtual bool setData(string file, string element, string parent,string valueName,double value){return false;}
	virtual bool getData(string file, string element, string parent,string valueName,double &value){return false;}
};
