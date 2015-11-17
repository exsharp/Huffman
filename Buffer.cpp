#include "Buffer.h"

Buffer::Buffer(uchar *buffer, int num, ofstream &out){
	this->buffer = buffer;
	memset(buffer, 0, sizeof(uchar)*num);
	this->maxBufferLen = num * 8;
	this->out = &out;
	this->currentLen = 0;
}

//�ѻ�����������д���ļ�����
void Buffer::write(){
	this->out->write((char*)buffer, sizeof(uchar)*(currentLen/8));

	//�Ѵ����������
	currentLen = 0;
	memset(buffer, 0, sizeof(uchar)*(maxBufferLen / 8));
}

//�򻺳������붫��
void Buffer::append(Coding::Binary bin){
	int index = currentLen / 8;
	int pos = 7 - (currentLen % 8);

	char add = bin << pos;
	buffer[index] |= add;
	currentLen++;

	if (currentLen == maxBufferLen){
		write();
	}
}

//��ջ���˳��д���ļ�
void Buffer::flush(){
	int count = currentLen % 8;
	count = 7 - (count - 1);
	for (int i = 0; i < count; i++){
		append(Coding::Binary::Zero);
	}
	write();
}

void callback(Buffer &buf, Coding::Binary bin){
	buf.append(bin);
}