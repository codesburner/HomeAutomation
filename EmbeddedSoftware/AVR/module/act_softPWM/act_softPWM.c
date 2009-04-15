
#include "act_softPWM.h"
uint16_t currentTimer = 0;
uint16_t maxTimer = 10;
uint8_t	resolution = 1;
uint8_t pwmDefaultState,pwmDefaultStartState,act_softPWM_ReportInterval;
uint16_t pwmDefaultValue;
uint16_t pwmPeriod;
uint8_t pwmStatus;
uint8_t currentSendChannelId = 0;

#ifdef act_softPWM_USEEEPROM
#include "act_softPWM_eeprom.h"
struct eeprom_act_softPWM EEMEM eeprom_act_softPWM = 
{
	{
		///TODO: Define initialization values on the EEPROM variables here, this will generate a *.eep file that can be used to store this values to the node, can in future be done with a EEPROM module and the make-scrips. Write the values in the exact same order as the struct is defined in the *.h file. 
		0xABcd,	// x
		0x1234,	// y
		0x00,
		0x14	//Reportinteval 20 sec.
	},
	0	// crc, must be a correct value, but this will also be handled by the EEPROM module or make scripts
}; 
#endif
#define NUMBEROFCHANNELS 0
#ifdef PIN_0
	#define PIN_0_ID NUMBEROFCHANNELS
	#undefine NUMBEROFCHANNELS
	#define NUMBEROFCHANNELS PIN_0_ID + 1
#endif
#ifdef PIN_1
	#define PIN_1_ID NUMBEROFCHANNELS
	#undefine NUMBEROFCHANNELS
	#define NUMBEROFCHANNELS PIN_1_ID + 1
#endif
#ifdef PIN_2
	#define PIN_2_ID NUMBEROFCHANNELS
	#undefine NUMBEROFCHANNELS
	#define NUMBEROFCHANNELS PIN_2_ID + 1
#endif
#ifdef PIN_3
	#define PIN_3_ID NUMBEROFCHANNELS
	#undefine NUMBEROFCHANNELS
	#define NUMBEROFCHANNELS PIN_3_ID + 1
#endif
#ifdef PIN_4
	#define PIN_4_ID NUMBEROFCHANNELS
	#undefine NUMBEROFCHANNELS
	#define NUMBEROFCHANNELS PIN_4_ID + 1
#endif
#ifdef PIN_5
	#define PIN_5_ID NUMBEROFCHANNELS
	#undefine NUMBEROFCHANNELS
	#define NUMBEROFCHANNELS PIN_5_ID + 1
#endif
#ifdef PIN_6
	#define PIN_6_ID NUMBEROFCHANNELS
	#undefine NUMBEROFCHANNELS
	#define NUMBEROFCHANNELS PIN_6_ID + 1
#endif
#ifdef PIN_7
	#define PIN_7_ID NUMBEROFCHANNELS
	#undefine NUMBEROFCHANNELS
	#define NUMBEROFCHANNELS PIN_7_ID + 1
#endif
uint16_t pwmValue[NUMBEROFCHANNELS];

void act_softPWM_Init(void)
{
#ifdef act_softPWM_USEEEPROM
	if (EEDATA_OK)
	{
	  ;
	} else
	{	//The CRC of the EEPROM is not correct, store default values and update CRC
		eeprom_write_word_crc(EEDATA16.PwmPeriod, DEFAULT_PWM_PERIOD , WITHOUT_CRC);
		eeprom_write_word_crc(EEDATA16.defaultPwmValue, DEFAULT_PWM_VALUE , WITHOUT_CRC);
		eeprom_write_byte_crc(EEDATA.defaultStates, 0xa0 , WITHOUT_CRC);
		eeprom_write_byte_crc(EEDATA.ReportInterval, 0x14 , WITHOUT_CRC);
		EEDATA_UPDATE_CRC;
	}
	pwmDefaultValue = eeprom_read_word(EEDATA16.defaultPwmValue);
	pwmPeriod = eeprom_read_word(EEDATA16.PwmPeriod);
	pwmDefaultState = (eeprom_read_byte(EEDATA.defaultStates)>>6) & 0x03;
	pwmDefaultStartState = ((eeprom_read_byte(EEDATA.defaultStates)>>5) & 0x01);
	act_softPWM_ReportInterval = (eeprom_read_byte(EEDATA.ReportInterval));
	Timer_SetTimeout(act_softPWM_SEND_TIMER, act_softPWM_ReportInterval*1000 , TimerTypeFreeRunning, 0);
#endif  
	///TODO: Initialize hardware etc here
#ifdef PIN_0
	gpio_set_out(PIN_0);
	gpio_clr_pin(PIN_0);
#endif
#ifdef PIN_1
	gpio_set_out(PIN_1);
	gpio_clr_pin(PIN_1);
#endif
#ifdef PIN_2
	gpio_set_out(PIN_2);
	gpio_clr_pin(PIN_2);
#endif
#ifdef PIN_3
	gpio_set_out(PIN_3);
	gpio_clr_pin(PIN_3);
#endif
#ifdef PIN_4
	gpio_set_out(PIN_4);
	gpio_clr_pin(PIN_4);
#endif
#ifdef PIN_5
	gpio_set_out(PIN_5);
	gpio_clr_pin(PIN_5);
#endif
#ifdef PIN_6
	gpio_set_out(PIN_6);
	gpio_clr_pin(PIN_6);
#endif
#ifdef PIN_7
	gpio_set_out(PIN_7);
	gpio_clr_pin(PIN_7);
#endif
	
	Timer_SetTimeout(act_softPWM_TIMER, resolution, TimerTypeFreeRunning, NULL);
	// to use PCINt lib, call this function: (the callback function look as a timer callback function)
	// Pcint_SetCallbackPin(act_softPWM_PCINT, EXP_C , &act_softPWM_pcint_callback);

}

void act_softPWM_Process(void)
{
	if (Timer_Expired(act_softPWM_TIMER)) {
		currentTimer++;
		if (currentTimer == 10) {
			currentTimer=0;
			#ifdef PIN_0 
				gpio_set_pin(PIN_0);
			#endif
			#ifdef PIN_1 
				gpio_set_pin(PIN_1);
			#endif
			#ifdef PIN_2 
				gpio_set_pin(PIN_2);
			#endif
			#ifdef PIN_3 
				gpio_set_pin(PIN_3);
			#endif
			#ifdef PIN_4 
				gpio_set_pin(PIN_4);
			#endif
			#ifdef PIN_5 
				gpio_set_pin(PIN_5);
			#endif
			#ifdef PIN_6 
				gpio_set_pin(PIN_6);
			#endif
			#ifdef PIN_7 
				gpio_set_pin(PIN_7);
			#endif
		}
		#ifdef PIN_0
		if (currentTimer >= pwmValue[PIN_0_ID]) {
			gpio_clr_pin(PIN_0);
		}
		#endif
		#ifdef PIN_1
		if (currentTimer >= pwmValue[PIN_1_ID]) {
			gpio_clr_pin(PIN_1);
		}
		#endif
		#ifdef PIN_2
		if (currentTimer >= pwmValue[PIN_2_ID]) {
			gpio_clr_pin(PIN_2);
		}
		#endif
		#ifdef PIN_3
		if (currentTimer >= pwmValue[PIN_3_ID]) {
			gpio_clr_pin(PIN_3);
		}
		#endif
		#ifdef PIN_4
		if (currentTimer >= pwmValue[PIN_4_ID]) {
			gpio_clr_pin(PIN_4);
		}
		#endif
		#ifdef PIN_5
		if (currentTimer >= pwmValue[PIN_5_ID]) {
			gpio_clr_pin(PIN_5);
		}
		#endif
		#ifdef PIN_6
		if (currentTimer >= pwmValue[PIN_6_ID]) {
			gpio_clr_pin(PIN_6);
		}
		#endif
		#ifdef PIN_7
		if (currentTimer >= pwmValue[PIN_7_ID]) {
			gpio_clr_pin(PIN_7);
		}
		#endif
	}
	if (Timer_Expired(act_softPWM_SEND_TIMER)) {
		StdCan_Msg_t txMsg;
		StdCan_Set_class(txMsg.Header, CAN_MODULE_CLASS_ACT);
		StdCan_Set_direction(txMsg.Header, DIRECTIONFLAG_FROM_OWNER);
		txMsg.Header.ModuleType = CAN_MODULE_TYPE_ACT_SOFTPWM;
		txMsg.Header.ModuleId = act_softPWM_ID;
		txMsg.Header.Command = CAN_MODULE_CMD_PHYSICAL_PWM;
		txMsg.Length = 3;
		txMsg.Data[0] = currentSendChannelId;
		txMsg.Data[1] = (pwmValue[currentSendChannelId]>>8)&0xff;
		txMsg.Data[2] = (pwmValue[currentSendChannelId])&0xff;
		StdCan_Put(&txMsg);
		currentSendChannelId++;
		if (currentSendChannelId >= NUMBEROFCHANNELS)
			currentSendChannelId=0;
	}
}



void act_softPWM_HandleMessage(StdCan_Msg_t *rxMsg)
{
	if (	StdCan_Ret_class(rxMsg->Header) == CAN_MODULE_CLASS_ACT && 
		StdCan_Ret_direction(rxMsg->Header) == DIRECTIONFLAG_TO_OWNER &&
		rxMsg->Header.ModuleType == CAN_MODULE_TYPE_ACT_SOFTPWM && 
		rxMsg->Header.ModuleId == act_softPWM_ID)
	{
		switch (rxMsg->Header.Command)
		{
		case CAN_MODULE_CMD_PHYSICAL_PWM:
			if ((((uint16_t)rxMsg->Data[1])<8) + rxMsg->Data[2] > maxTimer)
			{
				rxMsg->Data[2] = maxTimer & 0x00ff;
				rxMsg->Data[1] = (maxTimer>>8) & 0x00ff;
			}
			switch (rxMsg->Data[0])
			{
			#ifdef PIN_0
			case 0:
				pwmValue[PIN_0_ID] = (((uint16_t)rxMsg->Data[1])<<8) + rxMsg->Data[2];
				break;
			#endif
			#ifdef PIN_1
			case 1:
				pwmValue[PIN_1_ID] = (((uint16_t)rxMsg->Data[1])<<8) + rxMsg->Data[2];
				break;
			#endif
			#ifdef PIN_2
			case 2:
				pwmValue[PIN_2_ID] = (((uint16_t)rxMsg->Data[1])<<8) + rxMsg->Data[2];
				break;
			#endif
			#ifdef PIN_3
			case 3:
				pwmValue[PIN_3_ID] = (((uint16_t)rxMsg->Data[1])<<8) + rxMsg->Data[2];
				break;
			#endif
			#ifdef PIN_4
			case 4:
				pwmValue[PIN_4_ID] = (((uint16_t)rxMsg->Data[1])<<8) + rxMsg->Data[2];
				break;
			#endif
			#ifdef PIN_5
			case 5:
				pwmValue[PIN_5_ID] = (((uint16_t)rxMsg->Data[1])<<8) + rxMsg->Data[2];
				break;
			#endif
			#ifdef PIN_6
			case 6:
				pwmValue[PIN_6_ID] = (((uint16_t)rxMsg->Data[1])<<8) + rxMsg->Data[2];
				break;
			#endif
			#ifdef PIN_7
			case 7:
				pwmValue[PIN_7_ID] = (((uint16_t)rxMsg->Data[1])<<8) + rxMsg->Data[2];
				break;
			#endif
			}
			break;
		case CAN_MODULE_CMD_SOFTPWM_CONFIG:
			maxTimer = (((uint16_t)rxMsg->Data[0])<<8) + rxMsg->Data[1];
			resolution = rxMsg->Data[2];
			Timer_SetTimeout(act_softPWM_TIMER, resolution, TimerTypeFreeRunning, NULL);
			break;
		case CAN_MODULE_CMD_GLOBAL_REPORT_INTERVAL:
			if (rxMsg->Length > 0)
			{
				act_softPWM_ReportInterval = rxMsg->Data[0];
				eeprom_write_byte_crc(EEDATA.ReportInterval, act_softPWM_ReportInterval , WITH_CRC);
				Timer_SetTimeout(act_softPWM_SEND_TIMER, act_softPWM_ReportInterval*1000 , TimerTypeFreeRunning, 0);
			}

			StdCan_Msg_t txMsg;

			StdCan_Set_class(txMsg.Header, CAN_MODULE_CLASS_ACT);
			StdCan_Set_direction(txMsg.Header, DIRECTIONFLAG_FROM_OWNER);
			txMsg.Header.ModuleType = CAN_MODULE_TYPE_ACT_SOFTPWM;
			txMsg.Header.ModuleId = act_softPWM_ID;
			txMsg.Header.Command = CAN_MODULE_CMD_GLOBAL_REPORT_INTERVAL;
			txMsg.Length = 1;
			txMsg.Data[0] = act_softPWM_ReportInterval;
			StdCan_Put(&txMsg);
			break;
		}
	}
}

void act_softPWM_List(uint8_t ModuleSequenceNumber)
{
	StdCan_Msg_t txMsg;
	
	StdCan_Set_class(txMsg.Header, CAN_MODULE_CLASS_ACT); ///TODO: Change this to the actual class type
	StdCan_Set_direction(txMsg.Header, DIRECTIONFLAG_FROM_OWNER);
	txMsg.Header.ModuleType = CAN_MODULE_TYPE_ACT_SOFTPWM; ///TODO: Change this to the actual module type
	txMsg.Header.ModuleId = act_softPWM_ID;
	txMsg.Header.Command = CAN_MODULE_CMD_GLOBAL_LIST;
	txMsg.Length = 6;

	txMsg.Data[0] = NODE_HW_ID_BYTE0;
	txMsg.Data[1] = NODE_HW_ID_BYTE1;
	txMsg.Data[2] = NODE_HW_ID_BYTE2;
	txMsg.Data[3] = NODE_HW_ID_BYTE3;
	
	txMsg.Data[4] = NUMBER_OF_MODULES;
	txMsg.Data[5] = ModuleSequenceNumber;
	
	while (StdCan_Put(&txMsg) != StdCan_Ret_OK);
}
