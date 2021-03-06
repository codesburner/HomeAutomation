/***************************************************************************
 *   Copyright (C) December 5, 2008 by Mattias Runge                             *
 *   mattias@runge.se                                                      *
 *   canvariable.h                                            *
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

#ifndef _CANVARIABLE_H
#define	_CANVARIABLE_H

using namespace std;

#include <string>
#include <map>

#include "../Tools/tools.h"

class CanVariable
{
public:
	CanVariable() {};
	CanVariable(string name, string value)
	{
		setName(name);
		setValue(value);
	};
	CanVariable(string name, string value, string type, string unit)
	{
		setName(name);
		setValue(value);
		setType(type);
		setUnit(unit);
	};
	~CanVariable() {};

	string getName() { return myName; };
	void setName(string name) { myName = name; };

	string getValue() { return myValue; };
	void setValue(string value) { myValue = value; };

	string getType() { return myType; };
	void setType(string type) { myType = type; };

	string getUnit() { return myUnit; };
	void setUnit(string unit) { myUnit = unit; };

	unsigned int getBitLength() { return myBitLength; };
	void setBitLength(int bitLength) { myBitLength = bitLength; };

	unsigned int getStartBit() { return myStartBit; };
	void setStartBit(int startBit) { myStartBit = startBit; };

	string getEnumIdValue()
	{
		for (map<string, string>::iterator iter = myEnumValues.begin(); iter != myEnumValues.end(); iter++)
		{
			if (iter->second == myValue)
			{
				return iter->first;
			}
		}

		return "";
	}

	string getEnumsString()
	{
		string enumString = "";
		for (map<string, string>::iterator iter = myEnumValues.begin(); iter != myEnumValues.end(); iter++)
		{
			enumString += iter->first + "=" + iter->second + ",";
		}

		enumString = trim(enumString, ',');

		return enumString;
	}

	void addEnumValue(string id, string name)
	{
		myEnumValues[id] = name;
	}

private:
	string myName;
	string myValue;
	string myType;
	string myUnit;
	unsigned int myBitLength;
	unsigned int myStartBit;
	map<string, string> myEnumValues;
};

#endif	/* _CANVARIABLE_H */

