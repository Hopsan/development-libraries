#ifndef ACTIVITYDIAGRAMEDGE_HPP_INCLUDED
#define ACTIVITYDIAGRAMEDGE_HPP_INCLUDED

#include <iostream>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"
#include "math.h"
#include "ActivityDiagramActionN.hpp"

//!
//! @file ActivityDiagramEdge.hpp
//! @author Petter Krus <petter.krus@liu.se>
//  co-author/auditor **Not yet audited by a second person**
//! @date Tue 20 Aug 2019 21:24:55
//! @brief Edge for an activity diagram
//! @ingroup ActivityDiagramComponents
//!
//==This code has been autogenerated using Compgen==
//from 
/*{, H:, PettersDropbox, Dropbox, HopsanComponents, ActivityDiagram, \
ActivityDiagram}/ActivityDiagramEdge.nb*/

using namespace hopsan;

class ActivityDiagramEdge : public ComponentQ
{
private:
     double diffEvent;
     Port *mpPpn1;
     Port *mpPpn2;
     int mNstep;
     //Port Ppn1 variable
     double spn1;
     double qpn1;
     //Port Ppn2 variable
     double spn2;
     double qpn2;
//==This code has been autogenerated using Compgen==
     //inputVariables
     double event;
     //outputVariables
     //InitialExpressions variables
     double oldEvent;
     //Expressions variables
     double dEvent;
     //Port Ppn1 pointer
     double *mpP_spn1;
     double *mpP_qpn1;
     //Port Ppn2 pointer
     double *mpP_spn2;
     double *mpP_qpn2;
     //Delay declarations
//==This code has been autogenerated using Compgen==
     //inputVariables pointers
     double *mpevent;
     //inputParameters pointers
     double *mpdiffEvent;
     //outputVariables pointers
     EquationSystemSolver *mpSolver;

public:
     static Component *Creator()
     {
        return new ActivityDiagramEdge();
     }

     void configure()
     {
//==This code has been autogenerated using Compgen==

        mNstep=9;

        //Add ports to the component
        mpPpn1=addPowerPort("Ppn1","NodePetriNet");
        mpPpn2=addPowerPort("Ppn2","NodePetriNet");
        //Add inputVariables to the component
            addInputVariable("event","event ","",1.,&mpevent);

        //Add inputParammeters to the component
            addInputVariable("diffEvent", "Trigg on level (0) or flank (1)", \
"", 0.,&mpdiffEvent);
        //Add outputVariables to the component

//==This code has been autogenerated using Compgen==
        //Add constantParameters
     }

    void initialize()
     {
        //Read port variable pointers from nodes
        //Port Ppn1
        mpP_spn1=getSafeNodeDataPtr(mpPpn1, NodePetriNet::State);
        mpP_qpn1=getSafeNodeDataPtr(mpPpn1, NodePetriNet::Flow);
        //Port Ppn2
        mpP_spn2=getSafeNodeDataPtr(mpPpn2, NodePetriNet::State);
        mpP_qpn2=getSafeNodeDataPtr(mpPpn2, NodePetriNet::Flow);

        //Read variables from nodes
        //Port Ppn1
        spn1 = (*mpP_spn1);
        qpn1 = (*mpP_qpn1);
        //Port Ppn2
        spn2 = (*mpP_spn2);
        qpn2 = (*mpP_qpn2);

        //Read inputVariables from nodes
        event = (*mpevent);

        //Read inputParameters from nodes
        diffEvent = (*mpdiffEvent);

        //Read outputVariables from nodes

//==This code has been autogenerated using Compgen==
        //InitialExpressions
        oldEvent = event;


        //Initialize delays


        simulateOneTimestep();

     }
    void simulateOneTimestep()
     {
        //Read variables from nodes
        //Port Ppn1
        spn1 = (*mpP_spn1);
        //Port Ppn2
        spn2 = (*mpP_spn2);

        //Read inputVariables from nodes
        event = (*mpevent);

        //Read inputParameters from nodes
        diffEvent = (*mpdiffEvent);

        //LocalExpressions

        //Expressions
        
        qpn1 = 0;
        qpn2 = 0;
        dEvent = onPositive(-0.5 + event - diffEvent*oldEvent);
        double drop = onPositive(-0.5 + spn1 - spn2);
        if(dEvent > 0 && drop > 0) {
            bool successUpstream = true;
            
            //Try to lock upstream component
            for(auto pPort : mpPpn1->getConnectedPorts()) {
                if(pPort->getComponent()->getTypeName() == "ActivityDiagramActionN") {
                    auto component = dynamic_cast<ActivityDiagramActionN*>(pPort->getComponent());
                    successUpstream = component->tryAndLockToken();
                }
            }
            
            //Try to lock downstream component
            bool successDownstream = true;
            for(auto pPort : mpPpn2->getConnectedPorts()) {
                if(pPort->getComponent()->getTypeName() == "ActivityDiagramActionN") {
                    auto component = dynamic_cast<ActivityDiagramActionN*>(pPort->getComponent());
                    successDownstream = component->tryAndLockToken();
                }
            }    
            
            //Locked both upstream and downstream (or not ActionN-components), compute flow
            if(successUpstream && successDownstream) {
                addDebugMessage("Locked tokens!");
                qpn2 = dEvent*onPositive(-0.5 + spn1 - spn2);
                qpn1 = -qpn2;
                oldEvent = event;
            }
        }
        /*dEvent = onPositive(-0.5 + event - diffEvent*oldEvent);
        qpn2 = dEvent*onPositive(-0.5 + spn1 - spn2);
        qpn1 = -qpn2;
        oldEvent = event;
        */    
        //Calculate the delayed parts


        //Write new values to nodes
        //Port Ppn1
        (*mpP_qpn1)=qpn1;
        //Port Ppn2
        (*mpP_qpn2)=qpn2;
        //outputVariables

        //Update the delayed variabels

     }
    void deconfigure()
    {
        delete mpSolver;
    }
};
#endif // ACTIVITYDIAGRAMEDGE_HPP_INCLUDED
