/* **************************************************************************
 *     _     _____  _   _____
 *    / \   |__  / | | |__  /    
 *   / _ \    / /  | |   / /     
 *  / ___ \  / /_  | |  / /_     
 * /_/   \_\/____| |_| /____|  LED RING LIGHT
 *
 * Copyright (C) 2013 Stephen Richardson (steve@tangentaudio.com)
 * http://www.tangentaudio.com/
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * **************************************************************************
 * MCU Target: Atmel ATTiny1634
 * Tool Chain: AtmelStudio 6.1 Beta
 * **************************************************************************
 * led_driver.h - basic driver to control TI TLC59116 I2C LED driver chip
 *          
 * **************************************************************************
 */

#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

enum tlc59116_reg {
	REG_MODE1 = 0x00,
	REG_MODE2 = 0x01,
	REG_PWM0 = 0x02,
	REG_PWM1 = 0x03,
	REG_PWM2 = 0x04,
	REG_PWM3 = 0x05,
	REG_PWM4 = 0x06,
	REG_PWM5 = 0x07,
	REG_PWM6 = 0x08,
	REG_PWM7 = 0x09,
	REG_PWM8 = 0x0A,
	REG_PWM9 = 0x0B,
	REG_PWM10 = 0x0C,
	REG_PWM11 = 0x0D,
	REG_PWM12 = 0x0E,
	REG_PWM13 = 0x0F,
	REG_PWM14 = 0x10,
	REG_PWM15 = 0x11,
	REG_GRPPWM = 0x12,
	REG_GRPFREQ = 0x13,
	REG_LEDOUT0 = 0x14,
	REG_LEDOUT1 = 0x15,
	REG_LEDOUT2 = 0x16,
	REG_LEDOUT3 = 0x17,
	REG_SUBADR1 = 0x18,
	REG_SUBADR2 = 0x19,
	REG_SUBADR3 = 0x1A,
	REG_ALLCALLADR = 0x1B,
	REG_IREF = 0x1C,
	REG_EFLAG1 = 0x1D,
	REG_EFLAG2 = 0x1E
};

enum tlc59116_mode1 {
	MODE1_AI2 = 0x80,
	MODE1_AI1 = 0x40,
	MODE1_AI0 = 0x20,
	MODE1_SLEEP = 0x10,
	MODE1_SUB1 = 0x08,
	MODE1_SUB2 = 0x04,
	MODE1_SUB3 = 0x02,
	MODE1_ALLCALL = 0x01
};

enum tlc59116_mode2 {
	MODE2_EFCLR = 0x80,
	MODE2_DMBLNK = 0x20,
	MODE2_OCH = 0x08
};


enum tlc59116_ledlevel {
	LEDOUT_OFF = 0x00,
	LEDOUT_FULLON = 0x55,
	LEDOUT_BRIGHT = 0xAA,
	LEDOUT_BRIGHTBLINK = 0xFF
};


#define LED_CHANNELS 16

#define FIXED_MULT	100

struct s_led_engine {
	short int current;
	short int inc;
	unsigned char steps;
};


void led_driver_init();
void led_driver_write(unsigned char addr, unsigned char byte);
void led_driver_set_pwm(unsigned char channel, unsigned char pwm);
void led_driver_set_target(unsigned char channel, short int target, unsigned char steps);
unsigned char led_driver_poll();

#endif
