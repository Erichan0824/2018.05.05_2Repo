


#define delay_us(us) __delay_cycles(36864*us/10000)
#define delay_ms(ms) __delay_cycles(36864*ms/10)

char BCDtoChar(char bcd);
char BCDtoChar(char bcd);
char charToBCD(char data);


char intToASCII(unsigned int data,char *buffer);

char generateCRC(char *data,char num);
int ASCIItoINT(char *data,char delimiter);

/*
±¨¾¯£º
1¡¢¼üÅÌ°´ÏÂ----------·äÃùÆ÷ÏìÒ»Éù
2¡¢µôµç--------------»ÆµÆÉÁ£¬·äÃùÆ÷ÉÁ
3¡¢µôµç¾²Òô----------»ÆµÆÉÁ£¬·äÃùÆ÷¹Ø
4¡¢Ğ¹Â©--------------ºìµÆÉÁ£¬·äÃùÆ÷ÉÁ
5¡¢Ğ¹Â©¾²Òô----------»ÆµÆÉÁ£¬·äÃùÆ÷¹Ø
6¡¢ÎŞ±¨--------------¶¼¹Ø
*/