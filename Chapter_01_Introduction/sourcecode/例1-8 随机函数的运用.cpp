# include "iostream.h"                 // 该文件包含标准输入输出流cout和cin
# include "stdlib.h"
void main( )
{
	int i;
	for(i=0;i<10;i++)
		cout<<rand()%100<<" ";
	cout<<endl;
	srand(2);
	for(i=0;i<10;i++)
		cout<<rand()%100<<" ";
	cout<<endl;
	srand(1);
	for(i=0;i<10;i++)
		cout<<rand()%100<<" ";
	cout<<endl;
}
