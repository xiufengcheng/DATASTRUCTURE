#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_SIZE 114514 //随便改


struct string {
	char ch[MAX_SIZE];
	int length;
 };

void fun(struct string *s, struct string *t);

int main(void)
{
	struct string S;
	struct string T;
	scanf("%s", &(S.ch));
	scanf("%s", &(T.ch));
	S.length = strlen(S.ch);
	T.length = strlen(T.ch);
	fun(&S, &T);
	return 0;
}

void fun(struct string *s, struct string *t)
{
	int newlen = 0 , j;
	for (int i = 0; i < s->length;i++)
	{
		j = 0;
		for (; j < t->length && i+j<s->length; j++)
		{
			if (s->ch[i+j] != t->ch[j])
				break;
		}
		if (j == t->length)
		{
			for (int k = i; k < i + j; k++)
				(s->ch)[k] = 0;
		}
	}
	for (int i = 0; i < s->length; i++)
	{
		if (s->ch[i])
			s->ch[newlen++] = s->ch[i];
	}
	s->length = newlen;
	return;
}
