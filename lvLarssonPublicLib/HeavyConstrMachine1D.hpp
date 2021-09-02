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
//! @file   HeavyConstrMachine1D.hpp
//! @author Viktor Larsson <viktor.larsson@liu.se>
//! @date   2020-04-29
//!
//! @brief Contains a Q-type 1D vehicle model of a generic construction machine, with a linear mechincal power port
//!

#ifndef HEAVYCONSTRMACHINE1D
#define HEAVYCONSTRMACHINE1D

#include <math.h>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"

using namespace std;

namespace hopsan {

class HeavyConstrMachine1D : public ComponentQ
{
private:
    
    FirstOrderTransferFunction mFilter_v;
    FirstOrderTransferFunction mFilter_x;
    FirstOrderTransferFunction mFilter_a;
    double m, Cr, B, i0, rw, pi, g, alpha,gamma,p,eta_0,P0,v0,eta_00,jr,j0,P,Jeq;
	double Ft, Fr, Fg, FB;
    double c1, Zc1, w1, a1, T1;
	double c2, Zc2, v2, x2, F2;
    double mNum_v[2];
    double mDen_v[2];
    double mNum_a1[2];
    double mDen_a1[2];
    double *mpND_w1, *mpND_a1, *mpND_T1, *mpND_c1, *mpND_Zc1;
	double *mpND_v2, *mpND_x2, *mpND_f2, *mpND_c2, *mpND_Zc2, *mpND_me;
	double *mpFr,*mpFB,*mpFg,*mpp,*mpJeq,*mpB,*mpCr,*mpeta_0;
    Port *mpP1;
    Port *mpP2;

public:
    static Component *Creator()
    {
        return new HeavyConstrMachine1D();
    }

    void configure()
    {
        addConstant("m", "Vehicle mass", "kg", 5000, m);
        addConstant("i0", "Final gear ratio (i0 = w_wheel/w1)", "-", 0.05, i0);
        addConstant("rw", "Wheel radius", "m", 0.65, rw);
        addConstant("v0", "Nominal vehicle velocity (to dampen rolling resistance force near 0 velocity)", "m/s", 0.001, v0);
		addConstant("P0", "Nominal power flow (to dampen final gear efficiency near 0 power flow)", "W", 2, P0);

		addInputVariable("eta_0", "Final gear ratio Efficiency", "-", 0.92, &mpeta_0);
        addInputVariable("p", "Grade of road", "%", 0, &mpp);
		addInputVariable("B", "Viscous friction", "Ns/m",45, &mpB);
		addInputVariable("Cr", "Coefficent of rolling resistance", "-", 0.02, &mpCr);
        
		addOutputVariable("Fr", "Rolling resistance force", "N",  &mpFr);
        addOutputVariable("FB", "Resistance force due to viscous friction", "N",  &mpFB);
        addOutputVariable("Fg", "Resistance force due to gravitation", "N",  &mpFg);
        addOutputVariable("Jeq", "Equivalent rotational inertia ( =m*(rw*i0)^2 )", "kgm^2", &mpJeq);

        mpP1 = addPowerPort("P1", "NodeMechanicRotational");
		mpP2 = addPowerPort("P2", "NodeMechanic");
    }

    void initialize()
    {
        mpND_w1 = getSafeNodeDataPtr(mpP1, NodeMechanicRotational::AngularVelocity);
        mpND_T1 = getSafeNodeDataPtr(mpP1, NodeMechanicRotational::Torque);
        mpND_a1 = getSafeNodeDataPtr(mpP1, NodeMechanicRotational::Angle);
        mpND_c1 = getSafeNodeDataPtr(mpP1, NodeMechanicRotational::WaveVariable);
        mpND_Zc1 = getSafeNodeDataPtr(mpP1, NodeMechanicRotational::CharImpedance);
       
	   mpND_f2 = getSafeNodeDataPtr(mpP2, NodeMechanic::Force);
	   mpND_x2 = getSafeNodeDataPtr(mpP2, NodeMechanic::Position);
	   mpND_v2 = getSafeNodeDataPtr(mpP2, NodeMechanic::Velocity);
	   mpND_c2 = getSafeNodeDataPtr(mpP2, NodeMechanic::WaveVariable);
	   mpND_Zc2 = getSafeNodeDataPtr(mpP2, NodeMechanic::CharImpedance);
	   mpND_me = getSafeNodeDataPtr(mpP2, NodeMechanic::EquivalentMass);
	   
	    
        p = (*mpp);
		B = (*mpB);
		Cr = (*mpCr);
		eta_0 = (*mpeta_0);

        w1 = (*mpND_w1);
        T1 = (*mpND_T1);
        a1 = (*mpND_a1);

        v2 = (*mpND_v2);
		F2 = (*mpND_f2);
		x2 = (*mpND_x2);

        //WRITE INITIALIZATION HERE

        pi=3.141592653589793;
        g = 9.81;
        gamma = atan(p/100.0);
		limitValue(eta_0,0.5,1);
        
		// Initialize filters
		mNum_v[0] = 1;
        mNum_v[1] = 0;
        mDen_v[1] = m;
        mDen_v[0] = B;
        
        mNum_a1[0] = 1.0;
        mNum_a1[1] = 0.0;
        mDen_a1[0] = 0.0;
        mDen_a1[1] = 1.0;
		
		// Sigmoid to dampen near 0 power flow
		P  = -T1*w1;
		j0 = 2*(1/(1+exp(-P/P0)))-1;
		eta_00 = pow(eta_0,j0);
		Ft = T1/i0/rw * eta_00;
		FB = v2*B;
		Fg = m*g*sin(gamma);
		
		// Sigmoid to smooth out around 0 velocity
		jr = 2.0/(1.0+exp(-v2/v0))-1.0;
		Fr = Cr*m*g*cos(gamma)*jr;
		Jeq = m*rw*rw*i0*i0;
		
		// w1 does not have a filter, as it scales with v2
        mFilter_v.initialize(mTimestep, mNum_v, mDen_v, Ft -FB - Fg - Fr - F2, v2);
        mFilter_a.initialize(mTimestep, mNum_a1, mDen_a1, w1, a1);
        mFilter_x.initialize(mTimestep, mNum_a1, mDen_a1, v2, x2);
		
		// Write to nodes
		(*mpND_w1) = w1;
        (*mpND_T1) = T1;
        (*mpND_a1) = a1;
        (*mpND_v2) = v2;
		(*mpND_f2) = F2;
		(*mpND_x2) = x2;
		
		// Calculate other interesting variables
        (*mpFB) = FB;
        (*mpFg) = Fg;
        (*mpFr) = Fr;
        (*mpJeq) = m*rw*rw*i0*i0;
		
    }

    void simulateOneTimestep()
    {
		// Read from nodes
        c1 = (*mpND_c1);
        Zc1 = (*mpND_Zc1);
        c2 = (*mpND_c2);
		Zc2 = (*mpND_Zc2);
		
		B = (*mpB);
		Cr = (*mpCr);
		eta_0 = (*mpeta_0);
		limitValue(eta_0,0.5,1);
		
		// Convert road grade to slope angle
        p = (*mpp);
		gamma = atan(p/100.0);
        
		// Update forces
		// Sigmoid to dampen near 0 power flow
		P  = -T1*w1;
		j0 = 2*(1/(1+exp(-P/P0)))-1;
		eta_00 = pow(eta_0,j0);
		
		// Use wave variable here to get correct with TLM
		Ft = c1/i0/rw * eta_00;
		FB = v2*B;
		Fg = m*g*sin(gamma);
		
		// Sigmoid to smooth out around 0 velocity
		jr = 2.0/(1.0+exp(-v2/v0))-1.0;
		Fr = Cr*m*g*cos(gamma)*jr;

		// Update filter denominator for speed
        mDen_v[0] = B + Zc1/(i0*i0*rw*rw)*eta_00+Zc2;
        mFilter_v.setDen(mDen_v);
        
		// Update state variables
		v2 = mFilter_v.update(Ft - Fg -Fr - c2);
        w1 = -v2/(i0*rw);
        a1 = mFilter_a.update(w1);
        x2 = mFilter_x.update(v2);
		
		T1 = c1 + Zc1*w1;
		F2 = c2 + Zc2*v2;
		
		// Write to nodes
        (*mpND_a1) = a1;
        (*mpND_w1) = w1;
        (*mpND_T1) = T1;
        
		(*mpND_v2) = v2;
		(*mpND_f2) = F2;
		(*mpND_x2) = x2;

		(*mpFr) = Fr;
        (*mpFB) = FB;
        (*mpFg) = Fg;
        (*mpJeq) = m*rw*rw*i0*i0;
		
    }

    void finalize()
    {
        //WRITE FINALIZE CODE HERE
    }
};
}




#endif // HEAVYCONSTRMACHINE1D
