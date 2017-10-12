#include <iostream.h>
#include"SLinkString.h"
int main() {
	SLinkString S1, S2, S3, S4;
	int x;
	StrAssign_L(S1, "child");
	StrAssign_L(S2, "children");
	StrAssign_L(S3, "chinese chair technology ");
	StrAssign_L(S4, "");
	StrTraveres_L(S1);
	
	StrCopy_L(S4, S1);
	cout << "串S4被复制后的值为：";
	StrTraveres_L(S4);
	if (StrCompare_L(S1, S2)>0) cout << "串S1>串S2" << endl;
	else if (StrCompare_L(S1, S2) == 0)  cout << "串S1=串S2" << endl;
	else if (StrCompare_L(S1, S2)<0)  cout << "串S1<串S2" << endl;
	if (StrConcat_L(S3, S4)) {
		cout << "串S3与S4连接成功\n即" << endl;
		StrTraveres_L(S3);
	}
	else {
		cout << "连接失败" << endl;
	}
	if (SubString_L(S3, S4, 9, 5)) {
		cout << "取子串成功\n即为：" << endl;
		StrTraveres_L(S4);
	}
	else {
		cout << "取子串失败" << endl;
	}
	StrAssign_L(S1, "ch");
	StrAssign_L(S2, "abcd");
	//StrDelet_L(S2, 1, 2);
	//StrTraveres_L(S2);
	//StrInsert_L(S2, 1, S1);
	//StrTraveres_L(S2);
	
	cout << "置换前S3的值为：" << endl;
	StrTraveres_L(S3);
	StrReplace_L(S3, S1, S2);
	cout << "置换后S3的值为：";
	StrTraveres_L(S3);
	visualization(S3,"show.dot");
	DestroyString_L(S1);
	DestroyString_L(S2);
	DestroyString_L(S3);
	DestroyString_L(S4);
	return 0;
}
