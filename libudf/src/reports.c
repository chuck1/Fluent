#include <math.h>

#include "udf.h"

#include "mymath.h"
#include "reports.h"

void		infinity(real *v, int n) {
	int i = 0;
	for(; i < n; ++i) {
		v[i] = 1E37;
	}
}

float		temperature(Thread *t, face_t f) {
	return F_T(f,t);
}
float		point_measure(Thread *tf, real NV_VEC(point), face_func func) {
	face_t f;
	
	real NV_VEC(v), NV_VEC(d), value;
	
	real distances[compute_node_count];
	real temperatures[compute_node_count];
	infinity(distances, compute_node_count);
	
	int found = 0;

	begin_f_loop(f,tf) {
		if PRINCIPAL_FACE_P(f,tf) {
			F_CENTROID(v,f,tf);
			
			NV_DD(d,=,v,-,point)
			
			/*d = distance(v, point, 3);*/

			if(d < dist) {
				value = func(t,f);
				dist = d;
				found = 1;
			}
		}
	} end_f_loop(f,tf)

	if(found == 0) {
		printf("ERROR! POINT EMASURE FAILED!\n");
	}

	return value;
}
float		area_weighted_average(Thread *t, face_func func) {
	face_t f;
	real NV_VEC(area);
	real total_aream total_valu_a;

	begin_f_loop(f,tf) {
		/* each compute node checks whether or not it is the principal compute
		 * node with respect to the given face and thread */
		if PRINCIPAL_FACE_P(f,tf) {
			/* face is on the principal compute node, so get the area and pressure
			 * vectors, and compute the total area and pressure for the thread
			 * from the magnitudes */
			F_AREA(area,f,tf);
			total_area += NV_MAG(area);
			total_pres_a += NV_MAG(area)*func(f,tf);
		}
	} end_f_loop(f,tf)

	total_area = PRF_GRSUM1(total_area);
	total_valu_a = PRF_GRSUM1(total_pres_a);

	return (total_valu_a / total_area);
}


