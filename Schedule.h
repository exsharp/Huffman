#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_

#include <iostream>
using namespace std;

class Schedule
{
private:
	unsigned int length;
	double old_percent;
	string tail;
public:
	Schedule(unsigned int totalLen);
	void SetProc(unsigned int);
	void SetTail(string);
	void ShowText(string);
	void ShowEndl();
};

#endif 

