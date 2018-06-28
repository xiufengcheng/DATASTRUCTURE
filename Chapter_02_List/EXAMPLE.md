#### 【例2.1】 假设利用两个线性表La和Lb分别表示两个集合A和B（线性表中的数据元素即为集合中的成员），求一个新的集合A=A∪B。

分析：这个问题相当于对线性表La做如下操作：把线性表Lb的元素依次插入到La表中。并且需要有一个判断La中是否已经存在Lb中某数据的操作
算法思想：

1. 从线性表Lb中取得一个数据元素；
2. 依该数据元素的值在线性表La中进行查查访；
3. 若线性表La中不存在和其值相同的元素，则将从Lb中删除的数据元素插入La中；重复以上操作直到遍历完Lb表为止。
```c
void union(List &La, List Lb, ElemType &e)
{
    int La_len = ListLength(La);   //求线性表La的长度
    while(!ListEmpty(Lb))     //Lb表的元素尚未处未处理完
    {
        ListDelete(Lb,1,e);    //从Lb中删除第一个数据元素赋值给e
        if(!LocateElem(La,e))     //若La中不存在值和e相等的数据元素
           ListInsert(La,++La_len,e);   //则将它插入在La中最后一个数据元素之后
    }
    DestroyList(Lb); //撤销线性表
}
```
提交者:

----------------

#### 【例2.2】已知一个非纯集合B（即集合B中可能有相同元素），试构造一个纯集合A，使A中只包含B中所有值各不相同的成员。

分析：与上例不同的是，此例中A先不存在，则第一步需要构造一个集合A
算法思想:

1. 构造一个空的线性表La，代表集合A;
2. 从线性表Lb中取得一个数据元素;
3. 依该数据元素的值在La中进行遍历；
4. 如果La中不存在和其值相同的元素，则将从Lb中删除该元素并插入到线性表La中。
5. 重复2至4步直至Lb空为止。
```c++
void purge(List &La,List Lb)
{
    InitList(La);          //初始化La,即创建一个新的，空的线性表La,这个放到外面写
    while(!ListEmpty(Lb))     //Lb表的元素尚未处未处理完
    {
        ListDelete(Lb,1,e);    //从Lb中删除第一个数据元素赋值给e
        if(!LocateElem(La,e))     //若La中不存在值和e相等的数据元素
           ListInsert(La,++La_len,e);   //则将它插入在La中最后一个数据元素之后
    }
    DestroyList(Lb); //撤销线性表
}
```
仔细比对例2.1和例2.2看区别语句在哪
提交者:

----------------

#### 【例2.3】判别两个纯集合A和B是否相等。

分析两个集合相等，指的是这两个集合的元素在值上具有仅仅包含的关系。顺序上不一定具有一一对应的关系。因此，一旦找到一个元素，它存在于A,但不存在于B，或者相反，那么则可以立即判定AB不相等
算法思想

1. 构造一个和La相同的线性表Lc;
2. 对Lb中的每一个数据元素，在Lc中进行查询；
3. 如果找到了该元素，则从Lc中删除该元素;
4. 遍历完Lb时检查Lc,若Lc为空，则两个集合相等，否则不等。
```C
bool Isequal(List La, List Lb)
{
   La_len = ListLength(La);    //求表长 
   Lb_len = ListLength(Lb);    //求表长
   if(La_len! = Lb_len) return false;
   else
   {
        InitList(Lc);           //初始化Lc
        for(k=1;k<=La_len;k++)  //生成La的复制品Lc
        {
            GetElem_(La,k,e);
            ListInsert(Lc,k,e);
        }
    found = true;
    for(k=1;k<=Lb_len,found;k++)
    {
        GetElem(Lb,k,e);        //取Lb中第k个数据元素
        i = LocateElem(Lc,e);   //在Lc中进行查询
        if(i==0) found = false; //La中不存在和该数据元素相同的元素
        else ListDelete(Lc,i,e); //从Lc中删除该数据元素
    }
    int k = ListEmpty(Lc);
    DestroyList(Lc);
    if(found&&k==0) return true;
    else return false;
   }
}//isequal
```


提交者:
----------------

#### 例2.4


提交者:
----------------

#### 例2.5

提交者:
----------------

#### 例2.6

提交者:
----------------

#### 2.7

提交者:
----------------

