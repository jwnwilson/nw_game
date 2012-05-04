#pragma once
#include "FileIO.h"
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include "tinyXML/tinyxml.h"


using namespace std;

class XMLReader: 
	public FileIO
{
public:
	XMLReader(void);
	~XMLReader(void);

	bool initialise();
	// read file store it in map
	bool read(string file);
	// look for file in map if it exists write it out
	bool write(string file, string newfile);
	// check file is correct type
	bool CheckFile(string file);
	
	// saves data to file
	bool setDoubleData(string file, string element, string parent,string valueName, double value);
	bool setStringData(string file, string element, string parent,string valueName, string value);
	// retrieves data using reference
	bool getDoubleData(string file, string element, string parent,string valueName, double &value);
	bool getStringData(string file, string element, string parent,string valueName, string &value);

private:
	// creates default start to a file
	bool createFile(string file);
	// get an element if it doesn't exist create it
	TiXmlElement* getElement(string file, string element, string parent);
	// adds text to element
	bool addText(string file, string element, string parent, string text);
	// map of files being used
	map<string, TiXmlDocument*> files;
};
