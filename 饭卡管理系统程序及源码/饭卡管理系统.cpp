#include<stdio.h> 
#include<stdlib.h> 
#include<conio.h> 
#include<string.h>
#define N 200 

// 参数定义 
struct card 
{ 
    char name[10],num[10]; 
    float yu,sum; 
    int guashi; 
}; //结构体数组以保存数据，定义卡片的编号，姓名，余额，使用范围，以及挂失 

void print(); 
void Creat(); //开卡 
void Buy(); //买饭 
int exist(char num[10]);//定义判断卡片存在 
int guashi(char num[10]); //定义是否挂失 
int yu(char num[10]);//定义余额是否充足 
void Add(); //定义饭卡充值 
char *fan (float fsum);//定义根据数值返回楼层 
void Query(); //定于查询饭卡信息 
int pd(char num[10],char id[10]); //定义判断两个数组的值是否相等 
void guahsi(); //定义饭卡挂失 与解除 
void Modify();//定义修改饭卡信息 
void Delete();//定义删除饭卡信息 
 
//主程序 
int main() 
{ 	
	char choose='\0'; 
    char yes_no='\0'; 
    do 
    { 
	   
	   print(); 
       printf("\n请选择菜单数字\n"); 
       choose=getch(); 
       switch(choose) 
        {
            case '1':Creat();break; 
            case '2':Buy();break; 
            case '3':Add();break;   
            case '4':guahsi();break; 
            case '5':Query();break;
            case '6':Modify();break;
            case '7':Delete();break;
            case '0':exit(0);break; 
            default :{printf("\n 无此选项!\n");}break; 
        } 
    print(); 
    system("cls");
    printf("\n 是否返回主菜单？（Y/N） "); 
    do 
    { 
		yes_no=getch(); 
    }
	while(yes_no!='Y'&&yes_no!='y'&&yes_no!='N'&&yes_no!='n'); // 判断是或否 
    }
	while(yes_no=='Y'||yes_no=='y'); 
} 
void print() 
{  
    printf("\n\n"); 
    printf(" ==================================================\n"); 
    printf("             饭卡管理系统  （请选择编号0～7）              \n"); 
    printf(" ==================================================\n"); 
    printf("              1--开卡              \n"); 
    printf("              2--买饭                      \n"); 
    printf("              3--饭卡充值                  \n");  
    printf("              4--饭卡挂失与解除            \n"); 
    printf("              5--查询饭卡信息              \n");
    printf("              6--修改饭卡信息              \n");
    printf("              7--删除饭卡信息（注销饭卡）              \n"); 
    printf("              0--退出系统                  \n"); 
    printf(" ==================================================\n"); 
} 

// 开卡 
void Creat() 
{ 
    system("cls");
	printf("\n1--开卡\n"); 
	int i=1; 
    struct card temp={0}; 
    FILE *fp=NULL; 
    char yes_no='\0'; 
    temp.guashi=0; 
    temp.sum=0; 
    fp=fopen("用户数据.txt","a");         // 打开用户数据.txt文档，并追加 
    if(fp==NULL) 
	    {
		    printf("\n\n 饭卡文件丢失!按任意键继续...");
			getch();
			exit(0);
		} 
    else 
    {
	    fclose(fp); 
        do 
        { 
		    printf("\n 请输入第%d个记录:\n\n",i); 
            printf(" 卡号（6位）:");scanf("%s",&temp.num); 
            if(exist(temp.num)!=1)                  
            { 
			    fp=fopen("用户数据.txt","a");    // 用户数据以文件形式保存 
                printf(" 姓名:"); 
                scanf("%s",&temp.name); 
                printf(" 充值金额:");               // 饭卡充值 
                scanf("%f",&temp.yu); 
                printf(" 使用范围（1、一楼；2、二楼；4、三楼，若都可使用则叠加，上限为7）:");     // 设置使用范围 
                scanf("%f",&temp.sum); 
                fprintf(fp,"%10s%10s%20.2f%4d%20.2f\n",temp.num,temp.name,temp.yu,temp.guashi,temp.sum); 
                fclose(fp); 
                i++; 
            } 
            else printf(" 卡号重复!\n"); 
            printf("\n 是否继续输入？（Y/N）\n"); 
            do
			{ 
			    yes_no=getch(); 
            }
			while(yes_no!='Y'&&yes_no!='y'&&yes_no!='N'&&yes_no!='n');    // 判断是或否 
       }
	   while(yes_no=='Y'||yes_no=='y'); 
    } 
} 

// 买饭 
void Buy() 
{ 
    FILE *fp=NULL; 
    struct card temp[N]={0}; 
    int i=0,j; 
    char num_temp[10]={0}; 
    float money; 
	system("cls");
	printf("\n"); 
    printf("2--买饭"); 
    printf("\n");  
    fp=fopen("用户数据.txt","r");       // 打开用户数据.txt文档，并读取 
    while(feof(fp)==0) 
    {
	    fscanf(fp,"%s%s%f%d%f",temp[i].num,temp[i].name,&temp[i].yu,&temp[i].guashi,&temp[i].sum);    
        i++; 
    } 
    fclose(fp); 
    printf("\n 请输入卡号:");
	scanf("%s",num_temp); 
    if(exist(num_temp)==-1) 
	    printf("\n 卡号不存在！");   // 判断输入卡号是否正确 
    else if(guashi(num_temp)==1) 
	    printf("\n 本卡已挂失！");   // 判断卡片是否挂失 
    else if(yu(num_temp)==0)
	    printf("\n 余额不够，请续费！"); // 判断余额是否足够 
    else 
    {
	    for(j=0;j<i;j++) 
        if(strcmp(num_temp,temp[j].num)==0)  // 判断输入卡号与已有卡号是否相同 
		    break; 
        printf("\n 请输入消费金额:");scanf("%f",&money); 
        printf("\n           卡号         姓名            余额\n"); 
        printf("\n 消费前:%-10s      %-10s      %-10.2f\n",temp[j].num,temp[j].name,temp[j].yu); 
        printf("\n 消费后:%-10s      %-10s      %-10.2f\n",temp[j].num,temp[j].name,temp[j].yu-money); 
        temp[j].yu=temp[j].yu-money;       // 计算修改后的余额 
        fp=fopen("用户数据.txt","w");     // 写入修改后的余额 
        for(j=0;j<i-1;j++)  
        fprintf(fp,"%10s%10s%20.2f%4d%20.2f\n",temp[j].num,temp[j].name,temp[j].yu,temp[j].guashi,temp[j].sum); 
        fclose(fp); 
        printf("\n\n 此次消费成功！按任意键返回主菜单.....");
		getch();
		return; 
	} 
    printf("\n\n 此次消费失败！按任意键返回主菜单...");
	getch(); 
} 

// 判断存在 
int exist(char num[10]) 
{
    FILE *fp=NULL; 
    struct card temp[N]={0}; 
    int i=0,flag=-1,k=0; 
    fp=fopen("用户数据.txt","r");   // 读取用户数据.txt中的数据
    while(feof(fp)==0) 
    { 
	    fscanf(fp,"%s%s%f%d%f\n",temp[k].num,temp[k].name,&temp[k].yu,&temp[k].guashi,&temp[k].sum); 
        k++; 
    } 
    fclose(fp); 
    for(i=0;i<k;i++) 
    {
	    if(strcmp(num,temp[i].num)==0)    // 判断卡片是否存在 
        { 
		    flag=1; 
            break; 
        } 
    }   
    return flag; 
} 

// 判断挂失 
int guashi(char num[10]) 
{
    FILE *fp=NULL; 
    struct card temp[N]={0}; 
    int i=0,j; 
    fp=fopen("用户数据.txt","r");   // 读取用户数据.txt中的数据 
    while(feof(fp)==0) 
    { 
	    fscanf(fp,"%s%s%f%d%f\n",temp[i].num,temp[i].name,&temp[i].yu,&temp[i].guashi,&temp[i].sum); 
        i++; 
    } 
    fclose(fp); 
    for(j=0;j<i;j++) 
    { 
	    if(strcmp(num,temp[j].num)==0)  // 判断是否挂失 
        break; 
    } 
    if(temp[j].guashi==1)  
    return 1; 
    else  
    return 0; 
} 

// 检查余额 
int yu(char num[10]) 
{ 
    FILE *fp=NULL; 
    struct card temp[N]={0}; 
    int i=0,j; 
    fp=fopen("用户数据.txt","r");   // 读取用户数据.txt中的数据
    while(feof(fp)==0) 
    {
	    fscanf(fp,"%s%s%f%d%f\n",temp[i].num,temp[i].name,&temp[i].yu,&temp[i].guashi,&temp[i].sum); 
        i++; 
    } 
    fclose(fp); 
    for(j=0;j<i;j++) 
    { 
	    if(strcmp(num,temp[j].num)==0)  
    break; 
    } 
    if(temp[j].yu<5.00)   // 判断余额是否充足 
 	    return 0; 
    else return 1; 
} 

// 饭卡充值 
void Add() 
{ 
    FILE *fp=NULL; 
    struct card temp[N]={0}; 
    int i=0,j,k; 
    char num_temp[10]={0}; 
    float money; 
    system("cls");
	printf("\n"); 
    printf("3--饭卡充值"); 
    printf("\n");
    fp=fopen("用户数据.txt","r");   // 读取用户数据.txt中的数据
    while(feof(fp)==0) 
    { 
	    fscanf(fp,"%s%s%f%d%f\n",temp[i].num,temp[i].name,&temp[i].yu,&temp[i].guashi,&temp[i].sum); 
        i++; 
    } 
    fclose(fp); 
    printf("\n\n 请输入卡号:");
	scanf("%s",&num_temp); 
    if(exist(num_temp)==1&&guashi(num_temp)==0)   // 判断卡片是否存在
    {
	    for(j=0;j<i;j++) 
        {
		    if(strcmp(num_temp,temp[j].num)==0)  // 判断卡号是否相同 
            {
			    printf("\n 请输入续费金额:");scanf("%f",&money); 
                printf("\n           卡号          姓名           余额\n"); 
                printf(" 续费前:%-10s      %-10s      %-10.2f\n\n",temp[j].num,temp[j].name,temp[j].yu); 
                printf(" 续费后:%-10s      %-10s      %-10.2f\n",temp[j].num,temp[j].name,temp[j].yu+money); 
                temp[j].yu=temp[j].yu+money;    // 计算余额 
            } 
        } 
        fp=fopen("用户数据.txt","w");   // 写入用户数据.txt文档
        for(k=0;k<i;k++)  
        fprintf(fp,"%10s%10s%20.2f%4d%20.2f\n",temp[k].num,temp[k].name,temp[k].yu,temp[k].guashi,temp[k].sum); 
        fclose(fp); 
        printf("\n\n 续费成功！按任意键返回主菜单......"); 
    } 
    else 
    printf("\n\n 卡号不存在或已挂失！按任意键返回主菜单..."); 
    getch(); 
} 

// 饭卡挂失与解除 
void guahsi() 
{ 
    FILE *fp=NULL; 
    struct card temp[N]={0}; 
    int i=0,j,k; 
    char num_temp[10]={0},choose; 
    system("cls");
	printf("\n"); 
    printf("4--饭卡挂失与解除\n"); 
    printf(" |------------------------------------------|\n"); 
    printf(" |          请输入选项编号(0～2)            |\n"); 
    printf(" |------------------------------------------|\n"); 
    printf(" |             1--设置挂失                  |\n"); 
    printf(" |                                          |\n"); 
    printf(" |             2--解除挂失                  |\n"); 
    printf(" |                                          |\n"); 
    printf(" |             0--返回                      |\n"); 
    printf(" |------------------------------------------|\n"); 
    printf("\n 请输入操作编号:"); 
    fp=fopen("用户数据.txt","r");   // 读取用户数据.txt中的数据
    if(fp==NULL)
	{
		printf("\n 饭卡文件丢失!");
		exit(0);
	} 
    while(feof(fp)==0) 
    { 
	    fscanf(fp,"%s%s%f%d%f\n",temp[i].num,temp[i].name,&temp[i].yu,&temp[i].guashi,&temp[i].sum); 
        i++; 
    } 
    fclose(fp); 
    choose=getch(); 
    if(choose=='1') 
    { 
	    printf("\n\n 请输入卡号:");
		scanf("%s",&num_temp); 
        if(exist(num_temp)==1) // 判断卡片是否存在 
        {
		    for(j=0;j<i;j++) 
            if(strcmp(num_temp,temp[j].num)==0) break;   // 判断输入卡号与已有卡号是否相同 
            temp[j].guashi=1;     // 饭卡设置挂失 
            fp=fopen("用户数据.txt","w");   // 写入用户数据.txt文档 
            for(k=0;k<i;k++)  
            fprintf(fp,"%10s%10s%20.2f%4d%20.2f\n",temp[k].num,temp[k].name,temp[k].yu,temp[k].guashi,temp[k].sum); 
            fclose(fp); 
            printf("\n 设置成功！按任意键返回主菜单......");
			getch();
			return; 
        } 
        else
		{
		    printf("\n 此卡不存在！按任意键返回主菜单......");
			getch();
			return;
		} 
    } 
    else if(choose=='2') 
    {
	    printf("\n\n 请输入卡号:");
		scanf("%s",&num_temp);
		printf("\n"); 
        if(exist(num_temp)==1) // 判断卡片是否存在 
        { 
		    for(j=0;j<i;j++) 
            if(strcmp(num_temp,temp[j].num)==0)  // 判断输入卡号与已有卡号是否相同 
			    break; 
            temp[j].guashi=0;   // 饭卡解除挂失
            fp=fopen("用户数据.txt","w");   // 写入用户数据.txt文档 
            for(k=0;k<i;k++)  
            fprintf(fp,"%10s%10s%20.2f%4d%20.2f%\n",temp[k].num,temp[k].name,temp[k].yu,temp[k].guashi,temp[k].sum); 
            fclose(fp); 
            printf("\n 解除成功！按任意键返回主菜单......");
			getch();
			return;
        }
		else 
		{
		    printf(" 此卡不存在！按任意键返回主菜单......");
			getch();
		} 
    } 
} 

// 查询饭卡信息 
void Query() 
{ 
    int i=0,j=0; 
    char ch[20]="",choose,id[10]; 
    struct card temp[N]={0}; 

    FILE *fp=NULL; 
    fp=fopen("用户数据.txt","r");   // 读取用户数据.txt数据 
    while(feof(fp)==0) 
    {
	    fscanf(fp,"%s%s%f%d%f\n",temp[i].num,temp[i].name,&temp[i].yu,&temp[i].guashi,&temp[i].sum); 
        i++; 
    } 
    if(fp==NULL) 
    {
	    printf("\n打开文件失败!\n");
		return;
	} 
    system("cls");
	printf("\n"); 
    printf("5--查询饭卡信息");
	printf("\n"); 
    printf(" |------------------------------------------|\n"); 
    printf(" |          请输入选项编号(0～3)            |\n"); 
    printf(" |------------------------------------------|\n"); 
    printf(" |             1--饭卡编号查询              |\n"); 
    printf(" |                                          |\n"); 
    printf(" |             2--饭卡使用人查询            |\n"); 
    printf(" |                                          |\n"); 
	printf(" |             3--查询所有数据              |\n"); 
    printf(" |                                          |\n"); 
    printf(" |             0--返回                      |\n"); 
    printf(" |------------------------------------------|\n"); 
    printf("\n显示为1表示挂失，显示为0表示未挂失\n");
    printf("\n 请输入操作编号：\n"); 
    choose=getch();
	if (choose=='1')  // 选择使用饭卡编号查询 
	{
		printf("\n 请输入要查询的饭卡编号:");
		scanf("%s",&id);
		printf("%13s%15s%17s%10s%18s\n","饭卡编号","饭卡使用人","饭卡余额","是否挂失","使用范围");
		for(i=0;i<=20;i++) if (pd(temp[i].num,id)==1 && temp[i].num[1] !=0) {printf("%13s%15s%15.2f%10d%20s\n",temp[i].num,temp[i].name,temp[i].yu,temp[i].guashi,fan(temp[i].sum));j++;}
		if (j==0) printf("查无此数据！\n\n");
	 } 
	if (choose=='2')  // 选择使用饭卡使用人查询 
	{
		printf("\n 请输入要查询的饭卡使用人:");
		scanf("%s",&id);
		printf("%13s%15s%17s%10s%18s\n","饭卡编号","饭卡使用人","饭卡余额","是否挂失","使用范围");
		for(i=0;i<=20;i++) if (pd(temp[i].name,id)==1 && temp[i].num[1] !=0)  {printf("%13s%15s%15.2f%10d%20s\n",temp[i].num,temp[i].name,temp[i].yu,temp[i].guashi,fan(temp[i].sum));j++;}
		if (j==0) printf("查无此数据！\n\n");
	 } 
	 if (choose=='3')  // 查询所有饭卡信息 
	{
		printf("%13s%15s%17s%10s%18s\n","饭卡编号","饭卡使用人","饭卡余额","是否挂失","使用范围");
		for(i=0;i<=20;i++) if (temp[i].num[1] !=0) printf("%13s%15s%15.2f%10d%20s\n",temp[i].num,temp[i].name,temp[i].yu,temp[i].guashi,fan(temp[i].sum));
	 } 
    fclose(fp); 
    printf("\n按任意键返回主菜单.....");
	getch();
	return;
}

// 修改饭卡信息 
void Modify()
{
	FILE *fp=NULL; 
    struct card temp[N]={0}; 
    int i=0,j,k,choose; 
    char num_temp[10]={0},yes_no; 
    float shuru; 
    fp=fopen("用户数据.txt","r"); 
    while(feof(fp)==0) 
    { 
	    fscanf(fp,"%s%s%f%d%f\n",temp[i].num,temp[i].name,&temp[i].yu,&temp[i].guashi,&temp[i].sum); 
        i++; 
    } 
    fclose(fp); 
    printf("\n\n 请输入卡号:");
	scanf("%s",&num_temp); 
    if(exist(num_temp)==1&&guashi(num_temp)==0)   // 判断卡片是否存在 
    {
    	do{
	    for(j=0;j<i;j++) 
        {
		    if(strcmp(num_temp,temp[j].num)==0)  // 判断输入卡号与已有卡号是否相同
            {
		
			    system("cls");
	            printf("\n"); 
                printf("6--修改饭卡信息"); 
                printf("\n");
   				printf(" |---------------------------------------------|\n"); 
  				printf(" |         请输入选项编号(0～4)                |\n"); 
  				printf(" |---------------------------------------------|\n"); 
  				printf(" |            1--修改饭卡编号                  |\n"); 
  				printf(" |                                             |\n"); 
  				printf(" |            2--修改饭卡使用人                |\n"); 
  				printf(" |                                             |\n"); 
				printf(" |            3--修改饭卡余额（防止盗刷时使用）|\n"); 
				printf(" |                                             |\n"); 
				printf(" |            4--修改使用范围                  |\n");
  				printf(" |                                             |\n");  
  				printf(" |            0--返回                          |\n"); 
  				printf(" |---------------------------------------------|\n"); 
				printf("\n 请输入修改项目:");scanf("%d",&choose); 
				printf("\n           卡号          姓名           余额        使用范围\n"); 
                printf("更改前:%-10s      %-10s      %-10.2f   %-10f\n\n",temp[j].num,temp[j].name,temp[j].yu,temp[k].sum); 
				if (choose==1)  // 修改饭卡编号 
				{
					printf("\n请输入新的卡号：");
					scanf("%s",&temp[j].num);
					while(exist(temp[j].num)==1)  //  判断输入卡号与已有卡号是否相同
					{
						printf (" 卡号重复!请重新输入：") ;
						scanf("%s",&temp[j].num);
					}
				 } 
                else if(choose==2)  // 修改饭卡使用人 
                {
                	printf("\n请输入新的使用人姓名：");
					scanf("%s",&temp[j].name);
				}
				else if (choose==3)  // 修改充值金额，防止盗刷 
				{
					printf("\n请输入新的余额：");
					scanf("%f",&temp[j].yu); 
				}
				else if (choose==4) // 修改饭卡适用范围 
				{
					printf("\n请输入新的使用范围：");
					scanf("%f",&temp[j].sum); 
				}
                printf("更改后:%-10s      %-10s      %-10.2f   %-10.2f\n",temp[j].num,temp[j].name,temp[j].yu,temp[k].sum); 
            } 
        } 
        fp=fopen("用户数据.txt","w");  // 写入用户数据 
        for(k=0;k<i;k++)  
        fprintf(fp,"%10s%10s%20.2f%4d%20.2f\n",temp[k].num,temp[k].name,temp[k].yu,temp[k].guashi,temp[k].sum); 
        fclose(fp); 
        printf("\n\n 修改成功！是否继续操作Y/N："); 
        yes_no=getch();
		}while (yes_no=='Y'||yes_no=='y');
    } 
    else 
    printf("\n\n 卡号不存在或已挂失！按任意键返回主菜单..."); 
    getch(); 
} 
 
// 删除饭卡信息（注销饭卡） 
 void Delete()
 {
 	int i=0,choose; 
    char ch[20]="";  // 设定20条用户数据 
    struct card temp[N]={0}; 
    system("cls");
	printf("\n"); 
    printf("7--删除饭卡信息"); 
    printf("\n");
    FILE *fp=NULL; 
    FILE *fp1=NULL;
    fp=fopen("用户数据.txt","r");   // 读取用户数据.txt的数据 
    while(feof(fp)==0) 
    {
	    fscanf(fp,"%s%s%f%d%f\n",temp[i].num,temp[i].name,&temp[i].yu,&temp[i].guashi,&temp[i].sum); 
        i++; 
    } 
    if(fp==NULL) 
    {
	    printf("\n打开文件失败!\n");
		return;
	}  
    printf("%10s%13s%15s%17s%10s%18s\n","命令编号","饭卡编号","饭卡使用人","饭卡余额","是否挂失","使用范围");
    for(i=0;i<=20;i++) 
     if (temp[i].num[1] !=0) 
	 printf("%10d%13s%15s%15.2f%10d%20s\n",i+1,temp[i].num,temp[i].name,temp[i].yu,temp[i].guashi,fan(temp[i].sum));  // 对饭卡所有饭卡信息进行编号 ，并在屏幕显示 
    fclose(fp); 
    printf("请选择需要删除的编号（0取消）:");
    scanf("%d",&choose);  // 选择要进行删除的饭卡信息所在行 
	fp=fopen("用户数据.txt","w");   // 写入更改后的数据 
	if(fp==NULL) 
    {
	    printf("\n打开文件失败!\n");
		return;
	} 
	if (choose<=20)
    {
    	for (i=0;i<=20;i++)
    	{
			if (i!=choose-1 && temp[i].num[1] !=0)   // 对已选择的饭卡信息进行删除 
			fprintf(fp,"%10s%10s%20.2f%4d%20.2f\n",temp[i].num,temp[i].name,temp[i].yu,temp[i].guashi,temp[i].sum);
		}
	}
	fclose(fp);

    printf("\n操作成功，按任意键返回主菜单.....");
	getch();
	return;
 }
 
// 判断两个数组的值是否想等 
 int pd(char num[10],char id[10])
 {
 	int i,j=1;
 	for (i=1;i<=10;i++)
 		{
 		if (id[i]=='\0') break;
 		if(num[i]!=id[i]) j=0;
		 }
 		
 	return j; 
 }
 
//  根据数值返回楼层
 char *fan (float fsum)
 {
 	static char re[20];
 	if (fsum == 1.0) strcpy(re,"一楼"); 
	 else  if (fsum == 2.0) strcpy(re,"二楼");
	 else  if (fsum == 3.0) strcpy(re,"一/二楼"); 
	 else if (fsum == 4.0) strcpy(re,"三楼"); 
	 else  if (fsum == 5.0) strcpy(re,"一/三楼");
	 else  if (fsum == 6.0) strcpy(re,"二/三楼"); 
	 else  if (fsum == 7.0) strcpy(re,"一/二/三楼");
	 return re; 
  } 
