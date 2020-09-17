/*-----------------------------------------------------------------------------
 This source file is a part of Hopsan

 Copyright (c) 2009 to present year, Hopsan Group

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

 For license details and information about the Hopsan Group see the files
 GPLv3 and HOPSANGROUP in the Hopsan source code root directory

 For author and contributor information see the AUTHORS file
-----------------------------------------------------------------------------*/

//!
//! @file    PneumaticVolumeMulti.hpp
//! @author Petter Krus <petter.krus@liu.se>
//! @date   2020-07-29
//! Based on HydraulicVolumeMultiPort.hpp
//! author Bj�rn Eriksson <bjorn.eriksson@liu.se>
//!
//! @brief Contains a Pneumatic Volume Component
//!

#ifndef PNEUMATICVOLUMEMULTI_HPP_INCLUDED
#define PNEUMATICVOLUMEMULTI_HPP_INCLUDED

#include "ComponentEssentials.h"
#include "ComponentSystem.h"
#include <vector>

namespace HopsanFMU8422 {

    //!
    //! @brief A pneumatic volume component
    //! @ingroup PneumaticComponents
    //!
    class PneumaticVolumeMulti : public ComponentC
    {

    private:
        double mPh;
        Port *mpP1;
        size_t mNumPorts;
        std::vector<double*> mvpP1_p, mvpP1_qm, mvpP1_T, mvpP1_dE, mvpP1_c, mvpP1_Zc;
        double  *mpV, *mpR, *mpcv, *mpka, *mpT0,*mpalpha,*mppmin,*mpmass;

        std::vector<double> mvCnew;
        std::vector<double> mvC0;

    public:
        static Component *Creator()
        {
            return new PneumaticVolumeMulti();
        }

        void configure()
        {
        //Add ports to the component
            mpP1 = addPowerMultiPort("P1", "NodePneumatic");

            addConstant("P_high", "High pressure (for animation)", "Pa", 2e6, mPh);
            setDefaultStartValue(mpP1, NodePneumatic::MASSFLOW, 0.0);
            setDefaultStartValue(mpP1, NodePneumatic::PRESSURE, 1.0e5);
            setDefaultStartValue(mpP1, NodePneumatic::ENERGYFLOW, 0.0);
			
		//Add inputParammeters to the component
            addInputVariable("V", "Volume", "m3", 0.001,&mpV);
            addInputVariable("R", "Gas constant", "J/Kg K", 287.,&mpR);
            addInputVariable("cv", "heatcoeff", "J/Kg K", 718.,&mpcv);
            addInputVariable("ka", "heat conductance", "J/Ks", 0.,&mpka);
            addInputVariable("T0", "Outside temperature", "K", 300.,&mpT0);
            addInputVariable("alpha", "numerical damping", "", 0.1,&mpalpha);
            addInputVariable("pmin", "numerical min pressure", "",1.,&mppmin);
        //Add outputVariables to the component
            addOutputVariable("mass","Mass in volume","kg",0.001,&mpmass);

        }


        void initialize()
        {
            double V,R,cv,ka,T0,alpha,pmin,mass,fak,Tav,pav,ZcE;
         //Read inputParameters from nodes
			V = (*mpV);
			R = (*mpR);
			cv = (*mpcv);
			ka = (*mpka);
			T0 = (*mpT0);
			alpha = (*mpalpha);
			pmin = (*mppmin);
        //Read outputVariables from nodes
			mass = (*mpmass);

            mNumPorts = mpP1->getNumPorts();
            mvpP1_p.resize(mNumPorts);
            mvpP1_qm.resize(mNumPorts);
            mvpP1_T.resize(mNumPorts);
            mvpP1_dE.resize(mNumPorts);
            mvpP1_c.resize(mNumPorts);
            mvpP1_Zc.resize(mNumPorts);
            mvC0.resize(mNumPorts);
            mvCnew.resize(mNumPorts);

        //InitialExpressions
//            ZcE = double(mNumPorts)*betae/(2.0*V)*mTimestep/(1.0-alpha);
			ZcE = double(fak*mTimestep*R)/((cv + R)*V);

            double pTot=0.0;
            for (size_t i=0; i<mNumPorts; ++i)
            {
				mvpP1_p[i]  = getSafeMultiPortNodeDataPtr(mpP1, i, NodePneumatic::PRESSURE, 0.0);
                mvpP1_qm[i]  = getSafeMultiPortNodeDataPtr(mpP1, i, NodePneumatic::MASSFLOW, 0.0);
                mvpP1_dE[i]  = getSafeMultiPortNodeDataPtr(mpP1, i, NodePneumatic::ENERGYFLOW, 0.0);
                mvpP1_c[i]  = getSafeMultiPortNodeDataPtr(mpP1, i, NodePneumatic::WAVEVARIABLE, 0.0);
                mvpP1_T[i] = getSafeMultiPortNodeDataPtr(mpP1, i, NodePneumatic::TEMPERATURE, 0.0);
                mvpP1_Zc[i] = getSafeMultiPortNodeDataPtr(mpP1, i, NodePneumatic::CHARIMP, 0.0);

                *mvpP1_p[i]  = getDefaultStartValue(mpP1, NodePneumatic::PRESSURE, i);
                *mvpP1_qm[i]  = getDefaultStartValue(mpP1, NodePneumatic::MASSFLOW, i);
                *mvpP1_dE[i]  = getDefaultStartValue(mpP1, NodePneumatic::ENERGYFLOW, i);
                *mvpP1_c[i]  = getDefaultStartValue(mpP1, NodePneumatic::WAVEVARIABLE, i);
                *mvpP1_T[i]  = getDefaultStartValue(mpP1, NodePneumatic::TEMPERATURE, i);
                *mvpP1_Zc[i]  = getDefaultStartValue(mpP1, NodePneumatic::CHARIMP, i);
//                pTot       += getDefaultStartValue(mpP1,NodePneumatic::Pressure, i)+ZcE*getDefaultStartValue(mpP1,NodePneumatic::Energyflow, i);
                *mvpP1_Zc[i] = ZcE;
            }
//            pTot = pTot/double(mNumPorts);
//            for (size_t i=0; i<mNumPorts; ++i)
//            {
//                *mvpP1_c[i] = pTot*2.0-(*mvpP1_p[i]) - ZcE*(*mvpP1_dE[i]);
//            }
			//InitialExpressions
			fak = 1/(1 - alpha);
			Tav = *mvpP1_T[0];
			pav = *mvpP1_p[0];
			mass = (pav*V)/(R*Tav);

        }


        void simulateOneTimestep()
        {
            double cTot = 0.0;
            double pav,ZcE,V,R,cv,alpha,mass,fak,Tav;
            R = (*mpR);
            cv = (*mpcv);
            alpha = (*mpalpha);
            V = (*mpV);
            fak = 1/(1 - alpha);
	
 //           Zc = double(mNumPorts)*betae/(2.0*V)*mTimestep/(1.0-alpha);
            ZcE = (fak*R*mTimestep)/((cv + R)*V);

            //Equations
            for (size_t i=0; i<mNumPorts; ++i)
            {
                cTot += (*mvpP1_c[i]) + 2.0*ZcE*(*mvpP1_dE[i]);
				mass=mass+(*mvpP1_qm[i])*mTimestep;
            }
            pav = cTot/double(mNumPorts);
			Tav=pav/(mass*R);

            for (size_t i=0; i<mNumPorts; ++i)
            {
                mvC0[i] = pav*2.0-(*mvpP1_c[i]) - 2.0*ZcE*(*mvpP1_dE[i]);
                mvCnew[i] = alpha*(*mvpP1_c[i]) + (1.0-alpha)*mvC0[i];
            }

            //Write new values
            for(size_t i=0; i<mNumPorts; ++i)
            {
                (*mvpP1_Zc[i]) = ZcE;
                (*mvpP1_c[i]) = mvCnew[i];
				(*mvpP1_T[i]) = Tav;
            }
        }


        void finalize()
        {
        }
    };
}

#endif // PNEUMATICVOLUMEMULTI_HPP_INCLUDED
