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

#ifndef FLIGHTWEATHER_HPP_INCLUDED
#define FLIGHTWEATHER_HPP_INCLUDED

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

    struct FlightGearWeatherData{
        float windheading;
        float windspeed;
    };

    class FlightGearWeather : public ComponentSignal
    {
    private:                         
        HString mAddress;
        int mPort;
        int mSocket;
		struct addrinfo *servinfo;

        double *mpWindHeading, *mpWindSpeed;

        FlightGearWeatherData mData;

    public:                             
        static Component *Creator()
        {
            return new FlightGearWeather();
        }
        
        void configure()
        {
            addConstant("address", "", "", "localhost", mAddress);
            addConstant("port", "", "", 9999, mPort);

            addOutputVariable("windheading", "", "deg", 0, &mpWindHeading);
            addOutputVariable("windspeed", "", "kt", 0, &mpWindSpeed);
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
            struct addrinfo hints;
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
            if((status = bind(mSocket, servinfo->ai_addr, servinfo->ai_addrlen)) < 0) {
                close(mSocket);
                stopSimulation("bind() failed: "+to_hstring(errno)+" ("+to_hstring(gai_strerror(errno))+")");
                WSACleanup();
                return;
            }
        }

        //Simulate one time step
        void simulateOneTimestep()
        {
			struct sockaddr_in si_other;
			int slen = sizeof(si_other);
			
			fd_set fds;
			FD_ZERO(&fds);
			FD_SET(mSocket, &fds);
			struct timeval timeout; 
			timeout.tv_sec = 0 ;
			timeout.tv_usec = mTimestep*1e5;	//= mTimestep*0.1 in microseconds
			int n = select(mSocket, &fds, NULL, NULL, &timeout) ;
			if(n <= 0) {
				return;
			}
	        recvfrom(mSocket, (char*)(&mData), sizeof(mData), 0, (struct sockaddr *) &si_other, &slen);

			(*mpWindHeading) = mData.windheading;
			(*mpWindSpeed) = mData.windspeed;
        }

        //Finalize
        void finalize()
        {
            closesocket(mSocket);
            WSACleanup();   
        }
       
    };
}

#endif // FLIGHTWEATHER_HPP_INCLUDED
