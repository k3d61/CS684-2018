/*
 * Author: Kedar Anavardekar
 * Roll No.  : 17305R006

*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_ints.h"
#include <time.h>

uint8_t sw2status = 0 ;

/*

* Function Name: pin_config()

* Input: none

* Output: none

* Description: Set Port F Pin 1, Pin 2, Pin 3 as output. On this pin Red, Blue and Green LEDs are connected.
               Set Port F Pin 0 and 4 as input, enable pull up on both these pins.
*/

void pin_config(void)
{
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0);

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK ) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR )   = 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK ) = 0;

    GPIOPadConfigSet(GPIO_PORTF_BASE,
                     GPIO_PIN_4 | GPIO_PIN_0,
                     GPIO_STRENGTH_2MA,
                     GPIO_PIN_TYPE_STD_WPU );

}

/*

 */
int lab1Part1(void)
{
    pin_config();
    uint8_t ui8LED = 2;
    uint8_t switch1Flag1 = 0, switch1Flag2 = 0;
    while(1)
    {
        switch1Flag2 = 0;
        uint8_t i = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);
        if ( i == 0 )
        {
            switch1Flag1 = 1;
        }
        else if( i != 0 && switch1Flag1 == 1 )
        {
            switch1Flag1 = 0;
            switch1Flag2 = 1;
        }
        if( i == 0 )
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, ui8LED);
        }
        else
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);

        if( switch1Flag2 == 1 )
        {
            ui8LED =  ui8LED == 8 ? 2 : ui8LED*2;

        }
    }
}

int lab1Part3(void)
{
    pin_config();
    uint8_t ui8LED = 2;
    uint8_t switch1Flag1 = 0, switch1Flag2 = 0;
    uint8_t switch2Flag1 = 0, switch2Flag2 = 0;
    uint8_t delayCounter = 1;
    while(1)
    {
        uint8_t i = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
        uint8_t j = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);


        switch2Flag2 = 0;
        if ( j == 0 )
        {
            switch2Flag1 = 1;
        }
        else if( j != 0 && switch2Flag1 == 1 )
        {
            switch2Flag1 = 0;
            sw2status++;
            switch2Flag2 = 1;
        }

        switch1Flag2 = 0;
        if ( i == 0 )
        {
            switch1Flag1 = 1;
        }
        else if( i != 0 && switch1Flag1 == 1 )
        {
            switch1Flag1 = 0;
            switch1Flag2 = 1;
        }

        if( i == 0 )
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, ui8LED);
            SysCtlDelay(6700000 * delayCounter);


        }
        else
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);

        if( switch1Flag2 == 1 )
        {
            ui8LED =  ui8LED == 8 ? 2 : ui8LED*2;

        }
        if( switch2Flag2 == 1 )
        {
            delayCounter =  delayCounter == 4 ? 1 : delayCounter * 2;

        }
    }
}
