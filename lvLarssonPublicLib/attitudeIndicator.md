![Indicator image](attitudeIndicator_help.svg)

Visualisation component for Trajectory. The component reads the X and Y coordinates and heading angle from another simulation model and moves and rotates the vehicle on the XY-plane accordingly.

### Component type
Signal/Animation

### Input Variables
* **X** - Vehicle center point X-coordinate [m]
* **Y** - Vehicle center point Y-coordinate [m]
* **Psi** - Heading angle [rad]
* **L** - Width of quadrant [m]

The **L** parameter may be used to scale the motion of the vehicle, since the size of the mission could vary greatly.
<!---EQUATION --->