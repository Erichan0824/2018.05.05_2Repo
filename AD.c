#define MY_AD_GLOBALS
#include "includes.h"


void adc_init(void)
{
  ADMUX = 1<<REFS0;
  ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);//64分频 172.8K@11.0592M
  DIDR0 = 0x1F;
}

INT16U read_adc(INT8U adc_input)//查询方式读取ADC单端通道
{
  INT8U index;
  INT16U adc_temp = 0;
  
  ADMUX &= 0xF8;
  ADMUX |= adc_input;
  
  for(index = 0; index < 5; index++)      //启动5次转换求平均值
  {
    ADCSRA |= (1<<ADSC); //启动AD转换
    while ((ADCSRA&(1<<ADIF))==0); 
    ADCSRA |= (1<<ADIF); //写1清除标志位
    adc_temp += ADC;
  }
  
  return (adc_temp/5); //ADC=ADCH:ADCL
}
