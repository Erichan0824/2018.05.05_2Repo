

void BCDtoASCII(char bcd, char *buf)
{
  buf[0] = (char)( (bcd>>4)+0x30 );
  buf[1] = (char)( (bcd&0x0f) + 0x30);
}

char BCDtoChar(char bcd)
{
  char value = 0;
  if(bcd > 0x99)
    return 99;
  value = (char)((bcd>>4)*10)+(char)(bcd&0x0f);
  return value;
}

char charToBCD(char data)
{
  char value = 0;
  if(data>99)
    return 0x99;
  value = (data/10)<<4;
  value += data%10;
  return value;
}

char intToASCII(unsigned int data,char *buffer)
{
  char i,value,flag=0,k=0;
  unsigned int factor=10000;
  if(data==0)     
  { 
    *(buffer+k)='0';
    k++;
  }
  else
  {
    for(i=0;i<5;i++)
    { 
      value=data/factor;
      if((value!=0)||flag)
      {
        *(buffer+k)=value|0x30;
        data%=factor; 
        k++; 
        flag++; 
      }  
      factor/=10;
    }
  }
  *(buffer+k) = 0;
  return k; 
}


char generateCRC(char *data,char num)
{
  char i,j,a,cy,cy1=0,crcdata,a1,a2=0,crc=0;
  for(j=0;j<num;j++)
  {   
    a=*(data+j);      
    a1=a; 
    for(i=0;i<8;i++)
    {
      a=a^crc;
      cy=a&0x01;  
      if(cy1!=0)
        crcdata=0x80;
      else
        crcdata=0; 
      a=crc;
      if(cy!=0)
      {
        a=a^0x18; 
        crcdata=0x80;
      }
      else
        crcdata=0;    
      cy1=a&0x01; 
      a>>=1;
      a=crcdata|a;
      crc=a;
      if(i==0)
        a=a1;
      else 
        a=a2;
      crcdata=a&0x01;
      a>>=1;
      if(crcdata!=0)
        a=a|0x80;
      a2=a;
    }
  } 
  return(crc); 
}   

int ASCIItoINT(char *data,char delimiter)
{
  char i,j=0,numOfDigit=0;
  int temp=0,f=1;      
  while(*(data+numOfDigit)!=delimiter) 
    numOfDigit++;
  if(*data=='-')
    j++;
  for(i=0;i<numOfDigit-j-1;i++)
    f*=10;
  for(i=j;i<numOfDigit;i++)
  {
    temp=temp+(*(data+i)&0xf)*f;
    f/=10;
  }
  if(j)
    temp=-temp;
  return temp;
}