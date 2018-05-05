#include <iom88p.h>
#include <inavr.h>
/*
#pragma vector = EE_RDY_vect
__interrupt void EEPROM_READY_interrupt(void)
{
}
*/
void writeChar(int position,char data)
{
  __disable_interrupt();
  EEAR = position;   //地址寄存器
  EEDR = data;   //数据寄存器
  EECR |= (1<<EEMPE);  // EEPROM 控制寄存器  位2 – EEMWE: EEPROM 写使能 EEMWE决定设置EEWE为"1“是否可以
  EECR |= (1<<EEPE);  // 位1 – EEPE: EEPROM 写使能  置位EEWE 以启动写操作E
  __enable_interrupt();
  SMCR = (1<<SE);
  __sleep();
  SMCR = 0;
}

void writeBlock(int position,char *buffer,char num)
{  
  char i;
  while (EECR & (1<<EEPE)); //等待上一次写操作结束
  EECR |= (1<<EERIE);  //位3 – EERIE: 使能EEPROM 准备好中断
  for(i=0;i<num;i++)
    writeChar(position+i,*(buffer+i));
  EECR &= ~(1<<EERIE);
}

char readChar(int position)
{
  EEAR = position; 
  EECR |= (1<<EERE); //位 0 – EERE: EEPROM 读使能  设置EERE 以启动读操作 */
  return EEDR;
}

void readBlock(char *buffer,int position,char num)
{
  char i;
  while (EECR & (1<<EEPE)); //等待上一次写操作结束
  for(i=0;i<num;i++)  //
    *(buffer+i) = readChar(position+i);
}
                              

