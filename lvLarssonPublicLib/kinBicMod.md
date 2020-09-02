![Bicycle model picture](kinBicMod_help.svg)

2D kinematic bicycle model.

### Component type
Signal

### Input Variables
* **v** - Vehicle center of gravity (CoG) velocity [m/s]
* **delta** - Front wheel steer angle [rad]
* **lr** - Distance from CoG to vehicle rear axle [m]
* **lx** - Distance from CoG to vehicle center axis [m]

### Output Variables
* **xr** - x-coordinate (global) of rear axle center point [m]
* **yr** - y-coordinate (global) of rear axle center point [m]
* **psi** - Yaw angle [rad]
* **xCog** - x-coordinate (global) of CoG [m]
* **yCog** - y-coordinate (global) of CoG [m]
* **beta** - Slip angle [rad]
* **deltaL** - Left wheel angle (relative to vehicle center axis) [rad]
* **deltaR** - Right wheel angle (relative to vehicle center axis) [rad]

### Constants
* **Vehicle** - Vehicle type to show on animation
* **Steering** - Type of steering to use to translate from delta to deltaL and deltaR (animation)
* **Background** - Background type to show on animation
* **B** - Wheel base [m] (changing this value scales the animated vehicle accordingly)
* **Lb** - Background width [m] (changing this value scales the animated background accordingly)
* **scaleV** - Scale factor of vehicle speed (animation)
* **scaleZ** - Zoom factor of complete view (scaleZ = 1 -> the standard scaling of 2.5 pixels/meter is used)



### Port Initial Conditions
The user sets the initial position **xr** and **yr** of the rear axle center point and initial yaw angle **psi**. 

The resulting position of CoG (**xCog**, **yCog**) is then calculated based on the vehicle geometry.

<!--- ### Tips--->

## Theory
The kinematic bicycle model ignores wheel slip and is in this implementation based on differential equations defining the time derivatives of the rear axle center position and the yaw angle:
<!---EQUATION \dot{x}_{r} = - v_r \sin \psi ~~~ (1) --->
<!---EQUATION \dot{y}_{r} =   v_r \cos \psi ~~~ (2) --->
<!---EQUATION \dot{\psi} = \frac{v}{R}~~~(3) --->

where the instantaneous radius of curvature is determined by:
<!---EQUATION R = \frac{l_r}{\sin \beta}~~~(4) --->

where the slip angle may be calculated from the vehicle geometry:
<!---EQUATION \beta = \arctan{\left(\frac{l_r}{B+l_x \tan{\delta}}\tan \delta\right)} ~~~(5) --->

and the velocity at the rear axle center point may be calculated from its instantaneous radius of curvature, combining with equations (4) and (5):

<!---EQUATION v_r = v  \frac{R_r}{R} = v \frac{\frac{B}{\tan{\delta}}}{R} = v \frac{B}{\sqrt{(B+l_x\tan \delta)^2 + (l_r \tan \delta)^2}}~~~ (6) --->

The CoG coordinates are calculated from the resulting values of **xr** and **yr**:

<!---EQUATION x_{cog} =  x_r + l_x \cos \psi  - l_r \sin \psi ~~~ (7) --->
<!---EQUATION y_{cog} =  y_r + l_r \cos \psi  + l_x \sin \psi ~~~ (8) --->

Note that the implementation above allows for the CoG position in the vehicle to be changed during simulation.

### Implementation adaptation
To avoid division by 0 in the case of **lr=0** in equation (3) or **delta=0** in equation (4), equations (3)-(5) can be combined:
<!---EQUATION \dot{\psi} = v  \frac{\tan \delta}{\sqrt{(B+l_x\tan \delta)^2 + (l_r \tan \delta)^2}}~~~(9) --->


## Steering

To calculate the individual wheel angles in the cases of four-wheeled vehicles, an assumption of the steering mechanism is needed. Two types have been implemented: "Ackermann", and "None".

### Ackermann
For perfect Ackermann steering, the wheel center lines of both front wheels coincide at the same point (the instantaneous point of rotation, O): 
<!---EQUATION \delta_{l} = \arctan{\left(\frac{\tan \delta}{1-\frac{C}{2B}\tan \delta}\right)}  ~~~ (10) --->
<!---EQUATION \delta_{r} = \arctan{\left(\frac{\tan \delta}{1+\frac{C}{2B}\tan \delta}\right)}  ~~~ (11) --->

### None
In the case of none, both wheel angles follow the main steer angle:
<!---EQUATION \delta_{l} = \delta  ~~~ (12) --->
<!---EQUATION \delta_{r} = \delta  ~~~ (13) --->


## Vehicles
This component allows for different vehicles to be animated. All of these have a set of geometric parameters that may be set to ensure correct output. The distance C is defined inside the component for each vehicle, and is then scaled based on the wheel base chosen (**B**):
<!---EQUATION C = C_0 \cdot scaleVeh  --->
 where
<!---EQUATION scaleVeh = \frac{B}{B_0}  --->

I.e. put **B = B0** to achieve the correct scaling for each vehicle.

The steer angle is limited to **deltaMax**, which is defined uniqiely for each vehicle. For the 4-wheeled vehicles, **deltaMax** is translated from the max steer angle allowed at the wheel:
<!---EQUATION \delta_{max} = \arctan{\left(\frac{1}{\frac{1}{\tan\delta_{max,l/r}}+\frac{C0}{2B0}}\right)}  --->

### Bicycle
* **B0** = 2 m 
* **C0** = 0 m (since the bicycle has only one front wheel)
* **deltaMax** = 90 degrees

### Car
The car dimensions are estimated from blueprints of the Mercedes Benz W115 chassis:

* **B0** = 2.75 m
* **C0** = 1.46 m 
* **deltaMaxLR** = 50 degrees

### Backhoe Loader
The backhoe loader dimensions are estimated from the datasheet of the Volvo BL61B backhoe loader:

* **B0** = 2.18 m
* **C0** = 1.46 m 
* **deltaMaxLR** = 55 degrees


## Backgrounds
By changing the **Lb** constant, the animated size of the background is scaled accordingly: 

<!---EQUATION scaleBG = \frac{L_b}{L_{b,0}}  --->

Put **Lb = Lb0** to achieve the correct scaling for each background (i.e. a scaling that results in 2.5 pixels/m).

Note that the constant **scaleZ** may be used to change the size of all components (background and vehicle), for instance if a larger cycle is simulated. The default value of **scaleZ = 20** is used to ensure that the bicycle component is animated at a reasonable size for default settings.

### Plain and Quarry
* **Lb0** = 160 m

This value is not very important for the plain background since it does not contain any objects. For the "Quarry" background it matters more since it contains vehicles that will change in size with scaling.

### Sviestad
This background is a copy of the Linköping Sviestad race track.

* **Lb0** = 1000 m

