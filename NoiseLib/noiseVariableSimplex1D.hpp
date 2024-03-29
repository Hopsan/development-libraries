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
 * @file   noiseVariableSimplex1D.hpp
 * @author Lönja Selter <Loenja@Selter.co.uk>
 * @date   2022-05-22
 *
 * @brief Simple variable based simplex noise.
 *
*/
#ifndef NOISEVARIABLESIMPLEX1D_HPP_INCLUDED
#define NOISEVARIABLESIMPLEX1D_HPP_INCLUDED

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

    class noiseVariableSimplex1D : public ComponentSignal
    {
    private:                         // Private section
        //Declare local variables
        double *mpSeed;
        double X;

        double mHeading;
        //Declare data pointer variables
        double *mpX;

        double *mpSignal;
        OpenSimplexNoise::Noise *mNoise;

        //Declare ports
        

    public:                              //Public section
        static Component *Creator()
        {
            return new noiseVariableSimplex1D();
        }
        
        //Configure
        void configure() override
        {
            //Register constants
            addInputVariable("Seed", "", "", 0, &mpSeed);
            addConstant("Heading", "", "", 0, mHeading);

            //Add ports
            addInputVariable("X", "", "", 0, &mpX);
            addOutputVariable("Signal", "", "", 0, &mpSignal);

            //Configuration code
            
        }
        
        //Initialize
        void initialize() override
        {

            //Get data pointers
            mNoise = new OpenSimplexNoise::Noise(lround(*mpSeed));

            mHeading = deg2rad(mHeading);

            //Read input variables
            X = (*mpX);

            //Write output variables
            (*mpSignal) = mNoise->eval(cos(mHeading) * X, sin(mHeading) * X);

        }

        //Simulate one time step
        void simulateOneTimestep() override
        {
            //Read input variables
            X = (*mpX);
            //Write output variables
            (*mpSignal) = mNoise->eval(cos(mHeading) * X, sin(mHeading) * X);
        }

        //Finalize
        void finalize() override
        {
            //Finalize code
            delete mNoise;

        }

        //Finalize
        void deconfigure() override
        {
            //Nothing to do here
            
        }

        //Auxiliary functions
        
    };
}

#endif // NOISEVARIABLESIMPLEX1D_HPP_INCLUDED
