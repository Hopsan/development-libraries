/*-----------------------------------------------------------------------------
 This source file is a part of Hopsan

 Copyright (c) 2009 to present year, Hopsan Group

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

 For license details and information about the Hopsan Group see the files
 GPLv3 and HOPSANGROUP in the Hopsan source code root directory

 For author and contributor information see the AUTHORS file
-----------------------------------------------------------------------------*/

// Include your component code code files here
// If you have lots of them you can include them in separate .h files and then include those files here instead.

#include "ElectricFuelCellL1.hpp"

// You need to include ComponentEssentials.h in order to gain access to the register function and the Factory types
// Also use the hopsan namespace

#include "ComponentEssentials.h"
using namespace hopsan;

// When you load your model into Hopsan, the register_contents() function bellow will be called
// It will register YOUR components into the Hopsan ComponentFactory

extern "C" DLLEXPORT void register_contents(ComponentFactory* pComponentFactory, NodeFactory* /*pNodeFactory*/)
{
    // ========== Register Components ==========
    // Use the registerCreatorFunction(KeyValue, Function) in the component factory to register components
    // The KeyValue is a text string with the TypeName of the component.
    // This value must be unique for every component in Hopsan.
    // If a typename is already in use, your component will not be added.
    // Suggestion, let the KeyValue (TypeName) be the same as your Class name
    // If that name is already in use, use something similar

    pComponentFactory->registerCreatorFunction("ElectricFuelCellL1", ElectricFuelCellL1::Creator);

    // ========== Register Custom Nodes (if any) ==========
    // This is not yet supported

}

// When you load your model into Hopsan, the get_hopsan_info() function bellow will be called
// This information is used to make sure that your component and the hopsan core have the same version

extern "C" DLLEXPORT void get_hopsan_info(HopsanExternalLibInfoT *pHopsanExternalLibInfo)
{
    //Change the name of the lib to something unique
    //You can include numbers in your name to indicate library version (if you want)
    pHopsanExternalLibInfo->libName = (char*)"HopsanDevTestLibrary";

    // Leave these two lines as they are
    pHopsanExternalLibInfo->hopsanCoreVersion = (char*)HOPSANCOREVERSION;
    pHopsanExternalLibInfo->libCompiledDebugRelease = (char*)DEBUGRELEASECOMPILED;

}
