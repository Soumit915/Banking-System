#include"FindDate.cpp"
int yeardiff(int day1,int mnth1,int year1)
{
	extcurdate();
	int yrd=year-year1;
	if(mnth1>mnth)
	{
		yrd-=1;
	}
	else
	if(mnth1==mnth)
	{
		if(day1>day)
		{
			yrd-=1;
		}
	}
	return yrd;
}
int monthdiff(int day1,int mnth1,int year1)
{
	int mnd;
	int yrd=yeardiff(day1,mnth1,year1);
	extcurdate();
	if(mnth1>mnth)
	{
		mnd=(mnth)+(12-mnth1);
		if(day<day1)
			mnd-=1;
	}
	else
	{
		mnd=(mnth-mnth1);
		if(day>day1)
			mnd-=1;
	}
	mnd+=(12*yrd);
	return mnd;
}
