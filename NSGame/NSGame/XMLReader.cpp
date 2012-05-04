#include "StdAfx.h"
#include "XMLReader.h"
#include "tinyXML/tinyxml.cpp"
#include "tinyXML/tinyxmlerror.cpp"
#include "tinyXML/tinyxmlparser.cpp"
#include "tinyXML/tinystr.cpp"

XMLReader::XMLReader(void)
{
}

XMLReader::~XMLReader(void)
{
	for(map<string, TiXmlDocument*>::iterator i=files.begin(); i!=files.end(); ++i)
	{
		delete files[(*i).first];
	}
}

bool XMLReader::initialise()
{
	return true;
}

bool XMLReader::read(string file)
{
	files[file] = new TiXmlDocument(&file[0]);
	if(! files[file]->LoadFile() )
	{
		// file not found
		cerr<< ("XML file: " + file + " not found!");
		return false;
	}

	return true;


}

bool XMLReader::write(string file, string newfile)
{
	files[file]->SaveFile(&newfile[0]);
	return true;
}

bool XMLReader::createFile(string file)
{
	if(files[file] != NULL)
	{
		delete files[file];
	}

	files[file] = new TiXmlDocument(&file[0]);

 	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	files[file]->LinkEndChild( decl );  

	TiXmlElement * root = new TiXmlElement( "NSGame" );  
	files[file]->LinkEndChild( root );

	return true;
}

bool XMLReader::CheckFile(string file)
{
	if(files[file] == NULL)
	{
		cerr<< "File not found when checking XML file.";
		return false;
	}

	return true;
}

bool XMLReader::setDoubleData(string file, string element, string parent, string valueName, double value)
{
	// loop through elements find parent
	TiXmlElement* root;
	TiXmlElement* pElem;
	TiXmlElement* cElem;
	TiXmlHandle docHandle( NULL );

	// if element doesn't exist craete it
	cElem = getElement(file, element,parent);
	// set element's value
	cElem->SetDoubleAttribute(&valueName[0], value);
	
	return true;
}

bool XMLReader::setStringData(string file, string element, string parent, string valueName, string value)
{
	// loop through elements find parent
	TiXmlElement* root;
	TiXmlElement* pElem;
	TiXmlElement* cElem;
	TiXmlHandle docHandle( NULL );

	// if element doesn't exist craete it
	cElem = getElement(file, element,parent);
	// set element's value
	cElem->SetAttribute(&valueName[0], &value[0]);
	
	return true;
}
bool XMLReader::getDoubleData(string file, string element,string parent,string valueName, double &value)
{
	// loop through elements find parent
	TiXmlElement* root;
	TiXmlElement* pElem;
	TiXmlElement* cElem;
	TiXmlHandle docHandle( NULL );

	// if element doesn't exist craete it
	cElem = getElement(file, element,parent);
	// set element's value
	if(!cElem->QueryDoubleAttribute(&valueName[0], &value))
	{
		return false;
	}
	// if element doesn't exist error

	// get element's value
	return true;
}

bool XMLReader::getStringData(string file, string element,string parent,string valueName, string &value)
{
	// loop through elements find parent
	TiXmlElement* root;
	TiXmlElement* pElem;
	TiXmlElement* cElem;
	TiXmlHandle docHandle( NULL );

	// if element doesn't exist craete it
	cElem = getElement(file, element,parent);
	// set element's value
	value = cElem->Attribute(&valueName[0]);
	if(value == "")
	{
		return false;
	}
	// if element doesn't exist error

	// get element's value
	return true;
}

TiXmlElement* XMLReader::getElement(string file, string element, string parent)
{
	// loop through elements find parent
	TiXmlElement* root;
	TiXmlElement* pElem;
	TiXmlElement* cElem;

	root = files[file]->RootElement();
	pElem = root;

	if (!root)
	{
		cerr<< ("No root element in xml file :" + file);
		return NULL;
	}

	// loop through elements
	for( pElem; pElem; pElem=pElem->NextSiblingElement())
	{
		if(pElem->Value() == parent)
		{
			cElem = pElem->FirstChildElement(&element[0]);
			if(!cElem)
			{
				// create child
				cElem = new TiXmlElement( &element[0] );  
				pElem->LinkEndChild(cElem);
			}
		}
	}
	return cElem;
}
bool XMLReader::addText(string file, string element, string parent, string text)
{
	// loop through elements find parent
	TiXmlElement* root;
	TiXmlElement* pElem;
	TiXmlElement* cElem;
	TiXmlHandle docHandle( NULL );
	TiXmlText * textXml;

	// if element doesn't exist craete it
	textXml = new TiXmlText( &text[0] );
	cElem = getElement(file, element,parent);
	// set element's value
	cElem->LinkEndChild(textXml);

	return true;
}


