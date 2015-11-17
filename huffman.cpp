#include "huffman.h"
#include "Schedule.h"

Huffman::Huffman(string fileName)
:fileLength(0)
{
	this->fileName = fileName;
	
	//构造输出文件的名字
	int pos = fileName.find_last_of('.');
	//判断文件后缀
	this->tail.assign(fileName.begin() + pos + 1, fileName.end());

	if (tail.find("hfm") < tail.length()){
		//是哈夫曼文件
		this->outFileName.assign(fileName.begin(), fileName.begin() + pos);
	}
	else{
		this->outFileName.assign(fileName.begin(),fileName.begin()+pos);
		this->outFileName.append(".hfm");

		this->input.open(this->fileName, ios::out | ios::binary);
		this->output.open(outFileName, ios::app | ios::binary | ios::ate);
	}

}

//第一次读文件，计算各各的频率
bool Huffman::CountFrequency(){

	unsigned int frequency[256];
	memset(frequency, 0, sizeof(frequency));
	
	input.seekg(0, ios::end);
	fileLength = input.tellg();
	input.seekg(0, ios::beg);

	uchar readChar;
	while (input.tellg() < fileLength){
		input.read((char*)&readChar,sizeof(readChar));
		frequency[readChar]++;
	}
	//while (!input.bad() && !input.eof() && !input.fail()){
	//	input.read((char*)&readChar,sizeof(readChar));
	//	frequency[readChar]++;
	//}

	//最后一个字符会被重复读一遍，于是
	//frequency[readChar]--;

	//获得编码表
	Tree tree(frequency);
	code = tree.GetCode();

	//input.close();
	return true;
}

bool less_second(Coding & m1, Coding & m2) {
	return m1.GetChar() < m2.GetChar();
	//return m1.GetLength() < m2.GetLength();
}

void Huffman::Normailizing(){
	bool map[256];
	memset(map, 0, sizeof(map));
	for (unsigned int i = 0; i < code.size(); i++){
		map[code.at(i).GetChar()] = 1;
	}

	for (int i = 0; i < 256; i++){
		if (0 == map[i]){
			code.push_back(Coding(i));
		}
	}
	sort(code.begin(), code.end(),less_second);
}

void Huffman::WriteHead(){

	output << tail.c_str();
	uchar tmp = 0;
	output.write((char*)&tmp, sizeof(char));
	output<<"ZFLIU_HUFFMAN";

}

void Huffman::WriteCode(){

	int code_len = code.size() - 1 ;
	//写入字符的数量
	output.write((char*)&code_len, sizeof(char));
	for (int i = 0; i < code_len+1; i++){
		Coding _code = code.at(i);

		// 获得各种属性
		unsigned char row = _code.GetChar();
		uchar length = _code.GetLength();
		int code_length = length / 8 + 1;
		unsigned char *tmp = new unsigned char[code_length];
		_code.GetCode(tmp);

		//开始写入各种属性
		output.write((char*)&row, sizeof(char));
		output.write((char*)&length, sizeof(char));
		output.write((char*)tmp, sizeof(char)*code_length);

		delete[] tmp;
	}
}

void Huffman::WriteData(){
	
	重新建立
	if (input.bad() || input.eof() || input.fail()){
		input.close();
		input.open(fileName, ios::out | ios::binary);
	}

	//填充完整，方便取值
	Normailizing();

	uchar *buf = new uchar[BUFFER_LEN];
	//写入文件的缓冲区
	Buffer buffer(buf, 1, output);

	for (unsigned int i = 0; !input.fail() && !input.eof() && !input.bad();i++){
		uchar readChar;
		input.read((char*)&readChar, sizeof(uchar));
		if (!input.fail() && !input.eof() && !input.bad()){
			//获得某个字符的信息
			Coding _code = code.at(readChar);
			//把这个字符的流写入缓冲
			_code.GetStream(buffer,callback);
		}
	}

	buffer.flush();

	delete[] buf;
}

void Huffman::Encode(){
	CountFrequency();
	WriteHead();
	WriteCode();
	WriteData();
}

void Huffman::ReadHead(){

}
