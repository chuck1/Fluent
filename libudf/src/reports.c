#include <math.h>
#include <float.h>

#include "udf.h"

#include "mymath.h"
#include "reports.h"

float		temperature(Thread *t, face_t f) {
	return F_T(f,t);
}
float		area_weighted_average(Thread *t, face_func func) {
	face_t f;
	
	float A[3];
	
	float v, a;
	float valu_area = 0;
	float area = 0;
	
	begin_f_loop( f, t )
	{
		F_AREA(A,f,t);
		
		a = magnitude(A,3);
		v = func(t,f);
		
		area += a;
		valu_area += v * a;
	}
	end_f_loop( f, t )
	
	return valu_area / area;
}


