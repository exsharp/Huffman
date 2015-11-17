#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <iostream>
#include <fstream>
using namespace std;

#include "Coding.h"

typedef unsigned char uchar;

//一个缓冲，把字符的编码放到这里面来
class Buffer{
private:
	uchar *buffer;
	ofstream *out;
	int maxBufferLen;//最大的比特数
	int currentLen;
	void write();
public:
	Buffer(uchar *buffer, int num, ofstream &out);
	void flush(); //主动调用，把剩余的输入到文件
	void append(Coding::Binary bin);//写入的编码，和该编码的k长度
};

void callback(Buffer &buf, Coding::Binary bin);

#endif
