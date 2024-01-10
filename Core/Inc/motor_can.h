/*
 * motor_can.h
 *
 *  Created on: Jan 9, 2024
 *      Author: Victor kalenda
 */

#ifndef APPLICATION_USER_MOTOR_CAN_H_
#define APPLICATION_USER_MOTOR_CAN_H_

void can_transmit_eid(uint32_t id, const uint8_t *data, uint8_t len);

void buffer_append_int16(uint8_t* buffer, int16_t number, int32_t *index);
void buffer_append_int32(uint8_t* buffer, int32_t number, int32_t *index);
void buffer_append_float16(uint8_t* buffer, float number, float scale, int32_t *index);
void buffer_append_float32(uint8_t* buffer, float number, float scale, int32_t *index);


void comm_can_set_duty(uint8_t controller_id, float duty);
void comm_can_set_current(uint8_t controller_id, float current);\
void comm_can_set_current_off_delay(uint8_t controller_id, float current, float off_delay);
void comm_can_set_current_brake(uint8_t controller_id, float current);
void comm_can_set_rpm(uint8_t controller_id, float rpm);
void comm_can_set_pos(uint8_t controller_id, float pos);
void comm_can_set_current_rel(uint8_t controller_id, float current_rel);
void comm_can_set_current_rel_off_delay(uint8_t controller_id, float current_rel, float off_delay);
void comm_can_set_current_brake_rel(uint8_t controller_id, float current_rel);
void comm_can_set_handbrake(uint8_t controller_id, float current);
void comm_can_set_handbrake_rel(uint8_t controller_id, float current_rel);


#endif /* APPLICATION_USER_MOTOR_CAN_H_ */
