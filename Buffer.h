#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <iostream>
#include <fstream>
using namespace std;

#include "Coding.h"

typedef unsigned char uchar;
typedef unsigned int uint;

//һ�����壬���ַ��ı���ŵ���������
class Buffer{
private:
	uchar *buffer;
	uint maxBufferLen;//���ı�����
	uint currentLen;
public:
	Buffer(uchar *buffer, int num);
	void clear();
	uint flush(); //�������ã���ʣ������뵽�ļ�
	bool append(Coding::Binary bin);//д��ı��룬�͸ñ����k����
};

#endif
