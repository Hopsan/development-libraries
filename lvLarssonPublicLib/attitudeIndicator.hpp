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
//! @file   attitudeIndicator.hpp
//! @author Viktor Larsson <viktor.larsson@liu.se>
//! @date   2020-08-13
//!
//! @brief  Attitude Indicator
//!
#ifndef ATTITUDEINDICATOR

#include "ComponentEssentials.h"
#include "ComponentUtilities.h"

namespace hopsan {

class AttitudeIndicator : public ComponentSignal
{
        
    

private:

    double *mpPhi, *mpTheta,*mpPsi, *mpBeta,*mpBetaMax,*mpAlpha,*mpAlphaMax,*mpThetaAni;
    double pi;
public:
    static Component *Creator()
    {
        return new AttitudeIndicator();
    }
    void configure()
    {
        
        //Register input variables
        
        addInputVariable("Phi", "Bank angle", "rad", 0.0, &mpPhi);
        addInputVariable("Theta", "Pitch angle", "rad", 0.0, &mpTheta);
        addInputVariable("Psi", "Heading angle", "rad", 0.0, &mpPsi);
        addInputVariable("Alpha",  "Angle of attack", "rad", 0.0, &mpAlpha);
        addInputVariable("AlphaMax",  "Max Sideslip angle (animation)", "rad", 0.261799, &mpAlphaMax); //  Default value 30 degrees
        addInputVariable("Beta",  "Sideslip angle", "rad", 0.0, &mpBeta);
        addInputVariable("BetaMax",  "Max Sideslip angle (animation)", "rad", 0.08726646, &mpBetaMax); // Default value 5 degrees


   

//Register output variables
        addOutputVariable("ThetaAni", "Scaled pitch angle (animation)", "-", &mpThetaAni);



    }


    void initialize()
    {
        // pi is nice to have
        pi = 3.141592654;
        // Run one timestep to update the scaling properly
       simulateOneTimestep();
     
    }


    void simulateOneTimestep()
    {
        // ANgle to start non-linear scaling
        double thetaLim = 40*pi/180;
        double slope = 0.25;
        // Change scaling for angles greater than thetaLim
       if (Abs((*mpTheta)) < thetaLim) {
        (*mpThetaAni) = (*mpTheta);
       }
        else if((*mpThetaAni)>0){
            (*mpThetaAni) = slope*(*mpTheta)+thetaLim*(1.0-slope);
        }
       else {(*mpThetaAni) = slope*(*mpTheta)-thetaLim*(1.0-slope);
       }

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

#endif //ATTITUDEINDICATOR


