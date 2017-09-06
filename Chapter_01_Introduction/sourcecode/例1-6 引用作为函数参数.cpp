# include "stdio.h"
void swap(int &p1,int &p2)
{int temp;
temp=p1;
p1=p2;
p2=temp;}

void main( )
{
 int a=5,b=9;
  if(a<b) swap(a,b);
printf("\na=%d,b=%d\n",a,b);
 }
