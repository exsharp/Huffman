#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <iostream>
#include <fstream>
using namespace std;

#include "Coding.h"

typedef unsigned char uchar;

//һ�����壬���ַ��ı���ŵ���������
class Buffer{
private:
	uchar *buffer;
	ofstream *out;
	int maxBufferLen;//���ı�����
	int currentLen;
	void write();
public:
	Buffer(uchar *buffer, int num, ofstream &out);
	void flush(); //�������ã���ʣ������뵽�ļ�
	void append(Coding::Binary bin);//д��ı��룬�͸ñ����k����
};

void callback(Buffer &buf, Coding::Binary bin);

#endif
