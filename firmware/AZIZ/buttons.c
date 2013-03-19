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
 * buttons.c - handle three user interface buttons
 *             interrupt driven, uses PCINT2 interrupt
 *          
 * **************************************************************************
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include "buttons.h"

static unsigned char m_buttons_changed;
unsigned char m_new_in;
static unsigned char m_last_in;

void buttons_init()
{
	PORTC |= BUTTON_MASK;
	PUEC |= BUTTON_MASK;
	DDRA &= ~BUTTON_MASK;
	
	PCMSK2 |= (1<<PCINT17) | (1<<PCINT16) | (1<<PCINT14);
	GIMSK |= (1<<PCIE2);

	m_new_in = BUTTON_PIN_MASKED;
	m_last_in = m_new_in;
}


unsigned char buttons_raw()
{
	unsigned char new_in = BUTTON_PIN_MASKED;
	return (~new_in) & BUTTON_MASK;
}

ISR(PCINT2_vect)
{
	m_new_in = BUTTON_PIN_MASKED;
	
	if (m_new_in != m_last_in) {
		m_last_in = m_new_in;
		m_buttons_changed = 1;		
	}
}

unsigned char buttons_changed(unsigned char* btn)
{
	unsigned char changed;
	cli();
	changed = m_buttons_changed;
	m_buttons_changed = 0;
	sei();

	*btn = (~m_new_in) & BUTTON_MASK;

	return changed;
}