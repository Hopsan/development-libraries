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

//!
//! @file   kinBicMod.hpp
//! @author Viktor Larsson <viktor.larsson@liu.se>
//! @date   2020-05-07
//!
//! @brief  kinematic bicycle model using steer angle and vehicle speed as input
//!
#ifndef KINEMATICBICYCLEMODEL
#define KINEMATICBICYCLEMODEL

#include "ComponentEssentials.h"
#include "ComponentUtilities.h"

namespace hopsan {

class KinematicBicycleModel : public ComponentSignal
{
        
    class vehicle {// Steered vehicle object
    std::string steerType; // Only "Ackermann" is implemented so far
    double B; // Wheel base (lf+lr) [m]
    double lr; // Distance from CoG to rear axle [m]
    double C; // Distance between center points of front wheels [m]
    double deltaMax; // Max steer angle
    double lx; // X-deviation of CoG from center axis 
   
        public:
        double v; // Vehicle velocity [m/s]
        double vr; // Rear axle center point velocity [m/s]
        double delta; // Steer angle [rad]
        double psi; // Yaw angle [rad]
        double xrDot; // Time derivative of global x-coordinate of rear axle center point [m/s]
        double yrDot; // Time derivative of global y-coordinate of rear axle center point [m/s]
        double psiDot; // Yaw rate [rad/s] 
        double beta; // Slip angle [rad]
        double deltaL; // Left front wheel angle [rad]
        double deltaR; // Right front wheel angle [rad]
        double xCog; // Global x-coordinate of CoG [m]
        double yCog; // Global y-coordinate of CoG [m]
        
        void initialize(std::string set_steerType, double geometryData[5],double set_v,double set_delta,double set_psi,double xr,double yr){
            steerType = set_steerType;
            setGeometry(geometryData);
            setCogGeometry(geometryData[0],geometryData[1]);
            update(set_v,set_delta,set_psi);
            updateCog(geometryData[0],geometryData[1],xr,yr);
            }
        
        void setGeometry(double geometryData[5]){
            setCogGeometry(geometryData[0],geometryData[1]);
            B = geometryData[2];
            C = geometryData[3];
            deltaMax = geometryData[4];         
            }
            
        void setCogGeometry(double set_lr,double set_lx){
            lr = set_lr; 
            lx = set_lx;
        }
        
        void update(double set_v,double set_delta, double set_psi){
            v = set_v;
            delta = set_delta;
            limitValue(delta,-deltaMax,deltaMax);
            psi = set_psi;
            steer();
            move();
            }

        void updateCog(double set_lr, double set_lx,double xr, double yr){
            setCogGeometry(set_lr,set_lx);
            xCog = xr + lx*cos(psi) - lr*sin(psi);
            yCog = yr + lr*cos(psi) + lx*sin(psi);
            }
            
        void steer(){
            beta = atan(lr/(B+lx*tan(delta))*tan(delta));
            if (steerType == "Ackermann"){
                ackermann();
                } else if (steerType == "None") {
                    none(); 
                    } else {
                        none();// Use none as default
                        };
            }
            
        void move(){
            vr = v * B /sqrt((B + lx*tan(delta))*(B + lx*tan(delta)) + lr*lr*tan(delta)*tan(delta));
            xrDot = -vr*sin(psi);
            yrDot = vr*cos(psi);
            psiDot = v*tan(delta)/sqrt((B + lx*tan(delta))*(B + lx*tan(delta)) + lr*lr*tan(delta)*tan(delta));
            }
            
        void ackermann(){
            deltaL = atan(tan(delta)/(1.0-(C/2.0)/B*tan(delta))); 
            deltaR = atan(tan(delta)/(1.0+(C/2.0)/B*tan(delta)));           
            }
                
        void none(){
            deltaL = delta;
            deltaR = delta;
            }
            
    };

private:
    FirstOrderTransferFunction mFilter_XR;
    FirstOrderTransferFunction mFilter_YR;
    FirstOrderTransferFunction mFilter_PSI;
    double mNumV[2];
    double mDenV[2];
    double geometryData[5];
    double *mpv, *mppsi, *mpxr,*mpyr,*mpxCog,*mpyCog,*mpdelta,*mpdeltaL,*mpdeltaR,*mpbeta,*mplr,*mplx;
    
    double pi;
    
    double B0,lr0,C0;
    double B;
    double deltaMax;
    double Lb0;
    double Lb;
    
    double scaleV;
    
    double scaleVeh,scaleBg,scaleZ;
    double *mpBgResizer,*mpVehResizer,*mpZResizer;
    
    double bGOn;
    
    double bLOn,bikeOn,carOn;
    double *mpbLOff,*mpbikeOff,*mpcarOff;
    
    double quarryOn, plainOn, sviestadOn;
    double *mpquarryOff, *mpplainOff, *mpsviestadOff;
    
    int mBackg;
    int mVehic;
    int mSteerType;
        
    std::string steerType;
    vehicle machine;

public:
    static Component *Creator()
    {
        return new KinematicBicycleModel();
    }
    void configure()
    {
        
        //Register input variables
        addInputVariable("v", "Vehicle velocity", "m/s", 0.0, &mpv);
        addInputVariable("delta", "Front steer angle", "rad", 0.0, &mpdelta);
        addInputVariable("lr","Distance from CoG to rear axle", "m", 1.0,&mplr);
        addInputVariable("lx","X-deviation of CoG from center axis", "m", 0.0,&mplx);
        
        std::vector<HString> vehicles;
        vehicles.push_back("Bicycle");
        vehicles.push_back("Car");
        vehicles.push_back("Backhoe loader");
        addConditionalConstant("Vehicle", "Vehicle type (Animation)", vehicles, mVehic);
        
        std::vector<HString> steerings; // Implement like this to make it easier to add different types of steerings
        steerings.push_back("Ackermann");
        steerings.push_back("None");
        addConditionalConstant("Steering", "Translation delta -> wheel angles (animation)", steerings, mSteerType);
        
        
        std::vector<HString> backgrounds;
        backgrounds.push_back("Off");
        backgrounds.push_back("Plain");
        backgrounds.push_back("Quarry");
        backgrounds.push_back("Sviestad");
        addConditionalConstant("Background", "Background used (animation)", backgrounds, mBackg);
        
        //Register constant parameters
        
        addConstant("B","Wheel base (lf+lr)", "m", 2.0, B); 
        addConstant("Lb","Background width (animation)", "m", 160,Lb); // Default value to get 400 pixels
        addConstant("scaleV","Velocity scale (animation)", "-", 1.0,scaleV); 
        addConstant("scaleZ","Zoom of complete view (animation)", "-", 20.0,scaleZ); 
        
        //Register output variables
        addOutputVariable("xr", "Rear axle center x-coordinate (global)", "m",0.0, &mpxr);
        addOutputVariable("yr", "Rear axle center y-coordinate (global)", "m",0.0, &mpyr);
        addOutputVariable("psi", "Yaw angle", "rad", 0.0, &mppsi);
            
        addOutputVariable("xCog", "CoG x-coordinate (global)", "m", &mpxCog);
        addOutputVariable("yCog", "CoG y-coordinate (global)", "m", &mpyCog);
        
        addOutputVariable("beta", "Slip angle", "rad", &mpbeta);
        addOutputVariable("deltaL", "Left front wheel angle", "rad", &mpdeltaL);
        addOutputVariable("deltaR", "Right front wheel angle", "rad",&mpdeltaR);
        addOutputVariable("vehResizer", "Vehicle resizer (animation)", "-", &mpVehResizer); 
        addOutputVariable("bGResizer", "Background resizer variable (animation)", "-", &mpBgResizer);
        addOutputVariable("ZResizer", "Zoom resizer variable (animation)", "-", &mpZResizer);
        
        addOutputVariable("quarryOff", "Quarry bg ON/OFF variable (animation)", "-", &mpquarryOff);
        addOutputVariable("plainOff", "Plain bg ON/OFF variable (animation)", "-", &mpplainOff);
        addOutputVariable("sviestadOff", "Plain bg ON/OFF variable (animation)", "-", &mpsviestadOff);
        
        
        addOutputVariable("bLOff", "Backhoe loader ON/OFF variable (animation)", "-", &mpbLOff);
        addOutputVariable("bikeOff", "Bicycle ON/OFF variable (animation)", "-", &mpbikeOff);
        addOutputVariable("carOff", "Car ON/OFF variable (animation)", "-", &mpcarOff);

    }


    void initialize()
    {
        //Pi is nice to have
        pi = 3.14159265359;
            
        // Apply reasonable limitations on some input parameters to avoid div. by 0 etc.
        limitValue(scaleV,0,1000);
        limitValue(scaleZ,0,1000);
        limitValue(Lb,0,1e100);
        limitValue(B,0,1e100);
        
        // Vehicle
        // Show nothing as default
        bLOn = 0.0;
        bikeOn = 0.0;
        carOn = 0.0;
        
        switch(mVehic)
        {
            case 0: // Simple bicycle
            B0 = 2.0; // Wheel base [m]
            C0 = 0.0; // Front axle width [m](Consider only the center wheel)
            deltaMax =  pi/2; // Max steer angle according to Volvo BL61B datasheet (translated from one of the wheels to the imaginary center wheel used in the bicycle model)
            bikeOn = 1.0; // Show bike
            break;
            case 1: // Car
            B0 = 2.75; // From Mercedes W115
            C0 =  1.46; // From Mercedes W115
            deltaMax = atan(1/(1/tan(50*pi/180)+C0/2.0/(B0)));
            carOn = 1.0;
            break;
            case 2: // Backhoe loader
            B0 = 2.18; // [m] (estimated from Volvo BL61B datasheet)
            C0 = 2.0; // C (distance between front wheel centers) in [m] (estimated from Volvo BL61B datasheet)
            deltaMax =  atan(1/(1/tan(55*pi/180)+C0/2.0/(B0))); // Max steer angle according to Volvo BL61B datasheet (translated from one of the wheels to the imaginary center wheel used in the bicycle model)
            bLOn = 1.0; // Show backhoe loader
            break;
            };
        
        switch(mSteerType)
        {
            case 0: // Ackermann
            steerType = "Ackermann";
            break;
            default:
            steerType = "None";
            break;
        };
        
        // Background
    
        // Show nothing specific as default
        quarryOn = 0.0;
        plainOn = 0.0;
        sviestadOn = 0.0;
        
        bGOn = 1.0; // This is special, must be 1.0 here!
        switch(mBackg)
        {
            case 0: // Off
            bGOn = 0.0;
            Lb0 = 160; // m --> 160*2.5 = 400 pixels
            break;

            case 1: // Plain
            plainOn = 1.0;
            Lb0 = 160; // m --> 160*2.5 = 400 pixels
            break;

            case 2:// Quarry 
            quarryOn = 1.0;
            Lb0 = 160; // m --> 160*2.5 = 400 pixels
            break;
                        
            case 3:// Sviestad 
            sviestadOn = 1.0;
            Lb0 = 1000; // m --> 160*2.5 = 2500 pixels
            break;
        };
        
        // Scaling factors with limitations
        scaleBg = Lb/Lb0; // Background scaling
        scaleVeh = B/B0; // Vehicle scaling factor
        
        limitValue(scaleVeh,0.01,1000); // Avoid div. by 0 inside the vehicle object
        limitValue(scaleBg,0,1000);

        
        
        // Initialize machine kinematics model object
        // Steering geometry data
        geometryData[0] = (*mplr);// This does not need to be scaled
        geometryData[1] = (*mplx);// This does not need to be scaled
        geometryData[2] = B; // This does not need to be scaled
        geometryData[3] = C0*scaleVeh; //This has to be scaled
        geometryData[4] = deltaMax;
    
        machine.initialize(steerType,geometryData,(*mpv)*scaleV,(*mpdelta),(*mppsi),(*mpxr),(*mpyr));
        
        // Initialize filters
        mNumV[0] = 1;
        mNumV[1] = 0;
        mDenV[0] = 0;
        mDenV[1] = 1;
        mFilter_XR.initialize(mTimestep, mNumV, mDenV, machine.xrDot, (*mpxr));
        mFilter_YR.initialize(mTimestep, mNumV, mDenV, machine.yrDot, (*mpyr));
        mFilter_PSI.initialize(mTimestep, mNumV, mDenV, machine.psiDot, (*mppsi));
 
        //Write new values to nodes and update everything according to equations
        simulateOneTimestep();  

        // Hide/show backgrounds (animation)
        (*mpplainOff) = 1.0-plainOn;// 0-> plain bg is shown (i.e. off = 0)
        (*mpquarryOff) = 1.0-quarryOn;// 0-> quarry is shown (i.e. off = 0)
        (*mpsviestadOff) = 1.0-sviestadOn;// 0-> quarry is shown (i.e. off = 0)     
        
        // Hide/show vehicles (animation)
        (*mpbLOff) = 1.0 - bLOn; // 0->backhoe loader is shown (i.e. off  = 0)
        (*mpbikeOff) = 1.0 - bikeOn; // 0-> Bike is shown (i.e. off  = 0)
        (*mpcarOff) = 1.0 - carOn; // 0-> Car is shown (i.e. off  = 0)
        
        //Modify scaling to something that the xml file can use
        (*mpZResizer) = 1.0-scaleZ; // Zoom scaling
        
        (*mpBgResizer) = 1.0-scaleBg*bGOn; // Background scaling, scale to 0 if no background is chosen to compensate the movement caused by scaling
        (*mpVehResizer) = 1.0-scaleVeh; // Vehicle scaling              
    }


    void simulateOneTimestep()
    {
        //Read variable values from nodes and update machine parameters
        // Note 1: Using psi from previous time step
        // Note 2: Scaling v directly
        machine.update((*mpv)*scaleV,(*mpdelta),(*mppsi));
        // Update center of gravity
        machine.updateCog((*mplr),(*mplx),(*mpxr),(*mpyr));

        //Update filters and write new values to nodes
        (*mpdeltaL) = machine.deltaL; // Output in rad (scaling in xml file: 180/pi = 57.3 deg/rad)
        (*mpdeltaR) = machine.deltaR; // Output in rad (scaling in xml file: 180/pi = 57.3 deg/rad, negative for articulated since alpha2 is defined in opposite direction as alpha1 in that case)
        
        (*mpxr) = mFilter_XR.update(machine.xrDot); // [m] (scaling in xml file: 2.5 pixels/m)
        (*mpyr) = mFilter_YR.update(machine.yrDot); // [m] (scaling in xml file: 2.5 pixels/m)
        (*mppsi) = mFilter_PSI.update(machine.psiDot);// Output in rad (scaling in xml file: 180/pi = 57.3 deg/rad)
        
        // CoG coordinates
        (*mpxCog) = machine.xCog; // [m] (scaling in xml file: 2.5 pixels/m)
        (*mpyCog) = machine.yCog; // [m] (scaling in xml file: 2.5 pixels/m)        
        
        // Slip angle
        (*mpbeta) = machine.beta; // [rad]
        

        
    }

    void finalize()
    {
        //WRITE YOUR FINALIZE CODE HERE (OPTIONAL)
    }


    void deconfigure()
    {
        //WRITE YOUR DECONFIGURATION CODE HERE (OPTIONAL)
    }


};
}

#endif //KINEMATICBICYCLEMODEL


