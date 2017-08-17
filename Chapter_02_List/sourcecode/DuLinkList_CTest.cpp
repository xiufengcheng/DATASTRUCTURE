# include "stdio.h"
# include "stdlib.h"
    void main()
     {int a,e;
      DuLinkList head,p,q;
      p=q=head=(DuLNode*)malloc(sizeof(DuLNode));
      scanf("%d",&a);
      while(a!=0)
       {p=(DuLNode*)malloc(sizeof(DuLNode));
        p->data=a;
        p->prior=q;
        q->next=p;
        q=p;
        scanf("%d",&a);}
        q->next=head;
		head->prior=q;
        printf("插入之前的双向链表是:");
        p=head->next;
        while(p!=head)
        {printf("%3d,",p->data);
         p=p->next;}
         printf("\n");
        if(ListInsert_DuL(head,1,7))
		{
			printf("插入成功\n");
			printf("插入之后的双向链表是:");
            p=head->next;
            while(p!=head)
			{printf("%3d,",p->data);
            p=p->next;}
            printf("\n");
		}  
		else printf("插入失败\n");
        
        if(ListDelete_DuL(head,1,e))
		{	
			printf("删除成功\n");
            printf("被删除的元素是：%d\n",e);
           printf("删除之后的双向链表是:");
           p=head->next;
          while(p!=head)
		  {printf("%3d,",p->data);
           p=p->next;}
           printf("\n");
		}
        else printf("删除失败\n");
       }