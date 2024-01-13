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

struct vec3d
{
	float x, y, z;
};
typedef struct vec3d vec3d;

struct triangle
{
	vec3d p[3];
};
typedef struct triangle triangle;

//TODO: this is hack, replace this with vector or dynamic array
struct mesh
{
	triangle tris[2000];
    int counter;
};
typedef struct mesh mesh;

void _clear_screen(tContext *sContext){
    tRectangle sRect;
    sRect.i16XMin = 0;
    sRect.i16YMin = 0;
    sRect.i16XMax = 320;
    sRect.i16YMax = 240;

    GrContextForegroundSet(&sContext, ClrBlack);
    GrRectFill(&sContext, &sRect);
}

uint32_t clacRGB(int R, int G, int B){
    uint32_t result = R*65536 + G*256 + B;
    return result;
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





GrFlush(&sContext);


}