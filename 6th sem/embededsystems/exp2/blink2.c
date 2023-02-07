#include <reg52.h>

sbit LED1 = P3 ^ 0;
sbit LED2 = P3 ^ 1;

void Delay(void);

void main(void)
{
    while (1)
    {
        LED1 = 0;
        LED2 = 0;
        Delay();
        LED1 = 1;
        Delay();
        LED2 = 1;
        Delay();
    }
}

void Delay(void)
{
    int j;
    int i;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10000; j++)
        {
        }
    }
}