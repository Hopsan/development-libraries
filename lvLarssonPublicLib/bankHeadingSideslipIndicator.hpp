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
//! @file   bankHeadingSideslipIndicator.hpp
//! @author Viktor Larsson <viktor.larsson@liu.se>
//! @date   2020-08-04
//!
//! @brief  Bank, heading and sideslip angles indicator
//!
#ifndef BankHeadingSideslipIndicator
#define BANKHEADINGSIDESLIPINDICATOR

#include "ComponentEssentials.h"
#include "ComponentUtilities.h"

namespace hopsan {

class BankHeadingSideslipIndicator : public ComponentSignal
{
        
    

private:

    double *mpPsi, *mpPhi, *mpbeta,*mpLGUp,*mpurud,*mpuelev,*mpuaerL,*mpuaerR;
    
public:
    static Component *Creator()
    {
        return new BankHeadingSideslipIndicator();
    }
    void configure()
    {
        
        //Register input variables
        addInputVariable("Psi", "Heading angle", "rad", 0.0, &mpPsi);
        addInputVariable("Phi", "Bank angle", "rad", 0.0, &mpPhi);
        addInputVariable("beta","Sideslip angle", "rad", 0.0, &mpbeta);
        addInputVariable("LandingGearUp", "Landing gear up", "-", 1, &mpLGUp);
		addInputVariable("urud","Rudder", "rad", 0.0, &mpurud);
		
		addInputVariable("uelev","Elevator", "rad", 0.0, &mpuelev);
		addInputVariable("uaerL","Left aileron", "rad", 0.0, &mpuaerL);
		
		addInputVariable("uaerR","Right aileron", "rad", 0.0, &mpuaerR);

    }


    void initialize()
    {
        // No initialization needed as everything is read from input ports directly in animation mode
    }


    void simulateOneTimestep()
    {
        // No code needed as everything is read from input ports directly in animation mode
    }

    void finalize()
    {
        //WRITE YOUR FINALIZE CODE HERE (OPTIONAL)
    }


    void deconfigure()
    {
        //WRITE YOUR DECONFIGURATION CODE HERE (OPTIONAL)
    }


};
}

#endif //BANKHEADINGSIDESLIPINDICATOR


