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

	//获得深度
	void _GetDepth(Node *tree,int depth);
	void _SetCoding(vector<Coding> &code,
		Node *tree, Coding _code, Node::Direction dir);

public:
	Tree();
	//编码的时候的构造方法
	Tree(const unsigned int feq[]);
	Tree(const vector<Coding> &code);
	//译码的时候的构造方法
	//~Tree();//TODO 防止内存泄漏

	//获得深度的接口
	int GetDepth();

	//获得字符表
	void GetCodeTable(vector<Coding> &code);
	bool GetCode(Coding::Binary bin, uchar &ch);
};
#endif