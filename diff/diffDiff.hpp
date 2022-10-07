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

#ifndef SELTERDIFF_HPP_INCLUDED
#define SELTERDIFF_HPP_INCLUDED

#include <math.h>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"
#include <sstream>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

namespace hopsan {

    class diffDiff : public ComponentSignal
    {
    private:                         // Private section
        //Declare local variables
        double In1;
        double Out1;
        double prev;
        //Declare data pointer variables
        double *mpIn1, *mpOut1;

        //Declare ports


    public:                              //Public section
        static Component *Creator()
        {
            return new diffDiff();
        }

        //Configure
        void configure()
        {
            //Register constants


            //Add ports
            addInputVariable("In1", "Input", "", 0, &mpIn1);
            addOutputVariable("Out1", "Output", "", 0, &mpOut1);

            //Configuration code

        }

        //Initialize
        void initialize()
        {
            //Initialize variables


            //Get data pointers


            //Read input variables
            In1 = (*mpIn1);
//            Out1 = (*mpOut1);
            //Simulation code
            prev = In1;

            //Write output variables
            (*mpOut1) = In1;
        }

        //Simulate one time step
        void simulateOneTimestep()
        {
            //Read input variables
            In1 = (*mpIn1);
            Out1 = (*mpOut1);

            //Simulation code


            //Write output variables
            (*mpOut1) = In1 - prev;
            prev = In1;
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

#endif // SELTERDIFF_HPP_INCLUDED
