#ifndef ACTIVITYDIAGRAMCONNECTOR_HPP_INCLUDED
#define ACTIVITYDIAGRAMCONNECTOR_HPP_INCLUDED

#include <iostream>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"
#include "math.h"

//!
//! @file ActivityDiagramConnector.hpp
//! @author Petter Krus <petter.krus@liu.se>
//  co-author/auditor **Not yet audited by a second person**
//! @date Thu 15 Aug 2019 15:00:38
//! @brief Connector between Q-components
//! @ingroup ActivityDiagramComponents
//!
//==This code has been autogenerated using Compgen==
//from 
/*{, H:, PettersDropbox, Dropbox, HopsanComponents, ActivityDiagram, \
ActivityDiagram}/ActivityDiagramConnector.nb*/

using namespace hopsan;

class ActivityDiagramConnector : public ComponentC
{
private:
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
     //outputVariables
     //InitialExpressions variables
     double stated;
     //Expressions variables
     double state;
     //Port Ppn1 pointer
     double *mpP_spn1;
     double *mpP_qpn1;
     //Port Ppn2 pointer
     double *mpP_spn2;
     double *mpP_qpn2;
     //Delay declarations
//==This code has been autogenerated using Compgen==
     //inputVariables pointers
     //inputParameters pointers
     //outputVariables pointers
     EquationSystemSolver *mpSolver;

public:
     static Component *Creator()
     {
        return new ActivityDiagramConnector();
     }

     void configure()
     {
//==This code has been autogenerated using Compgen==

        mNstep=9;

        //Add ports to the component
        mpPpn1=addPowerPort("Ppn1","NodePetriNet");
        mpPpn2=addPowerPort("Ppn2","NodePetriNet");
        //Add inputVariables to the component

        //Add inputParammeters to the component
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

        //Read inputParameters from nodes

        //Read outputVariables from nodes

//==This code has been autogenerated using Compgen==
        //InitialExpressions
        spn1 = state;
        spn2 = state;
        stated = state;


        //Initialize delays


        simulateOneTimestep();

     }
    void simulateOneTimestep()
     {
        //Read variables from nodes
        //Port Ppn1
        qpn1 = (*mpP_qpn1);
        //Port Ppn2
        qpn2 = (*mpP_qpn2);

        //Read inputVariables from nodes

        //Read inputParameters from nodes

        //LocalExpressions

        //Expressions
        state = onPositive(-0.5 + qpn1 + qpn2 + stated);
        spn1 = state;
        spn2 = state;
        stated = state;

        //Calculate the delayed parts


        //Write new values to nodes
        //Port Ppn1
        (*mpP_spn1)=spn1;
        //Port Ppn2
        (*mpP_spn2)=spn2;
        //outputVariables

        //Update the delayed variabels

     }
    void deconfigure()
    {
        delete mpSolver;
    }
};
#endif // ACTIVITYDIAGRAMCONNECTOR_HPP_INCLUDED
