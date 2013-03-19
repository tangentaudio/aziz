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
 * timer.c - basic interrupt-driven system tick timer using TIMER0
 *          
 * **************************************************************************
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

volatile unsigned int g_sys_tick = 0;

void timer_stop()
{
	TIMSK &= ~(1<<TOIE0);
}

void timer_start()
{
	TIMSK |= (1<<TOIE0);
}

void timer_init()
{
	TCCR0B |= (1<<CS02);

	timer_start();	
}

ISR(TIMER0_OVF_vect)
{
	++g_sys_tick;
}
