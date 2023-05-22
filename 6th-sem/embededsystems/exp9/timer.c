/*
Design and implement an ES that toggle pin P1.5 continuouasly every 250 ms
using 8051 board. Use crystal frequency = 11.0592 MHz & Timer 1 mode |.
*/

#include <p89v51rx2.h>
sbit x = P1 ^ 5;
sbit led1 = P3 ^ 0;
sbit buzz = P0 ^ 3;

void delay(unsigned int k)
{
    while (k--)
    {
        TMOD = 0x01;
        TH0 = 0xDC;
        TL0 = 0x00;
        TR0 = 1;
        while (TF0 == 0)
            ;
        TR0 = 0;
        TF0 = 0;
    }
}

void main(void)
{
    while (1)
    {
        x = 0;
        buzz = 0;
        led1 = 0;
        delay(500);
        x = 1;
        buzz = 1;
        led1 = 1;
        delay(500);
    }
}