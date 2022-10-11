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

#ifndef SIGNAL_DIFFERENTIATOR_HPP_INCLUDED
#define SIGNAL_DIFFERENTIATOR_HPP_INCLUDED

#include "ComponentEssentials.h"
#include "ComponentUtilities.h"


using namespace std;

namespace hopsan {

    class SignalDifferentiator : private ComponentSignal {
    private:                         // Private section
        double in;
        double *mpIn, *mpOut;


    public:                              //Public section
        static Component *Creator() {
            return new SignalDifferentiator();
        }

        //Configure
        void configure() {

            addInputVariable("in", "Input", "", 0, &mpIn);
            addOutputVariable("out", "Output", "", 0, &mpOut);


        }

        //Initialize
        void initialize() {
            in = (*mpIn);
        }

        //Simulate one time step
        void simulateOneTimestep() override {
            //Read input variables
            double prev = in;
            in = (*mpIn);
            (*mpOut) = (in - prev) / mTimestep;
        }


    };
}

#endif
