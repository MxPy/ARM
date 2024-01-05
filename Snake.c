//TODO: Zmień fonty


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

// Print some text to the display.
//
//***********************************************
void _clear_screen(tContext *sContext){
    tRectangle sRect;
    sRect.i16XMin = 0;
    sRect.i16YMin = 0;
    sRect.i16XMax = 320;
    sRect.i16YMax = 240;

    GrContextForegroundSet(&sContext, ClrBlack);
    GrRectFill(&sContext, &sRect);
}

void _draw_rect(tContext *sContext, int x, int y, int size){
    tRectangle sRect;
    sRect.i16XMin = x;
    sRect.i16YMin = y;
    sRect.i16XMax = x+size;
    sRect.i16YMax = y+size;
    
    GrContextForegroundSet(&sContext, ClrRed);
    GrRectFill(&sContext, &sRect);
}



int main(void){
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

    //X -> 320, Y -> 240 
    int i = 1;
    while(true){
        _clear_screen(&sContext);
        _draw_rect(&sContext, 10+i, 10, 10);
        ROM_SysCtlDelay(ROM_SysCtlClockGet()/2);
        GrFlush(&sContext);
        i+=10; 
    }

}