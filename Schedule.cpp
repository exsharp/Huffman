#include "Schedule.h"
#include <iomanip>
#include <assert.h>

Schedule::Schedule(unsigned int totalLen)
{
	this->length = totalLen;
	this->old_percent = 0.0;
}

Schedule::Schedule(int mode){
	if (mode == 1){
		file.open("C:\\Users\\zfliu\\Desktop\\fuck\\resutl.1.txt");
	}
	else{
		file.open("C:\\Users\\zfliu\\Desktop\\fuck\\resutl.2.txt");
	}
}

void Schedule::SetProc(unsigned int percent){

	if (percent <= 100){
		cout << "[";
		for (int i = 0; i < percent / 2; i++){
			cout << "*";
		}
		for (int i = 0; i < 50 - percent / 2; i++){
			cout << " ";
		}
		cout << "]" << setiosflags(ios::fixed) << setprecision(4) << percent << "% ";
		if (!tail.empty()){
			cout << tail.c_str();
		}
		cout << "\r";
		if (100 == percent){
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
void Schedule::WriteText(Coding _code){
	uchar ch = _code.GetChar();
	uchar len = _code.GetLength();
	queue<Coding::Binary> qu = _code.GetStream();

	if (char(ch) >= 32 && char(ch) <= 126){
		file << setw(1) << ch;
	}
	else{
		file << " ";
	}
	file <<"  "<<setw(3) << (int)ch << "  " <<setw(2)<< (int)len<<"  ";
	while (!qu.empty()){
		Coding::Binary bin = qu.front();
		qu.pop();
		switch (bin)
		{
		case Coding::Binary::One:
			file << "1";
			break;
		case Coding::Binary::Zero:
			file << "0";
			break;
		default:
			assert(0);
			break;
		}
	}
	file << endl;
}