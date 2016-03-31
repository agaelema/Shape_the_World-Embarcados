//*****************************************************************************
//
//	Lab02_HelloLaunchpad - launchpad Tiva/Stellaris
//	- version using the TivaWare - DriverLib
//
//	Author: Haroldo Amaral - 29/03/2016
//	www.embarcados.com.br/
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>

#include <inc/tm4c123gh6pm.h>			// include with specific hardware values
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

/*
 * Defines
 */
#define	SW_2		GPIO_PIN_0
#define LED_RED 	GPIO_PIN_1
#define LED_BLUE 	GPIO_PIN_2
#define LED_GREEN 	GPIO_PIN_3
#define	SW_1		GPIO_PIN_4


/*
 * Global Variable
 */
unsigned long In;  // input from PF4


/*
 * Prototypes of Functions
 */
void Delay(void);

/*
 * main code
 */
int main(void)
{
	/* Enable PORT F GPIO */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0
	GPIO_PORTF_CR_R = 0x01;           // allow changes to PF4-0

	/* set LED pins as outputs */
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_RED|LED_BLUE|LED_GREEN);

	/* set switch pins as input */
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, SW_1);


	/* configure the internal pullup */
	GPIOPadConfigSet(GPIO_PORTF_BASE, SW_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

	/*
	 * main loop - alternate RGB leds
	 */
    while(1)
    {
    	/* read the state of the switch */
    	In = GPIOPinRead(GPIO_PORTF_BASE, SW_1);

    	if (In == 0x00)
    	{
    		// set the green LED pin high, others low
        	GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_BLUE|LED_GREEN, LED_GREEN);	// set led Green
		}
    	else
    	{
    		// set the red LED pin high, others low
        	GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_BLUE|LED_GREEN, LED_RED);	// set led Green
    	}
    	Delay();
		// set the Blue LED pin high, others low
    	GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_BLUE|LED_GREEN, LED_BLUE);	// set led blue
    	Delay();
    }
}


void Delay(void)
{
	unsigned long volatile time;
	time = 727240*200/(91*4);

	while(time)
	{
		time--;
	}
}
