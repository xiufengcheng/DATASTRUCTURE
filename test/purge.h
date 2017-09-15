void purge(List &La ,List Lb)
{
	InitList(La);
	while(!ListEmpty(Lb)){
		ListDelete(Lb,1,e);
		if(!LocateElem(La,e)) ListInsert(La,++La_len,e)
	}
	DestoryList(Lb)
}