#ifndef ACT_LCD_EG2401_EEPROM
#define ACT_LCD_EG2401_EEPROM

#include "act_lcd_eg2401.h"
// Do not change anything below this line.
// ----------------------------------------------------------------

	#include <drivers/misc/eeprom_crc8.h>
	#include <avr/eeprom.h>
	#define EEDATA 			(uint8_t*)&eeprom_act_lcd_eg2401.Data
	#define EEDATA16		(uint16_t*)&eeprom_act_lcd_eg2401.Data
	#define EEDATA_CALC_CRC		eeprom_crc8((uint8_t*)&eeprom_act_lcd_eg2401.Data,sizeof(struct act_lcd_eg2401_Data))
	#define EEDATA_UPDATE_CRC	eeprom_write_byte((uint8_t*)&eeprom_act_lcd_eg2401.crc,eeprom_crc8((uint8_t*)&eeprom_act_lcd_eg2401.Data,sizeof(struct act_lcd_eg2401_Data)))
	#define EEDATA_OK		EEDATA_CALC_CRC == EEDATA_STORED_CRC
	#define EEDATA_STORED_CRC 	eeprom_read_byte((uint8_t*)&eeprom_act_lcd_eg2401.crc)
	
	struct eeprom_act_lcd_eg2401{
		struct act_lcd_eg2401_Data Data;
		uint8_t crc;
	};
	extern struct eeprom_act_lcd_eg2401 EEMEM eeprom_act_lcd_eg2401;
	
	#define WITH_CRC	1
	#define WITHOUT_CRC	0
	static __inline__ void eeprom_write_byte_crc(uint8_t *__p, uint8_t __value, uint8_t crc) {
	  if (__value != eeprom_read_byte(__p))
	  {
	    eeprom_write_byte(__p, __value);
	    if (crc == WITH_CRC)
	    {
	      EEDATA_UPDATE_CRC;
	    }
	  }
	}
	static __inline__ void eeprom_write_word_crc(uint16_t *__p, uint16_t __value, uint8_t crc) {
	  if (__value != eeprom_read_word(__p))
	  {
	    eeprom_write_word(__p, __value);
	    if (crc == WITH_CRC)
	    {
	      EEDATA_UPDATE_CRC;
	    }
	  }
	}
#endif