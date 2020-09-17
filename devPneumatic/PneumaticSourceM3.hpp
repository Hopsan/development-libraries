#ifndef PNEUMATICPSOURCEM_HPP_INCLUDED
#define PNEUMATICPSOURCEM_HPP_INCLUDED

#include <iostream>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"
#include "math.h"

//!
//! @file PneumaticPsourceM.hpp
//! @author Petter Krus <petter.krus@liu.se>
//  co-author/auditor **Not yet audited by a second person**
//! @date Tue 11 Aug 2020 11:21:36
//! @brief Pressure source
//! @ingroup PneumaticComponents
//!

using namespace hopsan;

   class PneumaticPsourceM : public ComponentC
    {

    private:
        double mPh;
		double R,cv,pin,Tin,ZcE;
        Port *mpP1;
        size_t mNumPorts;
        std::vector<double*> mvpP1_p, mvpP1_qm, mvpP1_T, mvpP1_dE, mvpP1_c, mvpP1_Zc;
        double  *mpR, *mpcv,*mpTin,*mppin;

    public:
        static Component *Creator()
        {
            return new PneumaticPsourceM();
        }

        void configure()
        {
        //Add ports to the component
            mpP1 = addPowerMultiPort("P1", "NodePneumatic");

		//Add inputParammeters to the component
            addInputVariable("pin","Pressure","Pa",100000.,&mppin);
            addInputVariable("Tin","Input temperature","K",293.,&mpTin);
			
			setDefaultStartValue(mpP1, NodePneumatic::MASSFLOW, 0.0);
            setDefaultStartValue(mpP1, NodePneumatic::PRESSURE, 1.0e5);
            setDefaultStartValue(mpP1, NodePneumatic::TEMPERATURE, 297.);
            setDefaultStartValue(mpP1, NodePneumatic::ENERGYFLOW, 0.0);
			
        //Add outputVariables to the component
        }


        void initialize()
        {
//   
         //Read inputParameters from nodes
        pin = (*mppin);
        Tin = (*mpTin);
        //Read outputVariables from nodes

            mNumPorts = mpP1->getNumPorts();
            mvpP1_p.resize(mNumPorts);
            mvpP1_qm.resize(mNumPorts);
            mvpP1_T.resize(mNumPorts);
            mvpP1_dE.resize(mNumPorts);
            mvpP1_c.resize(mNumPorts);
            mvpP1_Zc.resize(mNumPorts);


        //InitialExpressions
			ZcE = 0.;
			
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
            }

			//InitialExpressions
        }


        void simulateOneTimestep()
        {
            double cTot = 0.0;
            R = (*mpR);
            cv = (*mpcv);
			ZcE = 0.;

            //Equations

            //Write new values
            for(size_t i=0; i<mNumPorts; ++i)
            {
                (*mvpP1_Zc[i]) = 0.;
                (*mvpP1_c[i]) = pin;
				(*mvpP1_T[i]) = Tin;
            }        
			//outputVariables
        }


        void finalize()
        {
        }
    };
#endif // PNEUMATICPSOURCEM_HPP_INCLUDED