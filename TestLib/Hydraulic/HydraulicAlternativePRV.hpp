/*-----------------------------------------------------------------------------

 Copyright 2017 Hopsan Group

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.


 The full license is available in the file LICENSE.
 For details about the 'Hopsan Group' or information about Authors and
 Contributors see the HOPSANGROUP and AUTHORS files that are located in
 the Hopsan source code root directory.

-----------------------------------------------------------------------------*/

//!
//! @file   HydraulicAlternativePRV.hpp
//! @author Robert Braun <robert.braun@liu.se>
//! @date   2010-01-22
//!
//! @brief Alternative version of pressure relief valve with first order dynamics
//! Only for temporary use in comparison between HOPSAN NG and Modelica. Not to be used in release versions of HOPSAN NG!
//!
//$Id$

#ifndef HYDRAULICALTERNATIVEPRV_HPP_INCLUDED
#define HYDRAULICALTERNATIVEPRV_HPP_INCLUDED

#include <iostream>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"

namespace hopsan {

    //!
    //! @brief
    //! @ingroup HydraulicComponents
    //!
    class HydraulicAlternativePRV : public ComponentQ
    {
    private:
        double mX0, mPref, mCq, mW, mSpoolDiameter, mFrac, mPilotArea, mK, mC, mMass, mXhyst, mXmax, mFs;
        double mPrevX0;
        TurbulentFlowFunction mTurb;
        ValveHysteresis mHyst;
        SecondOrderTransferFunction mFilter;
        //FirstOrderFilter mFilter;
        Port *mpP1, *mpP2, *mpX;

        double debug,tid1,tid2;

    public:
        static Component *Creator()
        {
            return new HydraulicAlternativePRV();
        }

        void configure()
        {
            mPref = 20000000;
            mCq = 0.67;
            mSpoolDiameter = 0.01;
            mFrac = 1.0;
            mPilotArea = 0.001;
            mK = 1e6;
            mC = 1000;
            mMass = 0.05;
            mXhyst = 0.0;
            mXmax = 0.001;

            mpP1 = addPowerPort("P1", "NodeHydraulic");
            mpP2 = addPowerPort("P2", "NodeHydraulic");
            mpX  = addWritePort("X", "NodeSignal");

            addConstant("p_ref", "Reference Opening Pressure", "[Pa]", mPref);
            addConstant("C_q", "Flow Coefficient", "[-]", mCq);
            addConstant("D_s", "Spool Diameter", "[m]", mSpoolDiameter);
            addConstant("frac", "Fraction of Spool Circumference that is Opening", "[-]", mFrac);
            addConstant("A_p", "Working Area of Pilot Pressure", "[m^2]", mPilotArea);
            addConstant("k", "Steady State Characteristics of Spring", "[N/m]", mK);
            addConstant("c", "Steady State Damping Coefficient", "[Ns/m]", mC);
            addConstant("m", "Inertia of Spool", "[kg]", mMass);
            addConstant("x_hyst", "Hysteresis of Spool Position", "[m]", mXhyst);
            addConstant("x_max", "Maximum Spool Position", "[m]", mXmax);

            tid1 = 0.0;
            tid2 = 0.01;
            debug = 0;
            addConstant("debug", "debug", "[-]", debug);
            addConstant("t1", "debug", "[-]", tid1);
            addConstant("t2", "debug", "[-]", tid2);
        }


        void initialize()
        {
            mX0 = 0.00001;
            mW = mSpoolDiameter*mFrac;
            mFs = mPilotArea * mPref;   //Spring preload

            mPrevX0 = 0.0;

            double num[3];
            double den[3];
            num[0] = 0.0;
            num[1] = 0.0;
            num[2] = 1.0;
            den[0] = mMass;
            den[1] = mC;
            den[2] = mK;
            //        num[0] = 0.0;
            //        num[1] = 1.0;
            //        den[0] = mC;
            //        den[1] = mK;

            mFilter.initialize(mTimestep, num, den, 0.0, 0.0, 0.0, mXmax);

            if(mpX->isConnected())
                mpX->writeNode(NodeSignal::VALUE, 0.0);
        }

        void simulateOneTimestep()
        {
            //Get variable values from nodes
            double c1  = mpP1->readNode(NodeHydraulic::WAVEVARIABLE);
            double Zc1 = mpP1->readNode(NodeHydraulic::CHARIMP);
            double c2  = mpP2->readNode(NodeHydraulic::WAVEVARIABLE);
            double Zc2 = mpP2->readNode(NodeHydraulic::CHARIMP);

            //PRV Equations

            mFs = mPilotArea*mPref;

            double q1 = mpP1->readNode(NodeHydraulic::FLOW); //Needed to calculate p1 for the force equilibrium
            double p1 = c1 + q1*Zc1;

            double Ftot = p1*mPilotArea - mFs;      //Sum of forces in x direction beside from spring coeff and viscous friction
            mFilter.update(Ftot);
            double x0 = mFilter.value();        //Filter function G = 1/(mMass*s^2 + mC*s + mK)
            //   double v0 = (Ftot-mK*mPrevX0.value())/mC;
            //   double x0 = mPrevX0.value()+v0*mTimestep;
            //double x0 = Ftot/mK;
            //        if(x0>mXmax)                            //No filter function G = 1/mK
            //            x0=mXmax;                           //No filter function G = 1/mK
            //        if(x0<0.0)                              //No filter function G = 1/mK
            //            x0=0.0;                             //No filter function G = 1/mK
            //double x0h = mHyst.getValue(x0, mXhyst, mPrevX0); //Hysteresis


            //Turbulent flow equation
            mTurb.setFlowCoefficient(mCq*mW*x0);

            double q2 = mTurb.getFlow(c1,c2,Zc1,Zc2);
            q1 = -q2;

            p1 = c1 + Zc1*q1;
            double p2 = c2 + Zc2*q2;

            /*KÃ¶r utan kaviataion nu i bÃ¶rjan nÃ¤r vi jÃ¤mfÃ¶r med OpenModelica
        // Cavitation
        bool cav = false;
        if (p1 < 0.0)
        {
            c1 = 0.0;
            Zc1 = 0.0;
            cav = true;
        }
        if (p2 < 0.0)
        {
            c2 = 0.0;
            Zc2 = 0.0;
            cav = true;
        }
        if (cav)        //Cavitation, redo calculations with new c and Zc
        {
                //Calculation of Spool Position
            double p1 = c1 + q1*Zc1;
            double Ftot = p1*mPilotArea - mFs;      //Sum of forces in x direction
            double num [3] = {1.0, 0.0, 0.0};
            double den [3] = {mK, mC, mMass};
            mFilter.setNumDen(num,den);
            double x0 = mFilter.value(Ftot);            //Filter function
            double x0h = mHyst.getValue(x0, mXhyst, mPrevX0.value());            //Hysteresis

                //Turbulent flow equation
            mTurb.setFlowCoefficient(mCq*mW*x0h);
            q2 = mTurb.getFlow(c1,c2,Zc1,Zc2);
            q1 = -q2;
            p2 = c2+Zc2*q2;
            p1 = c1+Zc1*q1;

            if (p1 < 0.0) { p1 = 0.0; }
            if (p2 < 0.0) { p2 = 0.0; }
        }
*/
            if ((mTime>tid1) && (mTime<tid2) && (debug > 0.5))
                std::cout << this->getName().c_str() << ": " << std::endl << "mTime: " << mTime << "   p1: " << p1 << "   c1: " << c1 << "   Zc1: " << Zc1  << "   q1: " << q1 << "   p2: " << p2  << "   c2: " << c2 << "   Zc2: " << Zc2  << "   q2: " << q2 << "   x0: " << x0 << std::endl;
            //Write new values to nodes

            mpP1->writeNode(NodeHydraulic::PRESSURE, p1);
            mpP1->writeNode(NodeHydraulic::FLOW, q1);
            mpP2->writeNode(NodeHydraulic::PRESSURE, p2);
            mpP2->writeNode(NodeHydraulic::FLOW, q2);

            if(mpX->isConnected())
                mpX->writeNode(NodeSignal::VALUE, x0);

            //! @todo ska det verkligen vara x0 se kommentar nedan
            mPrevX0 = x0;  //Ska vara x0h
        }

        void finalize()
        {

        }
    };
}

#endif // HYDRAULICALTERNATIVEPRV_HPP_INCLUDED
