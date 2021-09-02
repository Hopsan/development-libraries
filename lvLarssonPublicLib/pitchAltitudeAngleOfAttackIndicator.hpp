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
//! @file   pitchAltitudeAngleOfAttackIndicator.hpp
//! @author Viktor Larsson <viktor.larsson@liu.se>
//! @date   2020-08-04
//!
//! @brief  Pitch angle, altitude and angle of attack indicator
//!
#ifndef PitchAltitudeAngleOfAttackIndicator
#define PITCHALTITUDEANGLEOFATTACKINDICATOR

#include "ComponentEssentials.h"
#include "ComponentUtilities.h"

namespace hopsan {

class PitchAltitudeAngleOfAttackIndicator : public ComponentSignal
{
        
    

private:

    double *mpTheta, *mpH, *mpAlpha, *mpHC,*mpHMax,*mpLGUp;
    
    
public:
    static Component *Creator()
    {
        return new PitchAltitudeAngleOfAttackIndicator();
    }
    void configure()
    {
        
        //Register input variables
        
        addInputVariable("Theta", "Pitch angle", "rad", 0.0, &mpTheta);
        addInputVariable("Altitude", "Altitude", "m", 0.0, &mpH);
        addInputVariable("Alpha", "Angle of attack", "rad", 0.0, &mpAlpha);
        
        addInputVariable("HC", "Cloud altitude (animation)", "m", 2000, &mpHC);        
        addInputVariable("HMax", "Max altitude (animation)", "m", 10000, &mpHMax); 
        
        addInputVariable("LandingGearUp", "Landing gear up", "-", 1, &mpLGUp);
        
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

#endif //PITCHALTITUDEANGLEOFATTACKINDICATOR


