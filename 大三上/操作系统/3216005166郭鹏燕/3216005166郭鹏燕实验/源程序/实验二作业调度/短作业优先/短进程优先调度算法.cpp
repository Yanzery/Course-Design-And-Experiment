#include "stdio.h" 
#include <stdlib.h> 
#include <conio.h> 
#define getpch(type) (type*)malloc(sizeof(type)) 
#define NULL 0 
struct pcb 
{ /* 定义进程控制块PCB */ 
	char name[10]; 
	char state; 
	int ctime; 
	int ntime; 
	int rtime; 
	struct pcb* link; 
}*ready=NULL,*p,*come=NULL; 
typedef struct pcb PCB;   

int h;

void sort_in_ready() /* 建立对进程进行优先级排列函数*/ 
{ 
	PCB *first, *second; 
	int insert=0; 
	if((ready==NULL)||((p->ntime-p->rtime)<(ready->ntime-ready->rtime))) /*优先级最大者,插入队首*/ 
	{ 
		p->link=ready; 
		ready=p; 
	} 
	else /* 进程比较优先级,插入适当的位置中*/ 
	{ 
		first=ready; 
		second=first->link; 
		while(second!=NULL) 
		{ 
			if((p->ntime-p->rtime)<(second->ntime-second->rtime)) /*若插入进程比当前进程优先数大,*/ 
			{ /*插入到当前进程前面*/ 
				p->link=second; 
				first->link=p; 
				second=NULL; 
				insert=1; 
			} 
			else /* 插入进程优先数最低,则插入到队尾*/ 
			{ 
				first=first->link; 
				second=second->link; 
			} 
		} 
		if(insert==0) first->link=p; 
	} 
} 

void sort_in_come() /* 建立对进程进行优先级排列函数*/ 
{ 
	PCB *first, *second; 
	int insert=0; 
	if((come==NULL)||((p->ctime)<(come->ctime))) /*优先级最大者,插入队首*/ 
	{ 
		p->link=come; 
		come=p; 
	} 
	else /* 进程比较优先级,插入适当的位置中*/ 
	{ 
		first=come; 
		second=first->link; 
		while(second!=NULL) 
		{ 
			if((p->ctime)<(second->ctime)) /*若插入进程比当前进程优先数大,*/ 
			{ /*插入到当前进程前面*/ 
				p->link=second; 
				first->link=p; 
				second=NULL; 
				insert=1; 
			} 
			else /* 插入进程优先数最低,则插入到队尾*/ 
			{ 
				first=first->link; 
				second=second->link; 
			} 
		} 
		if(insert==0) first->link=p; 
	} 
} 




void input() /* 建立进程控制块函数*/ 
{ 
	int i,num; 
	scanf("%d",&num); 
	for(i=0;i<num;i++) 
	{ 
		p=getpch(PCB); 
		scanf("%s %d %d",p->name,&p->ctime,&p->ntime); 
		p->rtime=0;p->state='w'; 
		p->link=NULL; 
		sort_in_come(); /* 调用sort函数*/ 
	} 
} 

void disp(PCB * pr) /*建立进程显示函数,用于显示当前进程*/ 
{ 
	printf("\n qname \t state \t ndtime \t runtime \n"); 
	printf("| %s \t",pr->name); 
	printf("| %c \t",pr->state); 
	printf("| %d \t",pr->ntime); 
	printf("    | %d \t",pr->rtime); 
	printf(" \n"); 
} 
void check() /* 建立进程查看函数 */ 
{ 
	PCB* pr; 
	printf("\n **** 当前正在运行的进程是:%s",p->name); /*显示当前运行进程*/ 
	disp(p); 
	pr=ready; 
	printf("\n ****当前就绪队列状态为:\n"); /*显示就绪队列状态*/ 
	while(pr!=NULL) 
	{ 
		disp(pr); 
		pr=pr->link; 
	} 
} 
void destroy() /*建立进程撤消函数(进程运行结束,撤消进程)*/ 
{ 
	printf("\n 进程 [%s] 已完成.\n",p->name); 
	free(p); 
} 
void running() /* 建立进程就绪函数(进程运行时间到,置就绪状态*/ 
{ 
	(p->rtime)++; 
	if(p->rtime==p->ntime) 
	destroy(); /* 调用destroy函数*/ 
	else 
	{ 
		p->state='w'; 
		sort_in_ready(); /*调用sort函数*/ 
	} 
} 

void come2ready()
{
	while (true)
	{
		if (come==NULL) return ;
		if (come->ctime==h)
		{
			p=come;
			come=come->link;
			p->link=NULL;			
			sort_in_ready();
		}
		else return ;
	}
}

int main() /*主函数*/ 
{ 
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int len; 
	h=-1;
	char ch; 
	input(); 
	while(((ready!=NULL) || (come!=NULL)) )
	{ 
		h++;
		printf("--------------------------------"); 
		printf("\n The execute number:%d \n",h); 
		come2ready(); 
		if (ready!=NULL)
		{
			p=ready; 
			ready=p->link; 
			p->link=NULL; 
			p->state='R'; 
		}
		else
		{
			printf("\n暂无程序运行\n",h);  
		}	
		check(); 
		running(); 
	} 
	printf("\n\n 进程已经完成.\n"); 
	ch=getchar(); 
} 

