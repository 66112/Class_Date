#include "Date.h"
Date::Date(int year , int month , int day )  //构造函数，声明中缺省为默认值，实现时就不用写了
{
	if (year >= 0              //公元0年以后
		&& month >= 1 && month <= 12      //1到12月
		&& day > 0 && day <= Getmonthday(year, month))      //天数
	{
		_year = year;
		_month = month;
		_day = day;
	}
	else
	{
		cout << "输入日期不合法!" << endl;
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
int Date::Getmonthday(int year, int month)  //判断天数
{
	static const int day[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if ((month == 2) && ((year % 4 == 0) && ((year % 100) != 0) || ((year%400)==0)))
		//四年一闰，百年不闰，四百年再闰
	{
		return 29;
	}
	return day[month];
}
bool Date::operator > (const Date& d)      //运算符重载之 >
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

bool Date::operator < (const Date& d)      //复用
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

Date Date::operator+(const int day)    //2018年10月20号  +  90天
{
	Date ret(*this);
	ret += day;
	return ret;
	//Date ret(*this);         //拷贝构造一个对象
	//if (day<0)
	//{
	//	return (ret) -= (-day);
	//}
	//int monthday = Getmonthday(ret._year, ret._month);  //本月有几天   
	//ret._day += day;        //一共成了多少天       2018.10.110
	//while (ret._day > monthday)
	//{
	//	ret._day -= monthday;       //天数把本月的一减    2018.10.79
	//	ret._month++;            //月加1             2018.11.79
	//	if (ret._month > 12)
	//	{
	//		ret._month -= 12;
	//		ret._year++;
	//	}
	//	monthday = Getmonthday(ret._year, ret._month);   //更新monthday
	//}
	//return ret;   //又要拷贝构造一个对象
}

Date Date::operator-(const int day)    
{
	Date ret(*this);
	ret -= day;
	return ret;
	//Date ret(*this);                  //有瑕疵，应该先实现-=
	//if (day < 0)
	//{
	//	return ret += (-day);
	//}
	//int monthday = Getmonthday(ret._year, ret._month);  //本月有几天   
	//ret._day -= day;        
	//while (ret._day <= 0)
	//{
	//	ret._month--;            
	//	if (ret._month <= 0)
	//	{
	//		ret._month = 12;
	//		ret._year--;
	//	}
	//	monthday = Getmonthday(ret._year, ret._month);   //更新monthday
	//	ret._day += monthday;       //更新ret._day
	//}
	//return ret;
}

Date& Date::operator+=(const int day)
{
	if (day < 0)
	{
		return *this -= (-day);
	}
	int monthday = Getmonthday((*this)._year, (*this)._month);  //本月有几天   
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
		monthday = Getmonthday((*this)._year, (*this)._month);   //更新monthday
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
		int monthday = Getmonthday((*this)._year, (*this)._month);   //更新monthday
		(*this)._day += monthday;       //更新ret._day
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

Date Date::operator--()          //--d  对象改变
{
	*this -= 1;
	return *this;
}
Date Date::operator--(int)       //d--   对象不改变
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
	//走到这，big里边是大日期，small里边是小日期
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
	////走到这，small._day==big._day;就差整月或整年
	//while ((big._year != small._year) || (big._month != small._month)) 
	//	//当它们不相等时，就进来
	//{
	//	int smd = Getmonthday(small._year, small._month);
	//	count += smd;                     //一个月一个月往上加
	//	small._month++;
	//	if (small._month > 12)
	//	{
	//		small._month = 1;
	//		small._year++;
	//	}
	//}
	//return count;
}

