


void Print(int a[],int n){
	//输出每次渡轮所在汽车的编号
	time_t t=time(0);  //当前时间
	cout<<endl;
	cout<<"轮渡开始启航->"<<endl;
	cout<<"本次过江时间："<<ctime(&t)<<endl;
	cout<<"本次渡轮所载汽车：";
	for(int i=0;i<n;i++) cout<<a[i]<<' ';
	cout << endl;
} 

void auto_register(LinkQueue &q1,LinkQueue &q2){
	//车到渡口进行登记
	int x;
	cout<<"输入车辆号，假定小于100为客车，否则为货车，"<<endl;
	cout<<"可以输入多辆车，用空格分开，直至输入-1为止。"<<endl;
	while(1){
		cin>>x;
		if(x==-1) break;
		if(x<100) EnQueue_L(q1,x);
		else EnQueue_L(q2,x);
	} 
} 

void ferry_register(long &t1,int &mark,int &n){
	//渡轮到渡口进行登记
	if(mark==1){
		cout<<"渡轮已在渡口等待，无需重复登记！"<<endl;
		return;
	} 
	mark=1;
	cout<<"渡轮已到渡口，可以上船！"<<endl;
	n=0;              //装载车辆初始为零
	t1=time(0);     //登记渡轮到渡口时间 
}

void auto_up_ferry(LinkQueue &q1,LinkQueue &q2,int a[10],int t1,int &mark,int &n){
	//汽车上渡轮
	int i;
	long t2;
	if(QueueEmpty_L(q1)&&QueueEmpty_L(q2)){
		cout<<"暂无汽车过江！"<<endl;
		if(mark==1&&n!=0){
			t2=time(0)-t1;  //计算等待时间
			cout<<"渡轮未满，有车"<<n<<"辆，已等待"<<t2/60<<"分";
			cout<<t2%60<<"秒，等待其他汽车上渡轮！" <<endl;
			
		}
		return;
	} 
	if(mark!=1){
		cout<<"渡轮未到，请汽车稍后上渡轮！"<<endl;
		exit(1);
	}
	do{
		i=n%5;
		while(!QueueEmpty_L(q1)&&n<10&&i<4){  //先上四辆客车
			DeQueue_L(q1,a[n++]);
			i++; 
		}
		//满10辆开车，打印车票号，重新队mark和n清0，转功能菜单
		if(n==10){Print(a,n);mark=0;n=0; return;} 
		if(i==4){if(!QueueEmpty_L(q2)) DeQueue_L(q2,a[n++]);}
		else {
			while(!QueueEmpty_L(q2)&& n<10&&i<5){
				DeQueue_L(q2,a[n++]);
				i++;
			}
		}
		if(n==10){Print(a,n);mark=0;n=0;return;}
	}while(!QueueEmpty_L(q1)||!QueueEmpty_L(q2));
	t2=time(0)-t1;   //登记渡轮等待时间
	cout<<"渡轮未满，有车"<<n<<"辆，已等待"<<t2/60<<"分";
	cout<<t2%60<<"秒，等待其他汽车上渡轮！" <<endl; 
	return;
}

void ferry_set_sail(int a[10],int &mark,int &n){
	//命令渡轮启航
	if(n==0||mark==0) cout<<"渡轮上无车过江或无渡轮！"<<endl;
	else {Print(a,n);mark=0;n=0;} 	
}

void OutputQueue(LinkQueue &q1,LinkQueue &q2){
	//输出汽车排队等待情况
	cout<<"客车排队的情况：";
	QueuePtr p=q1.front;
	if(!p) cout<<"暂无客车等候！"<<endl;
	while(p){
		cout<<p->data<<' ';
		p=p->next;
	} 
	cout <<endl;
	cout<<"货车排队的情况：";
	p=q2.front;
	if(!p) cout<<"暂无货车等候！"<<endl;
	while(p){
		cout<<p->data<<' ';
		p=p->next;
	} 
	cout <<endl;
}

void end_run(LinkQueue &q1,LinkQueue &q2,int n){
	//结束程序运行 
	if(!QueueEmpty_L(q1)||!QueueEmpty_L(q2)){
		cout<<"还有汽车未渡江，暂时不能结束！"<<endl;
		return;
	} 
	if(n!=0){
		cout<<"渡轮上有车，不能结束运行！"<<endl;
		return;
	}
	cout<<"程序结束运行！"<<endl;
	exit(0);
} 

