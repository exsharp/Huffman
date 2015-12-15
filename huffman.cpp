#include "huffman.h"
#include "Schedule.h"

Huffman::Huffman(string fileName)
:fileLength(0)
{
	this->inFileName = fileName;
	
	//获取文件文件后缀
	int pos = fileName.find_last_of('.');
	this->tail.assign(fileName.begin() + pos + 1, fileName.end());

	if (tail.find("hfm") < tail.length()){
		type = false;
		//是哈夫曼文件

		tail.clear();
		//把设置文件输入输出流放到ReadHead里面来做
		this->inFileName.assign(fileName.begin(), fileName.end());
		this->outFileName.assign(fileName.begin(), fileName.begin() + pos);
		this->outFileName += ".";
	}
	else{
		type = true;
		//不是哈夫曼文件

		//设置输出文件名
		this->outFileName.assign(fileName.begin(),fileName.begin()+pos);
		this->outFileName.append(".hfm");

		//设置文件输入输出流
		this->input.open(inFileName, ios::in | ios::binary);
		this->output.open(outFileName, ios::out | ios::binary);
	}
}

//第一次读文件，计算各各的频率
bool Huffman::CountFrequency(){

	//用来记录每个字符出现的频率
	unsigned int frequency[256];
	memset(frequency, 0, sizeof(frequency));
	
	//获得文件的长度
	input.seekg(0, ios::end);
	fileLength = input.tellg();
	input.seekg(0, ios::beg);

	uchar readChar;

	//以下为可视化
	streampos newLength = fileLength - input.tellg();
	int percent = (int)newLength / 100;
	int count = 0;
	Schedule she(0);
	she.ShowText("正在统计频率");
	//可视化结束

	while (input.tellg() < fileLength){

		//以下为可视化
		if (0 == percent){
			count++;
			she.SetProc(count);
			percent = (int)newLength / 100;
		}
		percent--;
		//可视化结束

		input.read((char*)&readChar,sizeof(readChar));
		frequency[readChar]++;
	}

	//获得编码表
	Tree tree(frequency);
	tree.GetCodeTable(code);

	return true;
}

bool less_second(Coding & m1, Coding & m2) {
	return m1.GetChar() < m2.GetChar();
	//return m1.GetLength() < m2.GetLength();
}

void Huffman::Normailizing(){
	// 把字符填充完整，共256个
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
	//写入头信息
	output << tail.c_str();
	uchar tmp = 0;
	output.write((char*)&tmp, sizeof(char));
	output<<"ZFLIU_HUFFMAN";
}

void Huffman::WriteCode(){

	int code_len = code.size() - 1 ;
	//写入字符的数量
	output.write((char*)&code_len, sizeof(char));
	for (int i = 0; i <= code_len; i++){
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
	output << "CodingEnd";
}

void Huffman::WriteData(){
	
	//填充完整，方便取值
	Normailizing();

	uchar *buf = new uchar[BUFFER_LEN];
	//写入文件的缓冲区
	Buffer buffer(buf, BUFFER_LEN); 


	//以下为可视化
	int percent = (int)fileLength / 100;
	int count = 0;
	Schedule she(0);
	she.ShowText("正在写入数据");
	//可视化结束

	input.seekg(0, ios::beg);
	while (input.tellg() < fileLength){


		//以下为可视化
		if (0 == percent){
			count++;
			she.SetProc(count);
			percent = (int)fileLength / 100;
		}
		percent--;
		//可视化结束

		uchar readChar;
		input.read((char*)&readChar, sizeof(uchar));	
		//获得某个字符的信息
		Coding _code = code.at(readChar);
		//把这个字符的流写入缓冲
		queue<Coding::Binary> qu = _code.GetStream();
		while (!qu.empty()){
			bool full = buffer.append(qu.front());
			qu.pop();
			if (full){
				output.write((char*)buf, sizeof(char)*BUFFER_LEN);
				buffer.clear();
			}
		}
	}

	unsigned int len = buffer.flush();
	output.write((char*)buf, sizeof(char)*len);
	
	delete[] buf;

	she.ShowText("编码完成");
}

void Huffman::Encode(){
	CountFrequency();
	WriteHead();
	WriteCode();
	WriteData();
}

//---------------------------
//Decode

void Huffman::ReadHead(){
	//设置文件输入输出流
	this->input.open(inFileName, ios::out | ios::binary);

	//获取文件长度
	input.seekg(0, ios::end);
	fileLength = input.tellg();
	input.seekg(0, ios::beg);

	uchar readChar = 1;
	int tail_count;
	for (tail_count = 0; 0 != readChar && tail_count < 10; tail_count++){
		input.read((char*)&readChar, sizeof(uchar));
		tail += readChar;
	}

	if (tail_count==10){
		//尾巴长度大于10，出错
		//TODO
		assert(0);
	}
	else{
		outFileName = outFileName + "OUT." + tail ;
		output.open(outFileName, ios::app | ios::binary | ios::ate);
	}
	
	//读取存入的标志
	char head[] = "ZFLIU_HUFFMAN";
	//可能是因为停止符的原因，会读多一位
	input.read((char*)&head, sizeof(head)-1);
	int ret = strcmp(head, "ZFLIU_HUFFMAN");

	if (0 != ret)
	{
		//读不到相应的标志位，错误
		//TODO
		assert(0);
	}
}

void Huffman::ReadCode(){

	uchar code_len = 0;
	input.read((char*)&code_len, sizeof(uchar));
	int len = code_len;//储存的时候减了一位
	len = len + 1;
	code.clear();

	uchar raw;
	uchar length;

	for (int i = 0; i < len; i++){
		vector<uchar> tmp_code(32);
		input.read((char*)&raw, sizeof(char));
		input.read((char*)&length, sizeof(char)); 

		int tmp_len = (length / 8) + 1;

		input.read((char*)&tmp_code[0], sizeof(char)*tmp_len);

		Coding _code(raw, length, tmp_code);
		this->code.push_back(_code);
	}

	//读取存入的标志
	char head[] = "CodingEnd";
	//可能是因为停止符的原因，会读多一位
	input.read((char*)&head, sizeof(head)-1);
	int ret = strcmp(head, "CodingEnd");

	if (0 != ret)
	{
		//读不到相应的标志位，错误
		//TODO
		assert(0);
	}
}

void Huffman::WriteSourData(){

	Tree tree(code);
	uchar readChar;
	uchar getChar;
	bool canWrite = 0;


	//以下为可视化
	int percent = (int)fileLength / 100;
	int count = 0;
	Schedule she(0);
	she.ShowText("正在解码");
	//可视化结束

	while (input.tellg() < fileLength){

		//以下为可视化
		if (0 == percent){
			count++;
			she.SetProc(count);
			percent = (int)fileLength / 100;
		}
		percent--;
		//可视化结束

		input.read((char*)&readChar, sizeof(readChar));
		for (int i = 7; i >= 0; i--){
			uchar add = 1 << i;
			uchar mask = readChar & add;
			mask = mask >> i;
			switch (mask)
			{
			case 1:
				canWrite = tree.GetCode(Coding::Binary::One, getChar);
				break;
			case 0:
				canWrite = tree.GetCode(Coding::Binary::Zero, getChar);
				break;
			default:
				assert(0);
				break;
			}
			if (canWrite){
				output.write((char*)&getChar, sizeof(uchar));
				output.flush();
			}
		}
	}
}

void Huffman::Decode(){
	ReadHead();
	ReadCode();
	WriteSourData();
}

void Huffman::run(){
	if (type)
		Encode();
	else
		Decode();
}

