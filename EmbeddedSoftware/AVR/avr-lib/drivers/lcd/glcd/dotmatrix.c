#include "dotmatrix.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#include <avr/pgmspace.h>

//Some parts of the code is from proycon avrlib written by Pascal Stang:
//*****************************************************************************
//
// File Name	: 'glcd.c'
// Title		: Graphic LCD API functions
// Author		: Pascal Stang - Copyright (C) 2002
// Date			: 5/30/2002
// Revised		: 5/30/2002
// Version		: 0.5
// Target MCU	: Atmel AVR
// Editor Tabs	: 4
//
// NOTE: This code is currently below version 1.0, and therefore is considered
// to be lacking in some functionality or documentation, or may not be fully
// tested.  Nonetheless, you can expect most functions to work.
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************
#ifndef GRAPHICS_WIDTH
#error GRAPHICS_WIDTH, GRAPHICS_HEIGHT must be defined
#endif

#define OUTPUT	0
#define INPUT	1

volatile GrLcdStateType GrLcdState;
uint8_t	dotmatrixFramebuf[8][dotmatrixSIZEX/8];
uint8_t dotmatrixRowCounter=0;

/* Write a byte on SPI */
void dotmatrixSPIWrite(uint8_t data) {
	uint8_t dummy = 0;
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	// write data
	dummy = UDR0;
	UDR0 = data;
	waitspi();
}

void dotmatrixSetColor(uint8_t color){
  GrLcdState.color=color;
}

uint8_t dotmatrixGetColor(void){
  return GrLcdState.color;
}

/* Sets data into framebuffer, data arrives in a byte as a column */
void dotmatrixSetData(uint8_t Data)
{
	/* Which ledmodule */
	uint8_t module = GrLcdState.lcdXAddr>>3;
	/* Which column in ledmodule */
	uint8_t column = GrLcdState.lcdXAddr%8;
	/* Which row */
//	uint8_t row = GrLcdState.lcdYAddr%8;

	/* Check panel size */
	if ((column < dotmatrixSIZEY) && (module < dotmatrixSIZEX/8))
	{
		dotmatrixFramebuf[column][module] = Data;
	}
}

uint8_t dotmatrixGetData(void){
	/* Which ledmodule */
	uint8_t module = GrLcdState.lcdXAddr>>3;
	/* Which column in ledmodule */
	uint8_t column = GrLcdState.lcdXAddr%8;
	/* Which row */
//	uint8_t row = GrLcdState.lcdYAddr%8;
	
	/* Check panel size */
	if ((column < dotmatrixSIZEY) && (module < dotmatrixSIZEX/8))
	{
		return (dotmatrixFramebuf[column][module]);
	}
	else
	{
		return 0;
	}
}

void dotmatrixWriteData(uint8_t data, uint8_t color){
	if (color == GLCD_COLOR_CLEAR)
	{
	  data = ~data;
	}
	if (GrLcdState.color == GLCD_COLOR_BLACK)
	{
	  dotmatrixSetData(data);
	}
	else
	{
	  dotmatrixSetData(~data);
	}
	
	GrLcdState.lcdXAddr++;

	if (GrLcdState.lcdXAddr > GRAPHICS_WIDTH ){
		dotmatrixSetXY(0,GrLcdState.lcdYAddr+8);
	}
}

void dotmatrixWriteDataTransparent(uint8_t inputdata, uint8_t color){
	uint8_t data = dotmatrixGetData();
	if (GrLcdState.color != GLCD_COLOR_BLACK)
	{
	  data = ~data;
	}

	if (color == GLCD_COLOR_CLEAR) 
	{
	  data = data&(~inputdata);
	}
	else
	{
	  data = data|inputdata;
	}
	
	if (GrLcdState.color == GLCD_COLOR_BLACK)
	{
	  dotmatrixSetData(data);
	}
	else
	{
	  dotmatrixSetData(~data);
	}

	GrLcdState.lcdXAddr++;

	if (GrLcdState.lcdXAddr > GRAPHICS_WIDTH ){
		dotmatrixSetXY(0,GrLcdState.lcdYAddr+8);
	}
}

uint8_t dotmatrixReadData(void){
	uint8_t data = 0;
	if (GrLcdState.color == GLCD_COLOR_BLACK)
	{
	  data = dotmatrixGetData();
	}
	else
	{
	  data = ~dotmatrixGetData();
	}

	return data;
}

/* Callback run periodically to manage rows.
   For each time callback is run, the next row is enabled and the last disabled
 */
void dotmatrixRefresh()
{
	/* Increase row counter */
	if (dotmatrixRowCounter++ == 8) {dotmatrixRowCounter = 0;}

	/* Disable all rows */
	gpio_clr_pin(dotmatrixROW_IO1);
	gpio_clr_pin(dotmatrixROW_IO2);
	gpio_clr_pin(dotmatrixROW_IO3);
	gpio_clr_pin(dotmatrixROW_IO4);
	gpio_clr_pin(dotmatrixROW_IO5);
	gpio_clr_pin(dotmatrixROW_IO6);
	gpio_clr_pin(dotmatrixROW_IO7);
	gpio_clr_pin(dotmatrixROW_IO8);

	/* Write one column of frame buffer to shift registers */
	dotmatrixSPIWrite(dotmatrixFramebuf[dotmatrixRowCounter][0]);
	dotmatrixSPIWrite(dotmatrixFramebuf[dotmatrixRowCounter][1]);
	dotmatrixSPIWrite(dotmatrixFramebuf[dotmatrixRowCounter][2]);
	dotmatrixSPIWrite(dotmatrixFramebuf[dotmatrixRowCounter][3]);
	/* Add more here to support 8-module panels */

	/* Toggle shift register latch */
	gpio_clr_pin(dotmatrixLATCHCLOCK_IO);
	gpio_set_pin(dotmatrixLATCHCLOCK_IO);

	/* Enable one row */
	switch (dotmatrixRowCounter)
	{
		case 0:
			gpio_set_pin(dotmatrixROW_IO1);
			break;
		case 1:
			gpio_set_pin(dotmatrixROW_IO2);
			break;
		case 2:
			gpio_set_pin(dotmatrixROW_IO3);
			break;
		case 3:
			gpio_set_pin(dotmatrixROW_IO4);
			break;
		case 4:
			gpio_set_pin(dotmatrixROW_IO5);
			break;
		case 5:
			gpio_set_pin(dotmatrixROW_IO6);
			break;
		case 6:
			gpio_set_pin(dotmatrixROW_IO7);
			break;
		case 7:
			gpio_set_pin(dotmatrixROW_IO8);
			break;
			
		default:
			break;
	}
}

void dotmatrixInit(){
	/* Set up row driver IO as low output */
	gpio_clr_pin(dotmatrixROW_IO1);
	gpio_set_out(dotmatrixROW_IO1);
	gpio_clr_pin(dotmatrixROW_IO2);
	gpio_set_out(dotmatrixROW_IO2);
	gpio_clr_pin(dotmatrixROW_IO3);
	gpio_set_out(dotmatrixROW_IO3);
	gpio_clr_pin(dotmatrixROW_IO4);
	gpio_set_out(dotmatrixROW_IO4);
	gpio_clr_pin(dotmatrixROW_IO5);
	gpio_set_out(dotmatrixROW_IO5);
	gpio_clr_pin(dotmatrixROW_IO6);
	gpio_set_out(dotmatrixROW_IO6);
	gpio_clr_pin(dotmatrixROW_IO7);
	gpio_set_out(dotmatrixROW_IO7);
	gpio_clr_pin(dotmatrixROW_IO8);
	gpio_set_out(dotmatrixROW_IO8);

	/* Set up PWM controlling brightness */
//	TCCR0A |= (1<<COM0B1)|(1<<WGM01)|(1<<WGM00);
//	TCCR0B |= (1<<CS00);
//	OCR0B = 0xff-act_DotMatrix_INITIAL_BRIGHTNESS;
//	DDRD |= (1<<PD5);

	/* Set up output latch clock */
	gpio_clr_pin(dotmatrixLATCHCLOCK_IO);
	gpio_set_out(dotmatrixLATCHCLOCK_IO);

	/* Initialize USART in SPI-mode */
	UBRR0 = 0;
	USART_SPI_XCK_DDR |= (1<<USART_SPI_XCK); // xck (sck) output
	UCSR0C = (1<<UMSEL01)|(1<<UMSEL00)|(0<<UCPHA0)|(0<<UCPOL0);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UBRR0 = 0;

	dotmatrixClear();

	GrLcdState.color = GLCD_COLOR_BLACK;
}

void dotmatrixClear(){
	/* Clear buffer memory */
	for (uint8_t i=0; i<8; i++)
	{
		for (uint8_t j=0; j<4; j++)
		{
			dotmatrixFramebuf[i][j] = dotmatrixINITIAL_ROW;
		}
	}
}

void dotmatrixSetXY(uint8_t x, uint8_t y){
	GrLcdState.lcdXAddr = x;
	GrLcdState.lcdYAddr = y;
	GrLcdState.lcdYpage = y/8;
}

uint8_t dotmatrixGetX(void){
	return GrLcdState.lcdXAddr;
}

uint8_t dotmatrixGetY(void){
	return GrLcdState.lcdYAddr;
}

