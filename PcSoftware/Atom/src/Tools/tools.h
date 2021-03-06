/***************************************************************************
 *   Copyright (C) 2003 by Mattias Runge                                   *
 *   mattias@mrunge.se                                                     *
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
#ifndef _TOOLS_H
#define _TOOLS_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

using namespace std;

#include <cmath>
#include <sys/types.h>
#include <dirent.h>

string niceTime();
unsigned int hex2uint(string hex);
string hex2bin(string hex);
string bin2hex(string bin);
float bin2float(string bin);
string float2bin(float num, int length);
unsigned int bin2uint(string bin);
int bin2int(string bin);
string uint2bin(unsigned int num, int length);
string uint2hex(unsigned int num, int length);
string int2bin(int num, int length);
string int2hex(int num, int length);
vector<string> explode(string delimiter, string str);
string strtoupper(string s);
string strtolower(string s);
string trim(string s);
string trim(const string s, char c);
int stoi(const string s);
string itos(int i);
string utos(unsigned int i);
unsigned int stou(const string s);
float stof(const string s);
string ftos(float f);
string str_replace(string search, string replace, string str);
string file_get_contents(string filename);
bool file_exists(string filename);
string escape(string in);
string rpad(string in, int length, char c);
string lpad(string in, int length, char c);

#endif // _TOOLS_H
