#include <iostream>
#include "ComponentEssentials.h"
#include "electricQGround.hpp"
#include "signalScientificNotation.hpp"
#include "signalPow.hpp"
#include "signalModulo.hpp"

using namespace hopsan;

extern "C" DLLEXPORT void register_contents(ComponentFactory* pComponentFactory, NodeFactory* pNodeFactory)
{
    //Register Components
    pComponentFactory->registerCreatorFunction("electricQGround", electricQGround::Creator);
    pComponentFactory->registerCreatorFunction("electricQGround", electricQGround::Creator);
    pComponentFactory->registerCreatorFunction("signalPow", signalPow::Creator);
    pComponentFactory->registerCreatorFunction("signalScientificNotation", signalScientificNotation::Creator);
    pComponentFactory->registerCreatorFunction("signalModulo", signalModulo::Creator);

    //Register custom nodes (if any)
    HOPSAN_UNUSED(pNodeFactory);
}

extern "C" DLLEXPORT void get_hopsan_info(HopsanExternalLibInfoT *pHopsanExternalLibInfo)
{
    pHopsanExternalLibInfo->hopsanCoreVersion = (char*)HOPSANCOREVERSION;
    pHopsanExternalLibInfo->libCompiledDebugRelease = (char*)HOPSAN_BUILD_TYPE_STR;
    pHopsanExternalLibInfo->libName = (char*)"selter";
}
