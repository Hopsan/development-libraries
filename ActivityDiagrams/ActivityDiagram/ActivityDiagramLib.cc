#include <iostream>
#include "ComponentEssentials.h"
#include "ActivityDiagram/ActivityDiagramInitiateState.hpp"
#include "ActivityDiagram/ActivityDiagramEdge.hpp"
#include "ActivityDiagram/ActivityDiagramAction.hpp"
#include "ActivityDiagram/ActivityDiagramActionN.hpp"
#include "ActivityDiagram/ActivityDiagramDecision.hpp"
#include "ActivityDiagram/ActivityDiagramForkN.hpp"
#include "ActivityDiagram/ActivityDiagramJoinN.hpp"
#include "ActivityDiagram/ActivityDiagramMergeN.hpp"
#include "ActivityDiagram/ActivityDiagramFork.hpp"
#include "ActivityDiagram/ActivityDiagramJoin0.hpp"
#include "ActivityDiagram/ActivityDiagramJoin.hpp"
#include "ActivityDiagram/ActivityDiagramMerge0.hpp"
#include "ActivityDiagram/ActivityDiagramMerge.hpp"
#include "ActivityDiagram/ActivityDiagramMergeN.hpp"
#include "ActivityDiagram/ActivityDiagramFinal.hpp"
#include "ActivityDiagram/ActivityDiagramFinalNode.hpp"

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
