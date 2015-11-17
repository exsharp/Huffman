#include "Buffer.h"

Buffer::Buffer(uchar *buffer, int num){
	this->buffer = buffer;
	memset(buffer, 0, sizeof(uchar)*num);
	this->maxBufferLen = num * 8;
	this->currentLen = 0;
}

//把缓冲区的内容写到文件里面
void Buffer::clear(){
	//已储存个数清零
	currentLen = 0;
	memset(buffer, 0, sizeof(uchar)*(maxBufferLen / 8));
}

//向缓冲区填入东西
bool Buffer::append(Coding::Binary bin){
	//返回是否已满
	int index = currentLen / 8;
	int pos = 7 - (currentLen % 8);

	char add = bin << pos;
	buffer[index] |= add;
	currentLen++;

	if (currentLen == maxBufferLen){
		return true;
	}
	return false;
}

//清空缓冲顺便写入文件
uint Buffer::flush(){
	int count = currentLen % 8;
	count = 7 - (count - 1);
	for (int i = 0; i < count; i++){
		append(Coding::Binary::Zero);
	}
	return currentLen/8;
}