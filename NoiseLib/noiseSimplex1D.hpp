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

#ifndef NOISESIMPLEX1D_HPP_INCLUDED
#define NOISESIMPLEX1D_HPP_INCLUDED

#include <math.h>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"
#include <sstream>
#include <cstring>
#include <vector>
#include <string>
#include "libs/OpenSimplexNoise/OpenSimplexNoise/OpenSimplexNoise.h"

using namespace std;

namespace hopsan {

    class noiseSimplex1D : public ComponentSignal {
    private:                         // Private section
        //Declare local variables
        double mscale = 1337;
        double Signal;
        OpenSimplexNoise::Noise *mNoise;
        //Declare data pointer variables
        double *mpSignal;
        double mSeed;
        double mHeading;

        //Declare ports


    public:                              //Public section
        static Component *Creator() {
            return new noiseSimplex1D();
        }

        //Configure
        void configure() {
            //Register constants
            addConstant("scale", "", "", 1, mscale);
            addConstant("Seed", "", "", 0, mSeed);
            addConstant("Offset_x", "", "", 0, mOffX);
            addConstant("Offset_y", "", "", 0, mOffY);
            addConstant("Seed", "", "", 0, mSeed);
            addConstant("Heading", "Angle (deg) at which to traverse a 3d Simplex field: 0 East, 90 North.", "deg", 0,mHeading);

            //Add ports
            addOutputVariable("Signal", "", "", 0, &mpSignal);

            //Configuration code

        }

        //Initialize
        void initialize() {
            //Initialize variables
            mNoise = new OpenSimplexNoise::Noise(mSeed);
            mHeading = deg2rad(mHeading);
            //Get data pointers


            //Read input variables
            Signal = (*mpSignal);

            //Initialization code


            //Write output variables
            (*mpSignal) =mNoise->eval(cos(mHeading) * mTime * mscale+mOffX, sin(mHeading) * mTime * mscale+ mOffY);;
        }

        //Simulate one time step
        void simulateOneTimestep() {
            //Read input variables
            Signal = (*mpSignal);

            //Simulation code
            Signal = mNoise->eval(cos(mHeading) * mTime * mscale+mOffX, sin(mHeading) * mTime * mscale+ mOffY);

            //Write output variables
            (*mpSignal) = Signal;
        }

        //Finalize
        void finalize() {
            //Finalize code
            delete mNoise;
        }

        //Finalize
        void deconfigure() {
            //Deconfigure code

        }

        //Auxiliary functions


        double mOffX;
        double mOffY;
    };
}

#endif // NOISESIMPLEX1D_HPP_INCLUDED
