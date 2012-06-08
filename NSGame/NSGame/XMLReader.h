#pragma once
#include "FileIO.h"
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <vector>
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
	
	// Simple functions to manage small xml files possibly obsolete
	bool setDoubleData(string file, string element, string parent,string valueName, double value);
	bool setStringData(string file, string element, string parent,string valueName, string value);
	// retrieves data using reference
	bool getDoubleData(string file, string element, string parent,string valueName, double &value);
	bool getStringData(string file, string element, string parent,string valueName, string &value);

	// Navigate XML file
	// set currentElement to root of file
	bool setRoot(string file);
	// look for child element of current element
	bool findChildElement(string element, string valueName, string value);
	// fill vector with values of elements
	bool listElementsWithValue(string element, string valueName, vector<string> *returnValues);
	// return current element data
	bool getDoubleDataFromCurrent(string child, string valueName, double &value);
	bool getStringDataFromCurrent(string child, string valueName, string &value);
	// set data on current
	bool setDoubleDataOnCurrent(string child, string valueName, double value);
	bool setStringDataOnCurrent(string child, string valueName, string value);

	TiXmlElement* getCurrentElement()const{return currentElement;}
	void setCurrentElement(TiXmlElement* c){currentElement =c;}
	

private:
	// creates default start to a file
	bool createFile(string file);
	// get an element if it doesn't exist create it
	TiXmlElement* getElement(string file, string element, string parent);
	// adds text to element
	bool addText(string file, string element, string parent, string text);
	// map of files being used
	map<string, TiXmlDocument*> files;
	// Large files require navigation so store current element
	string currentFile;
	TiXmlElement* currentElement;
};
