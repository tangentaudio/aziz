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
 * encoder.c - reads and decodes quadrature-output rotary encoders
 *             interrupt-driven, uses PCINT0 interrupt
 * **************************************************************************
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include "encoder.h"

// quadrature encoder lookup logic
// X states are not valid transitions, and currently map to no count
//
//      last  new
//      A  B  A  B
// bits 3  2  1  0    RESULT
// -------------------------
//      0  0  0  0    0
//      0  0  0  1    -1
//      0  0  1  0    +1
//      0  0  1  1    X
//      0  1  0  0    +1
//      0  1  0  1    0
//      0  1  1  0    X
//      0  1  1  1    -1
//		1  0  0  0    -1
//      1  0  0  1    X
//      1  0  1  0    0
//      1  0  1  1    +1
//      1  1  0  0    X
//      1  1  0  1    +1
//      1  1  1  0    -1
//      1  1  1  1    0
const short int m_enc_lut[] = { 0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0 };

static unsigned char m_encoder_changed = 0;
static short int m_encoder_a_count = 0;
static short int m_encoder_b_count = 0;

static unsigned char m_last_in;


void encoder_init()
{
	PORTA |= 0x0F;
	PUEA |= 0x0F;
	DDRA &= 0xF0;
	
	m_last_in = ENC_PIN_MASKED;
	
	PCMSK0 = (1<<PCINT0) | (1<<PCINT1) | (1<<PCINT2) | (1<<PCINT3);
	GIMSK |= (1<<PCIE0);
}

short int encoder_a_value()
{
	short int count;
	
	cli();
	count = m_encoder_a_count;
	sei();
	
	return count / ENCODER_DIVIDER;
}

void encoder_a_reset()
{
	cli();
	m_encoder_a_count %= ENCODER_DIVIDER;
	sei();
}

short int encoder_b_value()
{
	short int count;
	cli();
	count = m_encoder_b_count;
	sei();
	return count / ENCODER_DIVIDER;
}

void encoder_b_reset()
{
	cli();
	m_encoder_b_count %= ENCODER_DIVIDER;
	sei();
}

unsigned char encoder_changed()
{
	unsigned char changed;
	cli();
	changed = m_encoder_changed;
	m_encoder_changed = 0;
	sei();
	
	return changed;
}


ISR(PCINT0_vect)
{
	unsigned char new_in = ENC_PIN_MASKED;
	
	if (new_in != m_last_in) {
		unsigned char lookup_a = (new_in & 0x03) | ((m_last_in & 0x03)<<2);
		unsigned char lookup_b = ((new_in & 0x0C)>>2) | (m_last_in & 0x0C);
		
		m_encoder_a_count += m_enc_lut[lookup_a];
		m_encoder_b_count += m_enc_lut[lookup_b];

		m_last_in = new_in;
		m_encoder_changed = 1;
	}
}
