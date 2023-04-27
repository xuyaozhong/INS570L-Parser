#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include "gps.h"

void gps_to_utc(uint32_t week, uint32_t ms)
{
	time_t utc=0;
	struct tm gpsts;
	char       buf[80];
	utc = GPS_EPOCH  + SECS_PER_WEEK * week + (uint32_t)(ms * 0.001 * 0.25) - GPS_LEAF;
	gpsts = *localtime(&utc);
	strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &gpsts);
	printf("gps time %s\n", buf);
	time_t now = time(NULL);
	printf("current time %s\n", ctime(&now));
}
