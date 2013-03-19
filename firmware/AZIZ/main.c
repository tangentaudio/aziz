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
 * main.c - main round robin loop and overall logic
 *
 * **************************************************************************
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "timer.h"
#include "TWI_master.h"
#include "mode_leds.h"
#include "buttons.h"
#include "encoder.h"
#include "led_driver.h"
#include "led_pattern.h"

#define MODE_ROTATE			1
#define MODE_BRIGHT			2
#define MODE_FADE			3

static unsigned char m_power_on = 0;

static unsigned char m_mode = MODE_ROTATE;
static short int m_pattern = PATTERN_DEFAULT;
static short int m_rotate = ROTATE_DEFAULT;
static short int m_bright = BRIGHT_DEFAULT;
static short int m_fade = FADE_DEFAULT;


void init()
{
	// write unlock signature to CCP for write to CLKPR below
	CCP = 0xD8;
	// no prescaler on clock, run at full 8MHz
	CLKPR = 0x00;
	
	// initialize subsystems
	timer_init();
	buttons_init();
	encoder_init();
	mode_leds_init();
	twi_init();
	led_driver_init();
	led_pattern_init();
	
	// enable interrupts
	sei();
}	

ISR(WDT_vect)
{
	// write unlock signature to CCP for write to change watchdog below
	CCP = 0xD8;
	WDTCSR = (1<<WDIE) | (1<<WDE) | (1<<WDP2);
	
	LED3_ON;
	__delay_cycles(100000);
	LED3_OFF;
	
	if ( (BUTTON_PIN_MASKED & BUTTON3) == 0) {
		m_power_on = 1;
	}
}

void power_down()
{
	timer_stop();

	// turn LEDs off and allow them to fade out
	led_pattern_set(0, 0, 0, 0);
	while (led_driver_poll()) {
		__delay_cycles(10000);
	}
	
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	
	m_power_on = 0;
	
	while (!m_power_on) {
		WDTCSR = (1<<WDIE) | (1<<WDE) | (1<<WDP2) | (1<<WDP1) | (1<<WDP0);
	
		set_sleep_mode(SLEEP_MODE_PWR_DOWN);
		sleep_mode();
	}		

	// after wakeup
	
	// write unlock signature to CCP for write to disable watchdog below
	CCP = 0xD8;
	WDTCSR = 0;	
	
	timer_start();
}


void update_mode_leds(unsigned int tick)
{
	if (m_mode == MODE_BRIGHT) {
		LED1_OFF;
		LED2_OFF;
		LED3_ON;
	} else if (m_mode == MODE_FADE) {
		// flash fade mode LED if not at default value
		LED1_OFF;
		if (tick % 20 == 0 || m_fade == FADE_DEFAULT)
			LED2_ON;
		else
			LED2_OFF;
		LED3_OFF;
	} else if (m_mode == MODE_ROTATE) {
		LED1_ON;
		LED2_OFF;
		LED3_OFF;
	}
}

void set_mode(unsigned char new_mode)
{
	m_mode = new_mode;
}


void encoder_service(unsigned int tick)
{
	if (encoder_changed()) {
		short int enc_a = encoder_a_value();
		short int enc_b = encoder_b_value();
		
		if (enc_a != 0) {
			encoder_a_reset();
			m_pattern += enc_a;
			
			if (m_pattern < 0)
				m_pattern = 0;
			if (m_pattern > led_pattern_count())
				m_pattern = led_pattern_count();
				
			m_fade = FADE_DEFAULT;
		}
		
		if (enc_b != 0) {
			encoder_b_reset();
			
			if (m_mode == MODE_ROTATE) {
				// note, flips encoder direction
				m_rotate -= enc_b;

				if (m_rotate < 0)
					m_rotate = ROTATE_STEPS + m_rotate;
				
				if (m_rotate >= ROTATE_STEPS)
					m_rotate -= ROTATE_STEPS;
				
			} else if (m_mode == MODE_BRIGHT) {
				// note, flips encoder direction
				m_bright -= enc_b;

				if (m_bright < 1)
					m_bright = 1;
				
				if (m_bright >= BRIGHT_STEPS )
					m_bright = BRIGHT_STEPS - 1;
				
			} else if (m_mode == MODE_FADE) {
				// note, flips encoder direction
				m_fade -= enc_b;

				if (m_fade < 0)
				m_fade = 0;
				
				if (m_fade > FADE_STEPS )
				m_fade = FADE_STEPS;
			}
		}
		led_pattern_set(m_pattern, m_rotate, m_bright, m_fade);
		update_mode_leds(tick);

	}
}


void button_service(unsigned int tick)
{
	static unsigned char btns;
	static unsigned int btn2_tick;
	static unsigned int btn3_tick;
		
	if (buttons_changed(&btns)) {
			
		if (btns & BUTTON1) {
			set_mode(MODE_ROTATE);
		} else if (btns & BUTTON2) {
			btn2_tick = tick;
			set_mode(MODE_FADE);
		} else if (btns & BUTTON3) {
			btn3_tick = tick;
			set_mode(MODE_BRIGHT);
		}
		update_mode_leds(tick);
	} else {
		// hold down fade button to reset to default value
		if ((btns & BUTTON2) && (tick - btn2_tick > 50)) {
			m_fade = FADE_DEFAULT;
			led_pattern_set(m_pattern, m_rotate, m_bright, m_fade);
			update_mode_leds(tick);
		}
			
		// hold down brightness button to power down
		if (btns & BUTTON3) {
			if (tick - btn3_tick > 100) {
				power_down();

				// pick up after powerdown
				m_pattern = PATTERN_DEFAULT;
				m_rotate = ROTATE_DEFAULT;
				m_bright = BRIGHT_DEFAULT;
				m_fade = FADE_DEFAULT;
				led_pattern_set(m_pattern, m_rotate, m_bright, m_fade);
				update_mode_leds(tick);
				
				// clear the tick				
				btn3_tick = tick;
			} 								
		}
		
	}
}




int main(void)
{
	init();

	power_down();

	set_mode(MODE_BRIGHT);
	led_pattern_set(m_pattern, m_rotate, m_bright, m_fade);
				
    while(1) {
		// snapshot of system tick for this iteration through round robin loop
		static unsigned int tick = 0;
		static unsigned int last_tick = 0;
		
		if (m_power_on) {
			cli();
			tick = g_sys_tick;
			sei();
			
			if (tick % 10 == 0) {
				update_mode_leds(tick);
			}
			
			if (tick != last_tick) {
				led_driver_poll();	
			}
			
			encoder_service(tick);
			button_service(tick);
			last_tick = tick;
		}			
	}																			
}