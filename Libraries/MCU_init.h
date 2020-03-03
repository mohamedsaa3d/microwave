//------------------------------------------------------------------------------------------------------
// CONFIG1
#pragma config FOSC    = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE    = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE   = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE   = ON       // MCLR/VPP/RE3 Pin Function Select bit (MCLR/VPP/RE3 pin function is MCLR)
#pragma config BOREN   = OFF      // Brown-out Reset Enable bit (Disabled)
#pragma config BORV    = 20        // Brown-out Reset Voltage bits (VBOR set to 2.0V)
#pragma config CCP2MX  = RC1     // CCP2 Multiplex bit (CCP2 is on RC1)
#pragma config CP      = OFF         // Flash Program Memory Code Protection bits (Code protection off)

// CONFIG2
#pragma config FCMEN   = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO    = OFF       // Internal External Switchover bit (Internal External Switchover mode disabled)
#pragma config BORSEN  = OFF     // Brown-out Reset Software Enable bit (Disabled)

// #pragma config statements should precede project file includes.
//------------------------------------------------------------------------------------------------------