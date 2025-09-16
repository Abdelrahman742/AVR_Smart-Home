/*
 * Fan.c
 *
 *  Created on: Jul 4, 2024
 *      Author: Abdelrahman Ibrahem Adel
 * Description: Fan controller
 */
/**************************************Header Files***********************************************/
/*************************************************************************************************/
#include "adc.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "dc_motor.h"
/***************************************Application***********************************************/
/*************************************************************************************************/
int main()
{
	uint8 temp;/*variable of the temperature*/
	ADC_ConfigType ADC_Configurations = {F_CPU_8,Internal};/*structure of the adc configuration*/
	LCD_init();/*lcd initialization*/
	ADC_init(&ADC_Configurations);/*adc initializations*/
	DcMotor_init();/*dc motor initializations*/

	LCD_moveCursor(0,3);/*move the cursor to the place that t want write in it*/
	LCD_displayString("Fan is ");/*string that display all time in the program that show the fan state*/
	LCD_moveCursor(1,3);/*move the cursor to the place that t want write in it*/
	LCD_displayString("Temp =    C");/*string that display all time in the program that shows the temperature*/

	while(1)
	{
		temp=LM35_getTemperature();/*take the temperature from the sensor reading*/
		/*cases*/
		/*case 1 if the temperature lower than 30*/
		if(temp<30)
		{
			LCD_displayStringRowColumn(0,10,"OFF");/*Fan state*/
			DcMotor_Rotate(ST,0);/*motor state*/
			/*show the temperature*/
			LCD_moveCursor(1,9);
			LCD_intgerToString(temp);
		}
		/*case 2 if the temperature greater than 30*/
		/*make this case to allow increase and decrease the temperature and solve problem of the third number in decreasing case*/
		else if(temp>=30 && temp<100)
		{
			LCD_displayStringRowColumn(0,10,"ON");/*Fan state*/
			LCD_moveCursor(0,12);
			LCD_displayCharacter(' ');/*to overwrite F in OFF state*/
			LCD_moveCursor(1,11);
			LCD_displayCharacter(' ');
		    if(temp>=30 && temp<60)
		    {
		       DcMotor_Rotate(CW,25);/*motor state*/
		       /*show the temperature*/
		       LCD_moveCursor(1,9);
		       LCD_intgerToString(temp);
		    }
			else if(temp>=60 && temp<90)
			{
				DcMotor_Rotate(CW,50);/*motor state*/
				/*show the temperature*/
				LCD_moveCursor(1,9);
				LCD_intgerToString(temp);
			}
			else if(temp>=90 && temp<100)
			{
				DcMotor_Rotate(CW,75);/*motor state*/
			    /*show the temperature*/
			    LCD_moveCursor(1,9);
			    LCD_intgerToString(temp);
			}
		}
		else
		{
			LCD_displayStringRowColumn(0,10,"ON");/*Fan state*/
			LCD_moveCursor(0,12);
			LCD_displayCharacter(' ');/*to overwrite F in OFF state*/
			if(temp>=100 && temp<120)
			{
				DcMotor_Rotate(CW,75);/*motor state*/
				/*show the temperature*/
				LCD_moveCursor(1,9);
				LCD_intgerToString(temp);
			}
			else
			{
				DcMotor_Rotate(CW,100);/*motor state*/
				/*show the temperature*/
				LCD_moveCursor(1,9);
				LCD_intgerToString(temp);
			}
		}
	}
}
