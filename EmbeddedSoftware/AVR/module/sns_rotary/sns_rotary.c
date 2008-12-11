
#include "sns_rotary.h"
uint8_t rotaryEncoder_Position = 0;
uint8_t rotaryEncoder_Position_old = 0;
uint8_t rotaryEncoder_Button_Position = 0;
uint8_t rotaryEncoder_Button_Position_old = 0;

/*********************************************************************//**
Function: SIGNAL(ROTARY_CH1_SIGNAL)
Purpose:  Executed when pin change on ROTARY_CH1 is seen.
Input:    -
Returns:  -
**************************************************************************/
SIGNAL(ROTARY_BTN_PCINT_vector) {
	uint8_t rot_data = 0;
	static uint8_t rot_lastdir = 0, rot_laststate = 0;

	//Take care of button push
	if ((ROTARY_BTN_PIN&(1<<ROTARY_BTN)) != rotaryEncoder_Button_Position){ //The buttonstate has changed!
		rotaryEncoder_Button_Position = ROTARY_BTN_PIN&(1<<ROTARY_BTN);
	}

	//Take care of rotary encoder movement
	if(ROTARY_CH1_PIN&(1<<ROTARY_CH1)){
		rot_data |= 0x01;
	}
	if(ROTARY_CH2_PIN&(1<<ROTARY_CH2)){
		rot_data |= 0x02;
	}

	if( rot_data==0 || rot_data==3 ){ // Are both signals high or low?
		if( rot_data==0 && rot_laststate!=rot_data ){ // Are both signals low? In that case we are finished with one turn and should print out the direction it went.
			if( rot_lastdir&0x01 ){
			#ifndef ROTARY_CHx_INVERT_DIRECTION
				rotaryEncoder_Position--;	// Moving clockwise
			#else
				rotaryEncoder_Position++;	// Moving counter clockwise
			#endif
			}else{
			#ifndef ROTARY_CHx_INVERT_DIRECTION
				rotaryEncoder_Position++;	// Moving counter clockwise
			#else
				rotaryEncoder_Position--;	// Moving clockwise
			#endif
			}
		}
		rot_laststate = rot_data;
	} else { // No, only one of the signals are high. We can use this to find out what direction we are moving.
		rot_lastdir = rot_data;
	}
} /* SIGNAL(ROTARY_CH1_SIGNAL) */


/*********************************************************************//**
Function: SIGNAL(ROTARY_CH2_SIGNAL)
Purpose:  Executed when pin change on ROTARY_CH1 is seen.
		  This executes SIGNAL(ROTARY_BTN_SIGNAL) interupt code
Input:    -
Returns:  -
**************************************************************************/
#if (ROTARY_CH1_PCINT_vector != ROTARY_BTN_PCINT_vector)
ISR(ROTARY_CH1_PCINT_vector, ISR_ALIASOF(ROTARY_BTN_PCINT_vector));
#endif
/*********************************************************************//**
Function: SIGNAL(ROTARY_CH2_SIGNAL)
Purpose:  Executed when pin change on ROTARY_CH2 is seen.
		  This executes SIGNAL(ROTARY_BTN_SIGNAL) interupt code
Input:    -
Returns:  -
**************************************************************************/
#if (ROTARY_CH2_PCINT_vector != ROTARY_BTN_PCINT_vector && ROTARY_CH2_PCINT_vector != ROTARY_CH1_PCINT_vector)
ISR(ROTARY_CH2_PCINT_vector, ISR_ALIASOF(ROTARY_BTN_PCINT_vector));
#endif

void sns_rotary_Init(void)
{
	/*
	 * Initialize rotaryencoders and buttons
	 */
	rotaryEncoder_Position = 0;	// Set initial value to 0
	rotaryEncoder_Position_old = 0;	// Set initial value to 0

	ROTARY_CH1_DDR &= ~(1<<ROTARY_CH1);	// set as input
	ROTARY_CH2_DDR &= ~(1<<ROTARY_CH2);	// set as input
	ROTARY_BTN_DDR &= ~(1<<ROTARY_BTN);	// set as input
	ROTARY_CH1_PORT |= (1<<ROTARY_CH1);	// Enable pull-up
	ROTARY_CH2_PORT |= (1<<ROTARY_CH2);	// Enable pull-up
	ROTARY_BTN_PORT |= (1<<ROTARY_BTN);	// Enable pull-up

	// Enable IO-pin interrupt
	PCICR |= (1<<ROTARY_CH1_PCIE);
	ROTARY_CH1_PCMSK |= (1<<ROTARY_CH1_PCINT);
	PCICR |= (1<<ROTARY_CH2_PCIE);
	ROTARY_CH2_PCMSK |= (1<<ROTARY_CH2_PCINT);
	PCICR |= (1<<ROTARY_BTN_PCIE);
	ROTARY_BTN_PCMSK |= (1<<ROTARY_BTN_PCINT);
}

void sns_rotary_Process(void)
{
	if (rotaryEncoder_Position != rotaryEncoder_Position_old)
	{
		StdCan_Msg_t txMsg;
		StdCan_Set_class(txMsg.Header, CAN_CLASS_MODULE_SNS);
		StdCan_Set_direction(txMsg.Header, DIR_FROM_OWNER);
		txMsg.Header.ModuleType = CAN_TYPE_MODULE_sns_rotary;
		txMsg.Header.ModuleId = sns_rotary_ID;
		txMsg.Header.Command = CAN_CMD_MODULE_PHYS_ROTARY_SWITCH;
		txMsg.Length = 4;
		txMsg.Data[0] = 0x01;
		if ((rotaryEncoder_Position > rotaryEncoder_Position_old || (rotaryEncoder_Position_old==0xff && rotaryEncoder_Position==0x00)) && !(rotaryEncoder_Position_old==0x00 && rotaryEncoder_Position==0xff))
			txMsg.Data[1] = 0x00;	//Clockwice
		else
			txMsg.Data[1] = 0x01;	//Counter Clockwice
		txMsg.Data[2] = 0x01;
		txMsg.Data[3] = rotaryEncoder_Position;

		StdCan_Put(&txMsg);
		rotaryEncoder_Position_old = rotaryEncoder_Position;
	}
	if (rotaryEncoder_Button_Position != rotaryEncoder_Button_Position_old)
	{
		rotaryEncoder_Button_Position_old = rotaryEncoder_Button_Position;
		StdCan_Msg_t txMsg;
		StdCan_Set_class(txMsg.Header, CAN_CLASS_MODULE_SNS);
		StdCan_Set_direction(txMsg.Header, DIR_FROM_OWNER);
		txMsg.Header.ModuleType = CAN_TYPE_MODULE_sns_rotary;
		txMsg.Header.ModuleId = sns_rotary_ID;
		txMsg.Header.Command = CAN_CMD_MODULE_PHYS_BUTTON;
		txMsg.Length = 2;
		txMsg.Data[0] = 0x01;
#ifndef ROTARY_BTN_INVERT_OUTPUT
		if (rotaryEncoder_Button_Position_old)
			txMsg.Data[1] = 0x00;
		else
			txMsg.Data[1] = 0x01;
		StdCan_Put(&txMsg);
#else
		if (rotaryEncoder_Button_Position_old)
			txMsg.Data[1] = 0x01;
		else
			txMsg.Data[1] = 0x00;
		StdCan_Put(&txMsg);
#endif
	}

}

void sns_rotary_HandleMessage(StdCan_Msg_t *rxMsg)
{

}

void sns_rotary_List(uint8_t ModuleSequenceNumber)
{
	StdCan_Msg_t txMsg;

	StdCan_Set_class(txMsg.Header, CAN_CLASS_MODULE_SNS); ///TODO: Change this to the actual class type
	StdCan_Set_direction(txMsg.Header, DIR_FROM_OWNER);
	txMsg.Header.ModuleType = CAN_TYPE_MODULE_sns_rotary; ///TODO: Change this to the actual module type
	txMsg.Header.ModuleId = sns_rotary_ID;
	txMsg.Header.Command = CAN_CMD_MODULE_NMT_LIST;
	txMsg.Length = 6;

	txMsg.Data[0] = NODE_HW_ID_BYTE0;
	txMsg.Data[1] = NODE_HW_ID_BYTE1;
	txMsg.Data[2] = NODE_HW_ID_BYTE2;
	txMsg.Data[3] = NODE_HW_ID_BYTE3;

	txMsg.Data[4] = NUMBER_OF_MODULES;
	txMsg.Data[5] = ModuleSequenceNumber;

	StdCan_Put(&txMsg);
}