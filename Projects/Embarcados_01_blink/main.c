//*****************************************************************************
//
//	Blink led test - launchpad Tiva/Stellaris
//	- version without the TivaWare - DriverLib
//
//	Author: Haroldo Amaral - 02/03/2016
//	www.embarcados.com.br
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>

/*
 * Hardware Defines
 */
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))


/*
 * Defines
 */
#define LED_RED 	0x02		// GPIO_PIN_1
#define LED_BLUE 	0x04		// GPIO_PIN_2
#define LED_GREEN 	0x08		// GPIO_PIN_3


/*
 * Global Variable
 */
uint32_t ui32Loop;


/*
 * Prototypes of Functions
 */

/*
 * main code
 */
int main(void)
{
	volatile uint32_t delay = 0;		// dummy variable

	/* Enable the clock on PORTF */
	SYSCTL_RCGC2_R |= 0x00000020;     	// 1) F clock
	delay = SYSCTL_RCGC2_R;           	// delay - ensure clock

	/* configure other registers */
	GPIO_PORTF_LOCK_R = 0x4C4F434B;   	// 2) unlock PortF PF0
	GPIO_PORTF_CR_R = 0x1F;           	// allow changes to PF4-0
	GPIO_PORTF_AMSEL_R = 0x00;        	// 3) disable analog function
	GPIO_PORTF_PCTL_R = 0x00000000;   	// 4) GPIO clear bit PCTL
	GPIO_PORTF_DIR_R = 0x0E;          	// 5) PF4,PF0 input, PF3,PF2,PF1 output
	GPIO_PORTF_AFSEL_R = 0x00;        	// 6) no alternate function
	GPIO_PORTF_PUR_R = 0x11;          	// enable pullup resistors on PF4,PF0
	GPIO_PORTF_DEN_R = 0x1F;          	// 7) enable digital pins PF4-PF0

	/*
	 * main loop - alternate RGB leds
	 */
    while(1)
    {
    	GPIO_PORTF_DATA_R = LED_RED;  							// set led red
		for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++);		// little delay

    	GPIO_PORTF_DATA_R = LED_GREEN;  						// set led green
		for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++);		// little delay

    	GPIO_PORTF_DATA_R = LED_BLUE;  							// set led blue
		for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++);		// little delay
    }
}
