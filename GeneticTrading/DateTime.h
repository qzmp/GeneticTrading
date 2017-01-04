#pragma once

#include <string>
#include <sstream>

using namespace std;

class DateTime
{
private:
	int day;
	int month;
	int year;
	
	int hour;
	int minute;
	int second;

	void convertDate(string date);
	void convertTime(string time);

	void convertDateTime(string dateTime);

	unsigned long getDateInt() const;
	unsigned long getTimeInt() const;
public:
	DateTime(string dateTime);
	~DateTime();

	int getDay() { return day; };
	int getMonth() { return month; };
	int getYear() { return year; };

	bool operator<(const DateTime & other) const;
	bool operator==(const DateTime & other) const;
};

