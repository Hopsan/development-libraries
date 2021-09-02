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
//! @file   trajectoryIndicator.hpp
//! @author Viktor Larsson <viktor.larsson@liu.se>
//! @date   2020-08-13
//!
//! @brief  Indicator for trajectory
//!
#ifndef TRAJECTORYINDICATOR

#include "ComponentEssentials.h"
#include "ComponentUtilities.h"

namespace hopsan {

class TrajectoryIndicator : public ComponentSignal
{
        
    

private:

    double *mpX, *mpY, *mpPsi, *mpL;
    double *mpshowPlane,*mpshowCar,*mpshowDot,*mpshowBoat;
    int mVehic;
    
public:
    static Component *Creator()
    {
        return new TrajectoryIndicator();
    }
    void configure()
    {
        
        //Register input variables
        
        addInputVariable("X", "X-coordinate", "m", 0.0, &mpX);
        addInputVariable("Y", "Y-coordinate", "m", 0.0, &mpY);
        addInputVariable("Psi", "Heading angle", "rad", 0.0, &mpPsi);
        addInputVariable("L",  "Quadrant width (animation scaling)", "m", 10000, &mpL);


        std::vector<HString> vehicles;
        vehicles.push_back("Plane");
        vehicles.push_back("Car");
        vehicles.push_back("Boat");
        vehicles.push_back("Dot");
        addConditionalConstant("Vehicle", "Vehicle type (Animation)", vehicles, mVehic);
        

//Register output variables
        addOutputVariable("showPlane", "Plane ON/OFF variable (animation)", "-", &mpshowPlane);
        addOutputVariable("showCar", "Car ON/OFF variable (animation)", "-", &mpshowCar);        
        addOutputVariable("showBoat", "Boat ON/OFF variable (animation)", "-", &mpshowBoat);
        addOutputVariable("showDot", "Dot ON/OFF variable (animation)", "-", &mpshowDot);



    }


    void initialize()
    {
     
        // Show nothing as default
        (*mpshowPlane) = 0.0;
        (*mpshowCar) = 0.0;
        (*mpshowDot) = 0.0;
        (*mpshowBoat) = 0.0;
        
        switch(mVehic)
        {
            case 0: // Plane
            (*mpshowPlane) = 1.0;
            break;
            case 1: // Car
            (*mpshowCar) = 1.0;
            break;
            case 2: // Boat
            (*mpshowBoat) = 1.0;
            break;
            case 3: // Dot
            (*mpshowDot) = 1.0;
            break;
            };
        
        
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

#endif //TRAJECTORYINDICATOR


