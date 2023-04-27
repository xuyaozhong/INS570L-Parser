#ifndef _GPS_H_
#define _GPS_H_
#define GPS_EPOCH   315964800       /* 6 Jan 1981 00:00:00 UTC */
#define SECS_PER_WEEK        (60*60*24*7)    /* seconds per week */
#define GPS_ROLLOVER	(1024*SECS_PER_WEEK)	/* rollover period */
#define GPS_LEAF 18
void gps_to_utc(uint32_t week, uint32_t ms);
#endif
