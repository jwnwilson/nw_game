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
	bool setData(string file, string element, string parent,string valueName, double value);
	// retrieves data using reference
	bool getData(string file, string element, string parent,string valueName, double &value);

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
