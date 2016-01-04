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

#include "Eep24x.h"

Eep24x::Eep24x(uint8 i2c_dev){
	switch (i2c_dev){
		case 1:
			_dev = I2C1;
			break;
		default:			
		case 2:
			_dev = I2C2;
			break;
	}
	i2c_master_enable(_dev, I2C_XFER_MODE);
}

uint8 Eep24x::read(uint16 addr){
	uint8 data[1];
	readPage(addr, data, 1);	
	return data[0];
}

void Eep24x::readPage(uint16 addr, uint8 *buffer, uint8 length){
	i2c_msg msgs[2];
	uint8 ee_addr[2];
	
	// First address of the register to write
	ee_addr[0] = (uint8)(addr >> 8);
	ee_addr[1] = (uint8)(addr & 0xFF);	
	
	// Write command
	msgs[0].addr = DEV_ADDR;
	msgs[0].flags = 0;
	msgs[0].length = 2;
	msgs[0].data = ee_addr;	
	
	// Read command to the read buffer
	msgs[1].addr = DEV_ADDR;
	msgs[1].flags = I2C_MSG_READ;
	msgs[1].data = buffer;
	msgs[1].length = length;	

	i2c_master_xfer(_dev, msgs, 2, 50);	
}

void Eep24x::writePage(uint16 addr, uint8* data, uint8 length){
	i2c_msg msgs[1];
	uint8 buffer[MAX_WRITE_SIZE + 2]; //Max page size to write is 128byte + 2 address byte
		
	// First 2 bytes contains the address of the register where to start writing	
	buffer[0] = (uint8)(addr >> 8);
	buffer[1] = (uint8)(addr & 0xFF);
	
	length = (length < MAX_WRITE_SIZE) ? length : MAX_WRITE_SIZE;
	for (uint8 i=0; i < length; i++){
		buffer[2 + i] = data[i];
	}
	
	msgs[0].addr = DEV_ADDR;
	msgs[0].flags = 0;
	msgs[0].data = buffer;
	msgs[0].length = length + 2;
	
	i2c_master_xfer(_dev, msgs, 1, 50);	//Timeout 50ms	
}

void Eep24x::write(uint16 addr, uint8 value){
	uint8 data[] = { value };	
	writePage(addr, data, 1);
}

