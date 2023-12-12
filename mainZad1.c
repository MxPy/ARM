/*
main.c
*/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#define GPIO_PINS_ALL GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7

int8_t reverseBits(int8_t num) {
    int8_t result = 0;

    for (int i = 0; i < 8; i++) {
        result <<= 1;          // Left shift the result to make room for the next bit
        result |= (num & 1);   // Set the least significant bit of result to the current bit of num
        num >>= 1;             // Right shift num to move to the next bit
    }

    return result;
}

int8_t calcNWD(int8_t num1, int8_t num2){
    int8_t a = num1;
    int8_t b = num2;
    int8_t c = 0;
    while(b != 0){
        c = b;
        b = a%b;
        a = c;
    }
    return a;
}


int main(void)
{
int8_t a = 0;
int8_t b = 0;
int8_t c = 0;

//
// Set the clocking to run directly from the crystal.
//
ROM_SysCtlClockSet (SYSCTL_SYSDIV_20 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);
//
// Enable GPIOA, GPIOJ, GPIOC
//
SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOA);
SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOJ);
SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOH);
SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOE);
SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOG);
SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOC);
SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOB);
//
// Set all GPIOA and GPIOC pins as outputs
//
GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PINS_ALL);
GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PINS_ALL);
GPIOPinTypeGPIOOutput(GPIO_PORTG_BASE, GPIO_PINS_ALL);
GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PINS_ALL);
GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PINS_ALL);
//
// Set all GPIOJ pins as inputs
//
GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_6|GPIO_PIN_7);

GPIOPinTypeGPIOInput(GPIO_PORTH_BASE, GPIO_PIN_6|GPIO_PIN_7);

for (;;)
{
//
// Check button press and write data to port
//
if(GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_7) == GPIO_PIN_7)
    a++;
//GPIOPinWrite (GPIO_PORTA_BASE, GPIO_PIN_6|GPIO_PIN_7, 0x80);
if(GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_6) == GPIO_PIN_6)
    a--;
//GPIOPinWrite (GPIO_PORTA_BASE, GPIO_PIN_6|GPIO_PIN_7, 0x40);

if(GPIOPinRead(GPIO_PORTH_BASE,GPIO_PIN_7) == GPIO_PIN_7)
    b++;
//GPIOPinWrite (GPIO_PORTE_BASE, GPIO_PIN_6|GPIO_PIN_7, 0x80);
if(GPIOPinRead(GPIO_PORTH_BASE,GPIO_PIN_6) == GPIO_PIN_6)
    b--;
//GPIOPinWrite (GPIO_PORTE_BASE, GPIO_PIN_6|GPIO_PIN_7, 0x40);
//
// Show some patterns on LEDs
//


if(a>=0){
    GPIOPinWrite (GPIO_PORTE_BASE, 0xFF, a);
}else{
    GPIOPinWrite (GPIO_PORTE_BASE, 0xFF, reverseBits(a));
}

if(b>=0){
    GPIOPinWrite (GPIO_PORTA_BASE, 0xFF, b);
}else{
    GPIOPinWrite (GPIO_PORTA_BASE, 0xFF, reverseBits(b));
}
c = b-a;

if(c>=0){
    GPIOPinWrite (GPIO_PORTG_BASE, 0xFF, c);
}else{
    GPIOPinWrite (GPIO_PORTG_BASE, 0xFF, reverseBits(c));
}
if(a>0 && b>0){
    GPIOPinWrite (GPIO_PORTB_BASE, 0xFF, calcNWD(a,b));
    GPIOPinWrite (GPIO_PORTC_BASE, 0xFF, a*b/calcNWD(a,b));
}

//
// Delay for a while so changes can be visible
//
SysCtlDelay(SysCtlClockGet() / 2);
}
return 0;
}
