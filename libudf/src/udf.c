#include <math.h>
#include <float.h>

#include "udf.h"

#include "reports.h"

#define PI 3.1415

/** return peak location based on mode in char string */
float peak(float x0, float x1, char* mode) {

	if(strcmp(mode, "edge") == 0) {
		return x0;
	} else if(strcmp(mode, "center") == 0) {
		return (x0 + x1) / 2.0;
	} else {
		exit(0);
	}
	return 0;
}
/** return width based on mode in char string */
float width(float ws, char* mode) {
	if(strcmp(mode, "edge") == 0) {
		return ws * 2.0;
	} else if(strcmp(mode, "center") == 0) {
		return ws;
	} else {
		exit(0);
	}
	return 0;
}
float vel1(float r, float a, float umax, float p)
{
	return ( umax * pow( ((a-r)/a), p ) );
}

float vel2( float x, float a, float n, float um )
{
	/* profile
	 * u=A(x/a)^n-A
	 * 
	 */	
	return ( um * (n+1) / n * ( 1 - (x/a) * (x/a) ) );
}
float vel3(float x, float a, float y, float b, float m, float n, float um) {

	return ( um * ((m+1)/m) * ((n+1)/n) * (1 - pow(x/a,m)) * (1 - pow(y/b,n)) );

}


DEFINE_PROFILE( velocity, t, equation )
{
	/* this function creates a 1-D parabolic profile on a 2-D rectangular face
	 * face is a y-face
	 * velocity is uniform in x
	 */
	float v[3];
	face_t f;

	float x,z,u;

	if(!RP_Variable_Exists_P("inlet_x0")) {
		abort();
	}

	float x0 = RP_Get_Real("inlet_x0");
	float x1 = RP_Get_Real("inlet_x1");
	float z0 = RP_Get_Real("inlet_z0");
	float z1 = RP_Get_Real("inlet_z1");
	
	float rho = RP_Get_Real("inlet_rho");
	float m   = RP_Get_Real("inlet_mass_flow_rate");

	char* peak_x_mode = RP_Get_String("inlet_peak_x_mode");
	char* peak_z_mode = RP_Get_String("inlet_peak_z_mode");

	float xc = peak(x0, x1, peak_x_mode);
	float zc = peak(z0, z1, peak_z_mode);
	
	float xws = x1 - x0;
	float zws = z1 - z0;
	
	float xw = width(xws, peak_x_mode);
	float zw = width(xws, peak_z_mode);
	
	/* engineering values */
	float a = xw * 0.5;
	float b = zw * 0.5;
	
	float A = xws * zws; /* inlet area in simulation */
	
	float um = m / rho / A;
	
	
	/* set profile */
	begin_f_loop( f, t )
	{
		F_CENTROID(v, f, t);
		
		x = v[0] - xc;
		z = v[2] - zc;
		
		u = vel3(x, a, z, b, 2.0f, 2.0f, um);
		
		/*printf("x = %10f z = %10f um = %10f u = %10f\n",v[0],v[2],um,u);*/
		
		F_PROFILE( f, t, equation ) = u;
	}
	end_f_loop( f, t )
}

DEFINE_PROFILE( solar, t, equation )
{
	float v[3];
	face_t f;
	float x, z;
	float s, r2;
	
	
	/* get values */
	float solar_x0 = RP_Get_Real("solar_x0");
	float solar_x1 = RP_Get_Real("solar_x1");
	float solar_z0 = RP_Get_Real("solar_z0");
	float solar_z1 = RP_Get_Real("solar_z1");
	
	float A = RP_Get_Real("solar_a");
	float B = RP_Get_Real("solar_b");
	
	char* peak_x_mode = RP_Get_String("solar_peak_x_mode");
	char* peak_z_mode = RP_Get_String("solar_peak_z_mode");
	
	float xc = peak(solar_x0, solar_x1, peak_x_mode);
	float zc = peak(solar_z0, solar_z1, peak_z_mode);
	
	/* curvature based on measured peak and edge values */
	/*float a = parab_2d_coeff_from_meas( 1.3e6, 0.7e6, w / 2.0 );*/
	/*float b = a;*/

	/* desired integrated value */
	/*float S = 1e6 * w * h * 0.5;*/

	/* adject peak to give desired integral value */
	/*float c = scale(S, (x0 - xc), (x1 - xc), (z0 - zc), (z1 - zc), a, b);*/

	/*printf("% 4.2e % 4.2e % 4.2e\n", a, b, c);*/

	begin_f_loop( f, t )
	{
		F_CENTROID( v, f, t );


		/* peak at xc,yc */
		x = v[0] - xc;
		z = v[2] - zc;
		
		r2 = x*x + z*z;
		
		s = A * exp(B * r2);

		F_PROFILE( f, t, equation ) = s;
	}
	end_f_loop( f, t )
}
