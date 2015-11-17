#ifndef _TREE_H_
#define _TREE_H_

#include <iostream>
#include <queue>

using namespace std;

class Coding;

class Node{
public:
	enum Direction{
		LEFT,
		RIGHT,
		ROOT
	};

	unsigned char raw;
	unsigned int weight;

	Node *left;
	Node *right;

	Node();
	Node(unsigned char raw, unsigned int weight);

	class Compare{
	public:
		bool operator() (Node *n1, Node *n2){
			return n1->weight > n2->weight;
		}
	};
};

class Tree{
private:
	Node *tree;
	int max_depth;
	vector<Coding> code;

	//获得深度
	void _GetDepth(Node *tree,int depth);
	void _SetCoding(Node *tree, Coding _code, Node::Direction dir);

public:
	Tree();
	Tree(const unsigned int feq[]);
	//~Tree();//TODO 防止内存泄漏

	//获得深度的接口
	int GetDepth();

	//获得字符表
	vector<Coding> GetCode();
};
#endif