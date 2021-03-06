
#include "sns_input.h"
uint8_t pinStatus[8];
#define HIGH		1
#define LOW			2
#define NOCHANGE 	0
#define HIGH_NOCH	3
#define LOW_NOCH	4

#define IO_HIGH		1
#define IO_LOW		0

#ifndef sns_input_SEND_PERIODIC
#define sns_input_SEND_PERIODIC 0
#endif

/*

Callback function that is called from pin-change driver on AVR IO
id gives which pin that changed, status is the new state of the changed pin

*/
void sns_input_pcint_callback(uint8_t id, uint8_t status) 
{
#ifdef	sns_input_CH0
#if sns_input_CH0PCA95xxIO==0
	if (id == sns_input_PCINT_CH0) {
	  if (IO_LOW != status) {
	    pinStatus[0] = HIGH;
	  } else {
	    pinStatus[0] = LOW;
	  }
	}
#endif
#endif
#ifdef	sns_input_CH1
#if sns_input_CH1PCA95xxIO==0
	if (id == sns_input_PCINT_CH1) {
	  if (IO_LOW != status) {
	    pinStatus[1] = HIGH;
	  } else {
	    pinStatus[1] = LOW;
	  }
	}
#endif
#endif
#ifdef	sns_input_CH2
#if sns_input_CH2PCA95xxIO==0
	if (id == sns_input_PCINT_CH2) {
	  if (IO_LOW != status) {
	    pinStatus[2] = HIGH;
	  } else {
	    pinStatus[2] = LOW;
	  }
	}
#endif
#endif
#ifdef	sns_input_CH3
#if sns_input_CH3PCA95xxIO==0
	if (id == sns_input_PCINT_CH3) {
	  if (IO_LOW != status) {
	    pinStatus[3] = HIGH;
	  } else {
	    pinStatus[3] = LOW;
	  }
	}
#endif
#endif
#ifdef	sns_input_CH4
#if sns_input_CH4PCA95xxIO==0
	if (id == sns_input_PCINT_CH4) {
	  if (IO_LOW != status) {
	    pinStatus[4] = HIGH;
	  } else {
	    pinStatus[4] = LOW;
	  }
	}
#endif
#endif
#ifdef	sns_input_CH5
#if sns_input_CH5PCA95xxIO==0
	if (id == sns_input_PCINT_CH5) {
	  if (IO_LOW != status) {
	    pinStatus[5] = HIGH;
	  } else {
	    pinStatus[5] = LOW;
	  }
	}
#endif
#endif
#ifdef	sns_input_CH6
#if sns_input_CH6PCA95xxIO==0
	if (id == sns_input_PCINT_CH6) {
	  if (IO_LOW != status) {
	    pinStatus[6] = HIGH;
	  } else {
	    pinStatus[6] = LOW;
	  }
	}
#endif
#endif
#ifdef	sns_input_CH7
#if sns_input_CH7PCA95xxIO==0
	if (id == sns_input_PCINT_CH7) {
	  if (IO_LOW != status) {
	    pinStatus[7] = HIGH;
	  } else {
	    pinStatus[7] = LOW;
	  }
	}
#endif
#endif
}


#if sns_input_ENABLE_PCA95xx==1
/*

Callback function that is called from PCA95xx-driver when any pin has changed
status is the pin status of all pins on PCA95xx

*/
void sns_input_PCA95xx_callback(uint16_t status) 
{
#ifdef	sns_input_CH0
#if sns_input_CH0PCA95xxIO==1
	if (pinStatus[0] == LOW_NOCH && ((status>>sns_input_CH0)&0x1) == IO_HIGH) {
		pinStatus[0] = HIGH;
	} else if (pinStatus[0] == HIGH_NOCH && ((status>>sns_input_CH0)&0x1) == IO_LOW) {
		pinStatus[0] = LOW;
	}
#endif
#endif
#ifdef	sns_input_CH1
#if sns_input_CH1PCA95xxIO==1
	if (pinStatus[1] == LOW_NOCH && ((status>>sns_input_CH1)&0x1) == IO_HIGH) {
		pinStatus[1] = HIGH;
	} else if (pinStatus[1] == HIGH_NOCH && ((status>>sns_input_CH1)&0x1) == IO_LOW) {
		pinStatus[1] = LOW;
	}
#endif
#endif
#ifdef	sns_input_CH2
#if sns_input_CH2PCA95xxIO==1
	if (pinStatus[2] == LOW_NOCH && ((status>>sns_input_CH2)&0x1) == IO_HIGH) {
		pinStatus[2] = HIGH;
	} else if (pinStatus[2] == HIGH_NOCH && ((status>>sns_input_CH2)&0x1) == IO_LOW) {
		pinStatus[2] = LOW;
	}
#endif
#endif
#ifdef	sns_input_CH3
#if sns_input_CH3PCA95xxIO==1
	if (pinStatus[3] == LOW_NOCH && ((status>>sns_input_CH3)&0x1) == IO_HIGH) {
		pinStatus[3] = HIGH;
	} else if (pinStatus[3] == HIGH_NOCH && ((status>>sns_input_CH3)&0x1) == IO_LOW) {
		pinStatus[3] = LOW;
	}
#endif
#endif
#ifdef	sns_input_CH4
#if sns_input_CH4PCA95xxIO==1
	if (pinStatus[4] == LOW_NOCH && ((status>>sns_input_CH4)&0x1) == IO_HIGH) {
		pinStatus[4] = HIGH;
	} else if (pinStatus[4] == HIGH_NOCH && ((status>>sns_input_CH4)&0x1) == IO_LOW) {
		pinStatus[4] = LOW;
	}
#endif
#endif

#ifdef	sns_input_CH5
#if sns_input_CH5PCA95xxIO==1
	if (pinStatus[5] == LOW_NOCH && ((status>>sns_input_CH5)&0x1) == IO_HIGH) {
		pinStatus[5] = HIGH;
	} else if (pinStatus[5] == HIGH_NOCH && ((status>>sns_input_CH5)&0x1) == IO_LOW) {
		pinStatus[5] = LOW;
	}
#endif
#endif
#ifdef	sns_input_CH6
#if sns_input_CH0PCA95xxIO==1
	if (pinStatus[6] == LOW_NOCH && ((status>>sns_input_CH6)&0x1) == IO_HIGH) {
		pinStatus[6] = HIGH;
	} else if (pinStatus[6] == HIGH_NOCH && ((status>>sns_input_CH6)&0x1) == IO_LOW) {
		pinStatus[6] = LOW;
	}
#endif
#endif
#ifdef	sns_input_CH7
#if sns_input_CH7PCA95xxIO==1
	if (pinStatus[7] == LOW_NOCH && ((status>>sns_input_CH7)&0x1) == IO_HIGH) {
		pinStatus[7] = HIGH;
	} else if (pinStatus[7] == HIGH_NOCH && ((status>>sns_input_CH7)&0x1) == IO_LOW) {
		pinStatus[7] = LOW;
	}
#endif
#endif

}
#endif 


/*

Function that initiates status variables for pins
called at statup

*/
void sns_input_setPinStatus(void)
{
#if sns_input_ENABLE_PCA95xx==1
	uint16_t status = Pca95xx_GetInputs();
#endif
#ifdef	sns_input_CH0
#if sns_input_CH0PCA95xxIO==1
	if (((status>>sns_input_CH0)&0x1) != IO_LOW) {
		pinStatus[0] = HIGH_NOCH;
	} else {
		pinStatus[0] = LOW_NOCH;
	}
#else
	if (gpio_get_state(sns_input_CH0)) {
		pinStatus[0] = HIGH_NOCH;
	} else {
		pinStatus[0] = LOW_NOCH;
	}	
#endif
#endif
#ifdef	sns_input_CH1
#if sns_input_CH1PCA95xxIO==1
	if (((status>>sns_input_CH1)&0x1) != IO_LOW) {
		pinStatus[1] = HIGH_NOCH;
	} else {
		pinStatus[1] = LOW_NOCH;
	}
#else
	if (gpio_get_state(sns_input_CH1)) {
		pinStatus[1] = HIGH_NOCH;
	} else {
		pinStatus[1] = LOW_NOCH;
	}	
#endif
#endif
#ifdef	sns_input_CH2
#if sns_input_CH2PCA95xxIO==1
	if (((status>>sns_input_CH2)&0x1) != IO_LOW) {
		pinStatus[2] = HIGH_NOCH;
	} else {
		pinStatus[2] = LOW_NOCH;
	}
#else
	if (gpio_get_state(sns_input_CH2)) {
		pinStatus[2] = HIGH_NOCH;
	} else {
		pinStatus[2] = LOW_NOCH;
	}	
#endif
#endif
#ifdef	sns_input_CH3
#if sns_input_CH3PCA95xxIO==1
	if (((status>>sns_input_CH3)&0x1) != IO_LOW) {
		pinStatus[3] = HIGH_NOCH;
	} else {
		pinStatus[3] = LOW_NOCH;
	}
#else
	if (gpio_get_state(sns_input_CH3)) {
		pinStatus[3] = HIGH_NOCH;
	} else {
		pinStatus[3] = LOW_NOCH;
	}	
#endif
#endif
#ifdef	sns_input_CH4
#if sns_input_CH4PCA95xxIO==1
	if (((status>>sns_input_CH4)&0x1) != IO_LOW) {
		pinStatus[4] = HIGH_NOCH;
	} else {
		pinStatus[4] = LOW_NOCH;
	}
#else
	if (gpio_get_state(sns_input_CH4)) {
		pinStatus[4] = HIGH_NOCH;
	} else {
		pinStatus[4] = LOW_NOCH;
	}	
#endif
#endif
#ifdef	sns_input_CH5
#if sns_input_CH5PCA95xxIO==1
	if (((status>>sns_input_CH5)&0x1) != IO_LOW) {
		pinStatus[5] = HIGH_NOCH;
	} else {
		pinStatus[5] = LOW_NOCH;
	}
#else
	if (gpio_get_state(sns_input_CH5)) {
		pinStatus[5] = HIGH_NOCH;
	} else {
		pinStatus[5] = LOW_NOCH;
	}	
#endif
#endif
#ifdef	sns_input_CH6
#if sns_input_CH6PCA95xxIO==1
	if (((status>>sns_input_CH6)&0x1) != IO_LOW) {
		pinStatus[6] = HIGH_NOCH;
	} else {
		pinStatus[6] = LOW_NOCH;
	}
#else
	if (gpio_get_state(sns_input_CH6)) {
		pinStatus[6] = HIGH_NOCH;
	} else {
		pinStatus[6] = LOW_NOCH;
	}	
#endif
#endif
#ifdef	sns_input_CH7
#if sns_input_CH7PCA95xxIO==1
	if (((status>>sns_input_CH7)&0x1) != IO_LOW) {
		pinStatus[7] = HIGH_NOCH;
	} else {
		pinStatus[7] = LOW_NOCH;
	}
#else
	if (gpio_get_state(sns_input_CH7)) {
		pinStatus[7] = HIGH_NOCH;
	} else {
		pinStatus[7] = LOW_NOCH;
	}	
#endif
#endif
}

void sns_input_Init(void)
{
#if sns_input_ENABLE_PCA95xx==1
	Pca95xx_SetCallback(sns_input_PCA95XX_CALLBACK_INDEX, &sns_input_PCA95xx_callback);
	Pca95xx_Init(0);
#endif 

#ifdef	sns_input_CH0
#if sns_input_CH0PCA95xxIO==0
	#if (sns_input_CH0_pullup == 1)
		gpio_set_pullup(sns_input_CH0);
	#else
		gpio_clr_pullup(sns_input_CH0);
	#endif
		gpio_set_in(sns_input_CH0);
		Pcint_SetCallbackPin(sns_input_PCINT_CH0, sns_input_CH0, &sns_input_pcint_callback);
#else
		Pca95xx_set_in(sns_input_CH0);
#endif
#endif
#ifdef	sns_input_CH1
#if sns_input_CH1PCA95xxIO==0
	#if (sns_input_CH1_pullup == 1)
		gpio_set_pullup(sns_input_CH1);
	#else
		gpio_clr_pullup(sns_input_CH1);
	#endif		
		gpio_set_in(sns_input_CH1);
		Pcint_SetCallbackPin(sns_input_PCINT_CH1, sns_input_CH1, &sns_input_pcint_callback);
#else
		Pca95xx_set_in(sns_input_CH1);
#endif
#endif
#ifdef	sns_input_CH2
#if sns_input_CH2PCA95xxIO==0
	#if (sns_input_CH2_pullup == 1)
		gpio_set_pullup(sns_input_CH2);
	#else
		gpio_clr_pullup(sns_input_CH2);
	#endif		
		gpio_set_in(sns_input_CH2);
		Pcint_SetCallbackPin(sns_input_PCINT_CH2, sns_input_CH2, &sns_input_pcint_callback);
#else
		Pca95xx_set_in(sns_input_CH2);
#endif
#endif
#ifdef	sns_input_CH3
#if sns_input_CH3PCA95xxIO==0
	#if (sns_input_CH3_pullup == 1)
		gpio_set_pullup(sns_input_CH3);
	#else
		gpio_clr_pullup(sns_input_CH3);
	#endif		
		gpio_set_in(sns_input_CH3);
		Pcint_SetCallbackPin(sns_input_PCINT_CH3, sns_input_CH3, &sns_input_pcint_callback);
#else
		Pca95xx_set_in(sns_input_CH3);
#endif
#endif
#ifdef	sns_input_CH4
#if sns_input_CH4PCA95xxIO==0
	#if (sns_input_CH4_pullup == 1)
		gpio_set_pullup(sns_input_CH4);
	#else
		gpio_clr_pullup(sns_input_CH4);
	#endif		
		gpio_set_in(sns_input_CH4);
		Pcint_SetCallbackPin(sns_input_PCINT_CH4, sns_input_CH4, &sns_input_pcint_callback);
#else
		Pca95xx_set_in(sns_input_CH4);
#endif
#endif
#ifdef	sns_input_CH5
#if sns_input_CH5PCA95xxIO==0
	#if (sns_input_CH5_pullup == 1)
		gpio_set_pullup(sns_input_CH5);
	#else
		gpio_clr_pullup(sns_input_CH5);
	#endif		
		gpio_set_in(sns_input_CH5);
		Pcint_SetCallbackPin(sns_input_PCINT_CH5, sns_input_CH5, &sns_input_pcint_callback);
#else
		Pca95xx_set_in(sns_input_CH5);
#endif
#endif
#ifdef	sns_input_CH6
#if sns_input_CH6PCA95xxIO==0
	#if (sns_input_CH6_pullup == 1)
		gpio_set_pullup(sns_input_CH6);
	#else
		gpio_clr_pullup(sns_input_CH6);
	#endif			
		gpio_set_in(sns_input_CH6);
		Pcint_SetCallbackPin(sns_input_PCINT_CH6, sns_input_CH6, &sns_input_pcint_callback);
#else
		Pca95xx_set_in(sns_input_CH6);
#endif
#endif
#ifdef	sns_input_CH7
#if sns_input_CH7PCA95xxIO==0
	#if (sns_input_CH7_pullup == 1)
		gpio_set_pullup(sns_input_CH7);
	#else
		gpio_clr_pullup(sns_input_CH7);
	#endif		
		gpio_set_in(sns_input_CH7);
		Pcint_SetCallbackPin(sns_input_PCINT_CH7, sns_input_CH7, &sns_input_pcint_callback);
#else
		Pca95xx_set_in(sns_input_CH7);
#endif
#endif


	sns_input_setPinStatus();

	Timer_SetTimeout(sns_input_DEBOUNCE_TIMER, sns_input_DEBOUNCE_TIME_MS, TimerTypeFreeRunning, 0);
	Timer_SetTimeout(sns_input_SEND_PERIODIC_TIMER, sns_input_SEND_PERIOD_MS, TimerTypeFreeRunning, 0);
}

#if sns_input_SEND_PERIODIC==1
uint8_t ChannelToSend = 0;
#endif
void sns_input_Process(void)
{
	if (Timer_Expired(sns_input_DEBOUNCE_TIMER))
	{
		uint8_t index = 0;
		for (index = 0; index < 8; index++) {
			if (pinStatus[index] == LOW || pinStatus[index] == HIGH) {
				StdCan_Msg_t txMsg;
				StdCan_Set_class(txMsg.Header, CAN_MODULE_CLASS_SNS);
				StdCan_Set_direction(txMsg.Header, DIRECTIONFLAG_FROM_OWNER);
				txMsg.Header.ModuleType = CAN_MODULE_TYPE_SNS_INPUT;
				txMsg.Header.ModuleId = sns_input_ID;
				txMsg.Header.Command = CAN_MODULE_CMD_PHYSICAL_PINSTATUS;
				txMsg.Length = 2;
				txMsg.Data[0] = index;
				if (pinStatus[index] == HIGH) {
					txMsg.Data[1] = CAN_MODULE_ENUM_PHYSICAL_PINSTATUS_STATUS_HIGH;
					pinStatus[index] = HIGH_NOCH;
				} else {
					txMsg.Data[1] = CAN_MODULE_ENUM_PHYSICAL_PINSTATUS_STATUS_LOW;
					pinStatus[index] = LOW_NOCH;
				}
				StdCan_Put(&txMsg);
			}
		}
	}
	
#if sns_input_SEND_PERIODIC==1
	if (Timer_Expired(sns_input_SEND_PERIODIC_TIMER))
	{
		StdCan_Msg_t txMsg;
		StdCan_Set_class(txMsg.Header, CAN_MODULE_CLASS_SNS);
		StdCan_Set_direction(txMsg.Header, DIRECTIONFLAG_FROM_OWNER);
		txMsg.Header.ModuleType = CAN_MODULE_TYPE_SNS_INPUT;
		txMsg.Header.ModuleId = sns_input_ID;
		txMsg.Header.Command = CAN_MODULE_CMD_PHYSICAL_PINSTATUS;
		txMsg.Length = 2;
		txMsg.Data[0] = ChannelToSend;
#ifdef sns_input_CH0
		if (ChannelToSend==0)
		{
			if (pinStatus[ChannelToSend] == HIGH || pinStatus[ChannelToSend] == HIGH_NOCH) {
				txMsg.Data[1] = CAN_MODULE_ENUM_PHYSICAL_PINSTATUS_STATUS_HIGH;
			} else if (pinStatus[ChannelToSend] == LOW || pinStatus[ChannelToSend] == LOW_NOCH) {
				txMsg.Data[1] = CAN_MODULE_ENUM_PHYSICAL_PINSTATUS_STATUS_LOW;
			}

			StdCan_Put(&txMsg);
		}
#endif
#ifdef sns_input_CH1
		if (ChannelToSend==1)
		{
			if (pinStatus[ChannelToSend] == HIGH || pinStatus[ChannelToSend] == HIGH_NOCH) {
				txMsg.Data[1] = CAN_MODULE_ENUM_PHYSICAL_PINSTATUS_STATUS_HIGH;
			} else if (pinStatus[ChannelToSend] == LOW || pinStatus[ChannelToSend] == LOW_NOCH) {
				txMsg.Data[1] = CAN_MODULE_ENUM_PHYSICAL_PINSTATUS_STATUS_LOW;
			}

			StdCan_Put(&txMsg);
		}
#endif
#ifdef sns_input_CH2
		if (ChannelToSend==2)
		{
			if (pinStatus[ChannelToSend] == HIGH || pinStatus[ChannelToSend] == HIGH_NOCH) {
				txMsg.Data[1] = CAN_MODULE_ENUM_PHYSICAL_PINSTATUS_STATUS_HIGH;
			} else if (pinStatus[ChannelToSend] == LOW || pinStatus[ChannelToSend] == LOW_NOCH) {
				txMsg.Data[1] = CAN_MODULE_ENUM_PHYSICAL_PINSTATUS_STATUS_LOW;
			}

			StdCan_Put(&txMsg);
		}
#endif
#ifdef sns_input_CH3
		if (ChannelToSend==3)
		{
			if (pinStatus[ChannelToSend] == HIGH || pinStatus[ChannelToSend] == HIGH_NOCH) {
				txMsg.Data[1] = CAN_MODULE_ENUM_PHYSICAL_PINSTATUS_STATUS_HIGH;
			} else if (pinStatus[ChannelToSend] == LOW || pinStatus[ChannelToSend] == LOW_NOCH) {
				txMsg.Data[1] = CAN_MODULE_ENUM_PHYSICAL_PINSTATUS_STATUS_LOW;
			}

			StdCan_Put(&txMsg);
		}
#endif
#ifdef sns_input_CH4
		if (ChannelToSend==4)
		{
			if (pinStatus[ChannelToSend] == HIGH || pinStatus[ChannelToSend] == HIGH_NOCH) {
				txMsg.Data[1] = CAN_MODULE_ENUM_PHYSICAL_PINSTATUS_STATUS_HIGH;
			} else if (pinStatus[ChannelToSend] == LOW || pinStatus[ChannelToSend] == LOW_NOCH) {
				txMsg.Data[1] = CAN_MODULE_ENUM_PHYSICAL_PINSTATUS_STATUS_LOW;
			}

			StdCan_Put(&txMsg);
		}
#endif
#ifdef sns_input_CH5
		if (ChannelToSend==5)
		{
			if (pinStatus[ChannelToSend] == HIGH || pinStatus[ChannelToSend] == HIGH_NOCH) {
				txMsg.Data[1] = CAN_MODULE_ENUM_PHYSICAL_PINSTATUS_STATUS_HIGH;
			} else if (pinStatus[ChannelToSend] == LOW || pinStatus[ChannelToSend] == LOW_NOCH) {
				txMsg.Data[1] = CAN_MODULE_ENUM_PHYSICAL_PINSTATUS_STATUS_LOW;
			}

			StdCan_Put(&txMsg);
		}
#endif
#ifdef sns_input_CH6
		if (ChannelToSend==6)
		{
			if (pinStatus[ChannelToSend] == HIGH || pinStatus[ChannelToSend] == HIGH_NOCH) {
				txMsg.Data[1] = CAN_MODULE_ENUM_PHYSICAL_PINSTATUS_STATUS_HIGH;
			} else if (pinStatus[ChannelToSend] == LOW || pinStatus[ChannelToSend] == LOW_NOCH) {
				txMsg.Data[1] = CAN_MODULE_ENUM_PHYSICAL_PINSTATUS_STATUS_LOW;
			}

			StdCan_Put(&txMsg);
		}
#endif
#ifdef sns_input_CH7
		if (ChannelToSend==7)
		{
			if (pinStatus[ChannelToSend] == HIGH || pinStatus[ChannelToSend] == HIGH_NOCH) {
				txMsg.Data[1] = CAN_MODULE_ENUM_PHYSICAL_PINSTATUS_STATUS_HIGH;
			} else if (pinStatus[ChannelToSend] == LOW || pinStatus[ChannelToSend] == LOW_NOCH) {
				txMsg.Data[1] = CAN_MODULE_ENUM_PHYSICAL_PINSTATUS_STATUS_LOW;
			}

			StdCan_Put(&txMsg);
		}
#endif

		if (ChannelToSend++ >=8)
		{
			ChannelToSend=0;
		}
	}
#endif
}

void sns_input_HandleMessage(StdCan_Msg_t *rxMsg)
{
	
}

void sns_input_List(uint8_t ModuleSequenceNumber)
{
	StdCan_Msg_t txMsg;
	
	StdCan_Set_class(txMsg.Header, CAN_MODULE_CLASS_SNS);
	StdCan_Set_direction(txMsg.Header, DIRECTIONFLAG_FROM_OWNER);
	txMsg.Header.ModuleType = CAN_MODULE_TYPE_SNS_INPUT;
	txMsg.Header.ModuleId = sns_input_ID;
	txMsg.Header.Command = CAN_MODULE_CMD_GLOBAL_LIST;
	txMsg.Length = 6;

	uint32_t HwId=BIOS_GetHwId();
	txMsg.Data[0] = HwId&0xff;
	txMsg.Data[1] = (HwId>>8)&0xff;
	txMsg.Data[2] = (HwId>>16)&0xff;
	txMsg.Data[3] = (HwId>>24)&0xff;
	
	txMsg.Data[4] = NUMBER_OF_MODULES;
	txMsg.Data[5] = ModuleSequenceNumber;
	
	while (StdCan_Put(&txMsg) != StdCan_Ret_OK);
}
