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
 * buttons.h - handle three user interface buttons
 *             interrupt driven, uses PCINT2 interrupt
 *          
 * **************************************************************************
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#define BUTTON1	0x04
#define BUTTON2 0x10
#define BUTTON3 0x20
#define BUTTON_MASK (BUTTON1 | BUTTON2 | BUTTON3)

#define BUTTON_PIN_MASKED (PINC & BUTTON_MASK)

// why isn't this in iotn1634.h? it says "reserved" in that header.
#define PCMSK2  _SFR_IO8(0x29)

void buttons_init();
unsigned char buttons_changed(unsigned char* btn);
unsigned char buttons_raw();

#endif