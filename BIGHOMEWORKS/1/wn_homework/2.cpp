#include "LinkList.h"
//本题的算法思想是：先找到两个链表的表尾指针，将第一个链表的表尾指针域第二个链表的头结点链接起来，再使之成为循环的。实现本题功能的函数如下:
void link(LinkList La, LinkList Lb)
{
   LinkList p, q;
   p = head1; q= head2;
   while (p->next!=head1)   p=p->next;
   while (q->next!=head2)   q=q->next;
   p->next = head2; q->next = head1;
}

