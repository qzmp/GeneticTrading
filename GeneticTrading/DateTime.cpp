#include "DateTime.h"



void DateTime::convertDate(string date)
{
	stringstream ss(date);
	string token;

	getline(ss, token, '.');
	this->day = stoi(token);

	getline(ss, token, '.');
	this->month = stoi(token);

	getline(ss, token, '.');
	this->year = stoi(token);
}

void DateTime::convertTime(string time)
{
	stringstream ss(time);
	string token;

	getline(ss, token, ':');
	this->hour = stoi(token);

	getline(ss, token, ':');
	this->minute = stoi(token);

	getline(ss, token, ':');
	this->second = stoi(token);
}

void DateTime::convertDateTime(string dateTime)
{
	stringstream ss(dateTime);
	ss.str(dateTime);
	string token;

	getline(ss, token, ' ');
	convertDate(token);
	getline(ss, token);
	convertTime(token);
}

unsigned long DateTime::getDateInt() const
{
	return day + month * 100 + year * 10000;
}

unsigned long DateTime::getTimeInt() const
{
	return second + minute * 100 + hour * 10000;
}

DateTime::DateTime(string DateTime)
{
	convertDateTime(DateTime);
}

DateTime::~DateTime()
{
}

bool DateTime::operator<(const DateTime & other) const
{
	if (this->getDateInt() < other.getDateInt())
	{
		return true;
	}
	else if (this->getDateInt() == other.getDateInt())
	{
		return this->getTimeInt() < other.getTimeInt();
	}
	else return false;
}

bool DateTime::operator==(const DateTime & other) const
{
	return this->getDateInt() == other.getDateInt() && this->getTimeInt() == other.getTimeInt();
}
