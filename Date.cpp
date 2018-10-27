#include "Date.h"
Date::Date(int year , int month , int day )  //���캯����������ȱʡΪĬ��ֵ��ʵ��ʱ�Ͳ���д��
{
	if (year >= 0              //��Ԫ0���Ժ�
		&& month >= 1 && month <= 12      //1��12��
		&& day > 0 && day <= Getmonthday(year, month))      //����
	{
		_year = year;
		_month = month;
		_day = day;
	}
	else
	{
		cout << "�������ڲ��Ϸ�!" << endl;
		exit(1);
	}
}

Date& Date::operator=(const Date& d)
{
	if (this != &d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	return *this;
}
int Date::Getmonthday(int year, int month)  //�ж�����
{
	static const int day[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if ((month == 2) && ((year % 4 == 0) && ((year % 100) != 0) || ((year%400)==0)))
		//����һ�򣬰��겻���İ�������
	{
		return 29;
	}
	return day[month];
}
bool Date::operator > (const Date& d)      //���������֮ >
{
	if (_year > d._year)
	{
		return true;
	}
	else if (_year == d._year)
	{
		if (_month > d._month)
		{
			return true;
		}
		else if (_month == d._month)
		{
			if (_day > d._day)
			{
				return true;
			}
		}
	}
	return false;
}
bool Date::operator == (const Date& d)
{
	return (_year == d._year)&&(_month == d._month)&&(_day == d._day);
}

bool Date::operator < (const Date& d)      //����
{
	return !((*this>d) || (*this == d));
}

bool Date::operator >= (const Date& d)
{
	return !((*this)<d);
}

bool Date::operator <= (const Date& d)
{
	return !((*this)>d);
}

bool Date::operator != (const Date& d)
{
	return !((*this) == d);
}

Date Date::operator+(const int day)    //2018��10��20��  +  90��
{
	Date ret(*this);
	ret += day;
	return ret;
	//Date ret(*this);         //��������һ������
	//if (day<0)
	//{
	//	return (ret) -= (-day);
	//}
	//int monthday = Getmonthday(ret._year, ret._month);  //�����м���   
	//ret._day += day;        //һ�����˶�����       2018.10.110
	//while (ret._day > monthday)
	//{
	//	ret._day -= monthday;       //�����ѱ��µ�һ��    2018.10.79
	//	ret._month++;            //�¼�1             2018.11.79
	//	if (ret._month > 12)
	//	{
	//		ret._month -= 12;
	//		ret._year++;
	//	}
	//	monthday = Getmonthday(ret._year, ret._month);   //����monthday
	//}
	//return ret;   //��Ҫ��������һ������
}

Date Date::operator-(const int day)    
{
	Date ret(*this);
	ret -= day;
	return ret;
	//Date ret(*this);                  //��覴ã�Ӧ����ʵ��-=
	//if (day < 0)
	//{
	//	return ret += (-day);
	//}
	//int monthday = Getmonthday(ret._year, ret._month);  //�����м���   
	//ret._day -= day;        
	//while (ret._day <= 0)
	//{
	//	ret._month--;            
	//	if (ret._month <= 0)
	//	{
	//		ret._month = 12;
	//		ret._year--;
	//	}
	//	monthday = Getmonthday(ret._year, ret._month);   //����monthday
	//	ret._day += monthday;       //����ret._day
	//}
	//return ret;
}

Date& Date::operator+=(const int day)
{
	if (day < 0)
	{
		return *this -= (-day);
	}
	int monthday = Getmonthday((*this)._year, (*this)._month);  //�����м���   
	(*this)._day += day;
	while ((*this)._day > monthday)
	{
		(*this)._day -= monthday;
		(*this)._month++;
		if ((*this)._month > 12)
		{
			(*this)._month = 1;
			(*this)._year++;
		}
		monthday = Getmonthday((*this)._year, (*this)._month);   //����monthday
	}
	return *this;
}

Date& Date::operator-=(const int day)
{
	if (day < 0)
	{
		return *this += (-day);
	}
	(*this)._day -= day;
	while ((*this)._day <= 0)
	{
		(*this)._month--;
		if ((*this)._month <= 0)
		{
			(*this)._month = 12;
			(*this)._year--;
		}
		int monthday = Getmonthday((*this)._year, (*this)._month);   //����monthday
		(*this)._day += monthday;       //����ret._day
	}
	return *this;
}

Date Date::operator++()          //++d
{
	*this += 1;
	return *this;
}

Date Date::operator++(int)       //d++
{
	Date ret(*this);
	(*this) += 1;
	return ret;
}

Date Date::operator--()          //--d  ����ı�
{
	*this -= 1;
	return *this;
}
Date Date::operator--(int)       //d--   ���󲻸ı�
{
	Date ret(*this);
	(*this) -= 1;
	return ret;
}

int Date::operator-(const Date& d)
{
	int count = 0;
	if (*this == d)
	{
		return 0;
	}
	Date big(*this);
	Date small(d);
	if (big < small)
	{
		Date tmp = big;
		big = small;
		small = tmp;
	}                   
	//�ߵ��⣬big����Ǵ����ڣ�small�����С����
	while (small != big)
	{
		++small;
		++count;
	}
	return count;
////////////////////////////////////////////////////////////////	
	//if (big._day > small._day)
	//{
	//	count = big._day - small._day;
	//	small._day = big._day;
	//}
	//if (big._day < small._day)
	//{
	//	int smd = Getmonthday(small._year, small._month);
	//	int tmp = smd - small._day;
	//	count = tmp + big._day;
	//	small._month++;
	//	if (small._month>12)
	//	{
	//		small._month = 1;
	//		small._year++;
	//	}
	//	small._day = big._day;
	//}
	////�ߵ��⣬small._day==big._day;�Ͳ����»�����
	//while ((big._year != small._year) || (big._month != small._month)) 
	//	//�����ǲ����ʱ���ͽ���
	//{
	//	int smd = Getmonthday(small._year, small._month);
	//	count += smd;                     //һ����һ�������ϼ�
	//	small._month++;
	//	if (small._month > 12)
	//	{
	//		small._month = 1;
	//		small._year++;
	//	}
	//}
	//return count;
}

