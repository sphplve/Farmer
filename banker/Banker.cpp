#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>

//****************************************************************
//****************************数据结构****************************
#define M_NUMP 20
#define M_NUMR 20
#define M_LEAF 100
int NUMP;
int NUMR;
int flag[M_NUMP]={0};
int Max[M_NUMP][M_NUMR];
int Allocation[M_NUMP][M_NUMR];
int Need[M_NUMP][M_NUMR];
int Available[M_NUMR];
char Processes[M_NUMP][10];
char Resources[M_NUMR][10];
typedef struct PTNode
{
	PTNode *parent;
	int data;
	PTNode *child[M_NUMP];
	
}Node,*PNode;
PNode PPro[M_LEAF]={NULL};		//存储所有叶子节点
int M=0;					//作为PPro数组的下标，记录叶子节点的个数
//****************************数据结构****************************
//****************************************************************

//****************************************************************
//****************************函数介绍****************************

char CallFunction_0() ;					     	//	调用菜单函数	
char CallFunction_1() ;	
void Show();								    //  显示当前时刻资源分配情况
char Menu_0();									//  菜单
char Menu_1();
char Menu_2();
bool IsSafe(int flag);						    //  安全性检查
void RequestSource();							//  资源请求
void BankerAlgorithm(int i,int Request[]);		//  银行家算法
//void InitPTree();
PNode CreatePTree(PNode parent,int data);		//建立树的结构，存储所有安全序列	
void PrintSafeOrder();							//输出所有安全序列
int File_in();									//通过文件导入
int Keyboard_in();								//通过键盘输入							
void Check_data_safe(char &choice,char min,char max);//检验输入的数据是否合法
void End();											//	程序结束	
void Print_MAN(int str[][M_NUMR]);					//实现	Allocation Max Need 的输出
void Import_MAN(int str[][M_NUMR]);					//实现	Allocation Max Need 的输入 

//****************************函数介绍****************************
//****************************************************************


void main()
{
/*	 Keyboard_in();
	getch();*/
	printf("\n\n\t按ESC键退出，非ESC键进入...\n");
	char i=getch();
	if(i!=27)
	{
		system("cls");

		printf("\n\n\n\n\n\n");
		printf("\t\t\t 欢迎进入WQS版银行家算法！ \n\n");
		printf("\t\t\t   按任意键进入初始化界面！    \n");
		
		getch();

	
		do
		{
			i=CallFunction_1();
		}while(i=='4');		
		
	}
system("cls");
	End();
	
}


char Menu_0()
{
	char choice;
//	Show();
	
//	fflush(stdin);
	printf("\n\n\n\n\n\n\n\n");
	printf("\t\t欢迎进入系统服务界面！请选择服务项目:\n\n");
	printf("\t\t★★★★★★★★★★★★★★★★★★★★★★★ \n");
	printf("\t\t★★	1.显示当前时刻资源分配情况	  ★★     \n");
	printf("\t\t★★	2.检查当前时刻是否处于安全状态    ★★   \n");
	printf("\t\t★★	3.进入资源请求界面                ★★   \n");
	printf("\t\t★★	4.返回系统初始化界面	          ★★   \n");
	printf("\t\t★★    5.退出                            ★★   \n");
	printf("\t\t★★★★★★★★★★★★★★★★★★★★★★★ \n");
	fflush(stdin);
	scanf("%c",&choice);	
	getchar();

	Check_data_safe(choice,'1','5');

	return choice;
}


char Menu_1()
{
	char choice;
	system("cls");
	printf("\n\n\n");
	printf("\t\t\t★★★★★★★★★★★★★★★\n");
	printf("\t\t\t★★     请先导入数据！   ★★\n");
	printf("\t\t\t★★	1、从文件导入！	  ★★\n");
	printf("\t\t\t★★	2、从键盘导入！	  ★★\n");
	printf("\t\t\t★★★★★★★★★★★★★★★\n");	
	printf("\n");

	fflush(stdin);
	scanf("%c",&choice);	
	getchar();
	
	Check_data_safe(choice,'1','2');

	return choice;

}

char Menu_2()
{
	char choice;
	system("cls");
	printf("\n\n");
	printf("\t\t\t★★★★★★★★★★★★★★★★★★★★★\n");
	printf("\t\t\t★1、从文件“file1”导入（课本例子）★\n");
	printf("\t\t\t★2、从文件“file2”导入（课后习题）★\n");
	printf("\t\t\t★3、从文件“file3”中自定义导入    ★\n");
	printf("\t\t\t★★★★★★★★★★★★★★★★★★★★★\n");

	fflush(stdin);
	scanf("%c",&choice);	
	getchar();

	Check_data_safe(choice,'1','3');

	return choice;
}

void End()
{
	printf("\n\n\n\n\n\n\n");
	printf("\t\t\t\t ( ^_^ )/~~  拜拜  \n\n");

}

char CallFunction_0() 
{
	char choice;	
	do
	{
		system("cls");
		choice=Menu_0();

		switch(choice)
		{
			case '1' :Show();break;
			case '2' :IsSafe(0);break;
			case '3' :RequestSource();break;
		}
		
	}while(choice!='5'&&choice!='4');

	return choice;


}


char CallFunction_1() 
{
		int a=0;
			char choice;
			system("cls");
			choice=Menu_1();

			switch(choice)
			{
				case '1':a=File_in() ;break;
				case '2':a=Keyboard_in();break;
			}
			if(a==1)
			{
				printf("数据导入成功！ 进入系统服务主界面（Y/N）？\n");
				char ch=getch();
				if(ch=='Y'||ch=='y')
					choice=CallFunction_0();
			}	
			else
			{
				printf("数据导入失败！\n");
				exit(0);

		}
			return choice;	

}

/*void CallFunction_2() 
{
			char choice;
			system("cls");
			choice=Menu_2();

			switch(choice)
			{
				case '1':File_in();break;
				case '2':Keyboard_in();break;
			}
		

}
*/

int File_in()
{
	char choice=Menu_2();
	fflush(stdin);
	FILE *fp;
	int j,i;
		if(choice=='1')
		{
			if(!(fp=fopen("file1.txt","r")))
				{
					printf("不能打开文件！\n");
					exit(0);
				}
		}
			
		else if(choice=='2')
		{
			if(!(fp=fopen("file2.txt","r")))
				{
					printf("不能打开文件！\n");
					exit(0);
				}
		}	

		else
		{
			printf("\n请先向文件file3里输入数据！输入完毕请关闭文件，按回车键继续！\n");
			fflush(stdin);
			char ch=getch();
			while(ch!=0x0d)
				ch=getch();
			
	
		
					if(!(fp=fopen("file3.txt","r")))
					{
						printf("不能打开文件！\n");
						exit(0);
					}
				
		}	
	
		fseek(fp,sizeof("进程个数："),SEEK_SET);
	fscanf(fp,"%d\n\n",&NUMP);
		fseek(fp,sizeof("资源个数："),SEEK_CUR);
	fscanf(fp,"%d\n\n",&NUMR);

		fseek(fp,sizeof("进程名称："),SEEK_CUR);
	for( i=0;i<NUMP;i++)
		fscanf(fp,"%s\n\n",Processes[i]);

			fseek(fp,sizeof("资源名称："),SEEK_CUR);
	for( i=0;i<NUMR;i++)
		fscanf(fp,"%s\n\n",Resources[i]);

			fseek(fp,sizeof("资源数量："),SEEK_CUR);
		for( i=0;i<NUMR;i++)
			fscanf(fp,"%d\n\n",&Available[i]);


			fseek(fp,sizeof("最大需求矩阵："),SEEK_CUR);
	for( i=0;i<NUMP;i++)
		for(  j=0;j<NUMR;j++)		
			fscanf(fp,"%d\n\n",&Max[i][j]);
		
			fseek(fp,sizeof("分配矩阵："),SEEK_CUR);
		for( i=0;i<NUMP;i++)
			for( j=0;j<NUMR;j++)		
			fscanf(fp,"%d\n\n",&Allocation[i][j]);


		for( i=0;i<NUMP;i++)
			for( j=0;j<NUMR;j++)		
			{
				Need[i][j]=Max[i][j]-Allocation[i][j];
				Available[j]=Available[j]-Allocation[i][j];
			}

		fclose(fp);

		return 1;	
			
}

int Keyboard_in()
{
	int i,j;
	puts("请输入进程个数:");
	scanf("%d",&NUMP);

	puts("请输入资源个数:");
		scanf("%d",&NUMR);

	puts("请输入进程名称:");
	for(i=0;i<NUMP;i++)
		scanf("%s",Processes[i]);

	puts("请输入资源名称:");
	for(i=0;i<NUMR;i++)
		scanf("%s",Resources[i]);

	puts("请输入系统各类可利用资源的数量（按资源名称排列）:");
		for(i=0;i<NUMR;i++)
			scanf("%d",&Available[i]);

puts("请输入最大需求矩阵 Max (行表示进程，列表示资源):");
		Import_MAN(Max);

			puts("下面为请为各进程手动分配资源，这些资源将存储在 Allocation 里面(行表示进程，列表示资源):");
		Import_MAN(Allocation);
			for(i=0;i<NUMP;i++)
				for(j=0;j<NUMR;j++)
				{
					Need[i][j]=Max[i][j]-Allocation[i][j];
					Available[j]=Available[j]-Allocation[i][j];

				}
					

/*	puts("请输入最大需求矩阵 Max (行表示进程，列表示资源):");
			for(i=0;i<NUMP;i++)
				for(j=0;j<NUMR;j++)
				scanf("%d",&Max[i][j]);

	puts("请输入分配矩阵 Allocation (行表示进程，列表示资源):");
		for(i=0;i<NUMP;i++)
				for(j=0;j<NUMR;j++)
				scanf("%d",&Allocation[i][j]);

	puts("请输入需求矩阵 Need (行表示进程，列表示资源):");
		for(i=0;i<NUMP;i++)
				for(j=0;j<NUMR;j++)
				scanf("%d",&Need[i][j]);*/

	return 1;
}


void Import_MAN(int str[][M_NUMR])
{
	int j,i;
	for(i=0;i<NUMP;i++)
		for(j=0;j<NUMR;j++)
			scanf("%d",&str[i][j]);
}

void Check_data_safe(char &choice,char min,char max)
{
		while(choice<min||choice>max)
		{
			printf("\t警告！数值不合法！请重新输入！（只能在%c-%c范围内）\n",min,max);
			fflush(stdin);
			scanf("%c",&choice);		
			getchar();		
		}
}

void PrintSafeOrder()
{
	system("cls");
	PNode *parray=PPro;
	PNode pnode;
	int i=0,m=1;
	int ProcessIndex[M_NUMP];


	for(;*parray;parray++)
	{
		for(pnode=*parray;pnode->parent;pnode=pnode->parent)
			ProcessIndex[i++]=pnode->data;
		if(m<10)
			printf("(%02d)、",m++);
		else
			printf("(%2d)、",m++);
		for(i=NUMP-1;i>0;i--)
			printf("%s→",Processes[ProcessIndex[i]]);

		printf("%s",Processes[ProcessIndex[i]]);
		printf("\n");

		i=0;
		
	}	
	
}

PNode CreatePTree(PNode parent,int data,int Work[])
{
//创建一个节点，并给节点赋初值
	PNode p;	
	int i,j,m=0,count=0;
	p=(PNode)malloc(sizeof(Node));
	p->data=data;
	p->parent=parent;

//创建该节点的子树

	for(i=0;i<NUMP;i++)	
		if(flag[i]==0)
		{
			for(j=0;j<NUMR&&Work[j]>=Need[i][j];j++)
			;
			if(j>=NUMR)
			{
				for(j=0;j<NUMR;j++)
					Work[j]+=Allocation[i][j];
				flag[i]=1;
				p->child[m++]=CreatePTree(p,i,Work);
			//	count=1;
			}

		}
		else
			count++;
	
			
//该节点子树创建完毕


//用PPro数组存放所有检测出来的叶子节点
		if(count==NUMP)
			PPro[M++]=p;

//收回该进程的所有资源
	for(j=0;j<NUMR;j++)
		Work[j]-=Allocation[data][j];
	flag[data]=0;
	p->child[m]=NULL;

	return p;
}


/*void InitPTree()
{
	PNode p;
	p=(PNode)malloc(sizeof(Node));
	p->data=-1;
	p->parent=NULL;
	p->child=NULL;
	int Work[NUMR];
	for(int i=0;i<NUMR;i++)
		 Work[i]=Available[i];
	CreatePTree(NULL,-1,Work);
}

void Show()
{
	int i;
	int count=0;
	printf("Process\tMax\tAllocation\tNeed\tAvailable\n");
	for(count=0;count<3;count++)
	{
		printf("\t");
		for(i=0;i<NUMR;i++)
			printf("%c ",Resources[i]);
	}
	printf("\n");

	for(i=0;i<NUMR;i++)
		printf("\t\t\t\t\t%d ",Available[i]);

	printf("\r");

	for( i=0;i<NUMP;i++)
	{
		printf("%s\t",Processes[i]);
	
		for(int j=0;j<NUMR;j++)
			printf("%d ",Max[i][j]);

		for( j=0;j<NUMR;j++)
			printf("%d ",Allocation[i][j]);

		for( j=0;j<NUMR;j++)
			printf("%d ",Need[i][j]);
		printf("\n");

	}	
		
	printf("\n");
	

}
*/
void Show()
{
	system("cls");
	int i,j;
	printf("\n系统共有%d个进程、%d种资源，分别为(按序号排列)：\n",NUMP,NUMR);
	printf("\n进程名为：");
	for(i=0;i<NUMP;i++)
		printf("%s ",Processes[i]);
	printf("\n");

	printf("\n资源名为：");
	for(i=0;i<NUMR;i++)
		printf("%s ",Resources[i]);
	printf("\n");


	printf("\n系统可利用资源数目：Available[%d]={",NUMR);
		printf("%d",Available[0]);
		for(i=1;i<NUMR;i++)
			printf(",%d",Available[i]);
		
		printf("}\n");


		printf("\n最大需求矩阵：Max[%d][%d]={",NUMP,NUMR);
			Print_MAN(Max);

		printf("\n分配矩阵：Allocation[%d][%d]={",NUMP,NUMR);
			Print_MAN(Allocation);

		printf("\n需求矩阵：Need[%d][%d]={",NUMP,NUMR);
			Print_MAN(Need);

	printf("\n\t请输入任意键返回主界面...\n");
		getch();



}


void Print_MAN(int str[][M_NUMR])
{
		int i,j;
		for(i=0;i<NUMP;i++)
		{
			printf("{%d",str[i][0]);
		
			for(j=1;j<NUMR;j++)			
				printf(",%d",str[i][j]);
			printf("},");			
		}
	if(NUMP==0)
		printf("}\n");
	else
		printf("\b}\n");

}
bool IsSafe(int flag)
{
//初始化数据
	int i,j,count=0,cnt=0,Work[M_NUMR];
	bool Finish[M_NUMP]={false};  
	M=0;
	for( i=0;i<NUMR;i++)
		Work[i]=Available[i];

//进行安全性检查
	for(i=0;i<NUMP;i++)
	{
		if(Finish[i]==true)
			continue;
		for(j=0;j<NUMR;j++)
			if(Need[i][j]<=Work[j])
					count++;	//记录进程i是否满足条件	，若count==3则满足，否则不满足	
			if(count==NUMR)
			{
				for(j=0;j<NUMR;j++)
					Work[j]=Work[j]+Allocation[i][j];
				Finish[i]=true;
				cnt++;		//记录Finish[i]=true的个数
				i=-1;		//从头开始检查
			}
		count=0;
	}

//判断是否处于安全状态
	if(cnt==NUMP)
	{
		for( i=0;i<NUMR;i++)
			Work[i]=Available[i];
		CreatePTree(NULL,-1,Work);
		PPro[M]=NULL;
		printf("该系统处于安全状态！\n\n");
		printf("一共有%d个安全序列，是否列出所有的安全序列?（Y/N）\n",M);
		fflush(stdin);
		char ch=getch();
		if(ch=='Y'||ch=='y')		
		{
			PrintSafeOrder();
			printf("\t请输入任意键返回主界面...\n");
			getch();
		}

		

		return true;
	}
	else
	{
		if(flag==0)
			printf("该系统处于不安全状态！\n\n");
		else
			printf("该系统处于不安全状态！取消已分配的资源！\n\n");

		printf("\t请输入任意键返回主界面...\t");
		getch();

		return false;
		
	}

}

void RequestSource()
{
	char Process[10];
	int i,pro;									//记录进程序列号
	int	abc[M_NUMR];								//存储进程对资源的请求情况
	system("cls");								

	printf("欢迎进入资源请求界面：\n\n");
	printf("请输入进程的名称，可选进程名为：（");
	for(i=0;i<NUMP-1;i++)
		printf("%s,",Processes[i]);
	printf("%s）\n",Processes[i]);

	scanf("%s",Process);
		for(i=0;i<NUMR;i++)
		{
			printf("请输入 %s 进程对资源 %s 的请求情况\n",Process,Resources[i]);
			scanf("%d",&abc[i]);
		}		


	for(i=0;i<NUMP;i++)
		if(!strcmp(Process,Processes[i]))		
			pro=i;						
//printf("%d",pro);
		BankerAlgorithm(pro,abc);

}
void BankerAlgorithm(int i,int Request[])
{

//####################检查该进程是否满足要求#####################################

	for(int j=0;j<NUMR;j++)
		if(Request[j]>Need[i][j])
		{
			printf("该进程请求的资源数量大于其需要的资源数量，系统不予分配！\n\n");				
			printf("\t请输入任意键返回主界面...\t");
			getch();

			return;
		}
		else if(Request[j]>Available[j])
		{
			printf("该进程请求的资源数量大于系统可利用的资源数量，系统不予分配！\n\n");
			printf("\t请输入任意键返回主界面...\t");
			getch();

			return;
		}

//#########################################################

		printf("正在分配资源...\n");
		Sleep(1000);


//##################暂时为进程分配资源#######################################

	for( j=0;j<NUMR;j++)
	{
		Available[j]=Available[j]-Request[j];
		Allocation[i][j]=Allocation[i][j]+Request[j];
		Need[i][j]=Need[i][j]-Request[j];
	}
	printf("\n正在进行安全性检查...\n\n");
	Sleep(1000);


//##################进行安全性检查#######################################

	if(IsSafe(1)==true)
		;

	else
	{
		for( j=0;j<NUMR;j++)
		{
			Available[j]=Available[j]+Request[j];
			Allocation[i][j]=Allocation[i][j]-Request[j];
			Need[i][j]=Need[i][j]+Request[j];
		}


	}


}

