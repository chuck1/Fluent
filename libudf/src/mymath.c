#include <math.h>

float		magnitude(float *v, int n) {

	float sum = 0;
	int i = 0;
	for(; i < n; ++i) {
		sum += v[i]*v[i];
	}
	return sqrt(sum);
}



