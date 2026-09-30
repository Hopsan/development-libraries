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

#ifndef X_10_Y_HPP_INCLUDED
#define X_10_Y_HPP_INCLUDED

#include <math.h>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"
#include <sstream>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

namespace hopsan {

    class signalScientificNotation : public ComponentSignal
    {
    private:                         // Private section
        //Declare local variables
        double x;
        double y;
        double out;

        //Declare data pointer variables
        double *mpx, *mpy, *mpout;

        //Declare ports
        

    public:                              //Public section
        static Component *Creator()
        {
            return new signalScientificNotation();
        }
        
        //Configure
        void configure()
        {
            //Register constants
            

            //Add ports
            addInputVariable("x", "mantissa", "", 1, &mpx);
            addInputVariable("y", "exponent", "", 1, &mpy);
            addOutputVariable("out", "", "", 0, &mpout);

            //Configuration code
            
        }
        
        //Initialize
        void initialize()
        {
            //Initialize variables
            

            //Get data pointers
            

            //Read input variables
            x = (*mpx);
            y = (*mpy);
            out = (*mpout);

            //Initialization code
            
            out = x * pow(10, y);
            //Write output variables
            (*mpout) = out;
        }

        //Simulate one time step
        void simulateOneTimestep()
        {
            //Read input variables
            x = (*mpx);
            y = (*mpy);
            out = (*mpout);

            //Simulation code
            out = x * pow(10, y);

            //Write output variables
            (*mpout) = out;
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

#endif // X_10_Y_HPP_INCLUDED
