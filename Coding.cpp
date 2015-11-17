#include "Coding.h"

Coding::Coding(){
	raw = 0;
	length = 0;
	memset(code, 0, sizeof(code));
}

Coding::Coding(const Coding& _code){
	this->raw = _code.raw;
	this->length = _code.length;
	memset(code, 0, sizeof(code));
	for (int i = 0; i < 32; i++){
		this->code[i] = _code.code[i];
	}
}

Coding::Coding(uchar raw){
	this->raw = raw;
	length = 0;
	memset(code, 0, sizeof(code));
}

Coding::Coding(uchar raw, uchar length, vector<uchar> code){
	this->raw = raw;
	this->length = length;
	for (int i = 0; i < 32; i++){
		this->code[i] = code.at(i);
	}
}

void Coding::AddBit(Binary bin){
	int index = length / 8;
	int pos = length % 8;
	pos = 7 - pos;
	//Ҫ��ӵ���
	int	add = bin << pos;
	//��ԭ��������
	//int num = code[index] | add;
	code[index] |= add;
	length++;
}

void Coding::SetChar(unsigned char ch){
	this->raw = ch;
}

typedef void(*WriteBin)(Coding::Binary);
//һ����������һ���������������
queue<Coding::Binary> Coding::GetStream(){
	queue<Binary> qu;
	for (int i = 1; i <= length; i++){
		int index = i / 8;
		int pos = 7 - ((i - 1) % 8);

		//Ҫ�������
		uchar and = 1 << pos;

		uchar bin = (code[index] & and) >> pos;

		bool full = false;
		switch (bin)
		{
		case 1:
			qu.push(Binary::One);
			break;
		case 0:
			qu.push(Binary::Zero);
			break;
		}
	}
	return qu;
}