#include <math.h>
#include <float.h>

#include "udf.h"

#include "src/reports.h"


void heat_xfer_coeff(Thread *t, real *point, real temp_target) {

	/* measure temperature at point */
	temp = point_measure(t, point, temperature);
	
	/* calculate new htc */
	

	/* apply new htc */

}

/** apply a constant convective heat transfer coeff in order to reach a desired point value of temperature */
DEFINE_PROFILE(heat_xfer_coeff1, t, equation)
{
	/* inputs from scheme:
	 * temperature
	 * point
	 */
	
	real temp_target = RP_Get_Real("HTC1_T");
	
	real point[3];
	
	point[0] = RP_Get_Real("HTC1_x");
	point[1] = RP_Get_Real("HTC1_y");
	point[2] = RP_Get_Real("HTC1_z");
	

	heat_xfer_coeff(t, point, temp_target);

}


