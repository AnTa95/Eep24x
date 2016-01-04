/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2014 Nasir Ahmad.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 *  @brief 24LC64 EEPROM library for LeafLabs Maple
 */
 
 
#ifndef _EEP24X_H_
#define _EEP24X_H_
#include "libmaple_types.h"
#include <i2c.h>

#define  DEV_ADDR		(0xA0 >> 1)
#define	 I2C_XFER_MODE	1			//0=100KHZ; 1=400KHZ
#define  MAX_WRITE_SIZE	128

class Eep24x {	
	public:
		Eep24x(uint8);
		
		void readPage(uint16, uint8*, uint8);
		uint8 read(uint16);
		

		void writePage(uint16, uint8*, uint8);
		void write(uint16, uint8);
		
	private:
		i2c_dev *_dev;
};

#endif
