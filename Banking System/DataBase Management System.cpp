#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include"FindDiffDate.cpp"
int na;
struct lasttransac
{
	char date[12];
	float amnt;
	int status;
};
struct acc
{
	int accno;
	char name[50];
	char dob[13];
	int age;
	char gender[8];
	long long int phno;
	char city[50];
	float bkbal;
	struct lasttransac lt;
}a;
void gotoxy(int,int);
int genacno();
void Addnew();
void ModifyAccount();
void ViewAccount();
void deposit();
void withdraw();
void transaction();
int main()
{
	FILE *fp,*ft,*sf;
	sf=fopen("ESP.DAT","rb");
	if(sf==NULL)
	{
		na=0;
	}
	else
	{
		fread(&na,sizeof(int),1,sf);
	}
	fp=fopen("EMP.DAT","rb+");
	if(fp==NULL)
	{
		fp=fopen("EMP.DAT","wb+");
	}
	int i,res,fac;
	char ch,ch1;
	res=sizeof(a);
	do
	{
		system("cls");
		gotoxy(4,3);
		printf("Enter,");
		gotoxy(6,4);
		printf("1 to add new account,");
		gotoxy(6,5);
		printf("2 to list all accounts,");
		gotoxy(6,6);
		printf("3 to view an account,");
		gotoxy(6,7);
		printf("4 to modify account,");
		gotoxy(6,8);
		printf("5 to delete account,");
		gotoxy(6,9);
		printf("6 to do transactions,");
		gotoxy(6,10);
		printf("7 to exit : ");
		scanf("%d",&i);
		
		switch(i)
		{
			case 1:do
				   {
				   		fseek(fp,0,SEEK_END);
				   		system("cls");
				   		Addnew();
				   		fwrite(&a,res,1,fp);
				   		fclose(fp);
				   		fp=fopen("EMP.DAT","rb+");
				   		na++;
				   		fflush(stdin);
				   		printf("Do you want to add more account (Y/N): ");
				   		ch=getchar();
				   }while(ch=='Y');
				   break;
				   
			case 2:rewind(fp);
				   system("cls");
				   while(fread(&a,res,1,fp)==1)
				   {
				   		int day1,mnth1,year1;
						sscanf(a.dob,"%d%d%d",&day1,&mnth1,&year1);
				   		printf("Account number : %d\t\tName of Account holder : %s\nDate of Birth : %d:%d:%d\tCity : %s\n",a.accno,a.name,day1,mnth1,year1,a.city);
				   }
				   break;
				   
			case 3:rewind(fp);
				   printf("Enter the account number you want to view : ");
				   scanf("%d",&fac);
				   while(fread(&a,res,1,fp)==1)
				   {
				   		if(a.accno==fac)
				   		{
				   			ViewAccount();
				   			break;
						}
				   }
				   break;
				   
			case 4:rewind(fp);
				   printf("Enter the account number you want to modify : ");
				   scanf("%d",&fac);
				   while(fread(&a,res,1,fp)==1)
				   {
				   		if(a.accno==fac)
				   		{
				   			ModifyAccount();
				   			fseek(fp,-res,SEEK_CUR);
				   			fwrite(&a,res,1,fp);
				   			break;
						}
				   }
				   break;
				   
			case 5:ft=fopen("TEMP.DAT","wb");
				   rewind(fp);
				   printf("Enter the account number you want to delete : ");
				   scanf("%d",&fac);
				   while(fread(&a,res,1,fp)==1)
				   {
				   		if(a.accno!=fac)
				   		{
				   			fwrite(&a,res,1,ft);
						}
				   }
				   fclose(fp);
				   fclose(ft);
				   remove("EMP.DATA");
				   rename("TEMP.DATA","EMP.DATA");
				   na--;
				   fp=fopen("EMP.DATA","rb+");
				   break;
				   
			case 6:rewind(fp);
				   printf("Enter the account number you want to transfer money or withdraw : ");
				   scanf("%d",&fac);
				   while(fread(&a,res,1,fp)==1)
				   {
				   		if(a.accno==fac)
				   		{
				   			transaction();
				   			fseek(fp,-res,SEEK_CUR);
				   			fwrite(&a,res,1,fp);
				   			break;
				   		}
				   }
				   break;
				   
			case 7:fclose(fp);
				   sf=fopen("ESP.DAT","wb");
				   fwrite(&na,sizeof(int),1,sf);
				   fclose(sf);
				   exit(0);
			
			default:printf("Wrong Input");	   
		}
		printf("Enter to continue(Y/N) : ");
		fflush(stdin);
		ch1=getchar();
	}while(ch1=='Y');
	
	fclose(fp);
	sf=fopen("ESP.DAT","wb");
   	fwrite(&na,sizeof(int),1,sf);
	fclose(sf);
}
void ModifyAccount()
{
	fflush(stdin);
	printf("Enter your new name : ");
	gets(a.name);
	fflush(stdin);
	printf("Enter your new city : ");
	gets(a.city);
	fflush(stdin);
}
void ViewAccount()
{
	system("cls");
	gotoxy(6,4);
	printf("Account number is : %d",a.accno);
	gotoxy(6,5);
	printf("Name of Account holder : %s",a.name);
	int day1,mnth1,year1;
	sscanf(a.dob,"%d%d%d",&day1,&mnth1,&year1);
	gotoxy(6,6);
	printf("Date of birth : %d:%d:%d",day1,mnth1,year1);
	gotoxy(6,7);
	printf("Age : %d",a.age);
	gotoxy(6,8);
	printf("Gender : %s",a.gender);
	gotoxy(6,9);
	printf("Phone number : %lld",a.phno);
	gotoxy(6,10);
	printf("City : %s",a.city);
	gotoxy(6,11);
	printf("Account Balance : %f",a.bkbal);
	gotoxy(6,12);
	printf("-------------------------------------------------------------------------");
	gotoxy(6,13);
	printf("Last Transaction Details :---");
	gotoxy(6,14);
	printf("Date : %s",a.lt.date);
	gotoxy(6,15);
	printf("Amount transact : %f",a.lt.amnt);
	gotoxy(6,16);
	if(a.lt.status==1)
	printf("Status : Money Deposited");
	else
	printf("Status : Money Withdrawn");
	gotoxy(6,17);
}
void Addnew()
{
	gotoxy(6,4);
	a.accno=genacno();
	printf("Account no. is : %d",a.accno);
	gotoxy(6,5);
	fflush(stdin);
	printf("Enter name : ");
	gets(a.name);
	fflush(stdin);
	gotoxy(6,6);
	printf("Enter gender : ");
	scanf("%s",a.gender);
	fflush(stdin);
	gotoxy(6,7);
	printf("Enter date of birth in(DD MM YYYY) format only : ");
	gets(a.dob);
	fflush(stdin);
	gotoxy(6,8);
	printf("Enter your phone no. : ");
	scanf("%lld",&a.phno);
	fflush(stdin);
	gotoxy(6,9);
	printf("Enter city : ");
	gets(a.city);
	gotoxy(6,10);
	int day1,mnth1,year1;
	sscanf(a.dob,"%d%d%d",&day1,&mnth1,&year1);
	a.age=yeardiff(day1,mnth1,year1);
	printf("You have to deposit atleast Rs 1000 in your account.");
	gotoxy(6,11);
	printf("Enter any key to continue.");
	getch();
	gotoxy(6,12);
	a.bkbal=0.0;
	deposit();
}
void transaction()
{
	int i;
	printf("Enter,\n1 to deposit, and\n2 to withdraw money : ");
	scanf("%d",&i);
	switch(i)
	{
		case 1:deposit();
			   break;
			   
		case 2:withdraw();
			   break;
			   
		default:printf("Wrong respnse");
	}
}
void deposit()
{
	float dep;
	printf("Enter the amount you want to deposit : ");
	scanf("%f",&dep);
	a.bkbal+=dep;
	extcurdate();
	sprintf(a.lt.date,"%d:%d:%d\0",day,mnth,year);
	a.lt.amnt=dep;
	a.lt.status=1;
	ViewAccount();
}
void withdraw()
{
	float with;
	printf("Enter the amount you want to withdraw : ");
	scanf("%f",&with);
	if(a.bkbal>=with)
	{
		a.bkbal-=with;
		ViewAccount();
	}
	else
	{
		printf("Insufficient Balance");
	}
	extcurdate();
	sprintf(a.lt.date,"%d:%d:%d\0",day,mnth,year);
	a.lt.amnt=with;
	a.lt.status=2;
	ViewAccount();
}
int genacno()
{
	FILE *fp;
	int i,counta;
	struct acc e;
	int res=sizeof(e);
	for(i=100001;i<=999999;i++)
	{
		counta=0;
		fp=fopen("EMP.DAT","rb+");
		while(fread(&e,res,1,fp)==1)
		{
			if(e.accno!=i)
			{
				counta++;
			}
		}
		if(counta==na)
		{
			fclose(fp);
			return i;
		}
	}
	return 100001;
}
void gotoxy(int x,int y)
{
	HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position={x,y};
	SetConsoleCursorPosition(hStdout,position);
}
