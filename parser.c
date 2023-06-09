#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>
#include <time.h> 
#include "parser.h"
#include "INS570L.h"
#include "gps.h"
#include "cjson/cJSON.h"

void gnssimu2json(struct gnss_imu *d)
{
	cJSON *top = NULL;
	top = cJSON_CreateObject();
	cJSON *leafs = cJSON_CreateObject();
	cJSON_AddItemToObject(top, "NavInfo",leafs );
	{
		cJSON *node =  cJSON_CreateObject();
		cJSON_AddItemToObject(leafs, "AttiAngle" ,node);
		cJSON_AddNumberToObject(node, "AngleHeading", (d->azimuth * 360.0/32768.0));
		cJSON_AddNumberToObject(node, "AnglePitch", (d->pitch * 360.0/32768.0));
		cJSON_AddNumberToObject(node, "AngleRoll", (d->roll * 360.0/32768.0));
	};
	{
		cJSON *node =  cJSON_CreateObject();
		cJSON_AddItemToObject(leafs, "IMUAngRateRaw" ,node);
		cJSON_AddNumberToObject(node, "AngRateRawX", (d->gyro_x[0] * 300.0/32768.0));
		cJSON_AddNumberToObject(node, "AngRateRawY", (d->gyro_x[1] * 300.0/32768.0));
		cJSON_AddNumberToObject(node, "AngRateRawZ", (d->gyro_x[2] * 300.0/32768.0));
        };
	{
		cJSON *node =  cJSON_CreateObject();
		cJSON_AddItemToObject(leafs, "IMUAccelRaw" ,node);
		cJSON_AddNumberToObject(node, "AccelRawX", (d->accel_x[0] * 12.0/32768.0));
		cJSON_AddNumberToObject(node, "AccelRawY", (d->accel_x[1] * 12.0/32768.0));
		cJSON_AddNumberToObject(node, "AccelRawZ", (d->accel_x[2] * 12.0/32768.0));
	};
	{
		cJSON_AddNumberToObject(leafs, "PosLat", d->latitude);
		cJSON_AddNumberToObject(leafs, "PosLon", d->longitude);
		cJSON_AddNumberToObject(leafs, "PosAlt", d->altitude);
	};
	{
		cJSON *node =  cJSON_CreateObject();
		cJSON_AddItemToObject(leafs, "Vels" ,node);
		cJSON_AddNumberToObject(node, "VelN", d->northvelocity * 0.01 / 32768.0);
		cJSON_AddNumberToObject(node, "VelE", d->eastvelocity * 0.01 / 32768.0);
		cJSON_AddNumberToObject(node, "VelU", d->groundvelocity * 0.01 / 32768.0);
	};
	{
		cJSON *node =  cJSON_CreateObject();
		cJSON_AddItemToObject(leafs, "Time" ,node);
		cJSON_AddNumberToObject(node, "WeekTime", d->gpsweek);
		cJSON_AddNumberToObject(node, "GpsTime", (uint32_t)(d->time * 0.001 * 0.25));
	}
	
	printf("\n%s\n", cJSON_Print(top));
	
}

void dump_gnss_imu(struct gnss_imu *d)
{
	printf( "====================start dump_gnss_imu=============== \n");
	printf( "roll = %3.2lf \n",(d->roll * 360.0/32768.0));
	printf( "pitch = %3.2lf \n",(d->pitch * 360.0/32768.0));
	printf( "azimuth = %3.2lf \n",(d->azimuth * 360.0/32768.0));
	printf( "gyro_x[0] = %3.2lf \n",(d->gyro_x[0] * 300.0/32768.0));
	printf( "gyro_x[1] = %3.2lf \n",(d->gyro_x[1] * 300.0/32768.0));
	printf( "gyro_x[2] = %3.2lf \n",(d->gyro_x[2] * 300.0/32768.0));
	printf( "accel_x[0] = %3.2lf \n",(d->accel_x[0] * 12.0/32768.0));
	printf( "accel_x[1] = %3.2lf \n",(d->accel_x[1] * 12.0/32768.0));
	printf( "accel_x[2] = %3.2lf \n",(d->accel_x[2] * 12.0/32768.0));
	printf( "latitude = %3.7lf \n",d->latitude * 0.0000001);
	printf( "longitude = %3.7lf \n",d->longitude * 0.0000001);
	printf( "altitude = %3.7lf \n",d->altitude * 0.0000001);
	printf( "northvelocity = %3.5lf \n",d->northvelocity * 0.01 / 32768.0);
	printf( "eastvelocity = %3.5lf \n",d->eastvelocity * 0.01 / 32768.0 );
	printf( "groundvelocity = %3.5lf \n",d->groundvelocity * 0.01 / 32768.0);
	printf( "status = %d \n",d->status);
	printf( "polling[0] = %d \n",d->polling[0]);
	printf( "polling[1] = %d \n",d->polling[1]);
	printf( "polling[2] = %d \n",d->polling[2]);
	printf( "time = %d \n",d->time);
	printf( "type = %d \n",d->type);
	printf( "crc1 = %d \n",d->crc1);
	printf( "gpsweek = %d \n",d->gpsweek);
	printf( "crc2 = %d \n",d->crc2);
	printf( "====================endof dump_gnss_imu=============== \n");
	gps_to_utc(d->gpsweek,d->time);
}
int my_parser(uint8_t *data, int data_length)
{
	struct gnss_imu mydata;
	int x;
	if (data_length == sizeof(mydata)) {
		if(data[0] == 0xBD && data[1] == 0xDB && data[2] == 0x0B) 
		{
			memcpy(&mydata,data,data_length);
			for( x = 0; x < data_length; x++ ){
				printf( " 0x%02X ", data[ x ] );
			}
			gnssimu2json(&mydata);
			//dump_gnss_imu(&mydata);	
		}
	}
        printf( "\n\n\n" );
	return 0;
}
