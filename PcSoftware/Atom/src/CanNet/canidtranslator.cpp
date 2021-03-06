/***************************************************************************
 *   Copyright (C) November 28, 2008 by Mattias Runge                             *
 *   mattias@runge.se                                                      *
 *   canidtranslator.cpp                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "canmessageexception.h"


#include "canvariable.h"


#include <vector>


#include "canidtranslator.h"

CanIdTranslator* CanIdTranslator::myInstance = NULL;

CanIdTranslator& CanIdTranslator::getInstance()
{
	if (myInstance == NULL)
	{
		myInstance = new CanIdTranslator();
	}

	return *myInstance;
}

void CanIdTranslator::deleteInstance()
{
	delete myInstance;
	myInstance = NULL;
}

CanIdTranslator::CanIdTranslator()
{
	Logger &log = Logger::getInstance();

	string filename = Settings::get("CanIdXMLFile");

	if (file_exists(filename))
	{
		xmlNode.load(filename.c_str());

		log.add("Loading definitions from " + filename + ".\n");
	}
	else
	{
		log.add("CanIdXMLFile is not defined in the config file, this will probably not work at all.\n");
	}
}

string CanIdTranslator::lookupClassName(int classId)
{
	XmlNode classesNode = xmlNode.findChild("classes");
	vector<XmlNode> classNodes = classesNode.getChildren();

	for (int n = 0; n < classNodes.size(); n++)
	{
		map<string, string> attributes = classNodes[n].getAttributes();

		if (stoi(attributes["id"]) == classId)
		{
			return attributes["name"];
		}
	}

	return "";
}

int CanIdTranslator::resolveClassId(string className)
{
	XmlNode classesNode = xmlNode.findChild("classes");
	vector<XmlNode> classNodes = classesNode.getChildren();

	for (int n = 0; n < classNodes.size(); n++)
	{
		map<string, string> attributes = classNodes[n].getAttributes();

		if (attributes["name"].compare(className) == 0)
		{
			return stoi(attributes["id"]);
		}
	}

	return -1;
}

string CanIdTranslator::lookupCommandName(int commandId, string moduleName)
{
	XmlNode commandsNode = xmlNode.findChild("commands");
	vector<XmlNode> commandNodes = commandsNode.getChildren();

	for (int n = 0; n < commandNodes.size(); n++)
	{
		map<string, string> attributes = commandNodes[n].getAttributes();

		if (commandId >= 128)
		{
			if (stoi(attributes["id"]) == commandId && attributes["module"] == moduleName)
			{
				return attributes["name"];
			}
		}
		else if (stoi(attributes["id"]) == commandId)
		{
			return attributes["name"];
		}
	}

	return "";
}

int CanIdTranslator::resolveCommandId(string commandName, string moduleName)
{
	XmlNode commandsNode = xmlNode.findChild("commands");
	vector<XmlNode> commandNodes = commandsNode.getChildren();

	for (int n = 0; n < commandNodes.size(); n++)
	{
		map<string, string> attributes = commandNodes[n].getAttributes();

		if (attributes["name"].compare(commandName) == 0)
		{
			int commandId = stoi(attributes["id"]);

			if (commandId >= 128)
			{
				if (attributes["module"] == moduleName)
				{
					return commandId;
				}
			}
			else
			{
				return commandId;
			}
		}
	}

	return -1;
}

string CanIdTranslator::lookupNMTCommandName(int commandId)
{
	XmlNode commandsNode = xmlNode.findChild("nmt_messages");
	vector<XmlNode> commandNodes = commandsNode.getChildren();

	for (int n = 0; n < commandNodes.size(); n++)
	{
		map<string, string> attributes = commandNodes[n].getAttributes();

		if (stoi(attributes["id"]) == commandId)
		{
			return attributes["name"];
		}
	}

	return "";
}

int CanIdTranslator::resolveNMTCommandId(string commandName)
{
	XmlNode commandsNode = xmlNode.findChild("nmt_messages");
	vector<XmlNode> commandNodes = commandsNode.getChildren();

	for (int n = 0; n < commandNodes.size(); n++)
	{
		map<string, string> attributes = commandNodes[n].getAttributes();

		if (attributes["name"].compare(commandName) == 0)
		{
			return stoi(attributes["id"]);
		}
	}

	return -1;
}

string CanIdTranslator::getDefineId(string name, string group)
{
	XmlNode definesNode = xmlNode.findChild("defines");
	vector<XmlNode> defineNodes = definesNode.getChildren();

	for (int n = 0; n < defineNodes.size(); n++)
	{
		map<string, string> attributes = defineNodes[n].getAttributes();

		if (attributes["group"] == group && attributes["name"] == name)
		{
			return attributes["id"];
		}
	}

	return "";
}

string CanIdTranslator::lookupDirectionFlag(int directionFlag)
{
	XmlNode definesNode = xmlNode.findChild("defines");
	vector<XmlNode> defineNodes = definesNode.getChildren();

	for (int n = 0; n < defineNodes.size(); n++)
	{
		map<string, string> attributes = defineNodes[n].getAttributes();

		if (attributes["group"].compare("DirectionFlag") == 0 && stoi(attributes["id"]) == directionFlag)
		{
			return attributes["name"];
		}
	}

	return "";
}

int CanIdTranslator::resolveDirectionFlag(string directionName)
{
	XmlNode definesNode = xmlNode.findChild("defines");
	vector<XmlNode> defineNodes = definesNode.getChildren();

	for (int n = 0; n < defineNodes.size(); n++)
	{
		map<string, string> attributes = defineNodes[n].getAttributes();

		if (attributes["group"].compare("DirectionFlag") == 0 && attributes["name"].compare(directionName) == 0)
		{
			return stoi(attributes["id"]);
		}
	}

	return -1;
}

string CanIdTranslator::lookupModuleName(int moduleId)
{
	XmlNode modulesNode = xmlNode.findChild("modules");
	vector<XmlNode> moduleNodes = modulesNode.getChildren();

	for (int n = 0; n < moduleNodes.size(); n++)
	{
		map<string, string> attributes = moduleNodes[n].getAttributes();

		if (stoi(attributes["id"]) == moduleId)
		{
			return attributes["name"];
		}
	}

	return "";
}

int CanIdTranslator::resolveModuleId(string moduleName)
{
	XmlNode modulesNode = xmlNode.findChild("modules");
	vector<XmlNode> moduleNodes = modulesNode.getChildren();

	for (int n = 0; n < moduleNodes.size(); n++)
	{
		map<string, string> attributes = moduleNodes[n].getAttributes();

		if (attributes["name"].compare(moduleName) == 0)
		{
			return stoi(attributes["id"]);
		}
	}

	return -1;
}

void CanIdTranslator::makeNMTDataValid(string commandName, map<string, CanVariable> &data)
{
	vector<XmlNode> commandNodes = xmlNode.findChild("nmt_messages").getChildren();

	for (int n = 0; n < commandNodes.size(); n++)
	{
		map<string, string> attributes = commandNodes[n].getAttributes();

		if (attributes["name"] == commandName)
		{
			XmlNode varablesNode = commandNodes[n].findChild("variables");

			makeDataValid(varablesNode.getChildren(), data);

			return;
		}
	}
}

void CanIdTranslator::makeDataValid(int commandId, string moduleName, map<string, CanVariable> &data)
{
	vector<XmlNode> commandNodes = xmlNode.findChild("commands").getChildren();

	for (int n = 0; n < commandNodes.size(); n++)
	{
		map<string, string> attributes = commandNodes[n].getAttributes();

		bool correct = false;

		if (commandId >= 128)
		{
			if (stoi(attributes["id"]) == commandId && attributes["module"] == moduleName)
			{
				correct = true;
			}
		}
		else if (stoi(attributes["id"]) == commandId)
		{
			correct = true;
		}

		if (correct)
		{
			XmlNode varablesNode = commandNodes[n].findChild("variables");

			makeDataValid(varablesNode.getChildren(), data);

			return;
		}
	}
}

void CanIdTranslator::makeDataValid(vector<XmlNode> variableNodes, map<string, CanVariable> &data)
{
	///FIXME: Remove variables that do not exist in the xmlfile
	for (int c = 0; c < variableNodes.size(); c++)
	{
		map<string, string> attributes = variableNodes[c].getAttributes();

		if (data.find(attributes["name"]) != data.end())
		{
			data[attributes["name"]].setType(attributes["type"]);
			data[attributes["name"]].setUnit(attributes["unit"]);
			data[attributes["name"]].setBitLength(stoi(attributes["bit_length"]));
			data[attributes["name"]].setStartBit(stoi(attributes["start_bit"]));

			if (attributes["type"] == "enum")
			{
				vector<XmlNode> values = variableNodes[c].getChildren();

				for (int k = 0; k < values.size(); k++)
				{
					map<string, string> valueAttributes = values[k].getAttributes();
					data[attributes["name"]].addEnumValue(valueAttributes["id"], valueAttributes["name"]);
				}
			}
		}
	}
}

string CanIdTranslator::translateDataToHex(int commandId, string moduleName, map<string, CanVariable> &data)
{
	makeDataValid(commandId, moduleName, data);

	return translateValidDataToHex(data);
}


map<string, CanVariable> CanIdTranslator::translateData(int commandId, string moduleName, string dataHex)
{
	vector<XmlNode> commandNodes = xmlNode.findChild("commands").getChildren();

	for (int n = 0; n < commandNodes.size(); n++)
	{
		map<string, string> attributes = commandNodes[n].getAttributes();

		bool correct = false;

		if (commandId >= 128)
		{
			if (stoi(attributes["id"]) == commandId && attributes["module"] == moduleName)
			{
				correct = true;
			}
		}
		else if (stoi(attributes["id"]) == commandId)
		{
			correct = true;
		}

		if (correct)
		{
			XmlNode varablesNode = commandNodes[n].findChild("variables");

			return translateData(varablesNode.getChildren(), dataHex);
		}
	}

	map<string, CanVariable> variables;
	return variables;
}

map<string, CanVariable> CanIdTranslator::translateNMTData(int commandId, string dataHex)
{
	vector<XmlNode> commandNodes = xmlNode.findChild("nmt_messages").getChildren();

	for (int n = 0; n < commandNodes.size(); n++)
	{
		map<string, string> attributes = commandNodes[n].getAttributes();

		if (stoi(attributes["id"]) == commandId)
		{
			XmlNode varablesNode = commandNodes[n].findChild("variables");

			return translateData(varablesNode.getChildren(), dataHex);
		}
	}

	map<string, CanVariable> variables;
	return variables;
}

string CanIdTranslator::translateNMTDataToHex(string commandName, map<string, CanVariable> &data)
{
	makeNMTDataValid(commandName, data);

	return translateValidDataToHex(data);
}


template <class T>
bool from_string(T& t, 
                 const std::string& s, 
                 std::ios_base& (*f)(std::ios_base&))
{
  std::istringstream iss(s);
  return !(iss >> f >> t).fail();
}


string CanIdTranslator::translateValidDataToHex(map<string, CanVariable> &data)
{
	string bin = "0000000000000000000000000000000000000000000000000000000000000000";
	int highestBit = 0;

	for (map<string, CanVariable>::iterator iter = data.begin(); iter != data.end(); iter++)
	{
		if (iter->second.getType() == "uint")
		{
			if (iter->second.getStartBit() + iter->second.getBitLength() > highestBit)
				highestBit = iter->second.getStartBit() + iter->second.getBitLength();

			unsigned int a = stou(iter->second.getValue());
			bin.replace(iter->second.getStartBit(), iter->second.getBitLength(), uint2bin(a, iter->second.getBitLength()));
		}
		else if (iter->second.getType() == "int")
		{
if (iter->second.getStartBit() + iter->second.getBitLength() > highestBit)
				highestBit = iter->second.getStartBit() + iter->second.getBitLength();

			unsigned int a = stou(iter->second.getValue());
			bin.replace(iter->second.getStartBit(), iter->second.getBitLength(), uint2bin(a, iter->second.getBitLength()));
			/*if (iter->second.getStartBit() + iter->second.getBitLength() > highestBit)
				highestBit = iter->second.getStartBit() + iter->second.getBitLength();
cout << iter->second.getValue() << endl;

			int a = stoi(iter->second.getValue());
cout << a << endl;
			bin.replace(iter->second.getStartBit(), iter->second.getBitLength(), uint2bin(a, iter->second.getBitLength()));*/
		}
		else if (iter->second.getType() == "float")
		{
			if (iter->second.getStartBit() + iter->second.getBitLength() > highestBit)
				highestBit = iter->second.getStartBit() + iter->second.getBitLength();
			bin.replace(iter->second.getStartBit(), iter->second.getBitLength(), float2bin(stof(iter->second.getValue()), iter->second.getBitLength()));
			
		}
	else if (iter->second.getType() == "enum")
		{
			if (iter->second.getStartBit() + iter->second.getBitLength() > highestBit)
				highestBit = iter->second.getStartBit() + iter->second.getBitLength();

			string value = iter->second.getEnumIdValue();

			if (value == "")
			{
				throw new CanMessageException("Got enum that could not be converterd to a value. value = \"" + iter->second.getValue() + "\" enumString is \"" + iter->second.getEnumsString() + "\"\n");
			}
			else
			{
				bin.replace(iter->second.getStartBit(), iter->second.getBitLength(), uint2bin(stou(value), iter->second.getBitLength()));
			}
		}
		else if (iter->second.getType() == "ascii")
		{
			for (int n = 0; n < iter->second.getValue().length(); n++)
			{
				if (iter->second.getStartBit()+n*8 + 8 > highestBit)
					highestBit = iter->second.getStartBit()+n*8 + 8;

				//bin.replace(iter->second.getStartBit()+n*8, 8, uint2bin((unsigned int)iter->second.getValue()[n], 8));
				unsigned int temp = iter->second.getValue()[n];
				if (temp > 0xff)
				{
					temp &= 0xff;
				}
				bin.replace(iter->second.getStartBit()+n*8, 8, uint2bin(temp, 8));
			}
		}
		else if (iter->second.getType() == "hexstring")
		{
			for (int n = 0; n < iter->second.getValue().length(); n++)
			{
				if (iter->second.getStartBit()+n*4 + 4 > highestBit)
					highestBit = iter->second.getStartBit()+n*4 + 4;

				string character;
				character += iter->second.getValue()[n];

				bin.replace(iter->second.getStartBit()+n*4, 4, hex2bin(character));
			}
		}
	}

	try
	{
		while (highestBit%8 != 0)
		{
		    highestBit++;
		}
		bin = bin.substr(0, highestBit);
	}
	catch (std::out_of_range& e)
	{
		cout << "DEBUG: translateValidDataToHex exception: " << e.what() << "\n";
		cout << "DEBUG: A bin=" << bin << " :: highestBit=" << highestBit << endl;
	}

	return bin2hex(bin);
}

map<string, CanVariable> CanIdTranslator::translateData(vector<XmlNode> variableNodes, string dataHex)
{
	map<string, CanVariable> variables;
	string dataBin = hex2bin(dataHex);
	//dataBin = rpad(dataBin, 64, '0');

	for (int c = 0; c < variableNodes.size(); c++)
	{
		map<string, string> attributes = variableNodes[c].getAttributes();

		int bitStart = stoi(attributes["start_bit"]);
		int bitLength = stoi(attributes["bit_length"]);
		string bits;

		try
		{
			bits = dataBin.substr(bitStart, bitLength);
		}
		catch (std::out_of_range& e)
		{
			return variables;
		}

		CanVariable variable;

		variable.setName(attributes["name"]);
		variable.setType(attributes["type"]);
		variable.setUnit(attributes["unit"]);
		variable.setStartBit(bitStart);
		variable.setBitLength(bitLength);

		if (attributes["type"] == "uint")
		{
			variable.setValue(utos(bin2uint(bits)));
		}
		else if (attributes["type"] == "int")
		{
			variable.setValue(itos(bin2int(bits)));
		}
		else if (attributes["type"] == "float")
		{
			variable.setValue(ftos(bin2float(bits)));
		}
		else if (attributes["type"] == "enum")
		{
			vector<XmlNode> values = variableNodes[c].getChildren();

			string value = utos(bin2uint(bits));

			for (int k = 0; k < values.size(); k++)
			{
				map<string, string> valueAttributes = values[k].getAttributes();
				variable.addEnumValue(valueAttributes["id"], valueAttributes["name"]);

				if (valueAttributes["id"] == value)
				{
					variable.setValue(valueAttributes["name"]);
				}
			}
		}
		else if (attributes["type"] == "ascii")
		{
			string str;

			for (int k = 0; k < bits.length(); k += 8)
			{
				try
				{
					str += (char)bin2uint(bits.substr(k, 8));
				}
				catch (std::out_of_range& e)
				{
					cout << "DEBUG: TranslateData exception: " << e.what() << "\n";
					cout << "DEBUG: B bits=" << bits << " :: k=" << k << endl;
					continue;
				}
			}

			variable.setValue(str);
		}
		else if (attributes["type"] == "hexstring")
		{
			string str;

			for (int k = 0; k < bits.length(); k += 4)
			{
				try
				{
					str += bin2hex(bits.substr(k, 4));
				}
				catch (std::out_of_range& e)
				{
					cout << "DEBUG: TranslateData exception: " << e.what() << "\n";
					cout << "DEBUG: C bits=" << bits << " :: k=" << k << endl;
					continue;
				}
			}

			variable.setValue(str);
		}

		variables[attributes["name"]] = variable;
	}

	return variables;
}


