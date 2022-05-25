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
 * @file   noiseSeed.hpp
 * @author Lönja Selter <Loenja@Selter.co.uk>
 * @date   2022-05-22
 *
 * @brief Generates a single random value at start of simulation
 *
*/

#ifndef NOISESEED_HPP_INCLUDED
#define NOISESEED_HPP_INCLUDED

#include <cmath>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"
#include <sstream>
#include <cstring>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <chrono>

using namespace std;

namespace hopsan {

    class noiseSeed : public ComponentSignal {
    private:                         // Private section
        //Declare local variables

        double mMin, mMax;

        //Declare data pointer variables
        double *mpSeed;


    public:                              //Public section
        static Component *Creator() {
            return new noiseSeed();
        }

        //Configure
        void configure() override {
            //Register constants
            addConstant("Min", "", "", 0, mMin);
            addConstant("Max", "", "", 1, mMax);


            //Add ports
            addOutputVariable("Seed", "Pseudo random number beween limits", "", 0, &mpSeed);
            //Configuration code

        }

        //Initialize
        void initialize() override {
            //Initialization code
            std::mt19937 gen(
                    static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
            std::uniform_real_distribution<double> dis(mMin, mMax);

            //Write output variables
            (*mpSeed) = dis(gen);
        }

        //Simulate one time step
        void simulateOneTimestep() override {
            //nothing to do here.
        }

        //Finalize
        void finalize() override {
            //Finalize code

        }

        //Finalize
        void deconfigure() override {
            //Deconfigure code

        }

        //Auxiliary functions

    };
}

#endif // NOISESEED_HPP_INCLUDED
