#include<stdio.h> 
#include<stdlib.h> 
#include<conio.h> 
#include<string.h>
#define N 200 

// �������� 
struct card 
{ 
    char name[10],num[10]; 
    float yu,sum; 
    int guashi; 
}; //�ṹ�������Ա������ݣ����忨Ƭ�ı�ţ���������ʹ�÷�Χ���Լ���ʧ 

void print(); 
void Creat(); //���� 
void Buy(); //�� 
int exist(char num[10]);//�����жϿ�Ƭ���� 
int guashi(char num[10]); //�����Ƿ��ʧ 
int yu(char num[10]);//��������Ƿ���� 
void Add(); //���巹����ֵ 
char *fan (float fsum);//���������ֵ����¥�� 
void Query(); //���ڲ�ѯ������Ϣ 
int pd(char num[10],char id[10]); //�����ж����������ֵ�Ƿ���� 
void guahsi(); //���巹����ʧ ���� 
void Modify();//�����޸ķ�����Ϣ 
void Delete();//����ɾ��������Ϣ 
 
//������ 
int main() 
{ 	
	char choose='\0'; 
    char yes_no='\0'; 
    do 
    { 
	   
	   print(); 
       printf("\n��ѡ��˵�����\n"); 
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
            default :{printf("\n �޴�ѡ��!\n");}break; 
        } 
    print(); 
    system("cls");
    printf("\n �Ƿ񷵻����˵�����Y/N�� "); 
    do 
    { 
		yes_no=getch(); 
    }
	while(yes_no!='Y'&&yes_no!='y'&&yes_no!='N'&&yes_no!='n'); // �ж��ǻ�� 
    }
	while(yes_no=='Y'||yes_no=='y'); 
} 
void print() 
{  
    printf("\n\n"); 
    printf(" ==================================================\n"); 
    printf("             ��������ϵͳ  ����ѡ����0��7��              \n"); 
    printf(" ==================================================\n"); 
    printf("              1--����              \n"); 
    printf("              2--��                      \n"); 
    printf("              3--������ֵ                  \n");  
    printf("              4--������ʧ����            \n"); 
    printf("              5--��ѯ������Ϣ              \n");
    printf("              6--�޸ķ�����Ϣ              \n");
    printf("              7--ɾ��������Ϣ��ע��������              \n"); 
    printf("              0--�˳�ϵͳ                  \n"); 
    printf(" ==================================================\n"); 
} 

// ���� 
void Creat() 
{ 
    system("cls");
	printf("\n1--����\n"); 
	int i=1; 
    struct card temp={0}; 
    FILE *fp=NULL; 
    char yes_no='\0'; 
    temp.guashi=0; 
    temp.sum=0; 
    fp=fopen("�û�����.txt","a");         // ���û�����.txt�ĵ�����׷�� 
    if(fp==NULL) 
	    {
		    printf("\n\n �����ļ���ʧ!�����������...");
			getch();
			exit(0);
		} 
    else 
    {
	    fclose(fp); 
        do 
        { 
		    printf("\n �������%d����¼:\n\n",i); 
            printf(" ���ţ�6λ��:");scanf("%s",&temp.num); 
            if(exist(temp.num)!=1)                  
            { 
			    fp=fopen("�û�����.txt","a");    // �û��������ļ���ʽ���� 
                printf(" ����:"); 
                scanf("%s",&temp.name); 
                printf(" ��ֵ���:");               // ������ֵ 
                scanf("%f",&temp.yu); 
                printf(" ʹ�÷�Χ��1��һ¥��2����¥��4����¥��������ʹ������ӣ�����Ϊ7��:");     // ����ʹ�÷�Χ 
                scanf("%f",&temp.sum); 
                fprintf(fp,"%10s%10s%20.2f%4d%20.2f\n",temp.num,temp.name,temp.yu,temp.guashi,temp.sum); 
                fclose(fp); 
                i++; 
            } 
            else printf(" �����ظ�!\n"); 
            printf("\n �Ƿ�������룿��Y/N��\n"); 
            do
			{ 
			    yes_no=getch(); 
            }
			while(yes_no!='Y'&&yes_no!='y'&&yes_no!='N'&&yes_no!='n');    // �ж��ǻ�� 
       }
	   while(yes_no=='Y'||yes_no=='y'); 
    } 
} 

// �� 
void Buy() 
{ 
    FILE *fp=NULL; 
    struct card temp[N]={0}; 
    int i=0,j; 
    char num_temp[10]={0}; 
    float money; 
	system("cls");
	printf("\n"); 
    printf("2--��"); 
    printf("\n");  
    fp=fopen("�û�����.txt","r");       // ���û�����.txt�ĵ�������ȡ 
    while(feof(fp)==0) 
    {
	    fscanf(fp,"%s%s%f%d%f",temp[i].num,temp[i].name,&temp[i].yu,&temp[i].guashi,&temp[i].sum);    
        i++; 
    } 
    fclose(fp); 
    printf("\n �����뿨��:");
	scanf("%s",num_temp); 
    if(exist(num_temp)==-1) 
	    printf("\n ���Ų����ڣ�");   // �ж����뿨���Ƿ���ȷ 
    else if(guashi(num_temp)==1) 
	    printf("\n �����ѹ�ʧ��");   // �жϿ�Ƭ�Ƿ��ʧ 
    else if(yu(num_temp)==0)
	    printf("\n �����������ѣ�"); // �ж�����Ƿ��㹻 
    else 
    {
	    for(j=0;j<i;j++) 
        if(strcmp(num_temp,temp[j].num)==0)  // �ж����뿨�������п����Ƿ���ͬ 
		    break; 
        printf("\n ���������ѽ��:");scanf("%f",&money); 
        printf("\n           ����         ����            ���\n"); 
        printf("\n ����ǰ:%-10s      %-10s      %-10.2f\n",temp[j].num,temp[j].name,temp[j].yu); 
        printf("\n ���Ѻ�:%-10s      %-10s      %-10.2f\n",temp[j].num,temp[j].name,temp[j].yu-money); 
        temp[j].yu=temp[j].yu-money;       // �����޸ĺ����� 
        fp=fopen("�û�����.txt","w");     // д���޸ĺ����� 
        for(j=0;j<i-1;j++)  
        fprintf(fp,"%10s%10s%20.2f%4d%20.2f\n",temp[j].num,temp[j].name,temp[j].yu,temp[j].guashi,temp[j].sum); 
        fclose(fp); 
        printf("\n\n �˴����ѳɹ�����������������˵�.....");
		getch();
		return; 
	} 
    printf("\n\n �˴�����ʧ�ܣ���������������˵�...");
	getch(); 
} 

// �жϴ��� 
int exist(char num[10]) 
{
    FILE *fp=NULL; 
    struct card temp[N]={0}; 
    int i=0,flag=-1,k=0; 
    fp=fopen("�û�����.txt","r");   // ��ȡ�û�����.txt�е�����
    while(feof(fp)==0) 
    { 
	    fscanf(fp,"%s%s%f%d%f\n",temp[k].num,temp[k].name,&temp[k].yu,&temp[k].guashi,&temp[k].sum); 
        k++; 
    } 
    fclose(fp); 
    for(i=0;i<k;i++) 
    {
	    if(strcmp(num,temp[i].num)==0)    // �жϿ�Ƭ�Ƿ���� 
        { 
		    flag=1; 
            break; 
        } 
    }   
    return flag; 
} 

// �жϹ�ʧ 
int guashi(char num[10]) 
{
    FILE *fp=NULL; 
    struct card temp[N]={0}; 
    int i=0,j; 
    fp=fopen("�û�����.txt","r");   // ��ȡ�û�����.txt�е����� 
    while(feof(fp)==0) 
    { 
	    fscanf(fp,"%s%s%f%d%f\n",temp[i].num,temp[i].name,&temp[i].yu,&temp[i].guashi,&temp[i].sum); 
        i++; 
    } 
    fclose(fp); 
    for(j=0;j<i;j++) 
    { 
	    if(strcmp(num,temp[j].num)==0)  // �ж��Ƿ��ʧ 
        break; 
    } 
    if(temp[j].guashi==1)  
    return 1; 
    else  
    return 0; 
} 

// ������ 
int yu(char num[10]) 
{ 
    FILE *fp=NULL; 
    struct card temp[N]={0}; 
    int i=0,j; 
    fp=fopen("�û�����.txt","r");   // ��ȡ�û�����.txt�е�����
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
    if(temp[j].yu<5.00)   // �ж�����Ƿ���� 
 	    return 0; 
    else return 1; 
} 

// ������ֵ 
void Add() 
{ 
    FILE *fp=NULL; 
    struct card temp[N]={0}; 
    int i=0,j,k; 
    char num_temp[10]={0}; 
    float money; 
    system("cls");
	printf("\n"); 
    printf("3--������ֵ"); 
    printf("\n");
    fp=fopen("�û�����.txt","r");   // ��ȡ�û�����.txt�е�����
    while(feof(fp)==0) 
    { 
	    fscanf(fp,"%s%s%f%d%f\n",temp[i].num,temp[i].name,&temp[i].yu,&temp[i].guashi,&temp[i].sum); 
        i++; 
    } 
    fclose(fp); 
    printf("\n\n �����뿨��:");
	scanf("%s",&num_temp); 
    if(exist(num_temp)==1&&guashi(num_temp)==0)   // �жϿ�Ƭ�Ƿ����
    {
	    for(j=0;j<i;j++) 
        {
		    if(strcmp(num_temp,temp[j].num)==0)  // �жϿ����Ƿ���ͬ 
            {
			    printf("\n ���������ѽ��:");scanf("%f",&money); 
                printf("\n           ����          ����           ���\n"); 
                printf(" ����ǰ:%-10s      %-10s      %-10.2f\n\n",temp[j].num,temp[j].name,temp[j].yu); 
                printf(" ���Ѻ�:%-10s      %-10s      %-10.2f\n",temp[j].num,temp[j].name,temp[j].yu+money); 
                temp[j].yu=temp[j].yu+money;    // ������� 
            } 
        } 
        fp=fopen("�û�����.txt","w");   // д���û�����.txt�ĵ�
        for(k=0;k<i;k++)  
        fprintf(fp,"%10s%10s%20.2f%4d%20.2f\n",temp[k].num,temp[k].name,temp[k].yu,temp[k].guashi,temp[k].sum); 
        fclose(fp); 
        printf("\n\n ���ѳɹ�����������������˵�......"); 
    } 
    else 
    printf("\n\n ���Ų����ڻ��ѹ�ʧ����������������˵�..."); 
    getch(); 
} 

// ������ʧ���� 
void guahsi() 
{ 
    FILE *fp=NULL; 
    struct card temp[N]={0}; 
    int i=0,j,k; 
    char num_temp[10]={0},choose; 
    system("cls");
	printf("\n"); 
    printf("4--������ʧ����\n"); 
    printf(" |------------------------------------------|\n"); 
    printf(" |          ������ѡ����(0��2)            |\n"); 
    printf(" |------------------------------------------|\n"); 
    printf(" |             1--���ù�ʧ                  |\n"); 
    printf(" |                                          |\n"); 
    printf(" |             2--�����ʧ                  |\n"); 
    printf(" |                                          |\n"); 
    printf(" |             0--����                      |\n"); 
    printf(" |------------------------------------------|\n"); 
    printf("\n ������������:"); 
    fp=fopen("�û�����.txt","r");   // ��ȡ�û�����.txt�е�����
    if(fp==NULL)
	{
		printf("\n �����ļ���ʧ!");
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
	    printf("\n\n �����뿨��:");
		scanf("%s",&num_temp); 
        if(exist(num_temp)==1) // �жϿ�Ƭ�Ƿ���� 
        {
		    for(j=0;j<i;j++) 
            if(strcmp(num_temp,temp[j].num)==0) break;   // �ж����뿨�������п����Ƿ���ͬ 
            temp[j].guashi=1;     // �������ù�ʧ 
            fp=fopen("�û�����.txt","w");   // д���û�����.txt�ĵ� 
            for(k=0;k<i;k++)  
            fprintf(fp,"%10s%10s%20.2f%4d%20.2f\n",temp[k].num,temp[k].name,temp[k].yu,temp[k].guashi,temp[k].sum); 
            fclose(fp); 
            printf("\n ���óɹ�����������������˵�......");
			getch();
			return; 
        } 
        else
		{
		    printf("\n �˿������ڣ���������������˵�......");
			getch();
			return;
		} 
    } 
    else if(choose=='2') 
    {
	    printf("\n\n �����뿨��:");
		scanf("%s",&num_temp);
		printf("\n"); 
        if(exist(num_temp)==1) // �жϿ�Ƭ�Ƿ���� 
        { 
		    for(j=0;j<i;j++) 
            if(strcmp(num_temp,temp[j].num)==0)  // �ж����뿨�������п����Ƿ���ͬ 
			    break; 
            temp[j].guashi=0;   // ���������ʧ
            fp=fopen("�û�����.txt","w");   // д���û�����.txt�ĵ� 
            for(k=0;k<i;k++)  
            fprintf(fp,"%10s%10s%20.2f%4d%20.2f%\n",temp[k].num,temp[k].name,temp[k].yu,temp[k].guashi,temp[k].sum); 
            fclose(fp); 
            printf("\n ����ɹ�����������������˵�......");
			getch();
			return;
        }
		else 
		{
		    printf(" �˿������ڣ���������������˵�......");
			getch();
		} 
    } 
} 

// ��ѯ������Ϣ 
void Query() 
{ 
    int i=0,j=0; 
    char ch[20]="",choose,id[10]; 
    struct card temp[N]={0}; 

    FILE *fp=NULL; 
    fp=fopen("�û�����.txt","r");   // ��ȡ�û�����.txt���� 
    while(feof(fp)==0) 
    {
	    fscanf(fp,"%s%s%f%d%f\n",temp[i].num,temp[i].name,&temp[i].yu,&temp[i].guashi,&temp[i].sum); 
        i++; 
    } 
    if(fp==NULL) 
    {
	    printf("\n���ļ�ʧ��!\n");
		return;
	} 
    system("cls");
	printf("\n"); 
    printf("5--��ѯ������Ϣ");
	printf("\n"); 
    printf(" |------------------------------------------|\n"); 
    printf(" |          ������ѡ����(0��3)            |\n"); 
    printf(" |------------------------------------------|\n"); 
    printf(" |             1--������Ų�ѯ              |\n"); 
    printf(" |                                          |\n"); 
    printf(" |             2--����ʹ���˲�ѯ            |\n"); 
    printf(" |                                          |\n"); 
	printf(" |             3--��ѯ��������              |\n"); 
    printf(" |                                          |\n"); 
    printf(" |             0--����                      |\n"); 
    printf(" |------------------------------------------|\n"); 
    printf("\n��ʾΪ1��ʾ��ʧ����ʾΪ0��ʾδ��ʧ\n");
    printf("\n �����������ţ�\n"); 
    choose=getch();
	if (choose=='1')  // ѡ��ʹ�÷�����Ų�ѯ 
	{
		printf("\n ������Ҫ��ѯ�ķ������:");
		scanf("%s",&id);
		printf("%13s%15s%17s%10s%18s\n","�������","����ʹ����","�������","�Ƿ��ʧ","ʹ�÷�Χ");
		for(i=0;i<=20;i++) if (pd(temp[i].num,id)==1 && temp[i].num[1] !=0) {printf("%13s%15s%15.2f%10d%20s\n",temp[i].num,temp[i].name,temp[i].yu,temp[i].guashi,fan(temp[i].sum));j++;}
		if (j==0) printf("���޴����ݣ�\n\n");
	 } 
	if (choose=='2')  // ѡ��ʹ�÷���ʹ���˲�ѯ 
	{
		printf("\n ������Ҫ��ѯ�ķ���ʹ����:");
		scanf("%s",&id);
		printf("%13s%15s%17s%10s%18s\n","�������","����ʹ����","�������","�Ƿ��ʧ","ʹ�÷�Χ");
		for(i=0;i<=20;i++) if (pd(temp[i].name,id)==1 && temp[i].num[1] !=0)  {printf("%13s%15s%15.2f%10d%20s\n",temp[i].num,temp[i].name,temp[i].yu,temp[i].guashi,fan(temp[i].sum));j++;}
		if (j==0) printf("���޴����ݣ�\n\n");
	 } 
	 if (choose=='3')  // ��ѯ���з�����Ϣ 
	{
		printf("%13s%15s%17s%10s%18s\n","�������","����ʹ����","�������","�Ƿ��ʧ","ʹ�÷�Χ");
		for(i=0;i<=20;i++) if (temp[i].num[1] !=0) printf("%13s%15s%15.2f%10d%20s\n",temp[i].num,temp[i].name,temp[i].yu,temp[i].guashi,fan(temp[i].sum));
	 } 
    fclose(fp); 
    printf("\n��������������˵�.....");
	getch();
	return;
}

// �޸ķ�����Ϣ 
void Modify()
{
	FILE *fp=NULL; 
    struct card temp[N]={0}; 
    int i=0,j,k,choose; 
    char num_temp[10]={0},yes_no; 
    float shuru; 
    fp=fopen("�û�����.txt","r"); 
    while(feof(fp)==0) 
    { 
	    fscanf(fp,"%s%s%f%d%f\n",temp[i].num,temp[i].name,&temp[i].yu,&temp[i].guashi,&temp[i].sum); 
        i++; 
    } 
    fclose(fp); 
    printf("\n\n �����뿨��:");
	scanf("%s",&num_temp); 
    if(exist(num_temp)==1&&guashi(num_temp)==0)   // �жϿ�Ƭ�Ƿ���� 
    {
    	do{
	    for(j=0;j<i;j++) 
        {
		    if(strcmp(num_temp,temp[j].num)==0)  // �ж����뿨�������п����Ƿ���ͬ
            {
		
			    system("cls");
	            printf("\n"); 
                printf("6--�޸ķ�����Ϣ"); 
                printf("\n");
   				printf(" |---------------------------------------------|\n"); 
  				printf(" |         ������ѡ����(0��4)                |\n"); 
  				printf(" |---------------------------------------------|\n"); 
  				printf(" |            1--�޸ķ������                  |\n"); 
  				printf(" |                                             |\n"); 
  				printf(" |            2--�޸ķ���ʹ����                |\n"); 
  				printf(" |                                             |\n"); 
				printf(" |            3--�޸ķ�������ֹ��ˢʱʹ�ã�|\n"); 
				printf(" |                                             |\n"); 
				printf(" |            4--�޸�ʹ�÷�Χ                  |\n");
  				printf(" |                                             |\n");  
  				printf(" |            0--����                          |\n"); 
  				printf(" |---------------------------------------------|\n"); 
				printf("\n �������޸���Ŀ:");scanf("%d",&choose); 
				printf("\n           ����          ����           ���        ʹ�÷�Χ\n"); 
                printf("����ǰ:%-10s      %-10s      %-10.2f   %-10f\n\n",temp[j].num,temp[j].name,temp[j].yu,temp[k].sum); 
				if (choose==1)  // �޸ķ������ 
				{
					printf("\n�������µĿ��ţ�");
					scanf("%s",&temp[j].num);
					while(exist(temp[j].num)==1)  //  �ж����뿨�������п����Ƿ���ͬ
					{
						printf (" �����ظ�!���������룺") ;
						scanf("%s",&temp[j].num);
					}
				 } 
                else if(choose==2)  // �޸ķ���ʹ���� 
                {
                	printf("\n�������µ�ʹ����������");
					scanf("%s",&temp[j].name);
				}
				else if (choose==3)  // �޸ĳ�ֵ����ֹ��ˢ 
				{
					printf("\n�������µ���");
					scanf("%f",&temp[j].yu); 
				}
				else if (choose==4) // �޸ķ������÷�Χ 
				{
					printf("\n�������µ�ʹ�÷�Χ��");
					scanf("%f",&temp[j].sum); 
				}
                printf("���ĺ�:%-10s      %-10s      %-10.2f   %-10.2f\n",temp[j].num,temp[j].name,temp[j].yu,temp[k].sum); 
            } 
        } 
        fp=fopen("�û�����.txt","w");  // д���û����� 
        for(k=0;k<i;k++)  
        fprintf(fp,"%10s%10s%20.2f%4d%20.2f\n",temp[k].num,temp[k].name,temp[k].yu,temp[k].guashi,temp[k].sum); 
        fclose(fp); 
        printf("\n\n �޸ĳɹ����Ƿ��������Y/N��"); 
        yes_no=getch();
		}while (yes_no=='Y'||yes_no=='y');
    } 
    else 
    printf("\n\n ���Ų����ڻ��ѹ�ʧ����������������˵�..."); 
    getch(); 
} 
 
// ɾ��������Ϣ��ע�������� 
 void Delete()
 {
 	int i=0,choose; 
    char ch[20]="";  // �趨20���û����� 
    struct card temp[N]={0}; 
    system("cls");
	printf("\n"); 
    printf("7--ɾ��������Ϣ"); 
    printf("\n");
    FILE *fp=NULL; 
    FILE *fp1=NULL;
    fp=fopen("�û�����.txt","r");   // ��ȡ�û�����.txt������ 
    while(feof(fp)==0) 
    {
	    fscanf(fp,"%s%s%f%d%f\n",temp[i].num,temp[i].name,&temp[i].yu,&temp[i].guashi,&temp[i].sum); 
        i++; 
    } 
    if(fp==NULL) 
    {
	    printf("\n���ļ�ʧ��!\n");
		return;
	}  
    printf("%10s%13s%15s%17s%10s%18s\n","������","�������","����ʹ����","�������","�Ƿ��ʧ","ʹ�÷�Χ");
    for(i=0;i<=20;i++) 
     if (temp[i].num[1] !=0) 
	 printf("%10d%13s%15s%15.2f%10d%20s\n",i+1,temp[i].num,temp[i].name,temp[i].yu,temp[i].guashi,fan(temp[i].sum));  // �Է������з�����Ϣ���б�� ��������Ļ��ʾ 
    fclose(fp); 
    printf("��ѡ����Ҫɾ���ı�ţ�0ȡ����:");
    scanf("%d",&choose);  // ѡ��Ҫ����ɾ���ķ�����Ϣ������ 
	fp=fopen("�û�����.txt","w");   // д����ĺ������ 
	if(fp==NULL) 
    {
	    printf("\n���ļ�ʧ��!\n");
		return;
	} 
	if (choose<=20)
    {
    	for (i=0;i<=20;i++)
    	{
			if (i!=choose-1 && temp[i].num[1] !=0)   // ����ѡ��ķ�����Ϣ����ɾ�� 
			fprintf(fp,"%10s%10s%20.2f%4d%20.2f\n",temp[i].num,temp[i].name,temp[i].yu,temp[i].guashi,temp[i].sum);
		}
	}
	fclose(fp);

    printf("\n�����ɹ�����������������˵�.....");
	getch();
	return;
 }
 
// �ж����������ֵ�Ƿ���� 
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
 
//  ������ֵ����¥��
 char *fan (float fsum)
 {
 	static char re[20];
 	if (fsum == 1.0) strcpy(re,"һ¥"); 
	 else  if (fsum == 2.0) strcpy(re,"��¥");
	 else  if (fsum == 3.0) strcpy(re,"һ/��¥"); 
	 else if (fsum == 4.0) strcpy(re,"��¥"); 
	 else  if (fsum == 5.0) strcpy(re,"һ/��¥");
	 else  if (fsum == 6.0) strcpy(re,"��/��¥"); 
	 else  if (fsum == 7.0) strcpy(re,"һ/��/��¥");
	 return re; 
  } 
