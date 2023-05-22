/*
Design and implement a program that outputs factors of a number
(input through switch) on LCD with buzzzer in between every factor.
*/

#include <LCD.h>
sbit buzz = P0 ^ 3;
unsigned int count = 0;
unsigned char a[16];
unsigned int f[20];
void input()
{
    unsigned int val = 0;
    if (INT0 == 0)
        val += 8;

    if (INT1 == 0)
        val += 4;

    if (T0 == 0)
        val += 2;

    if (T1 == 0)
        val += 1;
    if (val != 0)
        count = val;
}

int factors(int n)
{
    int j = 0, i = 1;
    for (
        i = 1; i <= n; i++)
    {
        if (n % i == 0)
        {
            f[j] = i;
            j++;
        }
    }
    return j;
}
void intToChar(long n)
{
    int i = 0, j = 0;
    for (i = 0; i < 16; i++)
    {
        a[i] = ' ';
    }
    i = 0;
    while (n != 0)
    {
        a[i] = (n % 10) + '0';
        i++;
        n = n / 10;
    }
    i--;
    while (j <= i)
    {
        char temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        i--;
        j++;
    }
}
void main(void)
{
    int i = 0;
    int c = 0;
    buzz = 1;
    LCD_INIT();

    while (1)
    {
        input();
        if (count == 0)
        {
            LCD_WRITE("Enter a number", 0, 0);
        }
        else
        {
            LCD_WRITE("Factors of ", 0, 0);
            delay(20);
            intToChar(count);
            LCD_WRITE(a, 0, 8);
            delay(20);

            LCD_WRITE("are ", 1, 0);
            c = factors(count);
            for (k = 0; k < c; k++)
            {
                intToChar(f[k]);

                LCD_WRITE(a, 1, 5);
                buzz = 0;
                delay(4000);
                buzz = 1;
            }
            count = 0;
        }
    }
}