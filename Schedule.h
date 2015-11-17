#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_

#include <iostream>
#include <fstream>
using namespace std;

#include "Coding.h"

class Schedule
{
private:
	unsigned int length;
	double old_percent;
	string tail;
	ofstream file;
public:
	Schedule(unsigned int totalLen);
	Schedule(int mode);
	void SetProc(unsigned int);
	void SetTail(string);
	void ShowText(string);
	void ShowEndl();

	void WriteText(Coding _code);
};

#endif 

