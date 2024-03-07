/*
 * motor.h
 *
 *  Created on: Jan 9, 2024
 *      Author: Victor kalenda
 */

#ifndef APPLICATION_USER_MOTOR_H_
#define APPLICATION_USER_MOTOR_H_

/*
 *
 * CAN Protocol Commands for the VESC Motor Controller
 *
 */

void can_transmit_eid(uint32_t id, uint8_t *data, uint8_t len);

void buffer_append_int16(uint8_t* buffer, int16_t number, int32_t *index);
void buffer_append_int32(uint8_t* buffer, int32_t number, int32_t *index);
void buffer_append_float16(uint8_t* buffer, float number, float scale, int32_t *index);
void buffer_append_float32(uint8_t* buffer, float number, float scale, int32_t *index);

// Set the duty cycle of the motor as a percent, range -1.0 to 1.0
void comm_can_set_duty(uint8_t controller_id, float duty);

// Set the power going to the motors as amperage, range unknown (A)
void comm_can_set_current(uint8_t controller_id, float current);

// Set the delay required for the motor to automatically turn off
void comm_can_set_current_off_delay(uint8_t controller_id, float current, float off_delay);

void comm_can_set_current_brake(uint8_t controller_id, float current);

// Set the electrical RPM (ERPM) of the motor, range unknown
void comm_can_set_rpm(uint8_t controller_id, float rpm);

// Designed for servo type motors, range 0 - 360
void comm_can_set_pos(uint8_t controller_id, float pos);

/**
 * Set current relative to the minimum and maximum current limits.
 *
 * @param controller_id
 * The ID of the VESC to set the current on.
 *
 * @param current_rel
 * The relative current value, range [-1.0 1.0]
 */
void comm_can_set_current_rel(uint8_t controller_id, float current_rel);
/**
 * Same as above, but also sets the off delay
 */
void comm_can_set_current_rel_off_delay(uint8_t controller_id, float current_rel, float off_delay);

/**
 * Set brake current relative to the minimum current limit.
 *
 * @param controller_id
 * The ID of the VESC to set the current on.
 *
 * @param current_rel
 * The relative current value, range [0.0 1.0]
 */
void comm_can_set_current_brake_rel(uint8_t controller_id, float current_rel);

/**
 * Set handbrake current.
 *
 * @param controller_id
 * The ID of the VESC to set the handbrake current on.
 *
 * @param current_rel
 * The handbrake current value
 */
void comm_can_set_handbrake(uint8_t controller_id, float current);

/**
 * Set handbrake current relative to the minimum current limit.
 *
 * @param controller_id
 * The ID of the VESC to set the handbrake current on.
 *
 * @param current_rel
 * The relative handbrake current value, range [0.0 1.0]
 */
void comm_can_set_handbrake_rel(uint8_t controller_id, float current_rel);

// Safety to cut power from the motor
void comm_can_conf_battery_cut(uint8_t controller_id, uint8_t store, float start, float end);

// Shut down the motor controller
void comm_can_shutdown(uint8_t controller_id);

// Parameter Setting Commands

/**
 * Update current limits on VESC on CAN-bus.
 *
 * @param controller_id
 * ID of the VESC.
 *
 * @param store
 * Store parameters in emulated EEPROM (FLASH).
 *
 * @param min
 * Minimum current (negative value).
 *
 * @param max
 * Maximum current.
 */
void comm_can_conf_current_limits(uint8_t controller_id, uint8_t store, float min, float max);

/**
 * Update input current limits on VESC on CAN-bus.
 *
 * @param controller_id
 * ID of the VESC.
 *
 * @param store
 * Store parameters in emulated EEPROM (FLASH).
 *
 * @param min
 * Minimum current (negative value).
 *
 * @param max
 * Maximum current.
 */
void comm_can_conf_current_limits_in(uint8_t controller_id, uint8_t store, float min, float max);

/**
 * Update FOC ERPM settings on VESC on CAN-bus.
 *
 * @param controller_id
 * ID of the VESC.
 *
 * @param store
 * Store parameters in emulated EEPROM (FLASH).
 *
 * @param foc_openloop_rpm
 * Run in openloop below this ERPM in sensorless mode.
 *
 * @param foc_sl_erpm
 * Use sensors below this ERPM in sensored mode.
 */
void comm_can_conf_foc_erpms(uint8_t controller_id, uint8_t store, float foc_openloop_rpm, float foc_sl_erpm);

/**
 * Detect and apply FOC settings.
 *
 * @param controller_id
 * The ID of the VESC.
 *
 * @param activate_status_msgs
 * Activate CAN status messages on the target VESC on success.
 *
 * @param max_power_loss
 * Maximum accepted power losses.
 */
void comm_can_detect_apply_all_foc(uint8_t controller_id, uint8_t activate_status_msgs, float max_power_loss);

// Not sure what this is used for, but it looks useful
void comm_can_update_pid_pos_offset(int controller_id, float angle_now, uint8_t store);

/*
 *
 * Functions for Testing CAN protocol
 *
 */
/**
 * Check if a VESC on the CAN-bus responds.
 *
 * @param controller_id
 * The ID of the VESC.
 *
 * @return
 * True for success, false otherwise.
 */
uint8_t comm_can_ping(uint8_t controller_id);

/*
 *
 * Sensor Collection and Filtering Commands
 *
 */
void handle_throttle(uint32_t sensor_data, uint32_t *filtered_data, int32_t *acceleration);
void handle_brake(uint16_t t, float *brake_magnitude);

int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max);

#endif /* APPLICATION_USER_MOTOR_H_ */
