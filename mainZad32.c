//*****************************************************************************
// hello.c - Simple hello world example.
//
// Maciej Kucia July 2013
//
// This is part of revision 1.0 of the EK-LM4F232 Firmware Package.
//*****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/fpu.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "grlib/grlib.h"
#include "drivers/ili9341_240x320x262K.h"
#include "utils/uartstdio.h"
#include "driverlib/gpio.h"
//*****************************************************************************
//
// TI logo in array form (1 bit per pixel)
//
//*****************************************************************************
const unsigned char TI_logo[(16*2)+5] = {IMAGE_FMT_1BPP_UNCOMP, 16,0, 16,0,0x0f,0xff,0x0f,0xff,0x0f,0xf3,0x0f,0xfa,0x0f,0x8f,0x0f,0x89,0x81,0x99,0x81,0x19,0x03,0x09,0x07,0x89,0x07,0xdf,0x3f,0xee,0x7f,0xf0,0xff,0xf8,0xff,0xf9,0xff,0xfb};
// 1,1,1,1,0,0,0,0, 1,1,1,1,1,1,1,1,
// 1,1,1,1,0,0,0,0, 1,1,1,1,1,1,1,1,
// 1,1,1,1,0,0,0,0, 1,1,0,0,1,1,1,1,
// 1,1,1,1,0,0,0,0, 0,1,0,1,1,1,1,1,
// 1,1,1,1,0,0,0,0, 1,1,1,1,0,0,0,1,
// 1,1,1,1,0,0,0,0, 1,0,0,1,0,0,0,1,
// 1,0,0,0,0,0,0,1, 1,0,0,1,1,0,0,1,
// 1,0,0,0,0,0,0,1, 1,0,0,1,1,0,0,0,
// 1,1,0,0,0,0,0,0, 1,0,0,1,0,0,0,0,
// 1,1,1,0,0,0,0,0, 1,0,0,1,0,0,0,1,
// 1,1,1,0,0,0,0,0, 1,1,1,1,1,0,1,1,
// 1,1,1,1,1,1,0,0, 0,1,1,1,0,1,1,1,
// 1,1,1,1,1,1,1,0, 0,0,0,0,1,1,1,1,
// 1,1,1,1,1,1,1,1, 0,0,0,1,1,1,1,1,
// 1,1,1,1,1,1,1,1, 1,0,0,1,1,1,1,1,
// 1,1,1,1,1,1,1,1, 1,1,0,1,1,1,1,1
//*****************************************************************************
//
// Print some text to the display.
//
//***********************************************
int main(void)
{
tContext sContext;


//
// Enable lazy stacking for interrupt handlers. This allows floating-point
// instructions to be used within interrupt handlers, but at the expense of
// extra stack usage.
//
ROM_FPULazyStackingEnable();
//
// Set the clocking to run directly from the crystal.
//
ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
//
// Initialize the display driver.
//
ILI9341_240x320x262K_Init();
//
// Initialize the graphics context.
//
GrContextInit(&sContext, &g_sILI9341_240x320x262K);
//
// Print some text
//
//GrContextFontSet(&sContext, g_psFontCm12);
//GrStringDrawCentered(&sContext, "Hello", -1,GrContextDpyWidthGet(&sContext) / 2,//(GrContextDpyHeightGet(&sContext) / 2),0);


//
// Flush any cached drawing operations.
//

//
// We are finished. Hang around doing nothing.
//


//
// Draw RGB rectangles
//

//X -> 320, Y -> 240 

//TL
GrContextForegroundSet(&sContext, ClrBrown);
GrCircleFill(&sContext, 160, 100, 80);

GrFlush(&sContext);

GrContextForegroundSet(&sContext, ClrWhite);
GrContextFontSet(&sContext, g_psFontCm20b);
GrStringDrawCentered(&sContext, "Napis 1", -1,
90, 200, 0);

GrContextForegroundSet(&sContext, ClrGreen);
GrContextFontSet(&sContext, g_psFontCm20b);
GrStringDrawCentered(&sContext, "Napis 2", -1,
320-90, 200, 0);

int i = 228;
GrContextForegroundSet(&sContext, ClrYellow);
while(i>=91){
    GrLineDraw(&sContext, 160, 21, i, 140);
    i--;
}




}