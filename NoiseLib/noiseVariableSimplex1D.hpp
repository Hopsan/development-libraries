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

#ifndef NOISEVARIABLESIMPLEX1D_HPP_INCLUDED
#define NOISEVARIABLESIMPLEX1D_HPP_INCLUDED

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

    class noiseVariableSimplex1D : public ComponentSignal
    {
    private:                         // Private section
        //Declare local variables
        double mSeed;
        double *mpSeed;
        double X;

        double mHeading;
        //Declare data pointer variables
        double *mpX;

        double *mpSignal;
//        double signal;
        OpenSimplexNoise::Noise *mNoise;

        //Declare ports
        

    public:                              //Public section
        static Component *Creator()
        {
            return new noiseVariableSimplex1D();
        }
        
        //Configure
        void configure()
        {
            //Register constants
            addInputVariable("Seed", "", "", 0, &mpSeed);

            //Add ports
            addInputVariable("X", "", "", 0, &mpX);
            addOutputVariable("Signal", "", "", 0, &mpSignal);

            //Configuration code
            
        }
        
        //Initialize
        void initialize()
        {
            //Initialize variables
            

            //Get data pointers
            mNoise = new OpenSimplexNoise::Noise(mSeed);

            mHeading = deg2rad(mHeading);

            //Read input variables
            X = (*mpX);
//            Signal = (*mpSignal);

            //Initialization code
            

            //Write output variables
            (*mpSignal) = mNoise->eval(cos(mHeading) * X, sin(mHeading) * X);

        }

        //Simulate one time step
        void simulateOneTimestep()
        {
            //Read input variables
            X = (*mpX);
//            signal = (*mpSignal);
            //Simulation code


            //Write output variables
            (*mpSignal) = mNoise->eval(cos(mHeading) * X, sin(mHeading) * X);
        }

        //Finalize
        void finalize()
        {
            //Finalize code
            delete mNoise;

        }

        //Finalize
        void deconfigure()
        {
            //Deconfigure code
            
        }

        //Auxiliary functions
        
    };
}

#endif // NOISEVARIABLESIMPLEX1D_HPP_INCLUDED
