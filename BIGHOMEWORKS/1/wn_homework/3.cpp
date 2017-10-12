#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
using namespace std;

bool isHuiwen(char *ch){
    char *p,*q;
    q=p=ch;
    int i=0;
    while(*p!='@'){
        p++;
        i++;
    }
    p--;
    i=i/2;
    while(i>=0){
        if(*p==*q){
            p--;q++;
            i--;
        }else{
            return false;
        }
    }
    return true;
}

int main()
{
    char a[10],e;
    int i=0;
    cout<<"请输入回文字符串，以@结束："<<endl;
    while((e=getchar())!='@'){
        a[i++]=e;
    }
    a[i]='@';
    cout<<isHuiwen(a)<<endl;
    return 0;
}
