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

#ifndef FLIGHTGEARPOSITIONORIENTATION_HPP_INCLUDED
#define FLIGHTGEARPOSITIONORIENTATION_HPP_INCLUDED

#include <math.h>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"
#include <sstream>
#include <cstring>
#include <vector>
#include <string>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>

#ifdef _WIN32
#include "winsock2.h"
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif

using namespace std;

namespace hopsan {

    struct FlightGearData{
        float altitude;
        float latitude;
        float longitude;
        float roll;
        float pitch;
        float heading;
    };

    class FlightGearPositionOrientation : public ComponentSignal
    {
    private:                         
        HString mAddress;
        int mPort;
        int mSocket;
        double mFreq;
        double mNextSend;

        double *mpAltitude, *mpLatitude, *mpLongitude, *mpRoll, *mpPitch, *mpHeading;

        FlightGearData mData;

    public:                             
        static Component *Creator()
        {
            return new FlightGearPositionOrientation();
        }
        
        void configure()
        {
            addConstant("address", "", "", "localhost", mAddress);
            addConstant("port", "", "", 9999, mPort);
            addConstant("freq", "communication frequency", "Hz", 100, mFreq);

            addInputVariable("altitude", "", "m", 0, &mpAltitude);
            addInputVariable("latitude", "", "rad", 0, &mpLatitude);
            addInputVariable("longitude", "", "rad", 0, &mpLongitude);
            addInputVariable("roll", "", "rad", 0, &mpRoll);
            addInputVariable("pitch", "", "rad", 0, &mpPitch);
            addInputVariable("heading", "", "rad", 0, &mpHeading);
        }
        
        void initialize()
        {
			//Startup WSA
            WSADATA wsaData;
            int status;
            if((status = WSAStartup(MAKEWORD(2,2), &wsaData)) != 0) {
                stopSimulation("WSAStartup()) failed: "+to_hstring(gai_strerror(status)));
                return;
            }
            
			//Get address and port for FlightGear
            struct addrinfo hints, *servinfo;
            memset(&hints, 0, sizeof(hints));
            hints.ai_family = AF_INET;
            hints.ai_socktype = SOCK_DGRAM;
            if((status = getaddrinfo(mAddress.c_str(), to_hstring(mPort).c_str(), &hints, &servinfo)) != 0) {
                stopSimulation("getaddrinfo()) failed: "+to_hstring(gai_strerror(status)));
                WSACleanup;
                return;
            }
            
			//Create socket
            if ((mSocket = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1) {
                stopSimulation("socket() failed: "+to_hstring(mSocket)+" ("+to_hstring(gai_strerror(mSocket))+")");
                WSACleanup();
                return;
            }
            
			//Connect to FlightGear socket
            if((status = connect(mSocket, servinfo->ai_addr, servinfo->ai_addrlen)) < 0) {
                close(mSocket);
                stopSimulation("connect() failed: "+to_hstring(errno)+" ("+to_hstring(gai_strerror(errno))+")");
                WSACleanup();
                return;
            }
            
            mNextSend = 0;
        }

        //Simulate one time step
        void simulateOneTimestep()
        {
          //Read input variables
//            double altitude =  (*mpAltitude)*3.28;        //m to ft
//             double latitude =  (*mpLatitude);
//             double longitude = (*mpLongitude);
//             double roll =      (*mpRoll)*180.0/M_PI;      //rad to deg
//             double pitch =     (*mpPitch)*180.0/M_PI;     //rad to deg
//             double heading =   (*mpHeading)*180.0/M_PI;   //rad to degg

            //char send_data[1024];
            //int msg_len = sprintf(send_data, "%.2f,%.12f,%.12f,%.2f,%.2f,%.2f\n", altitude, latitude, longitude, roll, pitch, heading);
            //send(mSocket, send_data, msg_len, 0);
            
            if(mTime > mNextSend) {
                mData.altitude =  (*mpAltitude)*3.28;
                mData.latitude =  (*mpLatitude);
                mData.longitude = (*mpLongitude);
                mData.roll =      (*mpRoll)*180.0/M_PI;      //rad to deg
                mData.pitch =     (*mpPitch)*180.0/M_PI;     //rad to deg
                mData.heading =   (*mpHeading)*180.0/M_PI;   //rad to degg
    
                send(mSocket, (char*)(&mData), sizeof(mData), 0);
                
                mNextSend = mTime + 1.0/mFreq;
            }
        }

        //Finalize
        void finalize()
        {
            close(mSocket);
            WSACleanup();   
        }
       
    };
}

#endif // FLIGHTGEARPOSITIONORIENTATION_HPP_INCLUDED
