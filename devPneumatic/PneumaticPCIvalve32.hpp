#ifndef PNEUMATICPCIVALVE32_HPP_INCLUDED
#define PNEUMATICPCIVALVE32_HPP_INCLUDED

#include <iostream>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"
#include "math.h"

//!
//! @file PneumaticPCIvalve32.hpp
//! @author Petter Krus <petter.krus@liu.se>
//  co-author/auditor **Not yet audited by a second person**
//! @date Thu 13 Aug 2020 18:20:24
//! @brief Pneumatic pressure controlled inverted 32-valve
//! @ingroup PneumaticComponents
//!
//==This code has been autogenerated using Compgen==
//from 
/*{, H:, PettersDropbox, Dropbox, HopsanComponents, \
PneumaticDevelop}/PneumaticPCIvalve32.nb*/

using namespace hopsan;

class PneumaticPCIvalve32 : public ComponentQ
{
private:
     double Bf;
     double Cf;
     double x0;
     double pso;
     double psmax;
     double tau;
     double p0;
     double T0;
     double R;
     double cv;
     double eps;
     Port *mpP1;
     Port *mpP2;
     Port *mpP3;
     Port *mpPS;
     double delayParts1[9];
     double delayParts2[9];
     double delayParts3[9];
     double delayParts4[9];
     double delayParts5[9];
     double delayParts6[9];
     double delayParts7[9];
     double delayParts8[9];
     double delayParts9[9];
     double delayParts10[9];
     double delayParts11[9];
     double delayParts12[9];
     Matrix jacobianMatrix;
     Vec systemEquations;
     Matrix delayedPart;
     int i;
     int iter;
     int mNoiter;
     double jsyseqnweight[4];
     int order[12];
     int mNstep;
     //Port P1 variable
     double p1;
     double qm1;
     double T1;
     double dE1;
     double c1;
     double Zc1;
     //Port P2 variable
     double p2;
     double qm2;
     double T2;
     double dE2;
     double c2;
     double Zc2;
     //Port P3 variable
     double p3;
     double qm3;
     double T3;
     double dE3;
     double c3;
     double Zc3;
     //Port PS variable
     double pS;
     double qmS;
     double TS;
     double dES;
     double cS;
     double ZcS;
//==This code has been autogenerated using Compgen==
     //inputVariables
     //outputVariables
     double xvref;
     double xv;
     double qm12Pos;
     double qm12Neg;
     double qm32Pos;
     double qm32Neg;
     double Ng32e;
     double Ng12e;
     //LocalExpressions variables
     double cp;
     //Expressions variables
     //Port P1 pointer
     double *mpP_p1;
     double *mpP_qm1;
     double *mpP_T1;
     double *mpP_dE1;
     double *mpP_c1;
     double *mpP_Zc1;
     //Port P2 pointer
     double *mpP_p2;
     double *mpP_qm2;
     double *mpP_T2;
     double *mpP_dE2;
     double *mpP_c2;
     double *mpP_Zc2;
     //Port P3 pointer
     double *mpP_p3;
     double *mpP_qm3;
     double *mpP_T3;
     double *mpP_dE3;
     double *mpP_c3;
     double *mpP_Zc3;
     //Port PS pointer
     double *mpP_pS;
     double *mpP_qmS;
     double *mpP_TS;
     double *mpP_dES;
     double *mpP_cS;
     double *mpP_ZcS;
     //Delay declarations
//==This code has been autogenerated using Compgen==
     //inputVariables pointers
     //inputParameters pointers
     double *mpBf;
     double *mpCf;
     double *mpx0;
     double *mppso;
     double *mppsmax;
     double *mptau;
     double *mpp0;
     double *mpT0;
     double *mpR;
     double *mpcv;
     double *mpeps;
     //outputVariables pointers
     double *mpxvref;
     double *mpxv;
     double *mpqm12Pos;
     double *mpqm12Neg;
     double *mpqm32Pos;
     double *mpqm32Neg;
     double *mpNg32e;
     double *mpNg12e;
     Delay mDelayedPart10;
     Delay mDelayedPart11;
     Delay mDelayedPart20;
     Delay mDelayedPart30;
     Delay mDelayedPart40;
     Delay mDelayedPart50;
     Delay mDelayedPart60;
     Delay mDelayedPart70;
     Delay mDelayedPart80;
     EquationSystemSolver *mpSolver;

public:
     static Component *Creator()
     {
        return new PneumaticPCIvalve32();
     }

     void configure()
     {
//==This code has been autogenerated using Compgen==

        mNstep=9;
        jacobianMatrix.create(12,12);
        systemEquations.create(12);
        delayedPart.create(13,6);
        mNoiter=2;
        jsyseqnweight[0]=1;
        jsyseqnweight[1]=0.67;
        jsyseqnweight[2]=0.5;
        jsyseqnweight[3]=0.5;


        //Add ports to the component
        mpP1=addPowerPort("P1","NodePneumatic");
        mpP2=addPowerPort("P2","NodePneumatic");
        mpP3=addPowerPort("P3","NodePneumatic");
        mpPS=addPowerPort("PS","NodePneumatic");
        //Add inputVariables to the component

        //Add inputParammeters to the component
            addInputVariable("Bf", "B, ISO critical pressure ratio", "", \
0.528,&mpBf);
            addInputVariable("Cf", "C, ISO flow coefficient", "", \
1.e-13,&mpCf);
            addInputVariable("x0", "Relative overlap", "", 0.1,&mpx0);
            addInputVariable("pso", "Opening pressure", "Pa", \
800000.,&mppso);
            addInputVariable("psmax", "Fully open pressure", "Pa", \
900000.,&mppsmax);
            addInputVariable("tau", "valve time constant", "s", 0.01,&mptau);
            addInputVariable("p0", "Nominal pressure", "Pa", 100000.,&mpp0);
            addInputVariable("T0", "Nominal temperature", "K", 297.,&mpT0);
            addInputVariable("R", "Gas constant", "J/Kg K", 287.,&mpR);
            addInputVariable("cv", "heatcoeff", "J/Kg K", 718,&mpcv);
            addInputVariable("eps", "Linearisation coeff", "", 0.02,&mpeps);
        //Add outputVariables to the component
            addOutputVariable("xvref","Ref normalized spool \
position","",0.,&mpxvref);
            addOutputVariable("xv","Normalized spool position","",0.,&mpxv);
            addOutputVariable("qm12Pos","Internal \
variable","kg/s",0.,&mpqm12Pos);
            addOutputVariable("qm12Neg","Internal \
variable","kg/s",0.,&mpqm12Neg);
            addOutputVariable("qm32Pos","Internal \
variable","kg/s",0.,&mpqm32Pos);
            addOutputVariable("qm32Neg","Internal \
variable","kg/s",0.,&mpqm32Neg);
            addOutputVariable("Ng32e","Internal variable","",0.,&mpNg32e);
            addOutputVariable("Ng12e","Internal variable","",0.,&mpNg12e);

//==This code has been autogenerated using Compgen==
        //Add constantParameters
        mpSolver = new EquationSystemSolver(this,12);
     }

    void initialize()
     {
        //Read port variable pointers from nodes
        //Port P1
        mpP_p1=getSafeNodeDataPtr(mpP1, NodePneumatic::Pressure);
        mpP_qm1=getSafeNodeDataPtr(mpP1, NodePneumatic::MassFlow);
        mpP_T1=getSafeNodeDataPtr(mpP1, NodePneumatic::Temperature);
        mpP_dE1=getSafeNodeDataPtr(mpP1, NodePneumatic::EnergyFlow);
        mpP_c1=getSafeNodeDataPtr(mpP1, NodePneumatic::WaveVariable);
        mpP_Zc1=getSafeNodeDataPtr(mpP1, NodePneumatic::CharImpedance);
        //Port P2
        mpP_p2=getSafeNodeDataPtr(mpP2, NodePneumatic::Pressure);
        mpP_qm2=getSafeNodeDataPtr(mpP2, NodePneumatic::MassFlow);
        mpP_T2=getSafeNodeDataPtr(mpP2, NodePneumatic::Temperature);
        mpP_dE2=getSafeNodeDataPtr(mpP2, NodePneumatic::EnergyFlow);
        mpP_c2=getSafeNodeDataPtr(mpP2, NodePneumatic::WaveVariable);
        mpP_Zc2=getSafeNodeDataPtr(mpP2, NodePneumatic::CharImpedance);
        //Port P3
        mpP_p3=getSafeNodeDataPtr(mpP3, NodePneumatic::Pressure);
        mpP_qm3=getSafeNodeDataPtr(mpP3, NodePneumatic::MassFlow);
        mpP_T3=getSafeNodeDataPtr(mpP3, NodePneumatic::Temperature);
        mpP_dE3=getSafeNodeDataPtr(mpP3, NodePneumatic::EnergyFlow);
        mpP_c3=getSafeNodeDataPtr(mpP3, NodePneumatic::WaveVariable);
        mpP_Zc3=getSafeNodeDataPtr(mpP3, NodePneumatic::CharImpedance);
        //Port PS
        mpP_pS=getSafeNodeDataPtr(mpPS, NodePneumatic::Pressure);
        mpP_qmS=getSafeNodeDataPtr(mpPS, NodePneumatic::MassFlow);
        mpP_TS=getSafeNodeDataPtr(mpPS, NodePneumatic::Temperature);
        mpP_dES=getSafeNodeDataPtr(mpPS, NodePneumatic::EnergyFlow);
        mpP_cS=getSafeNodeDataPtr(mpPS, NodePneumatic::WaveVariable);
        mpP_ZcS=getSafeNodeDataPtr(mpPS, NodePneumatic::CharImpedance);

        //Read variables from nodes
        //Port P1
        p1 = (*mpP_p1);
        qm1 = (*mpP_qm1);
        T1 = (*mpP_T1);
        dE1 = (*mpP_dE1);
        c1 = (*mpP_c1);
        Zc1 = (*mpP_Zc1);
        //Port P2
        p2 = (*mpP_p2);
        qm2 = (*mpP_qm2);
        T2 = (*mpP_T2);
        dE2 = (*mpP_dE2);
        c2 = (*mpP_c2);
        Zc2 = (*mpP_Zc2);
        //Port P3
        p3 = (*mpP_p3);
        qm3 = (*mpP_qm3);
        T3 = (*mpP_T3);
        dE3 = (*mpP_dE3);
        c3 = (*mpP_c3);
        Zc3 = (*mpP_Zc3);
        //Port PS
        pS = (*mpP_pS);
        qmS = (*mpP_qmS);
        TS = (*mpP_TS);
        dES = (*mpP_dES);
        cS = (*mpP_cS);
        ZcS = (*mpP_ZcS);

        //Read inputVariables from nodes

        //Read inputParameters from nodes
        Bf = (*mpBf);
        Cf = (*mpCf);
        x0 = (*mpx0);
        pso = (*mppso);
        psmax = (*mppsmax);
        tau = (*mptau);
        p0 = (*mpp0);
        T0 = (*mpT0);
        R = (*mpR);
        cv = (*mpcv);
        eps = (*mpeps);

        //Read outputVariables from nodes
        xvref = (*mpxvref);
        xv = (*mpxv);
        qm12Pos = (*mpqm12Pos);
        qm12Neg = (*mpqm12Neg);
        qm32Pos = (*mpqm32Pos);
        qm32Neg = (*mpqm32Neg);
        Ng32e = (*mpNg32e);
        Ng12e = (*mpNg12e);

//==This code has been autogenerated using Compgen==

        //LocalExpressions
        xvref = 1 - 2*limit((pS - pso)/(psmax - pso),0,1);
        cp = cv + R;

        //Initialize delays
        delayParts1[1] = (mTimestep*xv - 2*tau*xv - \
mTimestep*xvref)/(mTimestep + 2*tau);
        mDelayedPart11.initialize(mNstep,delayParts1[1]);

        delayedPart[1][1] = delayParts1[1];
        delayedPart[2][1] = delayParts2[1];
        delayedPart[3][1] = delayParts3[1];
        delayedPart[4][1] = delayParts4[1];
        delayedPart[5][1] = delayParts5[1];
        delayedPart[6][1] = delayParts6[1];
        delayedPart[7][1] = delayParts7[1];
        delayedPart[8][1] = delayParts8[1];
        delayedPart[9][1] = delayParts9[1];
        delayedPart[10][1] = delayParts10[1];
        delayedPart[11][1] = delayParts11[1];
        delayedPart[12][1] = delayParts12[1];

        simulateOneTimestep();

     }
    void simulateOneTimestep()
     {
        Vec stateVar(12);
        Vec stateVark(12);
        Vec deltaStateVar(12);

        //Read variables from nodes
        //Port P1
        T1 = (*mpP_T1);
        c1 = (*mpP_c1);
        Zc1 = (*mpP_Zc1);
        //Port P2
        T2 = (*mpP_T2);
        c2 = (*mpP_c2);
        Zc2 = (*mpP_Zc2);
        //Port P3
        T3 = (*mpP_T3);
        c3 = (*mpP_c3);
        Zc3 = (*mpP_Zc3);
        //Port PS
        TS = (*mpP_TS);
        cS = (*mpP_cS);
        ZcS = (*mpP_ZcS);

        //Read inputVariables from nodes

        //Read inputParameters from nodes
        Bf = (*mpBf);
        Cf = (*mpCf);
        x0 = (*mpx0);
        pso = (*mppso);
        psmax = (*mppsmax);
        tau = (*mptau);
        p0 = (*mpp0);
        T0 = (*mpT0);
        R = (*mpR);
        cv = (*mpcv);
        eps = (*mpeps);

        //LocalExpressions
        xvref = 1 - 2*limit((pS - pso)/(psmax - pso),0,1);
        cp = cv + R;

        //Initializing variable vector for Newton-Raphson
        stateVark[0] = xv;
        stateVark[1] = qm12Pos;
        stateVark[2] = qm12Neg;
        stateVark[3] = qm32Pos;
        stateVark[4] = qm32Neg;
        stateVark[5] = dE2;
        stateVark[6] = dE1;
        stateVark[7] = dE3;
        stateVark[8] = p2;
        stateVark[9] = p1;
        stateVark[10] = p3;
        stateVark[11] = pS;

        //Iterative solution using Newton-Rapshson
        for(iter=1;iter<=mNoiter;iter++)
        {
         //PCIvalve32
         //Differential-algebraic system of equation parts

          //Assemble differential-algebraic equations
          systemEquations[0] =xv - (mTimestep*xvref)/(mTimestep + 2*tau) + \
delayedPart[1][1];
          systemEquations[1] =qm12Pos - Cf*p0*p1*Sqrt(T0/T1)*limit((x0 - \
xv)/(-1 + x0),0,1)*(onNegative(-Bf + p1/p2)*onNegative(p1 - p2) + \
onNegative(-Bf + p2/p1)*onPositive(p1 - p2) + onPositive(p1 - \
p2)*onPositive(-Bf + p2/p1)*signedSquareL(1 - Power(-(Bf*p1) + \
p2,2)/(Power(-1 + Bf,2)*Power(p1,2)),eps) + onNegative(p1 - \
p2)*onPositive(-Bf + p1/p2)*signedSquareL(1 - Power(p1 - Bf*p2,2)/(Power(-1 + \
Bf,2)*Power(p2,2)),eps));
          systemEquations[2] =qm12Neg - Cf*p0*p2*Sqrt(T0/T2)*limit((x0 - \
xv)/(-1 + x0),0,1)*(onNegative(-Bf + p1/p2)*onNegative(p1 - p2) + \
onNegative(-Bf + p2/p1)*onPositive(p1 - p2) + onPositive(p1 - \
p2)*onPositive(-Bf + p2/p1)*signedSquareL(1 - Power(-(Bf*p1) + \
p2,2)/(Power(-1 + Bf,2)*Power(p1,2)),eps) + onNegative(p1 - \
p2)*onPositive(-Bf + p1/p2)*signedSquareL(1 - Power(p1 - Bf*p2,2)/(Power(-1 + \
Bf,2)*Power(p2,2)),eps));
          systemEquations[3] =qm32Pos - Cf*p0*p3*Sqrt(T0/T3)*limit((x0 + \
xv)/(-1 + x0),0,1)*(onNegative(-p2 + p3)*(onNegative(-Bf + p3/p2) + \
onPositive(-Bf + p3/p2)*signedSquareL(1 - Power(-(Bf*p2) + p3,2)/(Power(-1 + \
Bf,2)*Power(p2,2)),eps)) + onPositive(-p2 + p3)*(onNegative(-Bf + p2/p3) + \
onPositive(-Bf + p2/p3)*signedSquareL(1 - Power(p2 - Bf*p3,2)/(Power(-1 + \
Bf,2)*Power(p3,2)),eps)));
          systemEquations[4] =qm32Neg - Cf*p0*p2*Sqrt(T0/T2)*limit((x0 + \
xv)/(-1 + x0),0,1)*(onNegative(-p2 + p3)*(onNegative(-Bf + p3/p2) + \
onPositive(-Bf + p3/p2)*signedSquareL(1 - Power(-(Bf*p2) + p3,2)/(Power(-1 + \
Bf,2)*Power(p2,2)),eps)) + onPositive(-p2 + p3)*(onNegative(-Bf + p2/p3) + \
onPositive(-Bf + p2/p3)*signedSquareL(1 - Power(p2 - Bf*p3,2)/(Power(-1 + \
Bf,2)*Power(p3,2)),eps)));
          systemEquations[5] =dE2 + \
cp*(-(qm12Pos*T2*onNegative(-(qm12Neg*onNegative(p1 - p2)) + \
qm12Pos*onPositive(p1 - p2))*onPositive(p1 - p2)) - \
qm32Pos*T2*onNegative(-(qm32Neg*onNegative(-p2 + p3)) + \
qm32Pos*onPositive(-p2 + p3))*onPositive(-p2 + p3) - qm12Pos*T1*onPositive(p1 \
- p2)*onPositive(-(qm12Neg*onNegative(p1 - p2)) + qm12Pos*onPositive(p1 - \
p2)) + qm12Neg*onNegative(p1 - p2)*(T2*onNegative(-(qm12Neg*onNegative(p1 - \
p2)) + qm12Pos*onPositive(p1 - p2)) + T1*onPositive(-(qm12Neg*onNegative(p1 - \
p2)) + qm12Pos*onPositive(p1 - p2))) - qm32Pos*T3*onPositive(-p2 + \
p3)*onPositive(-(qm32Neg*onNegative(-p2 + p3)) + qm32Pos*onPositive(-p2 + \
p3)) + qm32Neg*onNegative(-p2 + p3)*(T2*onNegative(-(qm32Neg*onNegative(-p2 + \
p3)) + qm32Pos*onPositive(-p2 + p3)) + T3*onPositive(-(qm32Neg*onNegative(-p2 \
+ p3)) + qm32Pos*onPositive(-p2 + p3))));
          systemEquations[6] =dE1 - cp*(qm12Neg*onNegative(p1 - p2) - \
qm12Pos*onPositive(p1 - p2))*(T2*onNegative(-(qm12Neg*onNegative(p1 - p2)) + \
qm12Pos*onPositive(p1 - p2)) + T1*onPositive(-(qm12Neg*onNegative(p1 - p2)) + \
qm12Pos*onPositive(p1 - p2)));
          systemEquations[7] =dE3 - cp*(qm32Neg*onNegative(-p2 + p3) - \
qm32Pos*onPositive(-p2 + p3))*(T2*onNegative(-(qm32Neg*onNegative(-p2 + p3)) \
+ qm32Pos*onPositive(-p2 + p3)) + T3*onPositive(-(qm32Neg*onNegative(-p2 + \
p3)) + qm32Pos*onPositive(-p2 + p3)));
          systemEquations[8] =-c2 + p2 - dE2*Zc2;
          systemEquations[9] =-c1 + p1 - dE1*Zc1;
          systemEquations[10] =-c3 + p3 - dE3*Zc3;
          systemEquations[11] =-cS + pS - dES*ZcS;

          //Jacobian matrix
          jacobianMatrix[0][0] = 1;
          jacobianMatrix[0][1] = 0;
          jacobianMatrix[0][2] = 0;
          jacobianMatrix[0][3] = 0;
          jacobianMatrix[0][4] = 0;
          jacobianMatrix[0][5] = 0;
          jacobianMatrix[0][6] = 0;
          jacobianMatrix[0][7] = 0;
          jacobianMatrix[0][8] = 0;
          jacobianMatrix[0][9] = 0;
          jacobianMatrix[0][10] = 0;
          jacobianMatrix[0][11] = 0;
          jacobianMatrix[1][0] = (Cf*p0*p1*Sqrt(T0/T1)*dxLimit((x0 - xv)/(-1 \
+ x0),0,1)*(onNegative(-Bf + p1/p2)*onNegative(p1 - p2) + onNegative(-Bf + \
p2/p1)*onPositive(p1 - p2) + onPositive(p1 - p2)*onPositive(-Bf + \
p2/p1)*signedSquareL(1 - Power(-(Bf*p1) + p2,2)/(Power(-1 + \
Bf,2)*Power(p1,2)),eps) + onNegative(p1 - p2)*onPositive(-Bf + \
p1/p2)*signedSquareL(1 - Power(p1 - Bf*p2,2)/(Power(-1 + \
Bf,2)*Power(p2,2)),eps)))/(-1 + x0);
          jacobianMatrix[1][1] = 1;
          jacobianMatrix[1][2] = 0;
          jacobianMatrix[1][3] = 0;
          jacobianMatrix[1][4] = 0;
          jacobianMatrix[1][5] = 0;
          jacobianMatrix[1][6] = 0;
          jacobianMatrix[1][7] = 0;
          jacobianMatrix[1][8] = -(Cf*p0*p1*Sqrt(T0/T1)*limit((x0 - xv)/(-1 + \
x0),0,1)*(((2*Bf*(p1 - Bf*p2))/(Power(-1 + Bf,2)*Power(p2,2)) + (2*Power(p1 - \
Bf*p2,2))/(Power(-1 + Bf,2)*Power(p2,3)))*dxSignedSquareL(1 - Power(p1 - \
Bf*p2,2)/(Power(-1 + Bf,2)*Power(p2,2)),eps)*onNegative(p1 - \
p2)*onPositive(-Bf + p1/p2) - (2*(-(Bf*p1) + p2)*dxSignedSquareL(1 - \
Power(-(Bf*p1) + p2,2)/(Power(-1 + Bf,2)*Power(p1,2)),eps)*onPositive(p1 - \
p2)*onPositive(-Bf + p2/p1))/(Power(-1 + Bf,2)*Power(p1,2))));
          jacobianMatrix[1][9] = -(Cf*p0*p1*Sqrt(T0/T1)*limit((x0 - xv)/(-1 + \
x0),0,1)*((-2*(p1 - Bf*p2)*dxSignedSquareL(1 - Power(p1 - Bf*p2,2)/(Power(-1 \
+ Bf,2)*Power(p2,2)),eps)*onNegative(p1 - p2)*onPositive(-Bf + \
p1/p2))/(Power(-1 + Bf,2)*Power(p2,2)) + ((2*Bf*(-(Bf*p1) + p2))/(Power(-1 + \
Bf,2)*Power(p1,2)) + (2*Power(-(Bf*p1) + p2,2))/(Power(-1 + \
Bf,2)*Power(p1,3)))*dxSignedSquareL(1 - Power(-(Bf*p1) + p2,2)/(Power(-1 + \
Bf,2)*Power(p1,2)),eps)*onPositive(p1 - p2)*onPositive(-Bf + p2/p1))) - \
Cf*p0*Sqrt(T0/T1)*limit((x0 - xv)/(-1 + x0),0,1)*(onNegative(-Bf + \
p1/p2)*onNegative(p1 - p2) + onNegative(-Bf + p2/p1)*onPositive(p1 - p2) + \
onPositive(p1 - p2)*onPositive(-Bf + p2/p1)*signedSquareL(1 - Power(-(Bf*p1) \
+ p2,2)/(Power(-1 + Bf,2)*Power(p1,2)),eps) + onNegative(p1 - \
p2)*onPositive(-Bf + p1/p2)*signedSquareL(1 - Power(p1 - Bf*p2,2)/(Power(-1 + \
Bf,2)*Power(p2,2)),eps));
          jacobianMatrix[1][10] = 0;
          jacobianMatrix[1][11] = 0;
          jacobianMatrix[2][0] = (Cf*p0*p2*Sqrt(T0/T2)*dxLimit((x0 - xv)/(-1 \
+ x0),0,1)*(onNegative(-Bf + p1/p2)*onNegative(p1 - p2) + onNegative(-Bf + \
p2/p1)*onPositive(p1 - p2) + onPositive(p1 - p2)*onPositive(-Bf + \
p2/p1)*signedSquareL(1 - Power(-(Bf*p1) + p2,2)/(Power(-1 + \
Bf,2)*Power(p1,2)),eps) + onNegative(p1 - p2)*onPositive(-Bf + \
p1/p2)*signedSquareL(1 - Power(p1 - Bf*p2,2)/(Power(-1 + \
Bf,2)*Power(p2,2)),eps)))/(-1 + x0);
          jacobianMatrix[2][1] = 0;
          jacobianMatrix[2][2] = 1;
          jacobianMatrix[2][3] = 0;
          jacobianMatrix[2][4] = 0;
          jacobianMatrix[2][5] = 0;
          jacobianMatrix[2][6] = 0;
          jacobianMatrix[2][7] = 0;
          jacobianMatrix[2][8] = -(Cf*p0*p2*Sqrt(T0/T2)*limit((x0 - xv)/(-1 + \
x0),0,1)*(((2*Bf*(p1 - Bf*p2))/(Power(-1 + Bf,2)*Power(p2,2)) + (2*Power(p1 - \
Bf*p2,2))/(Power(-1 + Bf,2)*Power(p2,3)))*dxSignedSquareL(1 - Power(p1 - \
Bf*p2,2)/(Power(-1 + Bf,2)*Power(p2,2)),eps)*onNegative(p1 - \
p2)*onPositive(-Bf + p1/p2) - (2*(-(Bf*p1) + p2)*dxSignedSquareL(1 - \
Power(-(Bf*p1) + p2,2)/(Power(-1 + Bf,2)*Power(p1,2)),eps)*onPositive(p1 - \
p2)*onPositive(-Bf + p2/p1))/(Power(-1 + Bf,2)*Power(p1,2)))) - \
Cf*p0*Sqrt(T0/T2)*limit((x0 - xv)/(-1 + x0),0,1)*(onNegative(-Bf + \
p1/p2)*onNegative(p1 - p2) + onNegative(-Bf + p2/p1)*onPositive(p1 - p2) + \
onPositive(p1 - p2)*onPositive(-Bf + p2/p1)*signedSquareL(1 - Power(-(Bf*p1) \
+ p2,2)/(Power(-1 + Bf,2)*Power(p1,2)),eps) + onNegative(p1 - \
p2)*onPositive(-Bf + p1/p2)*signedSquareL(1 - Power(p1 - Bf*p2,2)/(Power(-1 + \
Bf,2)*Power(p2,2)),eps));
          jacobianMatrix[2][9] = -(Cf*p0*p2*Sqrt(T0/T2)*limit((x0 - xv)/(-1 + \
x0),0,1)*((-2*(p1 - Bf*p2)*dxSignedSquareL(1 - Power(p1 - Bf*p2,2)/(Power(-1 \
+ Bf,2)*Power(p2,2)),eps)*onNegative(p1 - p2)*onPositive(-Bf + \
p1/p2))/(Power(-1 + Bf,2)*Power(p2,2)) + ((2*Bf*(-(Bf*p1) + p2))/(Power(-1 + \
Bf,2)*Power(p1,2)) + (2*Power(-(Bf*p1) + p2,2))/(Power(-1 + \
Bf,2)*Power(p1,3)))*dxSignedSquareL(1 - Power(-(Bf*p1) + p2,2)/(Power(-1 + \
Bf,2)*Power(p1,2)),eps)*onPositive(p1 - p2)*onPositive(-Bf + p2/p1)));
          jacobianMatrix[2][10] = 0;
          jacobianMatrix[2][11] = 0;
          jacobianMatrix[3][0] = -((Cf*p0*p3*Sqrt(T0/T3)*dxLimit((x0 + \
xv)/(-1 + x0),0,1)*(onNegative(-p2 + p3)*(onNegative(-Bf + p3/p2) + \
onPositive(-Bf + p3/p2)*signedSquareL(1 - Power(-(Bf*p2) + p3,2)/(Power(-1 + \
Bf,2)*Power(p2,2)),eps)) + onPositive(-p2 + p3)*(onNegative(-Bf + p2/p3) + \
onPositive(-Bf + p2/p3)*signedSquareL(1 - Power(p2 - Bf*p3,2)/(Power(-1 + \
Bf,2)*Power(p3,2)),eps))))/(-1 + x0));
          jacobianMatrix[3][1] = 0;
          jacobianMatrix[3][2] = 0;
          jacobianMatrix[3][3] = 1;
          jacobianMatrix[3][4] = 0;
          jacobianMatrix[3][5] = 0;
          jacobianMatrix[3][6] = 0;
          jacobianMatrix[3][7] = 0;
          jacobianMatrix[3][8] = -(Cf*p0*p3*Sqrt(T0/T3)*limit((x0 + xv)/(-1 + \
x0),0,1)*((-2*(p2 - Bf*p3)*dxSignedSquareL(1 - Power(p2 - Bf*p3,2)/(Power(-1 \
+ Bf,2)*Power(p3,2)),eps)*onPositive(-Bf + p2/p3)*onPositive(-p2 + \
p3))/(Power(-1 + Bf,2)*Power(p3,2)) + ((2*Bf*(-(Bf*p2) + p3))/(Power(-1 + \
Bf,2)*Power(p2,2)) + (2*Power(-(Bf*p2) + p3,2))/(Power(-1 + \
Bf,2)*Power(p2,3)))*dxSignedSquareL(1 - Power(-(Bf*p2) + p3,2)/(Power(-1 + \
Bf,2)*Power(p2,2)),eps)*onNegative(-p2 + p3)*onPositive(-Bf + p3/p2)));
          jacobianMatrix[3][9] = 0;
          jacobianMatrix[3][10] = -(Cf*p0*p3*Sqrt(T0/T3)*limit((x0 + xv)/(-1 \
+ x0),0,1)*(((2*Bf*(p2 - Bf*p3))/(Power(-1 + Bf,2)*Power(p3,2)) + (2*Power(p2 \
- Bf*p3,2))/(Power(-1 + Bf,2)*Power(p3,3)))*dxSignedSquareL(1 - Power(p2 - \
Bf*p3,2)/(Power(-1 + Bf,2)*Power(p3,2)),eps)*onPositive(-Bf + \
p2/p3)*onPositive(-p2 + p3) - (2*(-(Bf*p2) + p3)*dxSignedSquareL(1 - \
Power(-(Bf*p2) + p3,2)/(Power(-1 + Bf,2)*Power(p2,2)),eps)*onNegative(-p2 + \
p3)*onPositive(-Bf + p3/p2))/(Power(-1 + Bf,2)*Power(p2,2)))) - \
Cf*p0*Sqrt(T0/T3)*limit((x0 + xv)/(-1 + x0),0,1)*(onNegative(-p2 + \
p3)*(onNegative(-Bf + p3/p2) + onPositive(-Bf + p3/p2)*signedSquareL(1 - \
Power(-(Bf*p2) + p3,2)/(Power(-1 + Bf,2)*Power(p2,2)),eps)) + onPositive(-p2 \
+ p3)*(onNegative(-Bf + p2/p3) + onPositive(-Bf + p2/p3)*signedSquareL(1 - \
Power(p2 - Bf*p3,2)/(Power(-1 + Bf,2)*Power(p3,2)),eps)));
          jacobianMatrix[3][11] = 0;
          jacobianMatrix[4][0] = -((Cf*p0*p2*Sqrt(T0/T2)*dxLimit((x0 + \
xv)/(-1 + x0),0,1)*(onNegative(-p2 + p3)*(onNegative(-Bf + p3/p2) + \
onPositive(-Bf + p3/p2)*signedSquareL(1 - Power(-(Bf*p2) + p3,2)/(Power(-1 + \
Bf,2)*Power(p2,2)),eps)) + onPositive(-p2 + p3)*(onNegative(-Bf + p2/p3) + \
onPositive(-Bf + p2/p3)*signedSquareL(1 - Power(p2 - Bf*p3,2)/(Power(-1 + \
Bf,2)*Power(p3,2)),eps))))/(-1 + x0));
          jacobianMatrix[4][1] = 0;
          jacobianMatrix[4][2] = 0;
          jacobianMatrix[4][3] = 0;
          jacobianMatrix[4][4] = 1;
          jacobianMatrix[4][5] = 0;
          jacobianMatrix[4][6] = 0;
          jacobianMatrix[4][7] = 0;
          jacobianMatrix[4][8] = -(Cf*p0*p2*Sqrt(T0/T2)*limit((x0 + xv)/(-1 + \
x0),0,1)*((-2*(p2 - Bf*p3)*dxSignedSquareL(1 - Power(p2 - Bf*p3,2)/(Power(-1 \
+ Bf,2)*Power(p3,2)),eps)*onPositive(-Bf + p2/p3)*onPositive(-p2 + \
p3))/(Power(-1 + Bf,2)*Power(p3,2)) + ((2*Bf*(-(Bf*p2) + p3))/(Power(-1 + \
Bf,2)*Power(p2,2)) + (2*Power(-(Bf*p2) + p3,2))/(Power(-1 + \
Bf,2)*Power(p2,3)))*dxSignedSquareL(1 - Power(-(Bf*p2) + p3,2)/(Power(-1 + \
Bf,2)*Power(p2,2)),eps)*onNegative(-p2 + p3)*onPositive(-Bf + p3/p2))) - \
Cf*p0*Sqrt(T0/T2)*limit((x0 + xv)/(-1 + x0),0,1)*(onNegative(-p2 + \
p3)*(onNegative(-Bf + p3/p2) + onPositive(-Bf + p3/p2)*signedSquareL(1 - \
Power(-(Bf*p2) + p3,2)/(Power(-1 + Bf,2)*Power(p2,2)),eps)) + onPositive(-p2 \
+ p3)*(onNegative(-Bf + p2/p3) + onPositive(-Bf + p2/p3)*signedSquareL(1 - \
Power(p2 - Bf*p3,2)/(Power(-1 + Bf,2)*Power(p3,2)),eps)));
          jacobianMatrix[4][9] = 0;
          jacobianMatrix[4][10] = -(Cf*p0*p2*Sqrt(T0/T2)*limit((x0 + xv)/(-1 \
+ x0),0,1)*(((2*Bf*(p2 - Bf*p3))/(Power(-1 + Bf,2)*Power(p3,2)) + (2*Power(p2 \
- Bf*p3,2))/(Power(-1 + Bf,2)*Power(p3,3)))*dxSignedSquareL(1 - Power(p2 - \
Bf*p3,2)/(Power(-1 + Bf,2)*Power(p3,2)),eps)*onPositive(-Bf + \
p2/p3)*onPositive(-p2 + p3) - (2*(-(Bf*p2) + p3)*dxSignedSquareL(1 - \
Power(-(Bf*p2) + p3,2)/(Power(-1 + Bf,2)*Power(p2,2)),eps)*onNegative(-p2 + \
p3)*onPositive(-Bf + p3/p2))/(Power(-1 + Bf,2)*Power(p2,2))));
          jacobianMatrix[4][11] = 0;
          jacobianMatrix[5][0] = 0;
          jacobianMatrix[5][1] = cp*(-(T2*onNegative(-(qm12Neg*onNegative(p1 \
- p2)) + qm12Pos*onPositive(p1 - p2))*onPositive(p1 - p2)) - T1*onPositive(p1 \
- p2)*onPositive(-(qm12Neg*onNegative(p1 - p2)) + qm12Pos*onPositive(p1 - \
p2)));
          jacobianMatrix[5][2] = cp*onNegative(p1 - \
p2)*(T2*onNegative(-(qm12Neg*onNegative(p1 - p2)) + qm12Pos*onPositive(p1 - \
p2)) + T1*onPositive(-(qm12Neg*onNegative(p1 - p2)) + qm12Pos*onPositive(p1 - \
p2)));
          jacobianMatrix[5][3] = cp*(-(T2*onNegative(-(qm32Neg*onNegative(-p2 \
+ p3)) + qm32Pos*onPositive(-p2 + p3))*onPositive(-p2 + p3)) - \
T3*onPositive(-p2 + p3)*onPositive(-(qm32Neg*onNegative(-p2 + p3)) + \
qm32Pos*onPositive(-p2 + p3)));
          jacobianMatrix[5][4] = cp*onNegative(-p2 + \
p3)*(T2*onNegative(-(qm32Neg*onNegative(-p2 + p3)) + qm32Pos*onPositive(-p2 + \
p3)) + T3*onPositive(-(qm32Neg*onNegative(-p2 + p3)) + qm32Pos*onPositive(-p2 \
+ p3)));
          jacobianMatrix[5][5] = 1;
          jacobianMatrix[5][6] = 0;
          jacobianMatrix[5][7] = 0;
          jacobianMatrix[5][8] = 0;
          jacobianMatrix[5][9] = 0;
          jacobianMatrix[5][10] = 0;
          jacobianMatrix[5][11] = 0;
          jacobianMatrix[6][0] = 0;
          jacobianMatrix[6][1] = cp*onPositive(p1 - \
p2)*(T2*onNegative(-(qm12Neg*onNegative(p1 - p2)) + qm12Pos*onPositive(p1 - \
p2)) + T1*onPositive(-(qm12Neg*onNegative(p1 - p2)) + qm12Pos*onPositive(p1 - \
p2)));
          jacobianMatrix[6][2] = -(cp*onNegative(p1 - \
p2)*(T2*onNegative(-(qm12Neg*onNegative(p1 - p2)) + qm12Pos*onPositive(p1 - \
p2)) + T1*onPositive(-(qm12Neg*onNegative(p1 - p2)) + qm12Pos*onPositive(p1 - \
p2))));
          jacobianMatrix[6][3] = 0;
          jacobianMatrix[6][4] = 0;
          jacobianMatrix[6][5] = 0;
          jacobianMatrix[6][6] = 1;
          jacobianMatrix[6][7] = 0;
          jacobianMatrix[6][8] = 0;
          jacobianMatrix[6][9] = 0;
          jacobianMatrix[6][10] = 0;
          jacobianMatrix[6][11] = 0;
          jacobianMatrix[7][0] = 0;
          jacobianMatrix[7][1] = 0;
          jacobianMatrix[7][2] = 0;
          jacobianMatrix[7][3] = cp*onPositive(-p2 + \
p3)*(T2*onNegative(-(qm32Neg*onNegative(-p2 + p3)) + qm32Pos*onPositive(-p2 + \
p3)) + T3*onPositive(-(qm32Neg*onNegative(-p2 + p3)) + qm32Pos*onPositive(-p2 \
+ p3)));
          jacobianMatrix[7][4] = -(cp*onNegative(-p2 + \
p3)*(T2*onNegative(-(qm32Neg*onNegative(-p2 + p3)) + qm32Pos*onPositive(-p2 + \
p3)) + T3*onPositive(-(qm32Neg*onNegative(-p2 + p3)) + qm32Pos*onPositive(-p2 \
+ p3))));
          jacobianMatrix[7][5] = 0;
          jacobianMatrix[7][6] = 0;
          jacobianMatrix[7][7] = 1;
          jacobianMatrix[7][8] = 0;
          jacobianMatrix[7][9] = 0;
          jacobianMatrix[7][10] = 0;
          jacobianMatrix[7][11] = 0;
          jacobianMatrix[8][0] = 0;
          jacobianMatrix[8][1] = 0;
          jacobianMatrix[8][2] = 0;
          jacobianMatrix[8][3] = 0;
          jacobianMatrix[8][4] = 0;
          jacobianMatrix[8][5] = -Zc2;
          jacobianMatrix[8][6] = 0;
          jacobianMatrix[8][7] = 0;
          jacobianMatrix[8][8] = 1;
          jacobianMatrix[8][9] = 0;
          jacobianMatrix[8][10] = 0;
          jacobianMatrix[8][11] = 0;
          jacobianMatrix[9][0] = 0;
          jacobianMatrix[9][1] = 0;
          jacobianMatrix[9][2] = 0;
          jacobianMatrix[9][3] = 0;
          jacobianMatrix[9][4] = 0;
          jacobianMatrix[9][5] = 0;
          jacobianMatrix[9][6] = -Zc1;
          jacobianMatrix[9][7] = 0;
          jacobianMatrix[9][8] = 0;
          jacobianMatrix[9][9] = 1;
          jacobianMatrix[9][10] = 0;
          jacobianMatrix[9][11] = 0;
          jacobianMatrix[10][0] = 0;
          jacobianMatrix[10][1] = 0;
          jacobianMatrix[10][2] = 0;
          jacobianMatrix[10][3] = 0;
          jacobianMatrix[10][4] = 0;
          jacobianMatrix[10][5] = 0;
          jacobianMatrix[10][6] = 0;
          jacobianMatrix[10][7] = -Zc3;
          jacobianMatrix[10][8] = 0;
          jacobianMatrix[10][9] = 0;
          jacobianMatrix[10][10] = 1;
          jacobianMatrix[10][11] = 0;
          jacobianMatrix[11][0] = 0;
          jacobianMatrix[11][1] = 0;
          jacobianMatrix[11][2] = 0;
          jacobianMatrix[11][3] = 0;
          jacobianMatrix[11][4] = 0;
          jacobianMatrix[11][5] = 0;
          jacobianMatrix[11][6] = 0;
          jacobianMatrix[11][7] = 0;
          jacobianMatrix[11][8] = 0;
          jacobianMatrix[11][9] = 0;
          jacobianMatrix[11][10] = 0;
          jacobianMatrix[11][11] = 1;
//==This code has been autogenerated using Compgen==

          //Solving equation using LU-faktorisation
          mpSolver->solve(jacobianMatrix, systemEquations, stateVark, iter);
          xv=stateVark[0];
          qm12Pos=stateVark[1];
          qm12Neg=stateVark[2];
          qm32Pos=stateVark[3];
          qm32Neg=stateVark[4];
          dE2=stateVark[5];
          dE1=stateVark[6];
          dE3=stateVark[7];
          p2=stateVark[8];
          p1=stateVark[9];
          p3=stateVark[10];
          pS=stateVark[11];
        //Expressions
        qm2 = -(qm12Neg*onNegative(p1 - p2)) - qm32Neg*onNegative(-p2 + p3) + \
qm12Pos*onPositive(p1 - p2) + qm32Pos*onPositive(-p2 + p3);
        qm1 = qm12Neg*onNegative(p1 - p2) - qm12Pos*onPositive(p1 - p2);
        qm3 = qm32Neg*onNegative(-p2 + p3) - qm32Pos*onPositive(-p2 + p3);
        Ng32e = onPositive(-p2 + p3)*(onNegative(-Bf + p2/p3) + \
onPositive(-Bf + p2/p3)*signedSquareL(1 - Power(-Bf + p2/p3,2)/Power(1 - \
Bf,2),eps)) + onNegative(-p2 + p3)*(onNegative(-Bf + p3/p2) + onPositive(-Bf \
+ p3/p2)*signedSquareL(1 - Power(-Bf + p3/p2,2)/Power(1 - Bf,2),eps));
        Ng12e = onNegative(p1 - p2)*(onNegative(-Bf + p1/p2) + onPositive(-Bf \
+ p1/p2)*signedSquareL(1 - Power(-Bf + p1/p2,2)/Power(1 - Bf,2),eps)) + \
onPositive(p1 - p2)*(onNegative(-Bf + p2/p1) + onPositive(-Bf + \
p2/p1)*signedSquareL(1 - Power(-Bf + p2/p1,2)/Power(1 - Bf,2),eps));
        }

        //Calculate the delayed parts
        delayParts1[1] = (mTimestep*xv - 2*tau*xv - \
mTimestep*xvref)/(mTimestep + 2*tau);

        delayedPart[1][1] = delayParts1[1];
        delayedPart[2][1] = delayParts2[1];
        delayedPart[3][1] = delayParts3[1];
        delayedPart[4][1] = delayParts4[1];
        delayedPart[5][1] = delayParts5[1];
        delayedPart[6][1] = delayParts6[1];
        delayedPart[7][1] = delayParts7[1];
        delayedPart[8][1] = delayParts8[1];
        delayedPart[9][1] = delayParts9[1];
        delayedPart[10][1] = delayParts10[1];
        delayedPart[11][1] = delayParts11[1];
        delayedPart[12][1] = delayParts12[1];

        //Write new values to nodes
        //Port P1
        (*mpP_p1)=p1;
        (*mpP_qm1)=qm1;
        (*mpP_dE1)=dE1;
        //Port P2
        (*mpP_p2)=p2;
        (*mpP_qm2)=qm2;
        (*mpP_dE2)=dE2;
        //Port P3
        (*mpP_p3)=p3;
        (*mpP_qm3)=qm3;
        (*mpP_dE3)=dE3;
        //Port PS
        (*mpP_pS)=pS;
        (*mpP_qmS)=qmS;
        (*mpP_dES)=dES;
        //outputVariables
        (*mpxvref)=xvref;
        (*mpxv)=xv;
        (*mpqm12Pos)=qm12Pos;
        (*mpqm12Neg)=qm12Neg;
        (*mpqm32Pos)=qm32Pos;
        (*mpqm32Neg)=qm32Neg;
        (*mpNg32e)=Ng32e;
        (*mpNg12e)=Ng12e;

        //Update the delayed variabels
        mDelayedPart11.update(delayParts1[1]);

     }
    void deconfigure()
    {
        delete mpSolver;
    }
};
#endif // PNEUMATICPCIVALVE32_HPP_INCLUDED
