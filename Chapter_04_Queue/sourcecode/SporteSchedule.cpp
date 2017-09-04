#define N 9
typedef int ElemType;
#include <stdlib.h>
#include <iomanip.h>
#include "SqQueue.h"

void division(int R[N][N],int n,int result[],int &group){
	//已知R[n][n]是编号0至n-1的n个元素的关系矩阵,子集划分的结果
	//计入result数组，result[k]的值是编号为k的元素所属的组号
	int i,j,pre=n;
	int clash[N];
	SqQueue Q;
	InitQueue_Sq(Q,n+1);
	for(int e=0;e<n;e++) EnQueue_Sq(Q,e);
	while(!QueueEmpty_Sq(Q)){
		DeQueue_Sq(Q,i);
		if(i<=pre){
			group++;
			for(j=0;j<n;j++){
				clash[j]=0;
			}
		}
		if(clash[i]==0){
			result[i]=group;
			for(j=0;j<n;j++) clash[j]+=R[i][j];
		}else{
			EnQueue_Sq(Q,i); 
		}
		pre=i;
	} 	
}
int main(){
	int i,j,result[N],group=0;
	int R[N][N]={{0,1,0,0,0,1,0,0,0},{1,0,0,0,1,1,0,1,1},{0,0,0,0,0,1,1,0,0},
				 {0,0,0,0,1,0,0,0,1},{0,1,0,1,0,0,1,0,1},{1,1,1,0,0,0,1,0,0},
				 {0,0,1,0,1,1,0,0,0},{0,1,0,0,0,0,0,0,0},{0,1,0,1,1,0,0,0,0}};
	division(R,N,result,group);
	cout<<"总共分"<<group<<"个小组。"<<endl;
	cout<<"分组情况如下："<<endl;
	for(i=0;i<N;i++){
		cout<<result[i]<<' ';
	} 
	cout<<endl;
	for(i=1;i<=group;i++){
		cout<<"第"<<i<<"小组的项目为：";
		for(j=0;j<N;j++){
			if(result[j]==i) cout<<j<<' ';
		} 
		cout<<endl;
	}
	
	return 0;
}