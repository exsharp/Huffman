#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <iostream>
#include <fstream>
#include <assert.h>
using namespace std;

#include "Tree.h"
#include "Coding.h"
#include "Buffer.h"

#define BUFFER_LEN 2048

typedef unsigned char uchar;

enum Error{
	
};

class Huffman{
	vector<Coding> code;

private:
	streampos fileLength;
	uint sourLength; //原文件的字节数
	string inFileName;
	string outFileName;
	string tail; //文件后缀

	bool type; //true Encode false Decode

	ofstream output;
	ifstream input;

	void itoc(uint in,uchar *c){
		c[0] = (char)(in & 0xff);
		c[1] = (char)((in >> 8) & 0xff);
		c[2] = (char)((in >> 16) & 0xff);
		c[3] = (char)((in >> 24) & 0xff);
	}
	uint ctoi(uchar *tmp){
		unsigned int b = 0, c = 0;
		c = tmp[0];
		b |= c;
		c = tmp[1];
		b |= (c << 8);
		c = tmp[2];
		b |= (c << 16);
		c = tmp[3];
		b |= (c << 24);
		return b;
	}

	// Encode
	bool CountFrequency();
	void Normailizing();
	void WriteHead();
	void WriteCode();
	void WriteData();

	// Decode
	void ReadHead();
	void ReadCode();
	void WriteSourData();
public:
	Huffman(string fileName);

	void Encode();
	void Decode();

	void run();
};

#endif