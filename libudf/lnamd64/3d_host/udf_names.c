/* This file generated automatically. */
/*          Do not modify.            */
#include "udf.h"
#include "prop.h"
#include "dpm.h"
extern DEFINE_PROFILE( velocity, t, equation );
extern DEFINE_PROFILE( solar, t, equation );
UDF_Data udf_data[] = {
{"velocity", (void (*)())velocity, UDF_TYPE_PROFILE},
{"solar", (void (*)())solar, UDF_TYPE_PROFILE},
};
int n_udf_data = sizeof(udf_data)/sizeof(UDF_Data);
#include "version.h"
void UDF_Inquire_Release(int *major, int *minor, int *revision)
{
  *major = RampantReleaseMajor;
  *minor = RampantReleaseMinor;
  *revision = RampantReleaseRevision;
}
