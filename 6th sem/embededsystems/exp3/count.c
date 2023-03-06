#include<p89v51rx2.h>

void delay(unsigned int count)
{
    unsigned int i, j;
    for (i = 0; i < 1000; i++)
    {
        for (j = 0; j < count; j++)
        {
        }
    }
}

void main()
{
    while (1)
    {
        int i = 7, j;
        while (i >= 0)
        {
            j = i;
            WR = (j & 1);
            j >> 1;
            TxD = (j & 1);
            j >> 1;
            RxD = (j & 1);
            delay(20);
            i--;
        }
    }
}