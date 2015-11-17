#ifndef _TREE_H_
#define _TREE_H_

#include <iostream>
#include <queue>

using namespace std;

#include "Node.h"
#include "Coding.h"

class Tree{
private:
	Node *tree;
	Node *tmp;
	int max_depth;
	//vector<Coding> code;

	//������
	void _GetDepth(Node *tree,int depth);
	void _SetCoding(vector<Coding> &code,
		Node *tree, Coding _code, Node::Direction dir);

public:
	Tree();
	//�����ʱ��Ĺ��췽��
	Tree(const unsigned int feq[]);
	Tree(const vector<Coding> &code);
	//�����ʱ��Ĺ��췽��
	//~Tree();//TODO ��ֹ�ڴ�й©

	//�����ȵĽӿ�
	int GetDepth();

	//����ַ���
	void GetCodeTable(vector<Coding> &code);
	bool GetCode(Coding::Binary bin, uchar &ch);
};
#endif