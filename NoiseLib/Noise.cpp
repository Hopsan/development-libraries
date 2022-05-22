/*
 * Noise Library.
 * Components for various types of noise and randomness.
 *
 *
 * @file   Noise.cpp
 * @author Lönja Selter <Loenja@Selter.co.uk>
 * @date   2022-05-22
 *
 * @brief
 *
*/


#include "ComponentEssentials.h"
#include "noiseSimplex1D.hpp"
#include "noiseSimplex4D.hpp"
#include "noiseVariableSimplex1D.hpp"
#include "noiseSeed.hpp"

using namespace hopsan;

extern "C" DLLEXPORT void register_contents(ComponentFactory* pComponentFactory, NodeFactory* pNodeFactory)
{
    //Register Components
    pComponentFactory->registerCreatorFunction("noiseSimplex1D", noiseSimplex1D::Creator);
    pComponentFactory->registerCreatorFunction("noiseSimplex4D", noiseSimplex4D::Creator);
    pComponentFactory->registerCreatorFunction("noiseVariableSimplex1D", noiseVariableSimplex1D::Creator);
    pComponentFactory->registerCreatorFunction("noiseSeed", noiseSeed::Creator);

    //Register custom nodes (if any)
    HOPSAN_UNUSED(pNodeFactory)
}

extern "C" DLLEXPORT void get_hopsan_info(HopsanExternalLibInfoT *pHopsanExternalLibInfo)
{
    pHopsanExternalLibInfo->hopsanCoreVersion = (char*)HOPSANCOREVERSION;
    pHopsanExternalLibInfo->libCompiledDebugRelease = (char*)HOPSAN_BUILD_TYPE_STR;
    pHopsanExternalLibInfo->libName = (char*)"Noise";
}
