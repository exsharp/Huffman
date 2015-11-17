#include "Coding.h"

#include "Buffer.h"

Coding::Coding(){
	raw = 0;
	length = 0;
	memset(code, 0, sizeof(code));
}

Coding::Coding(uchar raw){
	this->raw = raw;
	length = 0;
	memset(code, 0, sizeof(code));
}

void Coding::AddBit(Binary bin){
	int index = length / 8;
	int pos = length % 8;
	pos = 7 - pos;
	//要添加的数
	int	add = bin << pos;
	//和原来的相与
	//int num = code[index] | add;
	code[index] |= add;
	length++;
}

void Coding::SetChar(unsigned char ch){
	this->raw = ch;
}

typedef void(*WriteBin)(Coding::Binary);
//一个流，传入一个函数处理这个流
void Coding::GetStream(Buffer &buffer, void(*WriteBin)(Buffer&, Binary)){
	for (int i = 1; i <= length; i++){
		int index = i / 8;
		int pos = 7 - ((i - 1) % 8);

		//要相与的数
		uchar and = 1 << pos;

		uchar bin = (code[index] & and) >> pos;

		switch (bin)
		{
		case 1:
			//TODO
			WriteBin(buffer, Binary::One);
			break;
		case 0:
			WriteBin(buffer, Binary::Zero);
			//TUDO
			break;
		}
	}
}