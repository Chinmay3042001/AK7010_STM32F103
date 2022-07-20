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

/** RECIEVE **/
MOTOR_FEEDBACK motor_data(uint8_t d[8]){
	MOTOR_FEEDBACK mot_data;
	mot_data.position =  (float)((d[0] << 8 | d[1])*0.1f);
	mot_data.speed = (float)((d[2] << 8 | d[3])*10.0f);
	mot_data.current = (float)((d[4]<<8|d[5])*0.01f);
	mot_data.temperature = d[7];
}

/** SEND **/
int CAN_PACKET_SET_DUTY = 0;
int CAN_PACKET_SET_CURRENT = 1;
int CAN_PACKET_SET_CURRENT_BRAKE = 2; // Current brake mode
int CAN_PACKET_SET_RPM = 3; //Velocity mode
int CAN_PACKET_SET_POS = 4; // Position mode
int CAN_PACKET_SET_ORIGIN_HERE = 5; //Set origin mode
int CAN_PACKET_SET_POS_SPD = 6; //Position Velocity loop mode





//CanTxMsg TxMessage;
//TxMessage.StdId = 0;
//TxMessage.IDE = CAN_ID_EXT;
//TxMessage.ExtId = id;
//TxMessage.RTR = CAN_RTR_DATA;
//TxMessage.DLC = len;
////memcpy(txmsg.data8, data, len);
//for(i=0;i<len;i++)
//TxMessage.Data[i]=data[i];
//CAN_Transmit(CHASSIS_CAN, &TxMessage);
}

void buffer_append_int32(uint8_t* buffer, int32_t number, int32_t *index) {
buffer[(*index)++] = number >> 24;
buffer[(*index)++] = number >> 16;
buffer[(*index)++] = number >> 8;
buffer[(*index)++] = number;
}


void buffer_append_int16(uint8_t* buffer, int16_t number, int16_t *index) {
buffer[(*index)++] = number >> 8;
buffer[(*index)++] = number;
}


void comm_can_set_duty(uint8_t controller_id, float duty) {
int32_t send_index = 0;
uint8_t buffer[4];
buffer_append_int32(buffer, (int32_t)(duty * 100000.0), &send_index);
comm_can_transmit_eid(controller_id |((uint32_t)CAN_PACKET_SET_DUTY << 8), buffer, send_index);
}


void comm_can_set_current(uint8_t controller_id, float current) {
int32_t send_index = 0;
uint8_t buffer[4];
buffer_append_int32(buffer, (int32_t)(current * 1000.0), &send_index);
comm_can_transmit_eid(controller_id |
((uint32_t)CAN_PACKET_SET_CURRENT << 8), buffer, send_index);
}

void comm_can_set_cb(uint8_t controller_id, float current) {
int32_t send_index = 0;
uint8_t buffer[4];
buffer_append_int32(buffer, (int32_t)(current * 1000.0), &send_index);
comm_can_transmit_eid(controller_id |
((uint32_t)CAN_PACKET_SET_CURRENT_BRAKE << 8), buffer, send_index);
}


void comm_can_set_rpm(uint8_t controller_id, float rpm) {
int32_t send_index = 0;
uint8_t buffer[4];
buffer_append_int32(buffer, (int32_t)rpm, &send_index);
comm_can_transmit_eid(controller_id |
((uint32_t)CAN_PACKET_SET_RPM << 8), buffer, send_index);
}



void comm_can_set_pos(uint8_t controller_id, float pos) {
int32_t send_index = 0;
uint8_t buffer[4];
buffer_append_int32(buffer, (int32_t)(pos * 1000000.0), &send_index);
comm_can_transmit_eid(controller_id |
((uint32_t)CAN_PACKET_SET_POS << 8), buffer, send_index);
}



void comm_can_set_origin(uint8_t controller_id, uint8_t set_origin_mode) {
  int32_t send_index = 0;
  uint8_t buffer[4];
comm_can_transmit_eid(controller_id |
((uint32_t) CAN_PACKET_SET_ORIGIN_HERE << 8), buffer, send_index);
}



void comm_can_set_pos_spd(uint8_t controller_id, float pos,int16_t spd, int16_t RPA ) {
int32_t send_index = 0;
int16_t send_index1 = 0;
uint8_t buffer[4];
buffer_append_int32(buffer, (int32_t)(pos * 10000.0), &send_index);
buffer_append_int16(buffer,spd, & send_index1);
buffer_append_int16(buffer,RPA, & send_index1);
comm_can_transmit_eid(controller_id |((uint32_t)CAN_PACKET_SET_POS_SPD << 8), buffer, send_index);
}




