/*
 * 
 *  Copyright (C) 2010  Mattias Runge
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * 
 */

#ifndef VM_PLUGIN_H
#define VM_PLUGIN_H

#include <string>
#include <map>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <v8-debug.h>

#include "types.h"

namespace atom {
namespace vm {

class Plugin
{
public:
    typedef boost::shared_ptr<Plugin> Pointer;
    
    Plugin();
    virtual ~Plugin();
    
    std::string GetName();
    ExportFunctionList& GetExportFunctions();
    
    virtual void InitializeDone();
    virtual void ExecutionResult(std::string response, unsigned int request_id);
    
protected:
    typedef boost::shared_ptr<char> TrackerPointer;
    
    std::string name_;
    TrackerPointer tracker_;
    
    void Call(unsigned int request_id, std::string name, ArgumentListPointer arguments);
    void Execute(unsigned int request_id, std::string code);
    void ExportFunction(std::string name, v8::InvocationCallback function);
    static bool ImportFunction(std::string name);
    
private:
    ExportFunctionList export_functions_;
};

}; // namespace vm
}; // namespace atom

#endif // VM_PLUGIN_H