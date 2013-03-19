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
 * mode_leds.h - init and control for the mode LEDs
 *          
 * **************************************************************************
 */

#ifndef MODE_LEDS_H_
#define MODE_LEDS_H_

#define LED1 (0x20)
#define LED2 (0x40)
#define LED3 (0x08)

#define LED1_ON		PORTA &= ~LED1
#define LED1_OFF	PORTA |= LED1
#define LED2_ON		PORTA &= ~LED2
#define LED2_OFF	PORTA |= LED2
#define LED3_ON		PORTB &= ~LED3
#define LED3_OFF	PORTB |= LED3

void mode_leds_init();

#endif