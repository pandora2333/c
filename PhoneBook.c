#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 15

typedef struct Contacts
{
	char *name;  //姓名,作为全局唯一标识符，唯一性
	char *sex;   //性别
	char phone[MAXSIZE]; //电话号码
	char *relation;//与本人关系
	char *address;//住址
	int length;//链表长度
	struct Contacts *next;//后继节点
}Contacts ,*People;

//全局化一个链表地址
People head =NULL;
//设置一个标志位判断是否已经初始化
static int flag = 1;
int ret = 1;//用于update
//主要功能函数
void addContacts();//增加联系人
void  delContacts();//删除联系人
People findContacts(People node,char *find);//查找联系人
void updateContacts(People node);//修改联系人
void showContacts(People node);//显示联系人
void showHead();//show的头部信息展示
void showTail();//show的尾部信息展示
void showFindSamePart();//用于保存find查找的相同部分代码
void printMainMenu();//打印主菜单
int notNullStr(char *str);//排除无效输入字符
/*链表操作--start--*/
void init();//初始化一个链表
void destory();//销毁链表，释放内存
/*--end--*/
int findWaySelected();//用于决定查找联系人的方式，是按名字，电话号码？
int validatePhone(char *phone);//判断电话号码是否有效
void printUpdateMenu(People node);//展示修改界面
void Free(People node);//释放节点分配的所有内存 

void Free(People node){
	if(node!=NULL){
		if(node->name!=NULL){
			free(node->address);
			free(node->name);
			free(node->relation);
			free(node->sex);
			free(node);//释放头节点以外节点 
		}else{
			free(node);//释放head头节点 
		}
	} 
} 

int notNullStr(char *str){
	if(strcmp(str,"\"\"")==0){
		printf("\t请输入有效字符!\n");
		return 0;
	}
	return 1;
}

void showFindSamePart(){
	int choose = findWaySelected();
	printf("\t选择 %d 号方式查找!!!!\n",choose);
	if(choose){
		printf("\t当前模式为按名字查找\n");
		printf("\t请输入查找联系人的名字:");
	}else{
		printf("\t当前模式为按电话号码查询\n");
		printf("\t请输入查找联系人的电话号码:");
	}
}

void showHead(){
	printf("\t\t\t     ★所有联系人信息★\n");
	printf("\t       已经添加的联系人人数:%d\n",head->length);
	printf("\t       *************************************************************\n");
	printf("\t\t姓名\t性别\t电话号码\t\t关系\t住址\n");
}

void showTail(){
	printf("\t       *************************************************************\n");
	printf("\t转移到对应界面...\n");
}

void printUpdateMenu(People node){
	//先展示node
	printf("\t修改样品展示:\n\n");
	showHead();
	showContacts(node);
	showTail();
	printf("\t\t\t进入修改联系人界面\n");
	printf("\t\t\t******************************\n\n");
	printf("\t\t\t*     ①修改姓名             *\n");
	printf("\t\t\t*     ②修改性别             *\n");
	printf("\t\t\t*     ③修改电话号码         *\n");
	printf("\t\t\t*     ④修改与本人关系       *\n");
	printf("\t\t\t*     ⑤修改住址             *\n");
	printf("\t\t\t*     ⑥返回主界面/退出      *\n");
	printf("\t\t\t******************************\n\n");
	printf("\t请选择:");
	fflush(stdin);
	int input;
	scanf("%d",&input);
	fflush(stdin);
	char *temp = (char *)malloc(sizeof(char)*MAXSIZE);
	/*用于case 1 --start--*/
	People distinct = head->next;//游标
	int ok = 0;//当出现名字冲突时，循环标志位
	/*--end--*/
	switch(input){
		case 1:
			//修改姓名
			//加入预先搜索,去重
			do{
				printf("\t请输入修改后的姓名:");
				scanf("%s",temp);
				ok = 0;//标志位复位
				while(distinct!=NULL){
					if(strcmp(temp,distinct->name)==0){
						printf("\t存在相关联系人，请重新输入其他名字!\n");
						ok = 1;
						break;//找到一个就不再向下查询，节约时间
					}
					distinct=distinct->next;
				}
				fflush(stdin);
			}while(ok);
			if(notNullStr(temp)){
				node->name = temp;
			}
			break;
		case 2:
			//修改性别
			printf("\t请输入修改后的性别:");
			scanf("%s",temp);
			fflush(stdin);
			if(notNullStr(temp)){
				node->sex = temp;
			}
			break;
		case 3:
			//修改电话号码
			printf("\t请输入修改后的电话号码:");
			do{
				printf("\t请输入电话号码:");
				scanf("%s",node->phone);
				fflush(stdin);
				//加入对phone的验证
			}while(!validatePhone(node->phone));
			break;
		case 4:
			//修改与本人关系
			printf("\t请输入修改后的关系:");
			scanf("%s",temp);
			fflush(stdin);
			if(notNullStr(temp)){
				node->relation = temp;
			}
			break;
		case 5:
			//修改住址
			printf("\t请输入修改后的地址:");
			scanf("%s",temp);
			fflush(stdin);
			if(notNullStr(temp)){
				node->address = temp;
			}
			break;
		case 6:
		default:
			//返回主界面
			printf("\t最终修改后:\n\n");
			showHead();
			showContacts(node);
			showTail();
			ret = 0;
			free(temp);
			temp=NULL;
	}

}

void init(){
	head = (People)malloc(sizeof(People));
	if(head){
		//建立一个带头结点的链表，其中length属性只有头结点有值
		head->next=NULL;
		head->length=0;
		head->name=NULL;//为updateContacts函数做准备
		flag = 0;
	}else{
		exit(0);//内存分配失败时，自动退出
	}
}

void destory(){
	People p;
	while(head!=NULL)
	{
		p = head;
		head = head->next;
	//	Free(p);
    }
}

void addContacts(){//头插法
	People temp = (People)malloc(sizeof(People));
	//以下代码实现添加--start---
	printf("\t请输入姓名:");
	temp->name = (char *)malloc(sizeof(char)*MAXSIZE);
	scanf("%s",temp->name);
	fflush(stdin);
	if(!notNullStr(temp->name)){
		printf("\t名字错误，请重试!\n");
		free(temp);
		return;
	}
	//先搜索是否已经存在相应联系人,去重
	People distinct = head->next;
	while(distinct!=NULL){
		if(strcmp(temp->name,distinct->name)==0){
			printf("\t存在相关联系人，自动跳转到修改页面\n");
			updateContacts(temp);//update唯一性使用
			free(temp);//不是新建节点，故释放内存
			return;
		}
		distinct=distinct->next;
	}
	printf("\t请输入性别:");
	temp->sex = (char *)malloc(sizeof(char)*MAXSIZE-5);
	scanf("%s",temp->sex);
	fflush(stdin);
	do{
	printf("\t请输入电话号码:");
	scanf("%s",temp->phone);
	fflush(stdin);
	//加入对phone的验证
	}while(!validatePhone(temp->phone));
	printf("\t请输入所添加联系人与本人关系:");
	temp->relation = (char *)malloc(sizeof(char)*MAXSIZE);
	scanf("%s",temp->relation);
	fflush(stdin);
	if(!notNullStr(temp->relation)){
		printf("\t关系错误，请重试!\n");
		free(temp);
		return;
	}
	printf("\t请输入所添加联系人住址:");
	temp->address = (char *)malloc(sizeof(char)*MAXSIZE);
	scanf("%s",temp->address);
	fflush(stdin);
	if(!notNullStr(temp->address)){
		printf("\t地址错误，请重试!\n");
		free(temp);
		return;
	}
	temp->length = 1;
	//--end---
	temp->next = head->next;
	head->next = temp;
	head->length=head->length+1;
	printf("\t联系人信息录入成功!!!!\n");
}

void  delContacts(){//可以批量删除
	printf("\t已经进入删除模式，请先查找你要修改的联系人...\n\n");
	printf("\t请输入你要删除的联系人姓名或电话号码:");
	char *delBy = (char *)malloc(sizeof(char)*MAXSIZE);
	fflush(stdin);
	scanf("%s",delBy);
	People temp =head->next;//遍历游标
	People delPre = head;//记录删除前的一个节点
	People tempf =NULL;//记录删除的节点位置
	while(temp!=NULL){
		if(strcmp(temp->name,delBy)==0||strcmp(temp->phone,delBy)==0){
			delPre->next = temp->next;
			head->length=head->length-1;
			printf("\t删除一条完毕!\n\n");
			tempf = temp;
		}else{
			delPre = temp;
			tempf=NULL;
		}
		temp = temp->next;
		if(tempf!=NULL){
			//Free(tempf);//dev c++上可以正常运行,vc上无法使用此段代码
			tempf=NULL;
		}
	}
	free(delBy);//节省内存
	delBy = NULL;
}

People findContacts(People node,char *find){
	People temp = node;
	while(temp!=NULL){
		if(strcmp(temp->name,find)==0||strcmp(temp->phone,find)==0){
			return temp;
		}
		temp=temp->next;
	}
	return NULL;
}

void updateContacts(People node){
	ret = 1;//每次调用初始化一次
	printf("\t已经进入修改模式...\n\n");
	int num = 1;//标识第几条记录,对应不唯一性使用
	if(node->name!=NULL){//唯一性
		People temp = head->next;
		while(temp!=NULL){//找到原有数据的地址
			if(strcmp(temp->name,node->name)==0){
				break;
			}
			temp=temp->next;
		}
		if(temp!=NULL){
			while(ret){
				printUpdateMenu(temp);
			}
		}
	}else{//不唯一性
		showFindSamePart();
		char *find = (char *)malloc(sizeof(char)*MAXSIZE);
		fflush(stdin);
		scanf("%s",find);
		People temp = head;
		do{
			temp = findContacts(temp->next,find);
			if(temp!=NULL){
				printf("\t这是查询到的第 %d 条记录!\n\n",num);
				num++;
				while(ret){
					printUpdateMenu(temp);
				}
				ret = 1;
			}
		}while(temp!=NULL);
		free(find);
		find = NULL;
	}
}

void showContacts(People node){
	//遍历链表
	People temp = NULL;
	int alone = 0;//标示是否打印全部
	if(node->name==NULL){
		temp = node->next;
	}else{
		temp = node;
		alone = 1;
	}
	while(temp!=NULL){
		printf("\t\t%s\t%s\t%s\t\t%s\t%s\n",temp->name,temp->sex,temp->phone,temp->relation,temp->address);
		if(alone){ break;}
		temp = temp->next;
	}
}

int findWaySelected(){//1.表示按名字查找，0.表示按电话号码查找
	int input;
	printf("\t请输入查找联系人方式(1.表示按名字查找  0. 表示按电话号码查找):");
	fflush(stdin);
	scanf("%d",&input);
	//验证输入数字
	if(input==1||input==0){
		return input;
	}else{
		printf("\t由于你的不正确输入，系统采用默认的按名字查找方式\n");
		return 1;//默认按名字查找
	}
}

int validatePhone(char *phone){
	printf("\t电话号码验证中...请稍等...\n");
	int i=0;
	while(phone[i]){//判断电话号码全由数字组成
		if(phone[i]<48||phone[i]>57){
			printf("\t请填写正确的电话号码,不要含有字符\n");
			return 0;
		}
		i++;
	}
	if(strlen(phone)!=11||phone[0]!=49||phone[1]<=50||phone[1]>=57){//判断组成的数字是否有效
		printf("\t请填写正确的位数，有效的电话号码\n");
		return 0;
	}
	return 1;
}

//入口函数
void printMainMenu(){
	printf("\t\t\t欢迎来到FortyThieves通讯录!\n");
	printf("\t\t\t         Version:1.0\n ");
	printf("\t\t\t▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃          ▲ \n");
	printf("\t\t\t▍        ①添加联系人       ▍        ▲▲\n");
	printf("\t\t\t▍        ②删除联系人       ▍       ▲▲▲\n");
	printf("\t\t\t▍        ③查找联系人       ▍      ▲▲▲▲\n");
	printf("\t\t\t▍        ④修改联系人信息   ▍     ▲▲▲▲▲\n");
	printf("\t\t\t▍        ⑤显示所有联系人   ▍         ■\n");
	printf("\t\t\t▍        ⑥退出             ▍         ■\n");
	printf("\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n\n");
	//先对链表初始化
	if(flag){
	init();
	}
	printf("\t您的选择:");
	fflush(stdin);
	int input;
	scanf("%d",&input);
	fflush(stdin);
	/*以下代码用于case 3 --start--*/
	int count = 0;//记录查询到的数量
	People temp = head;
	char *find = (char *)malloc(sizeof(char)*MAXSIZE);
	/*--end--*/
	switch(input){
		case 1:
			addContacts();
			break;
		case 2:
			delContacts();
			break;
		case 3:
			showFindSamePart();
			fflush(stdin);
			scanf("%s",find);
			printf("\t查询开始....\n");
			showHead();
			do{//循环遍历所有具有相同号码的联系人
				temp = findContacts(temp->next,find);
				if(temp!=NULL){
					showContacts(temp);
					count++;
				}
			}while(temp!=NULL);
			if(!count){//对应查询失败
				printf("\t查询失败!\n\n");
			}
			if(count){
				showTail();
			}
			printf("\t查询结束...,共计查询到: %d条记录\n",count);
			free(find);//节省内存
			find= NULL;
			break;
		case 4:
			updateContacts(head);
			break;
		case 5:
			showHead();
			showContacts(temp);
			showTail();
			break;
		case 6:
		default:
			destory();//销毁链表，释放内存
			exit(0);
	}
	
}

//test
int main(){
	//执行通信录功能
	while(1){
		printMainMenu();
	}
	return 0;
}
