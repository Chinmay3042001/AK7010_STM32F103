/*
 * ak7010.c
 *
 *  Created on: Jul 20, 2022
 *      Author: crmar
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include "ak7010.h"


MOTOR_FEEDBACK motor_data(uint8_t d[8]){
	MOTOR_FEEDBACK mot_data;
	mot_data.position =  (float)((d[0] << 8 | d[1])*0.1f);
	mot_data.speed = (float)((d[2] << 8 | d[3])*10.0f);
	mot_data.current = (float)((d[4]<<8|d[5])*0.01f);
	mot_data.temperature = d[7];
}



