#include "Buffer.h"

Buffer::Buffer(uchar *buffer, int num){
	this->buffer = buffer;
	memset(buffer, 0, sizeof(uchar)*num);
	this->maxBufferLen = num * 8;
	this->currentLen = 0;
}

//�ѻ�����������д���ļ�����
void Buffer::clear(){
	//�Ѵ����������
	currentLen = 0;
	memset(buffer, 0, sizeof(uchar)*(maxBufferLen / 8));
}

//�򻺳������붫��
bool Buffer::append(Coding::Binary bin){
	//�����Ƿ�����
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

//��ջ���˳��д���ļ�
uint Buffer::flush(){
	int count = currentLen % 8;
	count = 7 - (count - 1);
	for (int i = 0; i < count; i++){
		append(Coding::Binary::Zero);
	}
	return currentLen/8;
}