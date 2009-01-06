// Built on Tue Jan  6 14:08:53 2009 by makeCanId.pl
// DO NOT CHANGE MANUALLY

#ifndef MODULEID_H_
#define MODULEID_H_

//------------------ //
// Class definitions //
//------------------ //

#define CAN_MODULE_CLASS_NMT 0
#define CAN_MODULE_CLASS_MNMT 11
#define CAN_MODULE_CLASS_ACT 12
#define CAN_MODULE_CLASS_SNS 13
#define CAN_MODULE_CLASS_DEF 14
#define CAN_MODULE_CLASS_TST 15

//-------------------- //
// Command definitions //
//-------------------- //

#define CAN_MODULE_CMD_GLOBAL_LIST 0
#define CAN_MODULE_CMD_GLOBAL_DEBUG 2
#define CAN_MODULE_CMD_GLOBAL_REPORT_INTERVAL 3
#define CAN_MODULE_CMD_PHYSICAL_PWM 64
#define CAN_MODULE_CMD_PHYSICAL_TEMPERATURE_CELSIUS 65
#define CAN_MODULE_CMD_PHYSICAL_HUMIDITY_PERCENT 66
#define CAN_MODULE_CMD_PHYSICAL_VOLTAGE 67
#define CAN_MODULE_CMD_PHYSICAL_PHONENUMBER 68
#define CAN_MODULE_CMD_PHYSICAL_ROTARY_SWITCH 69
#define CAN_MODULE_CMD_PHYSICAL_BUTTON 70
#define CAN_MODULE_CMD_PHYSICAL_IR 71
#define CAN_MODULE_CMD_IRRECEIVE_IRRAW 128
#define CAN_MODULE_CMD_NMEA_POSITION 128
#define CAN_MODULE_CMD_DEBUG_PRINTF 128
#define CAN_MODULE_CMD_HD44789_LCD_CLEAR 128
#define CAN_MODULE_CMD_HD44789_LCD_CURSOR 129
#define CAN_MODULE_CMD_HD44789_LCD_TEXT 130
#define CAN_MODULE_CMD_HD44789_LCD_SIZE 131
#define CAN_MODULE_CMD_HD44789_LCD_BACKLIGHT 132
#define CAN_MODULE_CMD_HD44789_LCD_TEXTAT 133
#define CAN_MODULE_CMD_DIMMER230_DEMO 128
#define CAN_MODULE_CMD_DIMMER230_START_FADE 129
#define CAN_MODULE_CMD_DIMMER230_STOP_FADE 130
#define CAN_MODULE_CMD_DIMMER230_ABS_FADE 131
#define CAN_MODULE_CMD_DIMMER230_REL_FADE 132

//------------------- //
// Module definitions //
//------------------- //

#define CAN_MODULE_TYPE_TST_DEBUG 0
#define CAN_MODULE_TYPE_DEF_DEFAULT 1
#define CAN_MODULE_TYPE_SNS_DS18X20 3
#define CAN_MODULE_TYPE_SNS_FOST02 5
#define CAN_MODULE_TYPE_SNS_BUSVOLTAGE 6
#define CAN_MODULE_TYPE_SNS_SIMPLEDTMF 7
#define CAN_MODULE_TYPE_SNS_ROTARY 8
#define CAN_MODULE_TYPE_ACT_HD44789 9
#define CAN_MODULE_TYPE_ACT_DIMMER230 10
#define CAN_MODULE_TYPE_ACT_KS0108 11
#define CAN_MODULE_TYPE_ACT_RGBDRIVER 12
#define CAN_MODULE_TYPE_ACT_LEDPWM 13
#define CAN_MODULE_TYPE_SNS_IRRECEIVE 14
#define CAN_MODULE_TYPE_SNS_NMEA 15

//----------------- //
// Misc definitions //
//----------------- //

#define DIRECTIONFLAG_FROM_OWNER 1
#define DIRECTIONFLAG_TO_OWNER 0

#endif /*MODULEID_H_*/
