#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>

//****************************************************************
//****************************���ݽṹ****************************
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
PNode PPro[M_LEAF]={NULL};		//�洢����Ҷ�ӽڵ�
int M=0;					//��ΪPPro������±꣬��¼Ҷ�ӽڵ�ĸ���
//****************************���ݽṹ****************************
//****************************************************************

//****************************************************************
//****************************��������****************************

char CallFunction_0() ;					     	//	���ò˵�����	
char CallFunction_1() ;	
void Show();								    //  ��ʾ��ǰʱ����Դ�������
char Menu_0();									//  �˵�
char Menu_1();
char Menu_2();
bool IsSafe(int flag);						    //  ��ȫ�Լ��
void RequestSource();							//  ��Դ����
void BankerAlgorithm(int i,int Request[]);		//  ���м��㷨
//void InitPTree();
PNode CreatePTree(PNode parent,int data);		//�������Ľṹ���洢���а�ȫ����	
void PrintSafeOrder();							//������а�ȫ����
int File_in();									//ͨ���ļ�����
int Keyboard_in();								//ͨ����������							
void Check_data_safe(char &choice,char min,char max);//��������������Ƿ�Ϸ�
void End();											//	�������	
void Print_MAN(int str[][M_NUMR]);					//ʵ��	Allocation Max Need �����
void Import_MAN(int str[][M_NUMR]);					//ʵ��	Allocation Max Need ������ 

//****************************��������****************************
//****************************************************************


void main()
{
/*	 Keyboard_in();
	getch();*/
	printf("\n\n\t��ESC���˳�����ESC������...\n");
	char i=getch();
	if(i!=27)
	{
		system("cls");

		printf("\n\n\n\n\n\n");
		printf("\t\t\t ��ӭ����WQS�����м��㷨�� \n\n");
		printf("\t\t\t   ������������ʼ�����棡    \n");
		
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
	printf("\t\t��ӭ����ϵͳ������棡��ѡ�������Ŀ:\n\n");
	printf("\t\t������������������������ \n");
	printf("\t\t���	1.��ʾ��ǰʱ����Դ�������	  ���     \n");
	printf("\t\t���	2.��鵱ǰʱ���Ƿ��ڰ�ȫ״̬    ���   \n");
	printf("\t\t���	3.������Դ�������                ���   \n");
	printf("\t\t���	4.����ϵͳ��ʼ������	          ���   \n");
	printf("\t\t���    5.�˳�                            ���   \n");
	printf("\t\t������������������������ \n");
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
	printf("\t\t\t����������������\n");
	printf("\t\t\t���     ���ȵ������ݣ�   ���\n");
	printf("\t\t\t���	1�����ļ����룡	  ���\n");
	printf("\t\t\t���	2���Ӽ��̵��룡	  ���\n");
	printf("\t\t\t����������������\n");	
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
	printf("\t\t\t����������������������\n");
	printf("\t\t\t��1�����ļ���file1�����루�α����ӣ���\n");
	printf("\t\t\t��2�����ļ���file2�����루�κ�ϰ�⣩��\n");
	printf("\t\t\t��3�����ļ���file3�����Զ��嵼��    ��\n");
	printf("\t\t\t����������������������\n");

	fflush(stdin);
	scanf("%c",&choice);	
	getchar();

	Check_data_safe(choice,'1','3');

	return choice;
}

void End()
{
	printf("\n\n\n\n\n\n\n");
	printf("\t\t\t\t ( ^_^ )/~~  �ݰ�  \n\n");

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
				printf("���ݵ���ɹ��� ����ϵͳ���������棨Y/N����\n");
				char ch=getch();
				if(ch=='Y'||ch=='y')
					choice=CallFunction_0();
			}	
			else
			{
				printf("���ݵ���ʧ�ܣ�\n");
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
					printf("���ܴ��ļ���\n");
					exit(0);
				}
		}
			
		else if(choice=='2')
		{
			if(!(fp=fopen("file2.txt","r")))
				{
					printf("���ܴ��ļ���\n");
					exit(0);
				}
		}	

		else
		{
			printf("\n�������ļ�file3���������ݣ����������ر��ļ������س���������\n");
			fflush(stdin);
			char ch=getch();
			while(ch!=0x0d)
				ch=getch();
			
	
		
					if(!(fp=fopen("file3.txt","r")))
					{
						printf("���ܴ��ļ���\n");
						exit(0);
					}
				
		}	
	
		fseek(fp,sizeof("���̸�����"),SEEK_SET);
	fscanf(fp,"%d\n\n",&NUMP);
		fseek(fp,sizeof("��Դ������"),SEEK_CUR);
	fscanf(fp,"%d\n\n",&NUMR);

		fseek(fp,sizeof("�������ƣ�"),SEEK_CUR);
	for( i=0;i<NUMP;i++)
		fscanf(fp,"%s\n\n",Processes[i]);

			fseek(fp,sizeof("��Դ���ƣ�"),SEEK_CUR);
	for( i=0;i<NUMR;i++)
		fscanf(fp,"%s\n\n",Resources[i]);

			fseek(fp,sizeof("��Դ������"),SEEK_CUR);
		for( i=0;i<NUMR;i++)
			fscanf(fp,"%d\n\n",&Available[i]);


			fseek(fp,sizeof("����������"),SEEK_CUR);
	for( i=0;i<NUMP;i++)
		for(  j=0;j<NUMR;j++)		
			fscanf(fp,"%d\n\n",&Max[i][j]);
		
			fseek(fp,sizeof("�������"),SEEK_CUR);
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
	puts("��������̸���:");
	scanf("%d",&NUMP);

	puts("��������Դ����:");
		scanf("%d",&NUMR);

	puts("�������������:");
	for(i=0;i<NUMP;i++)
		scanf("%s",Processes[i]);

	puts("��������Դ����:");
	for(i=0;i<NUMR;i++)
		scanf("%s",Resources[i]);

	puts("������ϵͳ�����������Դ������������Դ�������У�:");
		for(i=0;i<NUMR;i++)
			scanf("%d",&Available[i]);

puts("���������������� Max (�б�ʾ���̣��б�ʾ��Դ):");
		Import_MAN(Max);

			puts("����Ϊ��Ϊ�������ֶ�������Դ����Щ��Դ���洢�� Allocation ����(�б�ʾ���̣��б�ʾ��Դ):");
		Import_MAN(Allocation);
			for(i=0;i<NUMP;i++)
				for(j=0;j<NUMR;j++)
				{
					Need[i][j]=Max[i][j]-Allocation[i][j];
					Available[j]=Available[j]-Allocation[i][j];

				}
					

/*	puts("���������������� Max (�б�ʾ���̣��б�ʾ��Դ):");
			for(i=0;i<NUMP;i++)
				for(j=0;j<NUMR;j++)
				scanf("%d",&Max[i][j]);

	puts("������������ Allocation (�б�ʾ���̣��б�ʾ��Դ):");
		for(i=0;i<NUMP;i++)
				for(j=0;j<NUMR;j++)
				scanf("%d",&Allocation[i][j]);

	puts("������������� Need (�б�ʾ���̣��б�ʾ��Դ):");
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
			printf("\t���棡��ֵ���Ϸ������������룡��ֻ����%c-%c��Χ�ڣ�\n",min,max);
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
			printf("(%02d)��",m++);
		else
			printf("(%2d)��",m++);
		for(i=NUMP-1;i>0;i--)
			printf("%s��",Processes[ProcessIndex[i]]);

		printf("%s",Processes[ProcessIndex[i]]);
		printf("\n");

		i=0;
		
	}	
	
}

PNode CreatePTree(PNode parent,int data,int Work[])
{
//����һ���ڵ㣬�����ڵ㸳��ֵ
	PNode p;	
	int i,j,m=0,count=0;
	p=(PNode)malloc(sizeof(Node));
	p->data=data;
	p->parent=parent;

//�����ýڵ������

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
	
			
//�ýڵ������������


//��PPro���������м�������Ҷ�ӽڵ�
		if(count==NUMP)
			PPro[M++]=p;

//�ջظý��̵�������Դ
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
	printf("\nϵͳ����%d�����̡�%d����Դ���ֱ�Ϊ(���������)��\n",NUMP,NUMR);
	printf("\n������Ϊ��");
	for(i=0;i<NUMP;i++)
		printf("%s ",Processes[i]);
	printf("\n");

	printf("\n��Դ��Ϊ��");
	for(i=0;i<NUMR;i++)
		printf("%s ",Resources[i]);
	printf("\n");


	printf("\nϵͳ��������Դ��Ŀ��Available[%d]={",NUMR);
		printf("%d",Available[0]);
		for(i=1;i<NUMR;i++)
			printf(",%d",Available[i]);
		
		printf("}\n");


		printf("\n����������Max[%d][%d]={",NUMP,NUMR);
			Print_MAN(Max);

		printf("\n�������Allocation[%d][%d]={",NUMP,NUMR);
			Print_MAN(Allocation);

		printf("\n�������Need[%d][%d]={",NUMP,NUMR);
			Print_MAN(Need);

	printf("\n\t���������������������...\n");
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
//��ʼ������
	int i,j,count=0,cnt=0,Work[M_NUMR];
	bool Finish[M_NUMP]={false};  
	M=0;
	for( i=0;i<NUMR;i++)
		Work[i]=Available[i];

//���а�ȫ�Լ��
	for(i=0;i<NUMP;i++)
	{
		if(Finish[i]==true)
			continue;
		for(j=0;j<NUMR;j++)
			if(Need[i][j]<=Work[j])
					count++;	//��¼����i�Ƿ���������	����count==3�����㣬��������	
			if(count==NUMR)
			{
				for(j=0;j<NUMR;j++)
					Work[j]=Work[j]+Allocation[i][j];
				Finish[i]=true;
				cnt++;		//��¼Finish[i]=true�ĸ���
				i=-1;		//��ͷ��ʼ���
			}
		count=0;
	}

//�ж��Ƿ��ڰ�ȫ״̬
	if(cnt==NUMP)
	{
		for( i=0;i<NUMR;i++)
			Work[i]=Available[i];
		CreatePTree(NULL,-1,Work);
		PPro[M]=NULL;
		printf("��ϵͳ���ڰ�ȫ״̬��\n\n");
		printf("һ����%d����ȫ���У��Ƿ��г����еİ�ȫ����?��Y/N��\n",M);
		fflush(stdin);
		char ch=getch();
		if(ch=='Y'||ch=='y')		
		{
			PrintSafeOrder();
			printf("\t���������������������...\n");
			getch();
		}

		

		return true;
	}
	else
	{
		if(flag==0)
			printf("��ϵͳ���ڲ���ȫ״̬��\n\n");
		else
			printf("��ϵͳ���ڲ���ȫ״̬��ȡ���ѷ������Դ��\n\n");

		printf("\t���������������������...\t");
		getch();

		return false;
		
	}

}

void RequestSource()
{
	char Process[10];
	int i,pro;									//��¼�������к�
	int	abc[M_NUMR];								//�洢���̶���Դ���������
	system("cls");								

	printf("��ӭ������Դ������棺\n\n");
	printf("��������̵����ƣ���ѡ������Ϊ����");
	for(i=0;i<NUMP-1;i++)
		printf("%s,",Processes[i]);
	printf("%s��\n",Processes[i]);

	scanf("%s",Process);
		for(i=0;i<NUMR;i++)
		{
			printf("������ %s ���̶���Դ %s ���������\n",Process,Resources[i]);
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

//####################���ý����Ƿ�����Ҫ��#####################################

	for(int j=0;j<NUMR;j++)
		if(Request[j]>Need[i][j])
		{
			printf("�ý����������Դ������������Ҫ����Դ������ϵͳ������䣡\n\n");				
			printf("\t���������������������...\t");
			getch();

			return;
		}
		else if(Request[j]>Available[j])
		{
			printf("�ý����������Դ��������ϵͳ�����õ���Դ������ϵͳ������䣡\n\n");
			printf("\t���������������������...\t");
			getch();

			return;
		}

//#########################################################

		printf("���ڷ�����Դ...\n");
		Sleep(1000);


//##################��ʱΪ���̷�����Դ#######################################

	for( j=0;j<NUMR;j++)
	{
		Available[j]=Available[j]-Request[j];
		Allocation[i][j]=Allocation[i][j]+Request[j];
		Need[i][j]=Need[i][j]-Request[j];
	}
	printf("\n���ڽ��а�ȫ�Լ��...\n\n");
	Sleep(1000);


//##################���а�ȫ�Լ��#######################################

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

