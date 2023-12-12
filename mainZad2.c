#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "inc/hw_gpio.h"
#include "driverlib/rom.h"
void playSound(uint32_t frequency, uint32_t duration, float volume)
{
uint32_t PWMclock = ROM_SysCtlClockGet() / 4 ; // get the current PWM clock value
uint32_t period = (PWMclock/frequency) - 1; // calculate the period for PWM signal
float numOfCyc = ROM_SysCtlClockGet()/1000.0; // calculate number of cycles per ms
uint32_t counter = duration * numOfCyc / 3; //calculate the counter for SysCtlDelay function;
ROM_PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, period); // set the period of the PWM signal
// Set the pulse width of PWM1 for a 50% duty cycle:
ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, volume * period);
ROM_PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, true); // enable PWM1 output
ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_1); // enable the PWM signal generation
ROM_SysCtlDelay(counter); // add delay
ROM_PWMGenDisable(PWM1_BASE, PWM_GEN_1); // disable the PWM signal generation
}
void noteC(int a, float volume){playSound(523+a*10, 200, volume);}
void noteD(int a, float volume){playSound(587+a*10, 200, volume);}
void noteE(int a, float volume){playSound(659+a*10, 200, volume);}
void noteF(int a, float volume){playSound(698+a*10, 200, volume);}
void noteG(int a, float volume){playSound(784+a*10, 200, volume);}
void noteA(int a, float volume){playSound(880+a*10, 200, volume);}
void noteB(int a, float volume){playSound(988+a*10, 200, volume);}


#define GPIO_PINS_ALL GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7



int main(void)
{
int8_t a = 0;
float volume = 0.5;
//
// Set the clocking to run directly from the crystal.
//
ROM_SysCtlClockSet (SYSCTL_SYSDIV_20 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);
//
// Enable GPIOA, GPIOJ, GPIOC




//
// Set all GPIOJ pins as inputs
//
GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_6|GPIO_PIN_7);
GPIOPinTypeGPIOInput(GPIO_PORTH_BASE, GPIO_PIN_6|GPIO_PIN_7);
GPIOPinTypeGPIOInput(GPIO_PORTG_BASE, GPIO_PIN_6|GPIO_PIN_7);

for (;;)
{
//
// Check button press and write data to port
//
if(GPIOPinRead(GPIO_PORTG_BASE,GPIO_PIN_7) == GPIO_PIN_7)
    a++;
if(GPIOPinRead(GPIO_PORTG_BASE,GPIO_PIN_6) == GPIO_PIN_6)
    a--;
if(GPIOPinRead(GPIO_PORTG_BASE,GPIO_PIN_3) == GPIO_PIN_7)
    volume+=0.1;
if(GPIOPinRead(GPIO_PORTG_BASE,GPIO_PIN_2) == GPIO_PIN_6)
    volume-=0.1;



if(GPIOPinRead(GPIO_PORTH_BASE,GPIO_PIN_0) == GPIO_PIN_7)
    noteC(a-10, volume);
if(GPIOPinRead(GPIO_PORTH_BASE,GPIO_PIN_1) == GPIO_PIN_7)
    noteD(a-10, volume);
if(GPIOPinRead(GPIO_PORTH_BASE,GPIO_PIN_2) == GPIO_PIN_7)
    noteE(a-10, volume);
if(GPIOPinRead(GPIO_PORTH_BASE,GPIO_PIN_3) == GPIO_PIN_7)
    noteF(a-10, volume);
if(GPIOPinRead(GPIO_PORTH_BASE,GPIO_PIN_4) == GPIO_PIN_7)
    noteG(a-10, volume);
if(GPIOPinRead(GPIO_PORTH_BASE,GPIO_PIN_5) == GPIO_PIN_7)
    noteA(a-10, volume);
if(GPIOPinRead(GPIO_PORTH_BASE,GPIO_PIN_6) == GPIO_PIN_7)
    noteB(a-10, volume);


if(GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_0) == GPIO_PIN_7)
    noteC(a, volume);
if(GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_1) == GPIO_PIN_7)
    noteD(a, volume);
if(GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_2) == GPIO_PIN_7)
    noteE(a, volume);
if(GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_3) == GPIO_PIN_7)
    noteF(a, volume);
if(GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_4) == GPIO_PIN_7)
    noteG(a, volume);
if(GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_5) == GPIO_PIN_7)
    noteA(a, volume);
if(GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_6) == GPIO_PIN_7)
    noteB(a, volume);






//
// Delay for a while so changes can be visible
//
SysCtlDelay(SysCtlClockGet() / 2);
}
return 0;
}
