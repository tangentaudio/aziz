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
 * encoder.h - reads and decodes quadrature-output rotary encoders
 *             interrupt-driven, uses PCINT0 interrupt
 * **************************************************************************
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#define ENCODER_DIVIDER 4

#define ENC_PIN_MASKED (PINA & 0x0F)

void encoder_init();
short int encoder_a_value();
void encoder_a_reset();
short int encoder_b_value();
void encoder_b_reset();

unsigned char encoder_changed();

#endif