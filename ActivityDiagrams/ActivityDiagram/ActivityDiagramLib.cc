#include <iostream>
#include "ComponentEssentials.h"
#include "ActivityDiagramInitiateState.hpp"
#include "ActivityDiagramEdge.hpp"
#include "ActivityDiagramAction.hpp"
#include "ActivityDiagramActionN.hpp"
#include "ActivityDiagramDecision.hpp"
#include "ActivityDiagramForkN.hpp"
#include "ActivityDiagramJoinN.hpp"
#include "ActivityDiagramMergeN.hpp"
#include "ActivityDiagramFork.hpp"
#include "ActivityDiagramJoin0.hpp"
#include "ActivityDiagramJoin.hpp"
#include "ActivityDiagramMerge0.hpp"
#include "ActivityDiagramMerge.hpp"
#include "ActivityDiagramMergeN.hpp"
#include "ActivityDiagramFinal.hpp"
#include "ActivityDiagramFinalNode.hpp"

using namespace hopsan;

extern "C" DLLEXPORT void register_contents(ComponentFactory* pComponentFactory, NodeFactory* pNodeFactory)
{
    //Register Components
    pComponentFactory->registerCreatorFunction("ActivityDiagramInitiateState", ActivityDiagramInitiateState::Creator);
    pComponentFactory->registerCreatorFunction("ActivityDiagramEdge", ActivityDiagramEdge::Creator);
    pComponentFactory->registerCreatorFunction("ActivityDiagramAction", ActivityDiagramAction::Creator);
    pComponentFactory->registerCreatorFunction("ActivityDiagramActionN", ActivityDiagramActionN::Creator);
    pComponentFactory->registerCreatorFunction("ActivityDiagramDecision", ActivityDiagramDecision::Creator);
    pComponentFactory->registerCreatorFunction("ActivityDiagramForkN", ActivityDiagramForkN::Creator);
    pComponentFactory->registerCreatorFunction("ActivityDiagramJoinN", ActivityDiagramJoinN::Creator);
    pComponentFactory->registerCreatorFunction("ActivityDiagramMergeN", ActivityDiagramMergeN::Creator);
    pComponentFactory->registerCreatorFunction("ActivityDiagramFork", ActivityDiagramFork::Creator);
    pComponentFactory->registerCreatorFunction("ActivityDiagramJoin0", ActivityDiagramJoin0::Creator);
    pComponentFactory->registerCreatorFunction("ActivityDiagramJoin", ActivityDiagramJoin::Creator);
    pComponentFactory->registerCreatorFunction("ActivityDiagramMerge0", ActivityDiagramMerge0::Creator);
    pComponentFactory->registerCreatorFunction("ActivityDiagramMerge", ActivityDiagramMerge::Creator);
    pComponentFactory->registerCreatorFunction("ActivityDiagramMergeN", ActivityDiagramMergeN::Creator);
    pComponentFactory->registerCreatorFunction("ActivityDiagramFinal", ActivityDiagramFinal::Creator);
    pComponentFactory->registerCreatorFunction("ActivityDiagramFinalNode", ActivityDiagramFinalNode::Creator);

    //Register custom nodes (if any)
    HOPSAN_UNUSED(pNodeFactory);
}

extern "C" DLLEXPORT void get_hopsan_info(HopsanExternalLibInfoT *pHopsanExternalLibInfo)
{
    pHopsanExternalLibInfo->hopsanCoreVersion = (char*)HOPSANCOREVERSION;
    pHopsanExternalLibInfo->libCompiledDebugRelease = (char*)DEBUGRELEASECOMPILED;
    pHopsanExternalLibInfo->libName = (char*)"ActivityDiagramLibrary";
}
