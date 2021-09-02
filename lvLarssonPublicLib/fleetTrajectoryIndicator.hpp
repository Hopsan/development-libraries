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
//! @file   fleetTrajectoryIndicator.hpp
//! @author Viktor Larsson <viktor.larsson@liu.se>
//! @date   2020-08-13
//!
//! @brief  Indicator for trajectory of several airplanes
//!
#ifndef FLEETTRAJECTORYINDICATOR

#include "ComponentEssentials.h"
#include "ComponentUtilities.h"

namespace hopsan {

class FleetTrajectoryIndicator : public ComponentSignal
{
        
    

private:

    double *mpX1, *mpY1, *mpPsi1;
    double *mpX2, *mpY2, *mpPsi2;
    double *mpX3, *mpY3, *mpPsi3;
    double *mpX4, *mpY4, *mpPsi4;
    double *mpX5, *mpY5, *mpPsi5;
    double *mpX6, *mpY6, *mpPsi6;
    double *mpX7, *mpY7, *mpPsi7;
    double *mpX8, *mpY8, *mpPsi8;
  
  
    double *mpL;
  
    double *mpshowPlane[8];
    
    int nPlanesMax;
    
    int nPlanes;
    
public:
    static Component *Creator()
    {
        return new FleetTrajectoryIndicator();
    }
    void configure()
    {
        
        //Register input variables
        addInputVariable("L",  "Quadrant width (animation scaling)", "m", 10000, &mpL);

        
        
        addInputVariable("X1", "X-coordinate plane 1 (yellow)", "m", 0.0, &mpX1);
        addInputVariable("Y1", "Y-coordinate plane 1 (yellow)", "m", 0.0, &mpY1);
        addInputVariable("Psi1", "Heading angle plane 1 (yellow)", "rad", 0.0, &mpPsi1);
        
        addInputVariable("X2", "X-coordinate plane 2 (green)", "m", 0.0, &mpX2);
        addInputVariable("Y2", "Y-coordinate plane 2 (green)", "m", 0.0, &mpY2);
        addInputVariable("Psi2", "Heading angle plane 2 (green)", "rad", 0.0, &mpPsi2);
        
        addInputVariable("X3", "X-coordinate plane 3 (red)", "m", 0.0, &mpX3);
        addInputVariable("Y3", "Y-coordinate plane 3 (red)", "m", 0.0, &mpY3);
        addInputVariable("Psi3", "Heading angle plane 3 (red)", "rad", 0.0, &mpPsi3);
        
        addInputVariable("X4", "X-coordinate plane 4 (blue)", "m", 0.0, &mpX4);
        addInputVariable("Y4", "Y-coordinate plane 4 (blue)", "m", 0.0, &mpY4);
        addInputVariable("Psi4", "Heading angle plane 4 (blue)", "rad", 0.0, &mpPsi4); 
                
        addInputVariable("X5", "X-coordinate plane 5 (black)", "m", 0.0, &mpX5);
        addInputVariable("Y5", "Y-coordinate plane 5 (black)", "m", 0.0, &mpY5);
        addInputVariable("Psi5", "Heading angle plane 5 (black)", "rad", 0.0, &mpPsi5);
        
        addInputVariable("X6", "X-coordinate plane 6 (grey)", "m", 0.0, &mpX6);
        addInputVariable("Y6", "Y-coordinate plane 6 (grey)", "m", 0.0, &mpY6);
        addInputVariable("Psi6", "Heading angle plane 6 (grey)", "rad", 0.0, &mpPsi6);
        
        addInputVariable("X7", "X-coordinate plane 7 (brown)", "m", 0.0, &mpX7);
        addInputVariable("Y7", "Y-coordinate plane 7 (brown)", "m", 0.0, &mpY7);
        addInputVariable("Psi7", "Heading angle plane 7 (brown)", "rad", 0.0, &mpPsi7);
        
        addInputVariable("X8", "X-coordinate plane 8 (purple)", "m", 0.0, &mpX8);
        addInputVariable("Y8", "Y-coordinate plane 8 (purple)", "m", 0.0, &mpY8);
        addInputVariable("Psi8", "Heading angle plane 8  (purple)", "rad", 0.0, &mpPsi8);
        
        
        

        std::vector<HString> planes;
        planes.push_back("1");
        planes.push_back("2");
        planes.push_back("3");
        planes.push_back("4");
        planes.push_back("5");
        planes.push_back("6");
        planes.push_back("7");
        planes.push_back("8");
        addConditionalConstant("NoPlanes", "Number of planes to show (Animation)", planes, nPlanes);



//Register output variables
        addOutputVariable("showPlane1", "Plane 1 ON/OFF variable (animation)", "-", &mpshowPlane[0]);
        addOutputVariable("showPlane2", "Plane 1 ON/OFF variable (animation)", "-", &mpshowPlane[1]);
        addOutputVariable("showPlane3", "Plane 2 ON/OFF variable (animation)", "-", &mpshowPlane[2]);
        addOutputVariable("showPlane4", "Plane 3 ON/OFF variable (animation)", "-", &mpshowPlane[3]);
        addOutputVariable("showPlane5", "Plane 4 ON/OFF variable (animation)", "-", &mpshowPlane[4]);
        addOutputVariable("showPlane6", "Plane 5 ON/OFF variable (animation)", "-", &mpshowPlane[5]);
        addOutputVariable("showPlane7", "Plane 6 ON/OFF variable (animation)", "-", &mpshowPlane[6]);
        addOutputVariable("showPlane8", "Plane 7 ON/OFF variable (animation)", "-", &mpshowPlane[7]);




    }


    void initialize()
    {
        
    nPlanesMax = 8;
     
     // Decide what to show or not
     for (int i=0; i<nPlanesMax; ++i)
         {
             if (i<=nPlanes){
             (*mpshowPlane[i]) = 1.0;
             }
             else{// Show nothing as default 
             (*mpshowPlane[i]) = 0.0;
             }
             }

  
        
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


