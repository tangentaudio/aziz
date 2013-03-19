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
 * mode_leds.c - init and control for the mode LEDs
 *          
 * **************************************************************************
 */

#include <avr/io.h>
#include "mode_leds.h"

void mode_leds_init()
{
	PORTA &= 0x0F;
	PUEA &= 0x0F;
	DDRA |= 0xF0;
	
	PORTB = 0x00;
	PUEB = 0x00;
	DDRB = 0x09;
	
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
}

