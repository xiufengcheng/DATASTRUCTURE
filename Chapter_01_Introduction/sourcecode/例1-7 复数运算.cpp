# include "iostream.h"                 // 该文件包含标准输入输出流cout和cin
struct complex {
int real;
int imag;
  complex&operator+(complex &s)   //重载"+"，函数直接写在结构体内！
{
    complex c;
    c.real=real+s.real;
    c.imag=imag+s.imag;
    return c;
   }
complex&operator+=(complex &s); //重载"+="，函数在结构体外部！
friend ostream&operator<<(ostream &output,complex &s); //以友元函数方式重载
};
complex &complex::operator+=(complex &s)
{
real+=s.real;
imag+=s.imag;
return *this;
}
ostream&operator<<(ostream &output,complex &s)
{
output<<" a.real="<<s.real<<"  a.imag="<<s.imag<<endl;
return output;
}
void main()
{
complex c={0,0},a,b={1,5};
a=b+b;
c+=b;
cout<<a;
cout<<" c.real="<<c.real<<"  c.imag="<<c.imag<<endl;
cout<<" b.real="<<b.real<<"  b.imag="<<b.imag<<endl;
}
