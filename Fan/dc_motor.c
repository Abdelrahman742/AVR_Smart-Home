/*
 * dc_motor.c
 *
 *  Created on: Jul 4, 2024
 *      Author: Abdelrahman Ibrahem Adel
 * Description: DC Motor driver
 */
#include "dc_motor.h"
#include "gpio.h"


void DcMotor_init()
{
	GPIO_setupPinDirection(PORTB_ID,PIN0_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN1_ID,PIN_OUTPUT);
	GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
	GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);
}
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	PWM_Timer0_Init(255*speed/100);
	if(state==CW)
	{
		GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_HIGH);
		GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);
	}
	else if(state==CCW)
	{
		GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
		GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_HIGH);
	}
	else
	{
		GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
		GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);
	}
}
