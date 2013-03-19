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
 * led_pattern.h - LED ring pattern structures
 *                 logic to set patterns, dim, rotate, and fade patterns
 *          
 * **************************************************************************
 */

#ifndef LED_PATTERN_H_
#define LED_PATTERN_H_

#define PATTERN_DEFAULT	0

#define PATTERN			1
#define PATTERN_END		0

#define ROTATE_NONE		0
#define ROTATE_EIGHTH	1
#define ROTATE_QUARTER	2

#define DIM_FADE_NONE	0

#define ROTATE_DEFAULT	0
#define ROTATE_STEPS	8

#define BRIGHT_STEPS	13
#define BRIGHT_MULT		(100 / BRIGHT_STEPS)
#define BRIGHT_DEFAULT	(BRIGHT_STEPS / 2)

#define FADE_STEPS		10
#define FADE_MULT		(100 / FADE_STEPS)
#define FADE_DEFAULT	(FADE_STEPS / 2)

#define RAMP_STEPS		32

struct s_led_pattern {
	unsigned char pattern_valid;
	unsigned char leds[16];
	unsigned char rotate;
	unsigned char dim_fade_mode;
};

void led_pattern_init();
unsigned char led_pattern_set(unsigned char num, unsigned char rotate, unsigned char bright, unsigned char fade);
unsigned char led_pattern_count();


#endif