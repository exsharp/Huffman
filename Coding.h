#ifndef _CODING_H_
#define _CODING_H_

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef unsigned char uchar;
//ÿһ���ַ�����

class Coding{
public:
	enum Binary{
		Zero = 0,
		One = 1
	};
private:
	unsigned char raw;	//ԭʼ�ַ�
	unsigned char code[32]; //�洢ĳ�����Ķ����Ʊ���,�255λ����Ȼ�����ϲ�����
	uchar length; //�洢�˶��ٸ�
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
};
#endif

