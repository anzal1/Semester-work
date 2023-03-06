#include <p89v51rx2.h>

sbit sw1 = P3 ^ 2;
sbit sw2 = P3 ^ 3;
sbit sw3 = P3 ^ 4;
sbit sw4 = P3 ^ 5;

void delay(unsigned int n)
{
    unsigned int i;
    unsigned int j;
    for (i = 0; i < 1000; i++)
    {
        for (j = 0; j <= 3 * n; j++)
        {
        }
    }
}

void counter(unsigned int count)
{
    int i = count, j;
    while (i >= 0)
    {
        j = i;
        RD = !(j & 1);
        j >>= 1;
        WR = !(j & 1);
        j >>= 1;
        TxD = !(j & 1);
        j >>= 1;
        RxD = !(j & 1);
        delay(10);
        i--;
    }
}

void main(void)
{
    sw1 = 1;
    sw2 = 1;
    sw3 = 1;
    sw4 = 1;
    while (1)
    {
        if (sw1 == 0)
        {
            while (1)
            {
                counter(1);
                if (sw2 == 0 || sw3 == 0 || sw4 == 0)
                {
                    break;
                };
            }
        }
        if (sw2 == 0)
        {

            while (1)
            {
                counter(3);
                if (sw1 == 0 || sw3 == 0 || sw4 == 0)
                {
                    break;
                };
            }
        }
        if (sw3 == 0)
        {

            while (1)
            {
                counter(7);
                if (sw2 == 0 || sw1 == 0 || sw4 == 0)
                {
                    break;
                };
            }
        }

        if (sw4 == 0)
        {
            while (1)
            {
                counter(15);
                if (sw2 == 0 || sw3 == 0 || sw1 == 0)
                {

                    break;
                };
            }
        }
    }
}
