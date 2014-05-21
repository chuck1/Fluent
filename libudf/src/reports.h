#ifndef REPORTS_H
#define REPORTS_H

#include "udf.h"

typedef float(*face_func)(Thread *, face_t);

float		temperature(Thread *t, face_t f);
float		area_weighted_average(Thread *t, face_func func);

#endif


