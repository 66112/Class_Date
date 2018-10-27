#ifndef __DATH_H__
#define __DATH_H__

#include <iostream>
using namespace std;

class Date
{
public:
	int Getmonthday(int year, int month);  //�ж�����
	Date(int year = 0 , int month = 1, int day = 1);  //���캯��
	Date(const Date& d)          //�������캯��
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	void Print()
	{
		cout <<"��Ԫ"<< _year << "��-" << _month << "��-" << _day << "��" << endl;
	}
	Date& operator = (const Date& d);     //��ֵ���������
	
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
	int operator-(const Date& d);  //������������֮����˶�����

	~Date(){}             //��������
private:
	int _year;
	int _month;
	int _day;
};

#endif //__DATH_H__