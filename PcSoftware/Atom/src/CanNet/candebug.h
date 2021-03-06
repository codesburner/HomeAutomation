/***************************************************************************
 *   Copyright (C) December 27, 2008 by Mattias Runge                             *
 *   mattias@runge.se                                                      *
 *   candebug.h                                            *
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

#ifndef _CANDEBUG_H
#define	_CANDEBUG_H

using namespace std;

#include <string>

#include "../Threads/thread.h"
#include "../Socket/asyncsocket.h"
#include "../Socket/socketexception.h"
#include "../Socket/server.h"
#include "../Settings/settings.h"
#include "canmessage.h"

class CanDebug : public Server
{
public:
	static CanDebug& getInstance();
	static void deleteInstance();

	void sendCanMessageToAll(CanMessage canMessage);

protected:
	void handleClientData(int id, string data);

private:
	CanDebug();
	~CanDebug();
	static CanDebug* myInstance;
};


#endif	/* _CANDEBUG_H */

