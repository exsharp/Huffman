#ifndef _CODING_H_
#define _CODING_H_

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef unsigned char uchar;
//每一个字符编码

class Coding{
public:
	enum Binary{
		Zero = 0,
		One = 1
	};
private:
	unsigned char raw;	//原始字符
	unsigned char code[32]; //存储某个数的二进制编码,最长255位，虽然理论上不可能
	uchar length; //存储了多少个
public:
	Coding();
	Coding(const Coding&);
	Coding(uchar raw);
	Coding(uchar raw, uchar length, vector<uchar> code);
	void AddBit(Binary bin);
	void SetChar(unsigned char ch);
	unsigned char GetChar(){
		return raw;
	}
	void GetCode(unsigned char *dst){
		for (int i = 0; i < (length / 8 + 1); i++){
			dst[i] = code[i];
		}
	}
	int GetLength(){
		return length;
	}
	queue<Binary> GetStream();
	bool operator < (const Coding &co){
		return this->raw < co.raw;
	}
};
#endif

