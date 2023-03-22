#include <LCD.h>
void main(void)
{
    int len = 0;
    int len2 = 0;
    LCD_INIT();
    len = (int)(sizeof("ANZAL") / sizeof(char));
    len2 = (int)(sizeof("20BCS009") / sizeof(char));
    LCD_WRITE("ANZAL", 0, (16 - len) / 2);
    LCD_WRITE("20BCS009", 1, (16 - len2) / 2);
    while (1)
        ;
}