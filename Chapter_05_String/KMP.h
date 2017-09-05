//求子串next值的算法
void get_next(DSqString T, int next[]) {
	int j = 1, k = 0;
	next[0] = -1;
	next[1] = 0;
	while (j < T.length) {
		if (T.str[j] == T.str[k]) {
			next[j + 1] = k + 1;
			j++; k++;
		}
		else if (k == 0) {
			next[j + 1] = 0;
			j++;
		}
		else {
			k = next[k];
		}
	}
}

bool Index_KMP(DSqString S, DSqString T, int next[], int &pos) {
	//利用模式串T的next函数求T在主串中的位置
	int i = 0, j = 0;
	while (i < S.length&&j < T.length) {
		if (j == -1 || S.str[i] == T.str[j]) {
			i++; j++;
		}
		else {
			j = next[j];
		}
	}
	if (j == T.length) { pos = i - T.length; return true; }
	else { return false; }
}

void testKMP() {
	int next[10], pos;
	DSqString S1, S2, S3;
	StrAssign_Sq(S1, "alid");
	StrAssign_Sq(S2, "children");
	StrAssign_Sq(S3, "ild");
	get_next(S1, next);
	if (Index_KMP(S2, S1, next, pos))
		cout << "匹配成功！pos=" << pos << endl;
	else cout << "匹配失败" << endl;
	get_next(S3, next);
	if(Index_KMP(S2,S3,next,pos))
		cout << "匹配成功！pos=" << pos << endl;
	else cout << "匹配失败" << endl;
	getchar();
}
