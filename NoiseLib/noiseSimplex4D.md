Generates Simplex noise based on 4 dimensional coordinates. [Simplex Noise on Wikipedia](https://en.wikipedia.org/wiki/Simplex_noise)


### Component type
Signal

### Input Variables
* **X** - 1st dimension coordinate.
* **Y** - 2nd dimension coordinate.
* **Z** - 3rd dimension coordinate.
* **W** - 4th dimension coordinate.
* **Seed** - Initialization seed. Only read at initialization. A good use case for the `Seed` block, or a constant, defaults to 0. Type required is Int64 so will be cast as such.

### Output Variables
* **Signal** - 0-1 constant variance noise signal.


### Constants
None


### Examples

![10 seconds of 1D simplex noise](F:\Documents\development-libraries\NoiseLib\1D.png)

![1000 seconds of simplex noise](F:\Documents\development-libraries\NoiseLib\1D_1000.png)

![1000 seconds of simplex noise (x=e^mTime/100)](F:\Documents\development-libraries\NoiseLib\1D_ex.png)
