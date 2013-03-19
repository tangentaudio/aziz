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
 * led_driver.c - basic driver to control TI TLC59116 I2C LED driver chip
 *          
 * **************************************************************************
 */

#include <avr/io.h>
#include "TWI_master.h"
#include "mode_leds.h"
#include "led_driver.h"

// this lookup table remaps the LEDs, which were wired to make layout easier and not to make any sort of logical sense
// channel 0..7 inner ring LEDs
//         8..15 outer ring LEDs
const unsigned char m_led_map[] = {0x01,0x03,0x05,0x06,0x08,0x0A,0x0C,0x0E,0x00,0x02,0x04,0x07,0x09,0x0B,0x0D,0x0F};

static struct s_led_engine m_led_engine[LED_CHANNELS];

void led_driver_init()
{
	// initialize MODE1 register
	led_driver_write(REG_MODE1, MODE1_ALLCALL);

	// set all channels to PWM brightness, no blink capability
	led_driver_write(REG_LEDOUT0, LEDOUT_BRIGHT);
	led_driver_write(REG_LEDOUT1, LEDOUT_BRIGHT);
	led_driver_write(REG_LEDOUT2, LEDOUT_BRIGHT);
	led_driver_write(REG_LEDOUT3, LEDOUT_BRIGHT);
	
	for (int i=0; i<LED_CHANNELS; i++) {
		m_led_engine[i].current = 0;
		m_led_engine[i].inc = 0;
		m_led_engine[i].steps = 0;
		
		led_driver_set_pwm(i, 0);
	}		
}

void led_driver_write(unsigned char addr, unsigned char byte)
{
	char success = 0;
	unsigned char data[2];
	
	data[0] = addr;
	data[1] = byte;
	
	success = write_data(data, 2);
	if (!success) {
		// i2c write error, halt and flash mode LEDs
		while(1) {
			LED1_ON;
			LED2_ON;
			LED3_ON;
			__delay_cycles(8000);
			LED1_OFF;
			LED2_OFF;
			LED3_OFF;
			__delay_cycles(8000);
		}
	}
}

void led_driver_set_pwm(unsigned char channel, unsigned char pwm)
{
	led_driver_write(REG_PWM0 + m_led_map[channel & 0x0F], pwm);
}



void led_driver_set_target(unsigned char channel, short int target, unsigned char steps)
{
	struct s_led_engine* led = &m_led_engine[channel % 16];
	
	target *= FIXED_MULT;
	
	if (steps < 1)
		steps = 1;
		
	led->steps = steps;

	led->inc = (target - led->current) / steps;
}

unsigned char led_driver_poll()
{
	unsigned char any_updated = 0;
	
	for (unsigned char channel=0; channel<LED_CHANNELS; channel++) {
		struct s_led_engine* led = &m_led_engine[channel];
		
		if (led->steps) {
			led->current += led->inc;
			led_driver_write(REG_PWM0 + m_led_map[channel], (unsigned char) (led->current / FIXED_MULT));
			led->steps--;
			any_updated = 1;
		}
	}
	return any_updated;
}