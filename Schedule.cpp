#include "Schedule.h"
#include <iomanip>

Schedule::Schedule(unsigned int totalLen)
{
	this->length = totalLen;
	this->old_percent = 0.0;
}

void Schedule::SetProc(unsigned int current){
	double percent = current*1.0 / length*50;
	if ((percent - old_percent > 0.002)||(old_percent == 0.0)){
		int statCount = (int)percent;

		cout << "[";
		for (int i = 0; i < statCount; i++){
			cout << "*";
		}
		for (int i = 0; i < 50 - statCount; i++){
			cout << " ";
		}
		cout << "]" << setiosflags(ios::fixed) << setprecision(4) << percent * 2 << "% ";
		if (!tail.empty()){
			cout << tail.c_str();
		}
		cout << "\r";
		if (50 <= percent){
			cout << endl;
		}
		cout.flush();
	}
}

void Schedule::SetTail(string tail){
	this->tail = tail;
}

void Schedule::ShowText(string text){
	cout << text.c_str() << endl;
}

void Schedule::ShowEndl(){
	cout << endl;
}
