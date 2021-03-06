/* the display object who created the menu item */
PIDMenuItem.prototype.parentDisplay = null;
//PIDMenuItem.prototype.sensors = null;
PIDMenuItem.prototype.mode = 0;
PIDMenuItem.prototype.sub_mode = 0;
PIDMenuItem.prototype.tempVariable = 0;
PIDMenuItem.prototype.myPIDService = null;

PIDMenuItem.prototype.StoredData = null;

PIDMenuItem.prototype.tempVariableKP = 0;
PIDMenuItem.prototype.tempVariableKI = 0;
PIDMenuItem.prototype.tempVariableKD = 0;
PIDMenuItem.prototype.tempVariableTime = 0;
PIDMenuItem.prototype.tempVariableUnit = 0;
PIDMenuItem.prototype.tempVariableActType = 0;
PIDMenuItem.prototype.tempVariableActModId = 0;
PIDMenuItem.prototype.tempVariableActId = 0;
PIDMenuItem.prototype.PIDTempsensorModuleNames    = [ "DS18x20", "FOST02"];

function PIDMenuItem(parentDisplay, hd44789Object)
{
	var self = this;
	this.parentDisplay = parentDisplay;
	this.display = hd44789Object;
	
	
	/* Get the PWM service that we want from the ServiceManager, it takes type, service name, service id */
	this.myPIDService = "PID";
}

/* the display object who created the menu item */
PIDMenuItem.prototype.parentDisplay = null;
/* the display that we are writing to */
PIDMenuItem.prototype.display = null;

/* How often the display shall update [ms]*/
PIDMenuItem.prototype.UpdateTime = 5000;

/* what PIDMenuItem is left of this item, if used */
PIDMenuItem.prototype.LeftItem = null;
/* what PIDMenuItem is right of this item, if used */
PIDMenuItem.prototype.RightItem = null;
/* what PIDMenuItem is after of this item, if used */
PIDMenuItem.prototype.PressEnterItem = null;


/*
Standard events can be:
left, right, enter, back, up, down....
*/
PIDMenuItem.prototype.processEvent = function (event)
{
	switch (this.mode)
	{
	case 0:
		switch (event)
		{
		case "right":
			this.parentDisplay.changeToRight();
			break;
		case "left":
			this.parentDisplay.changeToLeft();
			break;
		case "enter":
			this.mode = 1;
			this.sub_mode = 0;
			var last_value_string = Storage_GetParameter("LastValues", this.myPIDService);
			StoredData = eval("(" + last_value_string + ")");
			Display_Clear(this.display);
			break;
		}
		break;
	case 1:
		switch (event)
		{
		case "right":
			this.sub_mode++;
			if (this.sub_mode > 3) {
				this.sub_mode = 0;
			}
			break;
		case "left":
			if (this.sub_mode == 0) {
				this.sub_mode = 4;
			}
			this.sub_mode--;
			break;
		case "enter":
			switch (this.sub_mode)
			{
			case 0:
				this.mode = 2;
				this.sub_mode = 0;
				//this.tempVariable = this.myPIDService.Reference;
				this.tempVariable = parseFloat(StoredData["PID_status"]["Reference"]);
				break;
			case 1:
				this.mode = 3;
				this.sub_mode = 0;
				//this.tempVariableKP = this.myPIDService.K_P;
				//this.tempVariableKI = this.myPIDService.K_I;
				//this.tempVariableKD = this.myPIDService.K_D;
				//this.tempVariableTime = this.myPIDService.RegulatorTime;
				//this.tempVariableUnit = this.myPIDService.TimeUnit;
				this.tempVariableKP = parseInt(StoredData["Parameters"]["K_P"]);
				this.tempVariableKI = parseInt(StoredData["Parameters"]["K_I"]);
				this.tempVariableKD = parseInt(StoredData["Parameters"]["K_D"]);
				this.tempVariableTime = parseInt(StoredData["Parameters"]["RegulatorTime"]);
				this.tempVariableUnit = StoredData["Parameters"]["TimeUnit"];

				break;
			case 2:
				this.mode = 0;
				this.sub_mode = 0;
				break;
			case 3:
				this.mode = 4;
				this.sub_mode = 0;
				//this.tempVariableActType = this.myPIDService.actuatorModuleType;
				//this.tempVariableActModId = this.myPIDService.actuatorModuleId;
				//this.tempVariableActId = this.myPIDService.actuatorId;
				this.tempVariableActType = parseInt(StoredData["Actuator"]["actuatorModuleType"]);
				this.tempVariableActModId = parseInt(StoredData["Actuator"]["actuatorModuleId"]);
				this.tempVariableActId = parseInt(StoredData["Actuator"]["actuatorId"]);
			}
			Display_Clear(this.display);
			break;
		}
		break;
	case 2:
		switch (event)
		{
		case "right":
			if (this.sub_mode == 3) {
				this.tempVariable = this.tempVariable + 0.5;
			} else {
				this.sub_mode++;
				if (this.sub_mode > 2) {
					this.sub_mode = 0;
				}
			}
			break;
		case "left":
			if (this.sub_mode == 3) {
				this.tempVariable = this.tempVariable - 0.5;
			} else {
				if (this.sub_mode == 0) {
					this.sub_mode = 3;
				}
				this.sub_mode--;
			}
			break;
		case "enter":
			switch (this.sub_mode)
			{
			case 0:
				this.sub_mode = 3;
				break;
			case 1:
				//spara
				//this.myPIDService.setValue(this.tempVariable);
				PID_setValue(this.myPIDService, this.tempVariable);
				this.mode = 0;
				this.sub_mode = 0;
				break;
			case 2:
				this.mode = 0;
				this.sub_mode = 0;
				break;
			case 3:
				this.sub_mode = 0;
				break;
			}
			break;
		}
		break;
	case 3:
		switch (event)
		{
		case "right":
			switch (this.sub_mode)
			{
			case 7:
				this.tempVariableKP++;
				if (this.tempVariableKP >= 65000)
					this.tempVariableKP = 0;
				break;
			case 8:	
				this.tempVariableKI++;
				if (this.tempVariableKI >= 65000)
					this.tempVariableKI = 0;
				break;
			case 9:
				this.tempVariableKD++;
				if (this.tempVariableKD >= 65000)
					this.tempVariableKD = 0;
				break;
			case 10:
				this.tempVariableTime++;
				if (this.tempVariableUnit == "s") {
					if (this.tempVariableTime > 256) {
						this.tempVariableTime = 0;
					}
				} else {
					if (this.tempVariableTime > 65000) {
						this.tempVariableTime = 0;
					}
				}
	
				break;
			case 11:
				if (this.tempVariableUnit == "s")
					this.tempVariableUnit = "ms"
				else
					this.tempVariableUnit = "s"
				break;
			default:
				this.sub_mode++;
				if (this.sub_mode > 6) {
					this.sub_mode = 0;
				}
				break;
			}
			break;
		case "left":
			switch (this.sub_mode)
			{
			case 7:
				this.tempVariableKP--;
				if (this.tempVariableKP == -1)
					this.tempVariableKP = 65000;
				break;
			case 8:	
				this.tempVariableKI--;
				if (this.tempVariableKI == -1)
					this.tempVariableKI = 65000;
				break;
			case 9:
				this.tempVariableKD--;
				if (this.tempVariableKD == -1)
					this.tempVariableKD = 65000;
				break;
			case 10:
				this.tempVariableTime--;
				if (this.tempVariableTime == -1) {
					if (this.tempVariableUnit == "s")
						this.tempVariableTime = 255;
					else
						this.tempVariableTime = 65000;
				}
				break;
			case 11:
				if (this.tempVariableUnit == "s")
					this.tempVariableUnit = "ms"
				else
					this.tempVariableUnit = "s"
				break;
			default:
				if (this.sub_mode == 0) {
					this.sub_mode = 7;
				}
				this.sub_mode--;
				break;
			}
			break;
		case "enter":
			switch (this.sub_mode)
			{
			case 0:	//spara
				//this.myPIDService.setParameters(this.tempVariableKP,this.tempVariableKI,this.tempVariableKD,this.tempVariableTime,this.tempVariableUnit);
				PID_setParameters(this.myPIDService,this.tempVariableKP,this.tempVariableKI,this.tempVariableKD,this.tempVariableTime,this.tempVariableUnit);
				this.mode = 0;
				this.sub_mode = 0;
				break;
			case 1:	//goto main
				this.mode = 0;
				this.sub_mode = 0;
				break;
			case 2:	//change K_P
				this.sub_mode = 7;
				break;
			case 3:	//change K_I
				this.sub_mode = 8;
				break;
			case 4: //change K_D
				this.sub_mode = 9;
				break;
			case 5: //change time
				this.sub_mode = 10;
				break;
			case 6: //change time unit
				this.sub_mode = 11;
				break;
			default:
				this.sub_mode = this.sub_mode - 5;
				break;
			}
			break;
		}
		break;
	case 4:
		switch (event)
		{
		case "right":
			switch (this.sub_mode)
			{
			case 6:
				this.tempVariableActType++;
				if (this.tempVariableActType>= 255)
					this.tempVariableActType = 0;
				break;
			case 7:	
				this.tempVariableActModId++;
				if (this.tempVariableActModId>= 255)
					this.tempVariableActModId = 0;
				break;
			case 8:
				this.tempVariableActId++;
				if (this.tempVariableActId>= 255)
					this.tempVariableActId = 0;
				break;
			case 9:
				break;
			default:
				this.sub_mode++;
				if (this.sub_mode > 5) {
					this.sub_mode = 0;
				}
				break;
			}
			break;
		case "left":
			switch (this.sub_mode)
			{
			case 6:
				this.tempVariableActType--;
				if (this.tempVariableActType == -1)
					this.tempVariableActType = 255;
				break;
			case 7:	
				this.tempVariableActModId--;
				if (this.tempVariableActModId == -1)
					this.tempVariableActModId = 255;
				break;
			case 8:
				this.tempVariableActId--;
				if (this.tempVariableActId == -1)
					this.tempVariableActId = 255;
				break;
			case 9:
				break;
			default:
				this.sub_mode--;
				if (this.sub_mode == -1) {
					this.sub_mode = 5;
				}
				break;
			}
			break;
		case "enter":
			switch (this.sub_mode)
			{
			case 0:	//spara
				//this.myPIDService.setParameters(this.tempVariableKP,this.tempVariableKI,this.tempVariableKD,this.tempVariableTime,this.tempVariableUnit);
				this.mode = 0;
				this.sub_mode = 0;
				break;
			case 1:	//goto main
				this.mode = 0;
				this.sub_mode = 0;
				break;
			case 2:	//change K_P
				this.sub_mode = 6;
				break;
			case 3:	//change K_I
				this.sub_mode = 7;
				break;
			case 4: //change K_D
				this.sub_mode = 8;
				break;
			case 5: //change time
				this.sub_mode = 9;
				break;
			default:
				this.sub_mode = this.sub_mode - 4;
				break;
			}
			break;
		}
		break;

	}
}

PIDMenuItem.prototype.onEnter = function ()
{
	this.mode = 0;
	Display_Clear(this.display);
	//this.myPIDService.getConfiguration();
	PID_getConfiguration(this.myPIDService);
	
	var last_value_string = Storage_GetParameter("LastValues", this.myPIDService);
	this.StoredData = eval("(" + last_value_string + ")");
	//Log(this.StoredData["PID_status"]["Reference"]);
			
}
PIDMenuItem.prototype.update = function ()
{
	//this.display.clearScreen();
	switch (this.mode)
	{
	case 1:
		switch (this.sub_mode)
		{
		case 0:
			Display_Print(this.display,0, 3,"> Set Temperature");
			break;
		case 1:
			Display_Print(this.display,0, 3,"> Settings       ");
			break;
		case 2:
			Display_Print(this.display,0, 3,"> Tillbaka       ");
			break;
		case 3:
			Display_Print(this.display,0, 3,"> Konfiguration  ");
			break;
		}
		Display_Print(this.display,0, 0,"Reference:    "+parseFloat(this.StoredData["PID_status"]["Reference"]).toFixed(1).toString()+"¤C");	
		Display_Print(this.display,0, 1,"Measurment:   "+parseFloat(this.StoredData["PID_status"]["Measurment"]).toFixed(1).toString()+"¤C");
		Display_Print(this.display,0, 2,"Out:"+(parseFloat(this.StoredData["PID_status"]["PWM"])/100).toFixed(1).toString()+"% Sum: "+parseFloat(this.StoredData["PID_status"]["Sum"]).toFixed(0).toString());
		break;
	case 0:
		Display_Print(this.display,0, 0,"Reference:    "+parseFloat(this.StoredData["PID_status"]["Reference"]).toFixed(1).toString()+"¤C");	
		Display_Print(this.display,0, 1,"Measurment:   "+parseFloat(this.StoredData["PID_status"]["Measurment"]).toFixed(1).toString()+"¤C");
		Display_Print(this.display,0, 2,"Out:"+(parseFloat(this.StoredData["PID_status"]["PWM"])/100).toFixed(1).toString()+"% Sum: "+parseFloat(this.StoredData["PID_status"]["Sum"]).toFixed(0).toString());
		Display_Print(this.display,0, 3,"                    ");
		break;
	case 2:
		Display_Print(this.display,0, 0,"Set temperature:");
		switch (this.sub_mode)
		{
		case 0:
			Display_Print(this.display,0, 1,"   > "+this.tempVariable.toFixed(1).toString()+"¤C");
			Display_Print(this.display,0, 3,"  Spara     Ångra");
			break;
		case 1:
			Display_Print(this.display,0, 1,"     "+this.tempVariable.toFixed(1).toString()+"¤C")
			Display_Print(this.display,0, 3,"> Spara     Ångra");
			break;
		case 2:
			Display_Print(this.display,0, 1,"     "+this.tempVariable.toFixed(1).toString()+"¤C")
			Display_Print(this.display,0, 3,"  Spara   > Ångra");
			break;
		case 3:
			Display_Print(this.display,0, 1,"  <> "+this.tempVariable.toFixed(1).toString()+"¤C")
			Display_Print(this.display,0, 3,"  Spara     Ångra");
			break;
		}
		break;
	case 3:
		
		switch (this.sub_mode)
		{
		case 0:	//spara
			Display_Print(this.display,0, 0," K_P:  "+this.tempVariableKP);
			Display_Print(this.display,10, 0," K_I:  "+this.tempVariableKI);
			Display_Print(this.display,0, 1," K_D:  "+this.tempVariableKD);
			Display_Print(this.display,0, 2," Time: "+this.tempVariableTime+" "+this.tempVariableUnit);
			Display_Print(this.display,0, 3,"> Spara     Ångra");
			break;
		case 1:	//goto main
			Display_Print(this.display,0, 0," K_P:  "+this.tempVariableKP);
			Display_Print(this.display,10, 0," K_I:  "+this.tempVariableKI);
			Display_Print(this.display,0, 1," K_D:  "+this.tempVariableKD);
			Display_Print(this.display,0, 2," Time: "+this.tempVariableTime+" "+this.tempVariableUnit);
			Display_Print(this.display,0, 3,"  Spara   > Ångra");
			break;
		case 2:	//change K_P
			Display_Print(this.display,0, 0,">K_P:  "+this.tempVariableKP);
			Display_Print(this.display,10, 0," K_I:  "+this.tempVariableKI);
			Display_Print(this.display,0, 1," K_D:  "+this.tempVariableKD);
			Display_Print(this.display,0, 2," Time: "+this.tempVariableTime+" "+this.tempVariableUnit);
			Display_Print(this.display,0, 3,"  Spara     Ångra");
			break;
		case 3:	//change K_I
			Display_Print(this.display,0, 0," K_P:  "+this.tempVariableKP);
			Display_Print(this.display,10, 0,">K_I:  "+this.tempVariableKI);
			Display_Print(this.display,0, 1," K_D:  "+this.tempVariableKD);
			Display_Print(this.display,0, 2," Time: "+this.tempVariableTime+" "+this.tempVariableUnit);
			Display_Print(this.display,0, 3,"  Spara     Ångra");
			break;
		case 4: //change K_D
			Display_Print(this.display,0, 0," K_P:  "+this.tempVariableKP);
			Display_Print(this.display,10, 0," K_I:  "+this.tempVariableKI);
			Display_Print(this.display,0, 1,">K_D:  "+this.tempVariableKD);
			Display_Print(this.display,0, 2," Time: "+this.tempVariableTime+" "+this.tempVariableUnit);
			Display_Print(this.display,0, 3,"  Spara     Ångra");
			break;
		case 5: //change time
			Display_Print(this.display,0, 0," K_P:  "+this.tempVariableKP);
			Display_Print(this.display,10, 0," K_I:  "+this.tempVariableKI);
			Display_Print(this.display,0, 1," K_D:  "+this.tempVariableKD);
			Display_Print(this.display,0, 2,">Time: "+this.tempVariableTime+" "+this.tempVariableUnit);
			Display_Print(this.display,0, 3,"  Spara     Ångra");
			break;
		case 6: //change time unit
			Display_Print(this.display,0, 0," K_P:  "+this.tempVariableKP);
			Display_Print(this.display,10, 0," K_I:  "+this.tempVariableKI);
			Display_Print(this.display,0, 1," K_D:  "+this.tempVariableKD);
			Display_Print(this.display,0, 2," Time: "+this.tempVariableTime+">"+this.tempVariableUnit);
			Display_Print(this.display,0, 3,"  Spara     Ångra");
			break;
		case 7:	//change K_P
			Display_Print(this.display,0, 0," K_P: ["+this.tempVariableKP+"]");
			Display_Print(this.display,10, 0," K_I:  "+this.tempVariableKI);
			Display_Print(this.display,0, 1," K_D:  "+this.tempVariableKD);
			Display_Print(this.display,0, 2," Time: "+this.tempVariableTime+" "+this.tempVariableUnit);
			Display_Print(this.display,0, 3,"  Spara     Ångra");
			break;
		case 8:	//change K_I
			Display_Print(this.display,0, 0," K_P:  "+this.tempVariableKP);
			Display_Print(this.display,10, 0," K_I: ["+this.tempVariableKI+"]");
			Display_Print(this.display,0, 1," K_D:  "+this.tempVariableKD);
			Display_Print(this.display,0, 2," Time: "+this.tempVariableTime+" "+this.tempVariableUnit);
			Display_Print(this.display,0, 3,"  Spara     Ångra");
			break;
		case 9: //change K_D
			Display_Print(this.display,0, 0," K_P:  "+this.tempVariableKP);
			Display_Print(this.display,10, 0," K_I:  "+this.tempVariableKI);
			Display_Print(this.display,0, 1," K_D: ["+this.tempVariableKD+"]");
			Display_Print(this.display,0, 2," Time: "+this.tempVariableTime+" "+this.tempVariableUnit);
			Display_Print(this.display,0, 3,"  Spara     Ångra");
			break;
		case 10: //change time
			Display_Print(this.display,0, 0," K_P:  "+this.tempVariableKP);
			Display_Print(this.display,10, 0," K_I:  "+this.tempVariableKI);
			Display_Print(this.display,0, 1," K_D:  "+this.tempVariableKD);
			Display_Print(this.display,0, 2," Time:["+this.tempVariableTime+"]"+this.tempVariableUnit);
			Display_Print(this.display,0, 3,"  Spara     Ångra");
			break;
		case 11: //change time unit
			Display_Print(this.display,0, 0," K_P:  "+this.tempVariableKP);
			Display_Print(this.display,10, 0," K_I:  "+this.tempVariableKI);
			Display_Print(this.display,0, 1," K_D:  "+this.tempVariableKD);
			Display_Print(this.display,0, 2," Time: "+this.tempVariableTime+"["+this.tempVariableUnit+"]");
			Display_Print(this.display,0, 3,"  Spara     Ångra");
			break;
		}
		break;
	case 4:
		switch (this.sub_mode)
		{
		case 0:	//spara
			Display_Print(this.display,0, 0," PWM: "+this.tempVariableActType+ " "+this.tempVariableActModId +" " + this.tempVariableActId);
			Display_Print(this.display,0, 1," Sensor: "+getSensorName(this.myPIDService.sensorModuleType, this.myPIDService.sensorModuleId , this.myPIDService.sensorId));
			Display_Print(this.display,0, 3,"> Spara     Ångra");
			break;
		case 1:	//goto main
			Display_Print(this.display,0, 0," PWM: "+this.tempVariableActType+ " "+this.tempVariableActModId +" " + this.tempVariableActId);
			Display_Print(this.display,0, 1," Sensor: "+getSensorName(this.myPIDService.sensorModuleType, this.myPIDService.sensorModuleId , this.myPIDService.sensorId));
			Display_Print(this.display,0, 3,"  Spara   > Ångra");
			break;
		case 2:	//change pwm
			Display_Print(this.display,0, 0,">PWM: "+this.tempVariableActType+ " "+this.tempVariableActModId +" " + this.tempVariableActId);
			Display_Print(this.display,0, 1," Sensor: "+getSensorName(this.myPIDService.sensorModuleType, this.myPIDService.sensorModuleId , this.myPIDService.sensorId));
			Display_Print(this.display,0, 3,"  Spara     Ångra");
			break;
		case 3:	//change sensor
			Display_Print(this.display,0, 0," PWM: "+this.tempVariableActType+ " "+this.tempVariableActModId +" " + this.tempVariableActId);
			Display_Print(this.display,0, 1,">Sensor: "+getSensorName(this.myPIDService.sensorModuleType, this.myPIDService.sensorModuleId , this.myPIDService.sensorId));
			Display_Print(this.display,0, 3,"  Spara     Ångra");
			break;
		case 4: //change K_D
			Display_Print(this.display,0, 0," PWM:["+this.tempVariableActType+ "]"+this.tempVariableActModId +" " + this.tempVariableActId);
			Display_Print(this.display,0, 1," Sensor: "+getSensorName(this.myPIDService.sensorModuleType, this.myPIDService.sensorModuleId , this.myPIDService.sensorId));
			Display_Print(this.display,0, 3,"  Spara     Ångra");
			break;
		case 5: //change time
			Display_Print(this.display,0, 0," PWM: "+this.tempVariableActType+ "["+this.tempVariableActModId +"]" + this.tempVariableActId);
			Display_Print(this.display,0, 1," Sensor: "+getSensorName(this.myPIDService.sensorModuleType, this.myPIDService.sensorModuleId , this.myPIDService.sensorId));
			Display_Print(this.display,0, 3,"  Spara     Ångra");
			break;
		case 6: //change time unit
			Display_Print(this.display,0, 0," PWM: "+this.tempVariableActType+ " "+this.tempVariableActModId +"[" + this.tempVariableActId+"]");
			Display_Print(this.display,0, 1," Sensor: "+getSensorName(this.myPIDService.sensorModuleType, this.myPIDService.sensorModuleId , this.myPIDService.sensorId));
			Display_Print(this.display,0, 3,"  Spara     Ångra");
			break;
		case 7:	//change K_P
			Display_Print(this.display,0, 0," PWM: "+this.tempVariableActType+ " "+this.tempVariableActModId +" " + this.tempVariableActId);
			Display_Print(this.display,0, 1," Sensor:["+getSensorName(this.myPIDService.sensorModuleType,  this.myPIDService.sensorModuleId , this.myPIDService.sensorId)+"]");
			Display_Print(this.display,0, 3,"  Spara     Ångra");
			break;
		}
		break;

	}
}


PIDMenuItem.prototype.onExit = function ()
{
	this.mode = 0;
	this.sub_mode = 0;
}


