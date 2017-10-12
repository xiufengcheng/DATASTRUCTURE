#include <iostream.h>
#include"DSqString.h"
int main() {
	DSqString S1, S2, S3, S4;

	StrAssign_Sq(S1, "child");
	StrAssign_Sq(S2, "children");
	StrAssign_Sq(S3, "chinese chair technology ");
	StrAssign_Sq(S4, "");
	StrCopy_Sq(S4, S1);
	cout << "串S4被复制后的值为：";
	StrTraveres_Sq(S4);
	if (StrCompare_Sq(S1, S2)>0) cout << "串S1>串S2" << endl;
	else if (StrCompare_Sq(S1, S2) == 0)  cout << "串S1=串S2" << endl;
	else if (StrCompare_Sq(S1, S2)<0)  cout << "串S1<串S2" << endl;
	if (StrConcat_Sq(S3, S4)) {
		cout << "串S3与S4连接成功\n即" << endl;
		StrTraveres_Sq(S3);
	}
	else {
		cout << "连接失败" << endl;
	}
	if (SubString_Sq(S3, S4, 0, 4)) {
		cout << "取子串成功\n即为：" << endl;
		StrTraveres_Sq(S4);
	}
	else {
		cout << "取子串失败" << endl;
	}
	StrAssign_Sq(S1, "ch");
	StrAssign_Sq(S2, "abcd");
	cout << "置换前S3的值为：" << endl;
	StrTraveres_Sq(S3);
	StrReplace_Sq(S3, S1, S2);
	cout << "置换后S3的值为：";
	StrTraveres_Sq(S3);
	visualization(S3,"show.dot");
	DestroyString_Sq(S1);
	DestroyString_Sq(S2);
	DestroyString_Sq(S3);
	DestroyString_Sq(S4);
	return 0;
}
