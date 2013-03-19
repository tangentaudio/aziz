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
 * led_pattern.c - LED ring pattern structures
 *                 logic to set patterns, dim, rotate, and fade patterns
 *          
 * **************************************************************************
 */

#include "led_pattern.h"
#include "led_driver.h"

const struct s_led_pattern m_patterns[] = {
	{
		// all LEDs on full
		PATTERN,
		{
			0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	// inner ring
			0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF		// outer ring
		},		
		ROTATE_NONE,									// rotate mode
		DIM_FADE_NONE									// dim & fade mode
	},

	{
		// outer ring dim, inner ring full
		PATTERN,
		{
			0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	// inner ring
			0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F		// outer ring
		},
		ROTATE_NONE,									// rotate mode
		DIM_FADE_NONE									// dim & fade mode
	},
	
	{
		// inner ring on full
		PATTERN,
		{
			0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	// inner ring
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00		// outer ring
		},
		ROTATE_NONE,									// rotate mode
		DIM_FADE_NONE									// dim & fade mode
	},

	{
		// inner ring dim, outer ring full
		PATTERN,
		{
			0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,	// inner ring
			0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	// outer ring
		},
		ROTATE_NONE,									// rotate mode
		DIM_FADE_NONE									// dim & fade mode
	},

	{
		// outer ring on full
		PATTERN,
		{
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// inner ring
			0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	// outer ring
		},
		ROTATE_NONE,									// rotate mode
		DIM_FADE_NONE									// dim & fade mode
	},


	{
		// 1/8 cross
		PATTERN,
		{
			0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,	// inner ring
			0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,	// outer ring
		},
		ROTATE_EIGHTH,									// rotate mode
		DIM_FADE_NONE									// dim & fade mode
	},
	
	{
		// 1/4 stripes
		PATTERN,
		{
			0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,	// inner ring
			0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,	// outer ring
		},
		ROTATE_EIGHTH,									// rotate mode
		DIM_FADE_NONE									// dim & fade mode
	},

	{
		// 1/8 stripes
		PATTERN,
		{
			0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,	// inner ring
			0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,	// outer ring
		},
		ROTATE_EIGHTH,									// rotate mode
		DIM_FADE_NONE									// dim & fade mode
	},

	{
		// 1/8 circle spot
		PATTERN,
		{
			0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// inner ring
			0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// outer ring
		},
		ROTATE_EIGHTH,									// rotate mode
		DIM_FADE_NONE									// dim & fade mode
	},

	{
		// 1/4 circle spot
		PATTERN,
		{
			0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,	// inner ring
			0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,	// outer ring
		},
		ROTATE_EIGHTH,									// rotate mode
		DIM_FADE_NONE									// dim & fade mode
	},

	{
		// 1/2 circle spot
		PATTERN,
		{
			0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,	// inner ring
			0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,	// outer ring
		},
		ROTATE_EIGHTH,									// rotate mode
		DIM_FADE_NONE									// dim & fade mode
	},

	
	///////////////////////////////////////////////////////////////////////
	// structure fence
	{
		PATTERN_END,
		{
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// inner ring
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00		// outer ring
		},
		ROTATE_NONE,									// rotate mode
		DIM_FADE_NONE,									// dim & fade mode
	}
};

static unsigned char m_total_patterns = 0;
static unsigned char m_current_pattern = 0;

const unsigned char m_bright_curve[BRIGHT_STEPS] = { 0, 7, 8, 10, 15, 20, 30, 40, 50, 60, 70, 80, 100 };

void led_pattern_init()
{
	// iterate through pattern structure, find the fence, count total number
	for (m_total_patterns=0; m_patterns[m_total_patterns].pattern_valid; m_total_patterns++);
	m_total_patterns--;
}

unsigned char led_pattern_count()
{
	return m_total_patterns;
}

unsigned char led_pattern_set(unsigned char num, unsigned char rotate, unsigned char bright, unsigned char fade)
{
	const struct s_led_pattern* pp;
	
	if (num > m_total_patterns)
		m_current_pattern = m_total_patterns;
	else	
		m_current_pattern = num;
	
	pp = &m_patterns[m_current_pattern];


	for(unsigned char chan=0; chan<8; chan++) {
		unsigned char rot_chan = 0;
		unsigned int pwm_val;
		unsigned int bright_val = m_bright_curve[bright];
		unsigned int fade_inner_val = (unsigned int)fade * FADE_MULT;
		unsigned int fade_outer_val = 100 - fade_inner_val;
		
		if (fade_inner_val > 50)
			fade_inner_val = 50;
		
		if (fade_outer_val > 50)
			fade_outer_val = 50;
		
		if (pp->rotate == ROTATE_EIGHTH)
			rot_chan = (chan + rotate) % 8;

		pwm_val = ((unsigned int)pp->leds[rot_chan] * bright_val) / 100;
		pwm_val = (pwm_val * fade_inner_val) / 50;
		led_driver_set_target(chan, pwm_val, RAMP_STEPS);	

		pwm_val = ((unsigned int)pp->leds[rot_chan + 8] * bright_val) / 100;
		pwm_val = (pwm_val * fade_outer_val) / 50;
		led_driver_set_target(chan + 8, pwm_val, RAMP_STEPS);
	}
	
	return m_current_pattern;
}