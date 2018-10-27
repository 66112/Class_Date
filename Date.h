#ifndef __DATH_H__
#define __DATH_H__

#include <iostream>
using namespace std;

class Date
{
public:
	int Getmonthday(int year, int month);  //判断天数
	Date(int year = 0 , int month = 1, int day = 1);  //构造函数
	Date(const Date& d)          //拷贝构造函数
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	void Print()
	{
		cout <<"公元"<< _year << "年-" << _month << "月-" << _day << "日" << endl;
	}
	Date& operator = (const Date& d);     //赋值运算符重载
	
	bool operator == (const Date& d);
	bool operator > (const Date& d);

	bool operator < (const Date& d);
	bool operator >= (const Date& d);
	bool operator <= (const Date& d);
	bool operator != (const Date& d);

	Date operator+(const int day);
	Date operator-(const int day);    
	Date& operator+=(const int day);
	Date& operator-=(const int day);
	Date operator++();          //++d
	Date operator++(int);       //d++
	Date operator--();          //--d
	Date operator--(int);       //d--
	int operator-(const Date& d);  //计算两个日期之间隔了多少天

	~Date(){}             //析构函数
private:
	int _year;
	int _month;
	int _day;
};

#endif //__DATH_H__