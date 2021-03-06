MainMenuItem.prototype.CurrentPower = 0;
MainMenuItem.prototype.CurrentEnergy = 0;

function MainMenuItem(parentDisplay, hd44789Object)
{
	this.parentDisplay = parentDisplay;
	this.display = hd44789Object;
	var self = this;
	if (!this.parentDisplay.myInitialArguments["power"])
	{
		log(this.myName + ":" + this.myId + "> Failed to initialize, power-config missing from config.\n");
		return;
	}
	
	/* Get the PWM service that we want from the ServiceManager, it takes type, service name, service id */
	this.myPowerService = ServiceManager.getService("Can", "power", this.parentDisplay.myInitialArguments["power"]["Id"]);
	/* Add a callback for when the service goes online */
	this.myPowerService.registerEventCallback("online", function(args) { self.PowerOnline(); });
	/* Add a callback for when the sensor reports a new value */
	this.myPowerService.registerEventCallback("newValue", function(args) { self.powerUpdate(); });
	/* If the service is already online we should call the handler here */
	this.PowerOnline();


}

MainMenuItem.prototype.PowerOnline = function()
{
	/* If service is not online do nothing */
	if (this.myPowerService.isOnline())
	{
		log("Power is online!\n");
		/* Set report interval to 2 seconds */
	//	this.myPowerService.setReportInterval(4);
//this.myPowerService.setEnergy(1649500);
	}
}

MainMenuItem.prototype.powerUpdate = function()
{
	this.CurrentPower = this.myPowerService.getPower();
	this.CurrentEnergy = this.myPowerService.getEnergy();
}

/* the display object who created the menu item */
MainMenuItem.prototype.parentDisplay = null;
/* the display that we are writing to */
MainMenuItem.prototype.display = null;

/* How often the display shall update [ms]*/
MainMenuItem.prototype.UpdateTime = 5000;

/* what MainMenuItem is left of this item, if used */
MainMenuItem.prototype.LeftItem = null;
/* what MainMenuItem is right of this item, if used */
MainMenuItem.prototype.RightItem = null;
/* what MainMenuItem is after of this item, if used */
MainMenuItem.prototype.PressEnterItem = null;
/* what MainMenuItem is before of this item, if used */
MainMenuItem.prototype.PressBackItem = null;
/* what MainMenuItem is below of this item, if used */
MainMenuItem.prototype.DownItem = null;
/* what MainMenuItem is abowe of this item, if used */
MainMenuItem.prototype.UpItem = null;

/*
Standard events can be:
left, right, enter, back, up, down....
*/
MainMenuItem.prototype.processEvent = function (event)
{
		switch (event)
	{
	case "left":
		this.parentDisplay.changeToLeft();
		break;

	case "right":
		this.parentDisplay.changeToRight();
		break;
	
	case "up":
		//parentDisplay.changeToUp();
		break;
	
	case "down":
		//parentDisplay.changeToDown();
		break;
	
	case "enter":
		//parentDisplay.changeToEnter();
		break;
	
	case "back":
		//parentDisplay.changeToBack();
		break;
	}
}

MainMenuItem.prototype.onEnter = function ()
{
	this.display.clearScreen("Standard");
}
MainMenuItem.prototype.update = function ()
{
	var date = new Date();
	/* Get the current date time on the format YYYY-mm-dd HH.ii.ss */
	var dateAndTime = date.getDateFormated()+" "+date.getTimeShortFormated();
	this.display.printText(0, 1, this.parentDisplay.lcdCenterText(""+ getSensorValue('Vardagsrumssensor').toFixed(1).toString() + " C   " + getSensorValue('Västersensor').toFixed(1).toString() + "C"));
	this.display.printText(0, 0, this.parentDisplay.lcdCenterText(""+dateAndTime));

	this.display.printText(0, 2, this.parentDisplay.lcdCenterText(""+ getSensorValue('Sovrumssensor').toFixed(1).toString() + " C   " + getSensorValue('Östersensor').toFixed(1).toString() + "C"));

	this.display.printText(0, 3, this.parentDisplay.lcdCenterText(""+this.CurrentPower.toString()+" W  "+(this.CurrentEnergy/1000).toString() + "kWh"));
}
MainMenuItem.prototype.onExit = function ()
{
	
}

