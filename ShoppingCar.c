#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 6//定义一个宏:商品种类数量
/**
账户结构体声明
*/

typedef struct Account//typedef关键字相当是把struct Account进行重命名
{
	char *account;
	char *password;
}Account,*PAccount;
/**
商品结构体声明
*/

struct Goods
{
	char *ID;
	char *goodsName;
	float price;
	int flag;
}goods[N]={{"10001","addidas运动鞋",550.9f,0},
			{"10002","安踏的篮球鞋",330.3f,0},
			{"10003","华为手机",2000.9f,0},
			{"10004","中兴手机",2222.3f,0},
			{"10005","三星手机",1000.3f,0},
			{"10006","oppo手机",2000.3f,0}};//直接初始化商品信息

typedef struct Goods Goods;
typedef struct Goods *PGoods;
/**
相关功能函数声明
*/

void printMainMenu();//入口界面
void login();//用户登录
int validation(PAccount acc);//用户账户验证
void regist();//用户注册
void logingSucess();//用户登录成功页面
void printShoppingMenu();//购物功能展示界面
void printGoodsList();//商品展示界面
void shoppingCar();//展示购物车信息
/*CRUD操作*/
PGoods findGoodsById(char *id);//根据商品编号找到对应商品
void addGoods();
void operateGoods();
void deleteGoods();
void updateGoods();
void pay();//完成支付

//欢迎进入购物系统，并且具有控制功能
void printMainMenu()
{
	int input;
	printf("\t\t\t欢迎进入购物系统\n\n");
	printf("\t\t* * * * * * * * * * * * *\n\t\t*\t\t\t*\n");
	printf("\t\t*\t1.登录\t\t*\n\t\t*\t\t\t*\n");
	printf("\t\t*\t2.注册\t\t*\n\t\t*\t\t\t*\n");
	printf("\t\t*\t0.退出\t\t*\n\t\t*\t\t\t*\n");
	printf("\t\t* * * * * * * * * * * * *\n\n");
	printf("\t请输入你的选项:");
	scanf("%d",&input);
	switch(input)
	{
	case 1:
		login();
		break;
	case 2:
		void regist();
		break;
	case 0:
	default:
		exit(0);
		break;

	}

} 

PGoods findGoodsById(char *id){
	
	PGoods pgoods = NULL;
	for(int i=0;i<N;i++){
		if(strcmp(goods[i].ID,id)==0){
			pgoods = &goods[i];
		}
	}
	return pgoods;
}

void addGoods(){
	char *input = (char *)malloc(sizeof(char)*10);
	printf("\t请输入商品编号:");
	fflush(stdin);
	scanf("%s",input);
	PGoods pgoods = findGoodsById(input);
	if(pgoods){
		int count;
		printf("\t请输入商品数量:");
		scanf("%d",&count);
		if(count>0){
			pgoods->flag=count;
		}else{
			printf("\t数量不正确\n");
			exit(0);
		}
	}else{
		printf("\t你输入的商品不存在\n");
	}
	printf("\n");
}

int validation(PAccount acc)
{
	char account[10]="root";//模拟注册的账户
	char password[10]="123";//模拟对应的注册密码
	if(strcmp(account,acc->account)==0&&strcmp(password,acc->password)==0)
	{
		return 1;
	}else
	{
		return 0;
	}

}

void shoppingCar(){
	
	printf("\t\t\t欢迎进入商品列表\n\n");
	printf("\t\t* * * * * * * * * * * * * * * * * * * * *\n\t\t*\t\t\t\t        *\n");
	printf("\t\t*商品名\t\t商品编号 价格 数量      *\n");
	for(int i=0;i<N;i++){
		if(goods[i].flag!=0){
		printf("\t\t*%s\t%s\t%.2f %d\t*\n",goods[i].goodsName,goods[i].ID,goods[i].price,goods[i].flag);
		}
	}
	printf("\t\t* * * * * * * * * * * * * * * * * * * * *\n\n");
	operateGoods();
}

void operateGoods(){
	int input;
	printf("\t\t\t请选择你的操作\n\n");
	printf("\t\t* * * * * * * * * * * * *\n\t\t*\t\t\t*\n");
	printf("\t\t*\t1.删除商品\t*\n\t\t*\t\t\t*\n");
	printf("\t\t*\t2.修改商品的数目*\n\t\t*\t\t\t*\n");
	printf("\t\t*\t3.返回上一级菜单*\n\t\t*\t\t\t*\n");
	printf("\t\t* * * * * * * * * * * * *\n\n");
	printf("\t请输入你的选项:");
	scanf("%d",&input);
	switch(input)
	{
	case 1:
	    deleteGoods();
		break;
	case 2:
		updateGoods();
		break;
	case 3:
		printShoppingMenu();
		break;
	default:
		exit(0);
		break;

	}
}

void deleteGoods(){

	char *input = (char *)malloc(sizeof(char)*10);
	printf("\t请输入你要删除的id:");
	fflush(stdin);
	scanf("%s",input);
	PGoods pgoods = findGoodsById(input);
	if(pgoods&&pgoods->flag>0){
		pgoods->flag=0;
	}else{
		printf("\t购物车中没有该商品\n\n");
	}
	shoppingCar();
}

void updateGoods(){

	char *input = (char *)malloc(sizeof(char)*10);
	int count;
	printf("\t请输入你要修改的id:");
	fflush(stdin);
	scanf("%s",input);
	PGoods pgoods = findGoodsById(input);
	if(pgoods&&pgoods->flag>0){
		printf("\t请输入你要修改的商品数量:");
		fflush(stdin);
		scanf("%d",&count);
		if(count>0){
			pgoods->flag = count;
		}
	}else{
		printf("\t购物车中没有该商品\n\n");
	}
	shoppingCar();
	
}

void login()
{
	PAccount paccount=(PAccount)malloc(sizeof(Account));
	printf("\t请输入登录账户:");
	paccount->account = (char *)malloc(sizeof(char)*10);//使用指针属性的变量，记住给该属性动态分配内存
	scanf("%s",paccount->account);
	fflush(stdin);//输出缓冲区 在VC6.0上可以使用，但是其他编译器不能保证对fflush的实现
	printf("\t请输入密码:");
	paccount->password =  (char *)malloc(sizeof(char)*10);
	scanf("%s",paccount->password);
	int flag=validation(paccount);//返回值等于1表示验证成功，返回值为0表示验证失败
	if(flag)
	{
		logingSucess();	
	}else
	{
	    printMainMenu();
	}
} 

//登录成功
void logingSucess()
{
	printShoppingMenu();
}

void printShoppingMenu()
{	
	int input;
	printf("\t\t\t欢迎进入购物\n\n");
	printf("\t\t* * * * * * * * * * * * *\n\t\t*\t\t\t*\n");
	printf("\t\t*\t1.打印商品列表  *\n\t\t*\t\t\t*\n");
	printf("\t\t*\t2.购物车\t*\n\t\t*\t\t\t*\n");
	printf("\t\t*\t3.结算\t\t*\n\t\t*\t\t\t*\n");
	printf("\t\t*\t4.返回上一级菜单*\n\t\t*\t\t\t*\n");
	printf("\t\t* * * * * * * * * * * * *\n\n");
	printf("\t请输入你的选项:");
	scanf("%d",&input);
	switch(input)
	{
	case 1:
	    printGoodsList();
		break;
	case 2:
		shoppingCar();
		break;
	case 3:
		void pay();
		break;
	case 4:
		printMainMenu();
		break;
	default:
		exit(0);
		break;

	}
}

void printGoodsList(){
	printf("\t\t\t欢迎进入商品列表\n\n");
	printf("\t\t* * * * * * * * * * * * * * * * *\n\t\t*\t\t\t\t*\n");
	printf("\t\t*商品名\t\t商品编号 价格   *\n");
	for(int i=0;i<N;i++){
		printf("\t\t*%s\t%s\t%8.2f*\n",goods[i].goodsName,goods[i].ID,goods[i].price);
	}
	printf("\t\t* * * * * * * * * * * * * * * * *\n\n");
	char input;
	do{
	printf("\t是否添加商品（y/n）:");
	fflush(stdin);
	scanf("%c",&input);
	if(input=='y')
	{
		 addGoods();	
	}else
	{//待移除 
		printf("\n");
		printShoppingMenu();
	}
	}while(input=='y');
}

//test
int main()
{
//	printMainMenu();
//	printf("pass");//question:什么时候会打印?-->after calling  function printMainMenu?
	printGoodsList();//测试当前待测试方法
//	operateGoods();
	return 0;
}
