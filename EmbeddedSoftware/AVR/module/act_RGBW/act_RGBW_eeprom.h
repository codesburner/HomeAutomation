#ifndef ACT_RGBW_EEPROM
#define ACT_RGBW_EEPROM

#include "act_RGBW.h"
// Do not change anything below this line.
// ----------------------------------------------------------------

	#include <drivers/misc/eeprom_crc8.h>
	#include <avr/eeprom.h>
	#define EEDATA 			(uint8_t*)&eeprom_act_RGBW.Data
	#define EEDATA16		(uint16_t*)&eeprom_act_RGBW.Data
	#define EEDATA_CALC_CRC		eeprom_crc8((uint8_t*)&eeprom_act_RGBW.Data,sizeof(struct act_RGBW_Data))
	#define EEDATA_UPDATE_CRC	eeprom_write_byte((uint8_t*)&eeprom_act_RGBW.crc,eeprom_crc8((uint8_t*)&eeprom_act_RGBW.Data,sizeof(struct act_RGBW_Data)))
	#define EEDATA_OK		EEDATA_CALC_CRC == EEDATA_STORED_CRC
	#define EEDATA_STORED_CRC 	eeprom_read_byte((uint8_t*)&eeprom_act_RGBW.crc)
	
	struct eeprom_act_RGBW{
		struct act_RGBW_Data Data;
		uint8_t crc;
	};
	extern struct eeprom_act_RGBW EEMEM eeprom_act_RGBW;
	
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