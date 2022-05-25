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
/*
 * @file   noiseSimplex1D.hpp
 * @author Lönja Selter <Loenja@Selter.co.uk>
 * @date   2022-05-22
 *
 * @brief Simple simulation time based simplex noise.
 *
*/
#ifndef NOISESIMPLEX1D_HPP_INCLUDED
#define NOISESIMPLEX1D_HPP_INCLUDED

#include <cmath>
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
        double *mpSeed;
        double mHeading;

        //Declare ports


    public:                              //Public section
        static Component *Creator() {
            return new noiseSimplex1D();
        }

        //Configure
        void configure() override {
            //Register constants
            addConstant("scale", "", "", 1, mscale);
//            addConstant("Seed", "", "", 0, mSeed);
            addConstant("Offset_x", "", "", 0, mOffX);
            addConstant("Offset_y", "", "", 0, mOffY);
            addConstant("Heading", "Angle (deg) at which to traverse a 3d Simplex field: 0 East, 90 North.", "deg", 0,mHeading);
            addInputVariable("Seed", "", "", 0, &mpSeed);

            //Add ports
            addOutputVariable("Signal", "", "", 0, &mpSignal);

            //Configuration code

        }

        //Initialize
        void initialize() override {
            //Initialize variables
            mNoise = new OpenSimplexNoise::Noise(*mpSeed);
            mHeading = deg2rad(mHeading);
            //Get data pointers


            //Read input variables
            Signal = (*mpSignal);

            //Initialization code


            //Write output variables
            (*mpSignal) =mNoise->eval(cos(mHeading) * mTime * mscale+mOffX, sin(mHeading) * mTime * mscale+ mOffY);
        }

        //Simulate one time step
        void simulateOneTimestep() override {
            //Read input variables
            Signal = (*mpSignal);

            //Simulation code
            Signal = mNoise->eval(cos(mHeading) * mTime * mscale+mOffX, sin(mHeading) * mTime * mscale+ mOffY);

            //Write output variables
            (*mpSignal) = Signal;
        }

        //Finalize
        void finalize() override {
            //Finalize code
            delete mNoise;
        }

        //Finalize
        void deconfigure() override {
            //Deconfigure code

        }

        //Auxiliary functions


        double mOffX;
        double mOffY;
    };
}

#endif // NOISESIMPLEX1D_HPP_INCLUDED
