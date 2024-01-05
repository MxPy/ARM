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
const int MAXH = 240;
const int MAXW = 320;

struct triangle{
    int TopX;
    int TopY;
    int LeftX;
    int LeftY;
    int RightX;
    int RightY;
};
typedef struct triangle Triangle;

void drawTriangle(tContext *pContext,Triangle* tr1, uint32_t color){
    GrContextForegroundSet(&pContext, color);
    float x = (float)tr1->RightX;
    float y = (float)tr1->RightY;
    float yJump = (float)(tr1->RightY-tr1->LeftY)/(tr1->RightX-tr1->LeftX)/3;
    while(x>=tr1->LeftX){
        GrLineDraw(&pContext, tr1->TopX, tr1->TopY, x, y);
        x-=0.33;
        y-=yJump;
    }
}

uint32_t clacRGB(int R, int G, int B){
    uint32_t result = R*65536 + G*256 + B;
    return result;
}

void drawCube(tContext *pContext, int x, int y, int z, int rotationX, int rotationY, int rotationZ, uint32_t color){
    //int polygonsOnScreen = (int)(float)
}



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

uint32_t red = clacRGB(255,52,25);
uint32_t semiDarkRed = clacRGB(240,29,0);
uint32_t darkRed = clacRGB(180,21,0);

//left bottom
Triangle tr1;
tr1.TopX = 80;
tr1.TopY = 80;
tr1.LeftX = 80;
tr1.LeftY = MAXH-80;
tr1.RightX = MAXW/2;
tr1.RightY = MAXH-40;
//drawTriangle(&sContext, &tr1, ClrRed);
drawTriangle(&sContext, &tr1, semiDarkRed);

//left top
tr1.TopX = MAXW/2;
tr1.TopY = MAXH-40;
tr1.LeftX = 80;
tr1.LeftY = 80;
tr1.RightX = MAXW/2;
tr1.RightY = 120;
//drawTriangle(&sContext, &tr1, ClrBlue);
drawTriangle(&sContext, &tr1, semiDarkRed);

//rtight top
tr1.TopX = MAXW/2;
tr1.TopY = 120;
tr1.LeftX = MAXW/2;
tr1.LeftY = MAXH-40;
tr1.RightX = MAXW-80;
tr1.RightY = 80;
//drawTriangle(&sContext, &tr1, ClrGreen);
drawTriangle(&sContext, &tr1, darkRed);

//right bottom
tr1.TopX = MAXW-80;
tr1.TopY = 80;
tr1.LeftX = MAXW/2;
tr1.LeftY = MAXH-40;
tr1.RightX = MAXW-80;
tr1.RightY = MAXH-80;
//drawTriangle(&sContext, &tr1, ClrYellow);
drawTriangle(&sContext, &tr1, darkRed);

//top top
tr1.TopX = MAXW/2;
tr1.TopY = 40;
tr1.LeftX = MAXW/2;
tr1.LeftX = 80;
tr1.LeftY = 80;
tr1.RightX = MAXW-80;
tr1.RightY = 80;
//drawTriangle(&sContext, &tr1, ClrBrown);
drawTriangle(&sContext, &tr1, red);

//top bottom
tr1.TopX = MAXW/2;
tr1.TopY = 120;
tr1.LeftX = MAXW/2;
tr1.LeftX = 80;
tr1.LeftY = 80;
tr1.RightX = MAXW-80;
tr1.RightY = 80;
//drawTriangle(&sContext, &tr1, ClrWhite);
drawTriangle(&sContext, &tr1, red);



GrFlush(&sContext);


}