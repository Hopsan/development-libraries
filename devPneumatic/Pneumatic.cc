#include <iostream>
#include "ComponentEssentials.h"
#include "PneumaticPistonMass.hpp"
#include "PneumaticPistonSASpringMass.hpp"
#include "PneumaticPistonSpringMass.hpp"
#include "PneumaticCompressor.hpp"
#include "PneumaticRestrictor.hpp"
#include "PneumaticValve22.hpp"
#include "PneumaticValve32.hpp"
#include "PneumaticValve42.hpp"
#include "PneumaticValve43.hpp"
#include "PneumaticValve33.hpp"
#include "PneumaticValve52.hpp"
#include "PneumaticValve53.hpp"
#include "PneumaticExhaust.hpp"
#include "PneumaticPressureActivation.hpp"
#include "PneumaticVolumeM.hpp"
#include "PneumaticPsourceM.hpp"

using namespace hopsan;

extern "C" DLLEXPORT void register_contents(ComponentFactory* pComponentFactory, NodeFactory* pNodeFactory)
{
    //Register Components
    pComponentFactory->registerCreatorFunction("PneumaticPistonMass", PneumaticPistonMass::Creator);
    pComponentFactory->registerCreatorFunction("PneumaticPistonSASpringMass", PneumaticPistonSASpringMass::Creator);
    pComponentFactory->registerCreatorFunction("PneumaticPistonSpringMass", PneumaticPistonSpringMass::Creator);
    pComponentFactory->registerCreatorFunction("PneumaticCompressor", PneumaticCompressor::Creator);
    pComponentFactory->registerCreatorFunction("PneumaticRestrictor", PneumaticRestrictor::Creator);
    pComponentFactory->registerCreatorFunction("PneumaticValve22", PneumaticValve22::Creator);
    pComponentFactory->registerCreatorFunction("PneumaticValve32", PneumaticValve32::Creator);
    pComponentFactory->registerCreatorFunction("PneumaticValve42", PneumaticValve42::Creator);
    pComponentFactory->registerCreatorFunction("PneumaticValve43", PneumaticValve43::Creator);
    pComponentFactory->registerCreatorFunction("PneumaticValve33", PneumaticValve33::Creator);
    pComponentFactory->registerCreatorFunction("PneumaticValve52", PneumaticValve52::Creator);
    pComponentFactory->registerCreatorFunction("PneumaticValve53", PneumaticValve53::Creator);
    pComponentFactory->registerCreatorFunction("PneumaticExhaust", PneumaticExhaust::Creator);
    pComponentFactory->registerCreatorFunction("PneumaticPressureActivation", PneumaticPressureActivation::Creator);
    pComponentFactory->registerCreatorFunction("PneumaticVolumeM", PneumaticVolumeM::Creator);
    pComponentFactory->registerCreatorFunction("PneumaticPsourceM", PneumaticPsourceM::Creator);

    //Register custom nodes (if any)
    HOPSAN_UNUSED(pNodeFactory);
}

extern "C" DLLEXPORT void get_hopsan_info(HopsanExternalLibInfoT *pHopsanExternalLibInfo)
{
    pHopsanExternalLibInfo->hopsanCoreVersion = (char*)HOPSANCOREVERSION;
    pHopsanExternalLibInfo->libCompiledDebugRelease = (char*)DEBUGRELEASECOMPILED;
    pHopsanExternalLibInfo->libName = (char*)"PneumaticLib";
}
