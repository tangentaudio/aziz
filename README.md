=============================================================================
AZIZ LED Ring Light Firmware
Copyright (C) 2013 Stephen Richardson (steve@tangentaudio.com)

http://www.tangentaudio.com/
=============================================================================

This is the firmware code to control the AZIZ LED light ring.  AZIZ is based
around an Atmel ATTiny1634 microcontroller, connected to a Texas Instruments
TLC59116 constant current LED driver.  Sixty four (64) LEDs are arranged in
a ring and driven by the driver chip in groups of four.  User control is
provided via three buttons, three colored LEDs, and two rotary encoder knobs.

Several adjustments are allowed, included brightness, fading, and pattern
selection.  Forthcoming user documentation will describe modes of operation
in more detail. 

Code builds in Atmel Studio V6.1 Beta.

See http://www.tangentaudio.com/electronics/aziz/ for more information.

=============================================================================

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.


EXCEPT THE FOLLOWING CODE: TWI_master.c and TWI_master.h which are

Copyright (c) 2012, Atmel Corporation All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

3. The name of ATMEL may not be used to endorse or promote products derived
from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
