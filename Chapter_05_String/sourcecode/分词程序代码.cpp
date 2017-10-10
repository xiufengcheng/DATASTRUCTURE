// Document.cpp: implementation of the Document class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "frequency.h"
#include "Document.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "Document.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//词表操作

void Document::initTmpWordArray()
//词汇表初始化
{	
	int i;
	for (i=0;i<=255;i++) tmpWordArray[i]=NULL;	
}

void Document::InCreaseWord(WordType *pWord)
//指定词条频度加1
{	
	if (pWord==NULL) return;
	pWord->count ++;
}

void Document::ArrangeWord(WordType * pWord,int intMethod,int Direction)
//intMethod=1 词条频率 =2 词条文内权重
//插入词条按照词频或者词权重对wordtype进行排序
{	
	int i,j;
	if (intMethod==1)	
	{
		// 插入排序
		for (i=0;i<intWordCount[Direction-1];i++) //intWordCount描述lastWordArray[]中两个方向的词数.by xfguo
			if (lastWordArray[Direction-1][i].count<=pWord->count)//Direction; 1 正向　；2 反向
			{ 
				for(j=intWordCount[Direction-1]-1;j>=i;j--) 
					lastWordArray[Direction-1][j+1]=lastWordArray[Direction-1][j]; 
				break;
			}
		lastWordArray[Direction-1][i]=*pWord;
		intWordCount[Direction-1]++;
	}
	else if (intMethod==2)	
	{	
		for (i=0;i<intWordCount[Direction-1];i++)
			if (lastWordArray[Direction-1][i].weight_count<=pWord->weight_count )
			{ 
				for(j=intWordCount[Direction-1]-1;j>=i;j--) 
					lastWordArray[Direction-1][j+1]=lastWordArray[Direction-1][j]; 
				break;
			}
		lastWordArray[Direction-1][i]=*pWord;
		intWordCount[Direction-1]++;
	}
	else if (intMethod==0)
	{	
		lastWordArray[Direction-1][intWordCount[Direction-1]]=*pWord;
		intWordCount[Direction-1]++;
	}
}

void Document::AddNewWord(char * strWord,int intWordCount,int intWordLength,float weight)
//加入新的词汇
{	
	//if (IfExtendWordTable==2) return;
	if (strlen(strWord)>48 ) return ;
	WordType * pWordTmp,*pWordInsert,*pWordStart,*pTmp;	
	pWordTmp=(WordType *)malloc(sizeof(WordType));
    	pWordTmp->next=tmpWordArray[(unsigned char)(*strWord)];
	pWordTmp->count=intWordCount;
	pWordTmp->length=intWordLength;
	pWordTmp->weight=weight; //???
	strcpy(pWordTmp->word,strWord);

	//插入排序
	pWordStart=tmpWordArray[(unsigned char)(*strWord)];
	pWordInsert=NULL;

	while((pWordStart!=NULL)&&(pWordStart->length>intWordLength))
	{	
		pWordInsert=pWordStart;
		pWordStart=pWordStart->next;
	}
	
	if (pWordInsert==NULL)
	{	
		pTmp=tmpWordArray[(unsigned char)(*strWord)];
		tmpWordArray[(unsigned char)(*strWord)]=pWordTmp;
		pWordTmp->next=pTmp;
	}
	else
	{	
		pTmp=pWordInsert;
		pWordInsert->next=pWordTmp;
		pWordTmp->next =pWordStart;
	}
}

void Document::freeWordTable(WordType * pWord)
//词汇表行的释放
{	
	WordType *tmpWord;
	while (pWord!=NULL)
	{
		tmpWord=pWord->next;
		free(pWord);
		pWord=tmpWord;
	}

/*	WordType * q;
	while (pWord!=NULL)
	{	
		q=pWord->next;
	        free(pWord); 
		pWord=q;
	}
*/

}

void Document::ArrangeWordInTable(int YuZhi,int intMethod,int Direction)
//intMethod=1 词条频率 =2 词条文内权重 =0 不排序
//输出词条排序
//tmpWordArray[]按一定的顺序插入到lastWordArray[]中
{	
	int i;
	intWordCount[Direction-1]=0;
	WordType *pWord;
	
	for (i=0;i<=255;i++) 
	{	pWord=tmpWordArray[i];
		while (pWord!=NULL)
		{	if (pWord->count>=YuZhi) ArrangeWord(pWord,intMethod,Direction);
			pWord=pWord->next;
		}
	}
}

void Document::ResetWordTable()//将词频设置为0
{
	int i;
	WordType *pWord;
	for (i=0;i<=255;i++) 
	{	pWord=tmpWordArray[i];
		while (pWord!=NULL)
		{	pWord->count=0;
			pWord->weight_count=0; 
			pWord=pWord->next;
		}
	}
}

void Document::ClearWordTable()//清空词表内的词条
{	
	int i;
	WordType *pWord;
	for (i=0;i<=255;i++) 
	{	pWord=tmpWordArray[i];
		while (pWord!=NULL)
		{	pWord->count=0;
			pWord->weight_count=0; 
			pWord=pWord->next;
		}
	}
}

WordType * Document::FindWord(char *strWord)
//查询表中有无所查的单词，如果找到，返回指针位置，否则返回NULL
{	
	if (*strWord=='\0') return NULL;//出错误
	WordType * pStartPlace;
	pStartPlace=tmpWordArray[(unsigned char)(*strWord)];
	while (pStartPlace!=NULL)
	{	
		if (strcmp(strWord,pStartPlace->word)==0) return pStartPlace;  //找到了
		pStartPlace=pStartPlace->next ;
	}
	return NULL;//没有找到
}

void Document::freeTmpWordArray()
//词汇表的释放
{	
	int i;
	for (i=0;i<=255;i++) {freeWordTable(tmpWordArray[i]);tmpWordArray[i]=NULL;}
}

void Document::initArrangeTable()
//释放临时词表
{	
	intWordCount[0]=0;
	intWordCount[1]=0;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//词条文件操作

//筛选后导出词条
void Document::WriteWordToFile(char * strFileName,int ifWriteFre,int Direction)
//ifWriteFre =1 输出词频 =0 no
{	
	FILE *fWrite;
	if((fWrite=fopen(strFileName,"w"))==NULL) return ;
	int i;
	int count;
	char strWordTmp[50];
	count=intWordCount[Direction-1];

	for (i=0;i<count;i++)
	{	
		if (Direction==2)
			ReverseString(lastWordArray[Direction-1][i].word,strWordTmp);
		else	strcpy(strWordTmp,lastWordArray[Direction-1][i].word);
		if (ifWriteFre==1){
			//if (strWordTmp[0]<128)
			//	continue;
		 	fprintf(fWrite,"%s %d\n",strWordTmp,lastWordArray[Direction-1][i].count);
		}
		else 	fprintf(fWrite,"%s\n",strWordTmp);
	}
	fclose(fWrite);
}

void Document::copylastword(WordType *pWordtype,int *wordnum)
{             
	int i;
	int count=intWordCount[0];	
		
	*wordnum=intWordCount[0];
	
	for (i=0;i<intWordCount[0];i++)
	{	
		strcpy(pWordtype[i].word,lastWordArray[0][i].word);
                pWordtype[i].count =lastWordArray[0][i].count;
	}
} 

int Document::ReadFileFromText(char* strFileName)
//读取文本文件内容到字符串。自动分配内存。
{	
	/* if (strSource!=NULL) free(strSource); */
	FILE* fp;
	long lFileLength;
	if((fp=fopen(strFileName,"rb"))!=NULL)
	{           
		fseek(fp,0,SEEK_END);
		lFileLength=ftell(fp);
		rewind(fp);
		
		strSource=(char *)malloc(lFileLength+1);
		fread(strSource,lFileLength,1,fp);
		*(strSource+lFileLength)='\0';
		fclose(fp);
	
                //去掉换行 
		//直接在strsource上修改，那个更更好？？-

		char * strTmpSource;
		strTmpSource=(char *)malloc(lFileLength+1);
		int i,j;
		j=0;
		for (i=0;i<=lFileLength;i++)
		{
			if (*(strSource+i)!='\r' && *(strSource+i) !='\n')
			{  
				*(strTmpSource+j) = *(strSource+i);
			   	j ++;
			}
		}			
		lFileLength=j;
		free(strSource);
		strSource=(char *)malloc(lFileLength+1);
		*(strSource+lFileLength+1)='\0';
		strcpy(strSource,strTmpSource);
		free(strTmpSource);
		
	  	return 1;
	}
	else
	{
		//AfxMessageBox(strFileName);
		return 0;
	}
}
	
int Document::GetCharFromString(char * strSource,int intStartPlace,char * strReturn,int * intCharLength)
//取得源串中的从绝对地址开始的字符
//返回值：0 末尾；1 字符 ；2 符号 ；-1 出错 ；4 回车
//                 汉语    
{	
	unsigned char char1,char2;
	char strVertueWord[1000];

	int intStrLength;
	WordType * pWord;
	int i;
	
	char1=(unsigned char)(*(strSource+intStartPlace));
	if (char1==0) return 0;
	char2=(unsigned char)(*(strSource+intStartPlace+1));

	if (char1>128) 
	{	
		if (char2==0) return -1;
		*strReturn=(char)(char1);
		*(strReturn+1)=(char)(char2);
		*(strReturn+2)='\0';
		*intCharLength=2;
		
		if (Direction==2) ReverseString("－—；／　。，：、！？的了在你我她它他到是不和《〉》〈～【】〖〗×∥■▲○●→─·…★“”‘’（）—",strVertueWord);
		else strcpy(strVertueWord,"；－—／　。，：、！？的了在你我她它他到是不和《〉 》〈～【】〖〗×∥■▲○●→─·…★“”‘’（）—");
		if (strstr(strVertueWord,strReturn)==NULL) return 1;
		else if ((strstr(strVertueWord,strReturn)-strVertueWord)%2==1) return 1;
		else return 2;
	}
	
	*strReturn=(char)(char1);
	*(strReturn+1)='\0';

	if (CheckIfEnglishChar(char1))//字母开头字母结尾 
	{
		intStrLength=0;
		
		while (CheckIfEnglish(*(strSource+intStartPlace+1)))
		{
			* (strReturn+intStrLength)=LowerCase(*(strSource+intStartPlace));
			intStartPlace++;
			intStrLength++;
		}
		
		if (CheckIfEnglishChar(*(strSource+intStartPlace)))
		{ 
			* (strReturn+intStrLength)=LowerCase(*(strSource+intStartPlace));
			intStrLength++;
		}

    		*(strReturn+intStrLength)='\0';

		if (intStrLength>1) 
		{	
			for (i=0;i<intStrLength;i++)
			if (CheckIfEnglishChar(*(strReturn+i)))
			{	
				if (intStrLength<20) 
				{ 
					pWord=FindWord(strReturn);
				  	if (pWord==NULL) AddNewWord(strReturn,1,intStrLength,4.0);//???
				  	else InCreaseWord(pWord);
				  	break;
				}
			}
		}

		*intCharLength=intStrLength;return 2;
	}
	else 
	{	
		if (((Direction==1)&&((char1==13)&&(char2==10)))||((Direction==2)&&((char1==10)&&(char2==13)))) 
		{*intCharLength=2;*strReturn=10;return 4;}//回车
		else *intCharLength=1;//不是回车
		return 2;
	}
}

void Document::DevideWord(char *strSource)
{	
	char strWordTmp[1000],chrTmp[1000];
	WordType * pWordStart;
	unsigned char char1;
	int intReturn,intCharLength,pStart;
	
	int bHasAdd;

	pStart=0;
	intReturn=GetCharFromString(strSource,pStart,chrTmp,&intCharLength);
	pStart+=intCharLength;
	
	while(intReturn!=0)
	{
		if (intReturn==1)
		{	
			intReturn=GetCharFromString(strSource,pStart,chrTmp,&intCharLength);
			pStart+=intCharLength;	
			
			if (intReturn==1) 
			{	
				SubString(strSource+pStart-4,2,strWordTmp);
				char1=(unsigned char)(*strWordTmp);
				pWordStart=tmpWordArray[char1];
				
				bHasAdd=0;
				while (pWordStart!=NULL)
				{	
					SubString(strSource+pStart-4,pWordStart->length,strWordTmp);
					if (strcmp(strWordTmp,pWordStart->word)==0)
					{	
						pWordStart->count++;
						pStart=pStart+pWordStart->length-4;
						intReturn=GetCharFromString(strSource,pStart,chrTmp,&intCharLength);
						pStart+=intCharLength;

						if (intReturn==1)
						{	
							strcat(strWordTmp,chrTmp);
							if (strlen(strWordTmp)>=4) AddNewWord(strWordTmp,1,pWordStart->length+2,4.0);
							bHasAdd=1;
						}
						break;
					}
					pWordStart=pWordStart->next; 
				}
				if (bHasAdd!=1)
				{	
					SubString(strSource+pStart-4,4,strWordTmp);
					if (strlen(strWordTmp)>=4) AddNewWord(strWordTmp,1,4,4.0);
				}
			}
			else if (intReturn==2) 
			{	
				intReturn=GetCharFromString(strSource,pStart,chrTmp,&intCharLength);
				pStart+=intCharLength;	
			}
			else return;
		}
		else
		{	
			intReturn=GetCharFromString(strSource,pStart,chrTmp,&intCharLength);
			pStart+=intCharLength;	
		}
	}
}



void Document::FirstScanFile(char *strSource,char *strOutput)
{	
	char chrTmp[1000];
	int intReturn,intCharLength,pStart;
	
	*strOutput='\0';

	pStart=0;
	
	intReturn=GetCharFromString(strSource,pStart,chrTmp,&intCharLength);
	pStart+=intCharLength;
	
	while(intReturn!=0)
	{	
		//返回值：0 末尾；1 字符 ；2 符号 ；-1 出错 ；
		if ((intReturn==2)||(intReturn==4)) //???
		{	
			DevideWord(strOutput);	// 取到一句马上分词
			// ?这样的话,起步是最后一举如果没有标点符号,就不会用于分词当中了.(小问题)by xfguo
			*strOutput='\0';
			while (intReturn==2) 
			{	
				intReturn=GetCharFromString(strSource,pStart,chrTmp,&intCharLength);
				pStart+=intCharLength;
			}
			if (intReturn==1) strcat(strOutput,chrTmp);
		}
		else if (intReturn==1) strcat(strOutput,chrTmp);
		if (intReturn!=0)
		{  
			intReturn=GetCharFromString(strSource,pStart,chrTmp,&intCharLength);
		    	pStart+=intCharLength;
		}
	}
}

void Document::GetJiaoJiTable()
//取交集,在两个数组里,做完后在数组0里,词频为0
{	
	int i;
	WordType *pWord;
	
	//把一个数组里的东西词频设置为0,加入词表中
	char strWordTmp[50];
	for (i=0;i<intWordCount[0];i++)
		AddNewWord(lastWordArray[0][i].word,0,strlen(lastWordArray[0][i].word),lastWordArray[0][i].weight);
	
	//把另一个数组里的东西进行查询,命中设置词频为1
	for (i=0;i<intWordCount[1];i++)
		{	
			ReverseString(lastWordArray[1][i].word,strWordTmp);
			pWord=FindWord(strWordTmp);
			if (pWord!=NULL) pWord->count=1;
		}

	ArrangeWordInTable(1,1,1);//按照1过滤
	freeTmpWordArray();

	for (i=0;i<intWordCount[0];i++)
		AddNewWord(lastWordArray[0][i].word,0,strlen(lastWordArray[0][i].word),lastWordArray[0][i].weight);

}

void Document::LexicalAquisition() //char * outputFileName
//抽词,outputFileName非空则直接输出否则保留于词表中
{	
	char * buffer,* buffer_temp;
	buffer=(char *)malloc(strlen(strSource)+1);
	buffer_temp=(char *)malloc(strlen(strSource)+1);
	//IfExtendWordTable=1;
	Direction=1;
	strcpy(buffer,strSource);
	// 第一遍抽词
	FirstScanFile(buffer,buffer_temp);
	ArrangeWordInTable(3,1,1);
	freeTmpWordArray();
	// 第二遍抽词
	// 把当前的tmpWordArray清空
	Direction=2;
	ReverseString(buffer,buffer_temp);
	FirstScanFile(buffer_temp,buffer);
	ArrangeWordInTable(3,1,2);
	freeTmpWordArray();
	// 获得交集
	GetJiaoJiTable();

	free(buffer);
	free(buffer_temp);
	//if (outputFileName!=NULL) WriteWordToFile(outputFileName,0,1);
	initArrangeTable();	
}

void Document::WordSegmentation(char * outputFileName)
//分词
{	
	Direction=1;
	char * buffer;
	buffer=(char *)malloc(strlen(strSource)+1); 
	IfExtendWordTable=2;
	FirstScanFile(strSource,buffer);		// 重新计算频率
	ArrangeWordInTable(3,1,1);
	if (outputFileName!=NULL) WriteWordToFile(outputFileName,1,1);
	free(buffer);
}


void SubString(char *strSource,int intLength,char *strDest)
{	
	int i;
	for (i=0;i<intLength;i++) *(strDest+i)=*(strSource+i);
	*(strDest+i)='\0';
}

int CheckIfEnglishChar(char char1)
{	
	if (((char1>='a')&&(char1<='z'))||((char1>='A')&&(char1<='Z'))||((char1>='0')&&(char1<='9'))) return 1;
	else return 0;
}

int CheckIfEnglish(char char1)
{	
	if (CheckIfEnglishChar(char1)||(char1=='.')||(char1=='\\')||(char1=='-')||(char1=='!')||(char1=='/')) return 1;
	else return 0;
}

void ReverseString(char *strSource,char * strReturn)
{	
	int i,intStringLength;
	i=0;
	while (*(strSource+i)!=0) i++;
	intStringLength=i;
	    
	for (i=0;i<intStringLength;i++) 
		*(strReturn+i)=*(strSource+intStringLength-1-i);
	    	*(strReturn+i)='\0';
}

char LowerCase(char char1)
{	
	if ((char1>='A')&&(char1<='Z')) return (char)(char1-('A'-'a'));
	return char1;
}


void Document :: InitClassDocument()
{
	/*if (strSource!=NULL) 
	{   
	      free(strSource);
	      strSource=NULL;
	}*/
	initArrangeTable();
	IfExtendWordTable=1;
	Direction=1;
		//if (bIfUseDict==0)
	
	freeTmpWordArray();
	initTmpWordArray();
}
//else ResetWordTable();


/* added by Tan Bin */
void Document::outputList(vector<struct Occurrence>& vectorOccur){
	int i;
	int count;
	char strWordTmp[50];
	count=intWordCount[Direction-1];
	struct Occurrence occur;

	vectorOccur.clear();
	for (i=0;i<count;i++)
	{	
		strcpy(strWordTmp,lastWordArray[Direction-1][i].word);
		if (filterString(strWordTmp)){
			strcpy(occur.sKeyword,strWordTmp);
			occur.nFrequency=lastWordArray[Direction-1][i].count;
			vectorOccur.insert(vectorOccur.begin(),occur);
		}
	}
}

bool filterString(char* str){
	unsigned char ch1;
	unsigned char ch2;
	int i=0;
	int j=0;
	while (str[i]!=NULL){
		ch1=(unsigned char)str[i];
		if (ch1<128){
			i++;
			continue;
		}
		if (str[i+1]==NULL) break;
		ch2=(unsigned char)str[i+1];
		if (ch2<128){
			i++;
			continue;
		}
		if (j<i){
			str[j]=ch1;
			str[j+1]=ch2;
		}
		j+=2; i+=2;
	}
	str[j]='\0';
	return (j!=0);
}

