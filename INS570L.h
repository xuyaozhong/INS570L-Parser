#ifndef __INS570L_H_
#define __INS570L_H_

struct gnss_imu {
	uint8_t head[3];
	int16_t roll; //横滚角 
	int16_t pitch; //俯仰角
	int16_t azimuth; //方位角
	int16_t gyro_x[3]; //陀螺xyz
	int16_t accel_x[3]; //加速度xyz
	int32_t latitude;//纬度
	int32_t longitude;//经度
	int32_t altitude;//海拔
	int16_t northvelocity;//北向速度
	int16_t eastvelocity;//东向速度
	int16_t groundvelocity;//地向速度
	uint8_t status;
	uint8_t dummy[6];
	uint16_t polling[3];//轮询数据
	uint32_t time;//时间
	uint8_t type;
	uint8_t crc1;
	uint32_t gpsweek;//GPS周
	uint8_t crc2;
}__attribute__((packed, aligned(1)));
#endif
