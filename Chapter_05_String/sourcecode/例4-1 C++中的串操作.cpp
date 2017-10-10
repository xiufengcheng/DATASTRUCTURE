# include "string"                  // 该文件包含C++串的定义及相关操作
# include "iostream"                // 该文件包含标准输入输出流cout和cin
using namespace std;                 // 指定名空间，这是C++的规定
void main()
 {
	string s1="abcd",s2="123",s3;           // 串s1和串s2被赋初值
	cout<<"串s1的值为："<<s1<<endl;        // 输出串s1
	s1=s1+s2;                               // 串s2连接在串s1之后
	cout<<"串s1和串S2连接后的值为："<<s1<<endl;
	if(s1>s2) cout<<"s1>s2"<<endl;        // 串s1和串s2进行比较
	else if(s1==s2) cout<<"s1=s2"<<endl;
	       else cout<<"s1<s2"<<endl;
	s1.insert(2,s2);        // 将串s2插入到串s1中的第2个位置之前
	cout<<"插入后的串s1为："<<s1<<endl;
	s3=s1.substr(4,5);    // 从串s1中第42上位置开始取长度为5的子串
	cout<<"子串s3为："<<s3<<endl;
}
