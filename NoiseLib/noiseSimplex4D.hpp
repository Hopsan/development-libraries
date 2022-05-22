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

#ifndef NOISESIMPLEX4D_HPP_INCLUDED
#define NOISESIMPLEX4D_HPP_INCLUDED

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

    class noiseSimplex4D : public ComponentSignal {
    private:                         // Private section
        //Declare local variables
//        double mSeed;
        double X;
        double Y;
        double Z;
        double W;
        OpenSimplexNoise::Noise *mNoise;
        //Declare data pointer variables
        double *mpX, *mpY, *mpZ, *mpW, *mpSignal, *mpSeed;

        //Declare ports


    public:                              //Public section
        static Component *Creator() {
            return new noiseSimplex4D();
        }

        //Configure
        void configure() override {
            //Register constants
            addInputVariable("Seed", "", "", 0, &mpSeed);

            //Add ports
            addInputVariable("X", "", "", 0, &mpX);
            addInputVariable("Y", "", "", 0, &mpY);
            addInputVariable("Z", "", "", 0, &mpZ);
            addInputVariable("W", "", "", 0, &mpW);
            addOutputVariable("Signal", "", "", 0, &mpSignal);
            //Configuration code


        }

        //Initialize
        void initialize() override {
            //Initialize variables


            //Get data pointers


            //Read input variables
            X = (*mpX);
            Y = (*mpY);
            Z = (*mpZ);
            W = (*mpW);

            //Initialization code
            mNoise = new OpenSimplexNoise::Noise(lround(*mpSeed));

            //Write output variables
            (*mpSignal) = mNoise->eval(X, Y, Z, W);
        }

        //Simulate one time step
        void simulateOneTimestep() override {
            //Read input variables
            X = (*mpX);
            Y = (*mpY);
            Z = (*mpZ);
            W = (*mpW);
//            Signal = (*mpSignal);

            //Simulation code


            //Write output variables
            (*mpSignal) = mNoise->eval(X, Y, Z, W);
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

    };
}

#endif // NOISESIMPLEX4D_HPP_INCLUDED
