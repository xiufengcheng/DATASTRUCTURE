typedef struct LNode {
	char str;
	struct LNode *next;
}SNode,*SLinkString;

//串赋值操作
void StrAssign_L(SLinkString &S, char * chars) {
	//将字符串chars赋值给链式串S
	SLinkString p, q;
	S = (SLinkString)malloc(sizeof(LNode));
	if (!(*chars)) S->next = NULL;
	else {
		p = S;
		while (*chars) {
			q = (SLinkString)malloc(sizeof(LNode));
			q->str = *chars;
			p->next = q;
			p = q;
			chars++;
		}
		q->next = NULL;
	}
}

//串复制操作
void StrCopy_L(SLinkString &S, SLinkString T) {
	//将链式串T复制到S中
	SLinkString p, q, r;
	while (S->next) {
		p = S;
		S = S->next;
		free(p);
	}
	r = T->next;
	p = S;
	while (r) {
		q = (SLinkString)malloc(sizeof(LNode));
		if (!p) {
			cout << "错误" << endl;
			exit(0);
		}
		q->str = r->str;
		p->next = q;
		p = q;
		r = r->next;
	}
	p->next = NULL;
}

//求串长操作
int StrLength_L(SLinkString S) {
	int n = 0;
	SLinkString p = S->next;   //传的是指针
	while (p) {
		n++;
		p = p->next;
	}
	return n;
}

//串比较操作
int StrCompare_L(SLinkString S, SLinkString T) {
	SLinkString p = S->next, q = T->next;
	while (p&&q) {
		if (p->str > q->str) return 1;
		else if (p->str < q->str) return -1;
		p = p->next;
		q = q->next;
	}
	if (p) return 1;
	else if (q) return -1;
	return 0;
}

//串连接操作
bool StrConcat_L(SLinkString &S, SLinkString T) {
	SLinkString p, q = S->next, r = T->next;
	while (q->next) q = q->next;
	while (r) {
		p = (SLinkString)malloc(sizeof(LNode));
		if (!p) return false;
		p->str = r->str;
		q->next = p;
		q = p;
		r = r->next;
	}
	q->next = NULL;
	return true;
}

//取子串的操作
bool SubString_L(SLinkString S, SLinkString &Sub, int pos, int len) {
	SLinkString p, q, r;
	int i;
	if (len<0 || len>StrLength_L(S) - pos + 1) return false; //len值不合理
	p = S->next; i = 1;
	while (p&&i < pos) {
		p = p->next;
		i++;
	}
	if (i != pos) return false; //pos位置不合理
	while (Sub->next) {
		q = Sub;
		Sub = Sub->next;
		free(q);
	}
	r = Sub;
	for (i = 1; i <= len; i++) {
		q = (SLinkString)malloc(sizeof(LNode));
		q->str = p->str;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
	return true;
}

//子串的定位操作
bool Index_L(SLinkString S, SLinkString T, int &pos) {
	int i;
	SLinkString Sub;
	StrAssign_L(Sub, "");   //初始化
	for (i = 1; i < StrLength_L(S) - StrLength_L(T); i++) {
		SubString_L(S, Sub, i, StrLength_L(T));
		//cout << Sub->next->str << endl;
		if (!StrCompare_L(Sub, T)) {
			//cout << Sub->next->str << endl;
			pos = i;
			//cout << i << endl;
			return true;
		}
	}
	//cout << "fail" << endl;
	return false;
}

//插入子串的操作
bool StrInsert_L(SLinkString &S, int pos, SLinkString T) {
	SLinkString p, q, r, h;
	int i = 0;
	p = S;
	while (p&&i < pos-1) {
		p = p->next;
		i++;
	}
	q = p->next;
	if (i != pos-1) return false;
	r = T->next;
	while (r) {
		h = (SLinkString)malloc(sizeof(LNode));
		h->str = r->str;
		p->next = h; h->next = q;
		p = h; r = r->next;
	}
	return true;
}

//删除子串的操作
bool StrDelet_L(SLinkString &S, int pos, int len) {
	//从链式串的第pos个字符串开始删除
	SLinkString p = S, r, q;
	if (len < 0 || StrLength_L(S) - pos + 1 < len) return false;
	int i = 0;
	while (p&&i < pos-1) {
		p = p->next;
		i++;
	}
	if (i != pos-1) return false;
	q = p->next;
	for (i = 1; i <= len; i++) {
		r = q;
		p->next = q->next;
		q = q->next;
		free(r);
	}
	return true;
}

//置换子串的操作
void StrReplace_L(SLinkString &S, SLinkString T, SLinkString V) {
	int pos = 1;
	while (Index_L(S, T, pos)) {
		StrDelet_L(S, pos, StrLength_L(T));
		StrInsert_L(S, pos, V);
		//pos=pos+StrLength_L(V);
	}
}

//串的遍历操作
void StrTraveres_L(SLinkString S) {
	SLinkString p = S->next;
	while (p) {
		cout << p->str;
		p = p->next;
	}
	cout << endl;
}

//链式串的撤销操作
void DestroyString_L(SLinkString &S) {
	SLinkString p, p1;
	p = S;
	while (p)
	{
		p1 = p;
		p = p->next;
		free(p1);
	}
	S = NULL;
}
void visualization(SLinkString S, char* filename)
{   int temp;
	FILE *stream;  
	SLinkString p = S->next;
    if( NULL == (stream = fopen(filename, "w")) )  
    {  
	   printf("open file error");  exit(0);  
    }  
    fprintf(stream, "digraph\n{\n node [shape = record] \n ");  
    int i=1;
    fprintf(stream, "S[label=\"\头节点\"]; S%d[label=\"<L>%c|<R>*\"];\n  S->S%d:L[label=\"head\"] \n; ",i,p->str,i);
		i++;
		p=p->next;
	while(p){
		fprintf(stream, "S%d[label=\"<L>%c|<R>*\"];\n S%d:R->S%d:L \n; ",i,p->str,i-1,i,p->str);
		i++;
		p=p->next;
		if(p&&!p->next){
			fprintf(stream, "S%d[label=\"<L>%c|<R>NULL\"];\n S%d:R->S%d:L \n; ",i,p->str,i-1,i,p->str);
			p=p->next;
		}
	}
	fprintf(stream, "}"); 
	fclose(stream);  
	system("dot -Tpng show.dot -o show.png");
	system("show.png");
}

