#ifndef ACTIVITYDIAGRAMDECISION_HPP_INCLUDED
#define ACTIVITYDIAGRAMDECISION_HPP_INCLUDED

#include <iostream>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"
#include "math.h"
//!
//! @file ActivityDiagramDecision.hpp
//! @author Petter Krus <petter.krus@liu.se>
//  co-author/auditor **Not yet audited by a second person**
//! @date Tue 20 Aug 2019 21:23:44
//! @brief If selection for state machine
//! @ingroup ActivityDiagramComponents
//!
//==This code has been autogenerated using Compgen==
//from 
/*{, H:, PettersDropbox, Dropbox, HopsanComponents, ActivityDiagram, \
ActivityDiagram}/ActivityDiagramDecision.nb*/

using namespace hopsan;

class ActivityDiagramDecision : public ComponentQ
{
private:
     double diffevent;
     Port *mpPpn1;
     Port *mpPpn2;
     Port *mpPpn3;
     int mNstep;
     //Port Ppn1 variable
     double spn1;
     double qpn1;
     //Port Ppn2 variable
     double spn2;
     double qpn2;
     //Port Ppn3 variable
     double spn3;
     double qpn3;
//==This code has been autogenerated using Compgen==
     //inputVariables
     double event2;
     double event3;
     //outputVariables
     //InitialExpressions variables
     double oldEvent2;
     double oldEvent3;
     //Expressions variables
     double dEvent2;
     double dEvent3;
     //Port Ppn1 pointer
     double *mpP_spn1;
     double *mpP_qpn1;
     //Port Ppn2 pointer
     double *mpP_spn2;
     double *mpP_qpn2;
     //Port Ppn3 pointer
     double *mpP_spn3;
     double *mpP_qpn3;
     //Delay declarations
//==This code has been autogenerated using Compgen==
     //inputVariables pointers
     double *mpevent2;
     double *mpevent3;
     //inputParameters pointers
     double *mpdiffevent;
     //outputVariables pointers
     EquationSystemSolver *mpSolver;

public:
     static Component *Creator()
     {
        return new ActivityDiagramDecision();
     }

     void configure()
     {
//==This code has been autogenerated using Compgen==

        mNstep=9;

        //Add ports to the component
        mpPpn1=addPowerPort("Ppn1","NodePetriNet");
        mpPpn2=addPowerPort("Ppn2","NodePetriNet");
        mpPpn3=addPowerPort("Ppn3","NodePetriNet");
        //Add inputVariables to the component
            addInputVariable("event2","trigger on positive \
flank","",0.,&mpevent2);
            addInputVariable("event3","trigger on positive \
flank","",0.,&mpevent3);

        //Add inputParammeters to the component
            addInputVariable("diffevent", "Trigg on level (0) or flank (1)", \
"", 0.,&mpdiffevent);
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
        //Port Ppn3
        mpP_spn3=getSafeNodeDataPtr(mpPpn3, NodePetriNet::State);
        mpP_qpn3=getSafeNodeDataPtr(mpPpn3, NodePetriNet::Flow);

        //Read variables from nodes
        //Port Ppn1
        spn1 = (*mpP_spn1);
        qpn1 = (*mpP_qpn1);
        //Port Ppn2
        spn2 = (*mpP_spn2);
        qpn2 = (*mpP_qpn2);
        //Port Ppn3
        spn3 = (*mpP_spn3);
        qpn3 = (*mpP_qpn3);

        //Read inputVariables from nodes
        event2 = (*mpevent2);
        event3 = (*mpevent3);

        //Read inputParameters from nodes
        diffevent = (*mpdiffevent);

        //Read outputVariables from nodes

//==This code has been autogenerated using Compgen==
        //InitialExpressions
        oldEvent2 = event2;
        oldEvent3 = event3;


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
        //Port Ppn3
        spn3 = (*mpP_spn3);

        //Read inputVariables from nodes
        event2 = (*mpevent2);
        event3 = (*mpevent3);

        //Read inputParameters from nodes
        diffevent = (*mpdiffevent);

        //LocalExpressions

        //Expressions
        dEvent2 = onPositive(-0.5 + event2 - diffevent*oldEvent2);
        dEvent3 = onPositive(-0.5 + event3 - diffevent*oldEvent3);

		//Preventing creation of extra token
  		double qpn20 = dEvent2*onPositive(spn1 - spn2);
        double qpn30 = dEvent3*onPositive(spn1 - spn3);
		bool successP1;
		bool successP2;
		bool successP3;
   	
		qpn2 = 0;
        qpn3 = 0;
        qpn1 = 0;

        if(qpn20 > 0 || qpn30 > 0) {
            successP1 = true;
            //Try to lock P1
            for(auto pPort : mpPpn1->getConnectedPorts()) {
                if(pPort->getComponent()->getTypeName() == "ActivityDiagramActionN") {
                    auto component = dynamic_cast<ActivityDiagramActionN*>(pPort->getComponent());
                    successP1 = component->tryAndLockToken();
                }
            }
		}
            //Try to lock P2
        if(qpn20 > 0) {
			successP2 = true;
            for(auto pPort : mpPpn2->getConnectedPorts()) {
                if(pPort->getComponent()->getTypeName() == "ActivityDiagramActionN") {
                    auto component = dynamic_cast<ActivityDiagramActionN*>(pPort->getComponent());
                    successP2 = component->tryAndLockToken();
                }
            }   
		}
            //Try to lock P3
        if(qpn30 > 0) {
            successP3 = true;
			for(auto pPort : mpPpn3->getConnectedPorts()) {
                if(pPort->getComponent()->getTypeName() == "ActivityDiagramActionN") {
                    auto component = dynamic_cast<ActivityDiagramActionN*>(pPort->getComponent());
                    successP3 = component->tryAndLockToken();
                }
            }  
		}
        if(qpn20 > 0 || qpn30 > 0) {    
            //Locked both upstream and downstream (or not ActionN-components), compute flow
            if(successP1 && successP2) {
                addDebugMessage("Locked tokens!");
				qpn2 = dEvent2*onPositive(spn1 - spn2);
			}
            if(successP1 && successP3) {			
				qpn3 = dEvent3*(1 - qpn2)*onPositive(spn1 - spn3);
			}
       }
	   	qpn1 = -onPositive(-0.5 + qpn2 + qpn3);
		oldEvent2 = event2;
		oldEvent3 = event3;

        //Calculate the delayed parts


        //Write new values to nodes
        //Port Ppn1
        (*mpP_qpn1)=qpn1;
        //Port Ppn2
        (*mpP_qpn2)=qpn2;
        //Port Ppn3
        (*mpP_qpn3)=qpn3;
        //outputVariables

        //Update the delayed variabels

     }
    void deconfigure()
    {
        delete mpSolver;
    }
};
#endif // ACTIVITYDIAGRAMDECISION_HPP_INCLUDED
