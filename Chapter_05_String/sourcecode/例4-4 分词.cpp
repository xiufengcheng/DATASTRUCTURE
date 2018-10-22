# include "stdlib.h"          // ���ļ�����malloc()��realloc()��free()�Ⱥ���
# include "iostream.h"        // ���ļ�������׼���������cout��cin
# include "DSqString.h"           // ���ļ�������̬˳�򴮵���ض��弰����
# define  MaxDictionaryLen   10   // �ִʴʵ����󳤶�
# define MaxWordLen 12            // ����ʵ���󳤶�

typedef struct 
{
	DSqString word;
	int num;
}WORD;        

int Segmentation(DSqString D[],int n,DSqString Str,WORD Result[])
{  // �Ժ��ִ�Str���зִ�,�ִʽ�����������Result��,�����ز�ͬ����ʵĸ���,
   // ����DΪ�ִʴʵ�
	int len,i,j,k=0,flag;                  // kͳ�Ʋ�ͬ����ʵĸ���
	DSqString Sub;
	for(i=0;i<n;i++)                       // �Խ��������г�ʼ��
	{
		StrAssign_Sq(Result[i].word,"");
		Result[i].num=0;
	}
    StrAssign_Sq(Sub,""); 
	for(i=0;i<Str.length;)                 // ���±�Ϊ0����ʼȡ��
	{
    for(len=MaxWordLen,flag=1;len>2&&flag;) // ��ǰ�ִʳ���Ϊlen
	   {
		if(i+len<Str.length)                    // ʣ�೤�ȴ��ڵ���len
            SubString_Sq(Str,Sub,i,len);          // ȡ����Ϊlen�Ӵ�
	    else                                    // ʣ�೤��С��len
            SubString_Sq(Str,Sub,i,Str.length-i); // ��ʣ����ַ���Ϊ�Ӵ�
		for(j=0;j<n;j++)                 // ��ȡ�����Ӵ���ִʴʵ����ƥ��
		    if(!StrCompare_Sq(Sub,D[j]))      // �ִʴʵ����д��ַ���
		    {  int m;
               for(m=0;m<k;m++)
		          if(!StrCompare_Sq(Sub,Result[m].word))// ����������д��ַ���(�������)
	              { Result[m].num++; break;  }         // �ú����Ƶ�ʼ�1
		          if(m==k)                            // ����������޴��ַ���(�������)
	              { StrCopy_Sq(Result[k].word,Sub);   // ��ȡ���ĺ���ʴ�ŵ����������
                 	Result[k].num=1;                  // �´ʵ�Ƶ��Ϊ1
                	k++;                              // �´�����1
	           }
	           i=i+len;flag=0; break;               // ȡ�ʳɹ�,׼��ȡ��һ�������
	        }
		if(j==n) len=len-2;                // �ִʴʵ����޴��ַ���,ȥ�����һ������
	   }
	   if(len==2) i=i+len;	                // ֻʣ��һ������,����һ�����ֿ�ʼȡ��
	}
   return k;     
}// Segmentation




void main()
{
	DSqString D[9]={{"�ٽ�",4},{"ѧ��",4},{"�������ʷ�չ",12},{"���ٽ�ѧģʽ",12},{"�о���ʵ��",10},{"�ܺ�",4},{"����",4},{"����",4},{"��չ",4}};
	DSqString Str={"�������ʷ�չ�о���ʵ��ٽ�ѧ������ѧ�����ʷ�չ�ĺܺø��ٽ�ѧģʽ�о���ʵ��ٽ�ѧ��",82};
	WORD Result[MaxDictionaryLen];
	int k;
	k=Segmentation(D,9,Str,Result);
	for(int i=0;i<k;i++)                           // ����ִʽ��
	{
		for(int j=0;j<Result[i].word.length;j++)
		cout<<Result[i].word.str[j];
		cout<<"���ôʳ���Ƶ��Ϊ��"<<Result[i].num<<endl;
	}
	return 0;
}
