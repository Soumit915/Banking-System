#include<stdio.h>
#include<time.h>
int day,year,mnth;
int month(char *);
int extcurdate()
{
    time_t t;
    time(&t);
	struct emp
	{
		char a[10];
		char b[10];
		char c[10];
		char d[10];
		char e[10];
	}str;
	sscanf(ctime(&t),"%s%s%s%s%s",&str.a,&str.b,&str.c,&str.d,&str.e);
	sscanf(str.c,"%d",&day);
	sscanf(str.e,"%d",&year);
	mnth=month(str.b);
}
int month(char *a)
{
	if(*a=='J')
	{
		a++;
		if(*a=='a')
		return 1;
		a++;
		if(*a=='n')
		return 6;
		else
		return 7;
	}
	else
	if(*a=='F')
	return 2;
	else
	if(*a=='M')
	{
		if(*(a+2)=='r')
		return 3;
		else
		return 5;
	}
	else
	if(*a=='A')
	{
		a++;
		if(*a=='p')
		return 4;
		else
		return 8;
	}
	else
	if(*a=='S')
	return 9;
	else
	if(*a=='O')
	return 10;
	else
	if(*a=='N')
	return 11;
	else
	return 12;
}
