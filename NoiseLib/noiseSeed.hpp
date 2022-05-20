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

#ifndef NOISESEED_HPP_INCLUDED
#define NOISESEED_HPP_INCLUDED

#include <math.h>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"
#include <sstream>
#include <cstring>
#include <vector>
#include <string>
#include <random>
#include <ctime>

using namespace std;

namespace hopsan {

    class noiseSeed : public ComponentSignal
    {
    private:                         // Private section
        //Declare local variables
        double Seed;

        //Declare data pointer variables
        double *mpSeed;
        double mMin, mMax;
        //Declare ports
        

    public:                              //Public section
        static Component *Creator()
        {
            return new noiseSeed();
        }
        
        //Configure
        void configure()
        {
            //Register constants


            //Add ports
            addOutputVariable("Seed", "Pseudo random number beween limits", "", 0, &mpSeed);
            addConstant("Min", "", "", 0, mMin);
            addConstant("Max", "", "", 1, mMax);
            //Configuration code
            
        }
        
        //Initialize
        void initialize()
        {
            //Initialize variables


            //Get data pointers
            

            //Read input variables
            Seed = (*mpSeed);

            //Initialization code
            std::mt19937 gen (std::time(NULL));
            std::uniform_real_distribution<double> dis(mMin, mMax);

            //Write output variables
            (*mpSeed) = dis(gen);
        }

        //Simulate one time step
        void simulateOneTimestep()
        {
            //Read input variables
//            Seed = (*mpSeed);
//
//            //Simulation code
//
//
//            //Write output variables
//            (*mpSeed) = Seed;
        }

        //Finalize
        void finalize()
        {
            //Finalize code
            
        }

        //Finalize
        void deconfigure()
        {
            //Deconfigure code
            
        }

        //Auxiliary functions
        
    };
}

#endif // NOISESEED_HPP_INCLUDED