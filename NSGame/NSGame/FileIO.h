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
	virtual bool setDoubleData(string file, string element, string parent,string valueName, double value){return false;}
	virtual bool setStringData(string file, string element, string parent,string valueName, string value){return false;}
	// retrieves data using reference
	virtual bool getDoubleData(string file, string element, string parent,string valueName, double &value){return false;}
	virtual bool getStringData(string file, string element, string parent,string valueName, string &value){return false;}

	void setWinHandle(HWND w){winHandle = w;}

private:
	// For error handling
	HWND winHandle;
};
