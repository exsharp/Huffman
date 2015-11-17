#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <iostream>
#include <fstream>
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
	string inFileName;
	string outFileName;
	string tail; //文件后缀

	bool type; //true Encode false Decode

	ofstream output;
	ifstream input;

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