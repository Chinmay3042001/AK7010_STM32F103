/*
 * ak7010.h
 *
 *  Created on: Jul 20, 2022
 *      Author: crmar
 */

#ifndef AK7010_H_
#define AK7010_H_



typedef struct MOTOR_FEEDBACK{
	float position;
	float speed;
	float current;
	int temperature;

}MOTOR_FEEDBACK;

MOTOR_FEEDBACK motor_data(uint8_t d[8]);
#endif /* AK7010_H_ */
