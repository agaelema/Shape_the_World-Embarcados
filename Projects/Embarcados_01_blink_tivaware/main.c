//*****************************************************************************
//
//	Blink led test - launchpad Tiva/Stellaris
//	- version using the TivaWare - DriverLib (Stéfano Tutorial)
//
//	Author: Haroldo Amaral - 02/03/2016
//	www.embarcados.com.br
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
#define LED_RED 	GPIO_PIN_1
#define LED_BLUE 	GPIO_PIN_2
#define LED_GREEN 	GPIO_PIN_3

/*
 * Global Variable
 */
volatile uint32_t ui32Loop;				// used in delay function inside the loop

/*
 * Prototypes of Functions
 */

/*
 * main code
 */
int main(void)
{
	/* Enable PORT F GPIO */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	/* set LED pins as outputs */
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_RED|LED_BLUE|LED_GREEN);

	/*
	 * main loop - alternate RGB leds
	 */
    while(1)
    {
		GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_BLUE|LED_GREEN, LED_RED);		// set led red
		for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++);						// little delay

		// set the green LED pin high, others low
    	GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_BLUE|LED_GREEN, LED_GREEN);	// set led Green
    	for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++);						// little delay

		// set the green LED pin high, others low
    	GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_BLUE|LED_GREEN, LED_BLUE);	// set led blue
    	for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++);						// little delay
    }
}
