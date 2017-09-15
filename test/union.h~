void union(List &La,List Lb)
{
	La_len=ListLength(La);
	while(!ListEmpty(Lb)){
		ListDelete(Lb,1,e);
		if(!LocateElem(La,E))ListInsert(La,++La_len,e);
	}
	DestoryList(Lb);
}