/*-----------------------------------------------------------------------------
 This source file is part of Hopsan NG

 Copyright (c) 2011
    Mikael Axin, Robert Braun, Alessandro Dell'Amico, Björn Eriksson,
    Peter Nordin, Karl Pettersson, Petter Krus, Ingo Staack

 This file is provided "as is", with no guarantee or warranty for the
 functionality or reliability of the contents. All contents in this file is
 the original work of the copyright holders at the Division of Fluid and
 Mechatronic Systems (Flumes) at Linköping University. Modifying, using or
 redistributing any part of this file is prohibited without explicit
 permission from the copyright holders.
-----------------------------------------------------------------------------*/

// Include your component code code files here
// If you have lots of them you can include them in separate .h files and then include those files here instead.

#include "kinBicMod.hpp"
#include "bankHeadingSideslipIndicator.hpp"
#include "pitchAltitudeAngleOfAttackIndicator.hpp"
#include "trajectoryIndicator.hpp"
#include "attitudeIndicator.hpp"
#include "HeavyConstrMachine1D.hpp"
#include "mechanicRotPowerSensor.hpp"
#include "fleetTrajectoryIndicator.hpp"
#include "ComponentEssentials.h"


using namespace hopsan;

// When you load your model into Hopsan, the register_contents() function bellow will be called
// It will register YOUR components into the Hopsan ComponentFactory

extern "C" DLLEXPORT void register_contents(ComponentFactory* pComponentFactory, NodeFactory* pNodeFactory)
{
    // ========== Register Components ==========
    // Use the registerCreatorFunction(KeyValue, Function) in the component factory to register components
    // The KeyValue is a text string with the TypeName of the component.
    // This value must be unique for every component in Hopsan.
    // If a typename is already in use, your component will not be added.
    // Suggestion, let the KeyValue (TypeName) be the same as your Class name
    // If that name is already in use, use something similar

    pComponentFactory->registerCreatorFunction("KinematicBicycleModel", KinematicBicycleModel::Creator);
    pComponentFactory->registerCreatorFunction("BankHeadingSideslipIndicator", BankHeadingSideslipIndicator::Creator);
    pComponentFactory->registerCreatorFunction("PitchAltitudeAngleOfAttackIndicator", PitchAltitudeAngleOfAttackIndicator::Creator);
    pComponentFactory->registerCreatorFunction("TrajectoryIndicator", TrajectoryIndicator::Creator);
    pComponentFactory->registerCreatorFunction("AttitudeIndicator", AttitudeIndicator::Creator);
    pComponentFactory->registerCreatorFunction("HeavyConstrMachine1D", HeavyConstrMachine1D::Creator);
    pComponentFactory->registerCreatorFunction("MechanicRotationalPowerSensor", MechanicRotationalPowerSensor::Creator);
    pComponentFactory->registerCreatorFunction("FleetTrajectoryIndicator", FleetTrajectoryIndicator::Creator);
    
    
    
    // Register Custom Nodes (not yet supported)
    HOPSAN_UNUSED(pNodeFactory);


}

// When you load your model into Hopsan, the get_hopsan_info() function bellow will be called
// This information is used to make sure that your component and the hopsan core have the same version

extern "C" DLLEXPORT void get_hopsan_info(HopsanExternalLibInfoT *pHopsanExternalLibInfo)
{
    //Change the name of the lib to something unique
    //You can include numbers in your name to indicate library version (if you want)
    pHopsanExternalLibInfo->libName = (char*)"LarssonLibPublic";

    // Leave these two lines as they are
    pHopsanExternalLibInfo->hopsanCoreVersion = (char*)HOPSANCOREVERSION;
    pHopsanExternalLibInfo->libCompiledDebugRelease = (char*)DEBUGRELEASECOMPILED;
}
