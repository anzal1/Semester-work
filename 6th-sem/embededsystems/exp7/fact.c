#include <LCD.h>

unsigned int count = 0;
unsigned char a[16];

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

void delay(unsigned int d)
{
    unsigned int j, i;
    for (i = 0; i <= 1000; i++)
    {
        for (j = 0; j < d; j++)
            ;
    }
}

int fact(int n)
{
    long factorial = 1;
    while (n)
    {
        factorial *= n;
        n--;
    }
}

void intToChar(int n)
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
            LCD_WRITE("You entered ", 0, 0);
            intToChar(count);
            LCD_WRITE(a, 0, 12);
            delay(20);

            LCD_WRITE("Factorial is ", 1, 0);
            intToChar(fact(count));
            LCD_WRITE(a, 1, 12);
            delay(20);
            count = 0;
        }
    }
}