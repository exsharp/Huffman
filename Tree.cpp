#include "Tree.h"
#include "huffman.h"

Node::Node(){
	raw = 0;
	weight = 0;
	left = 0;
	right = 0;
}

Node::Node(unsigned char raw, unsigned int weight){
	//cout << (int)raw <<"  "<< weight << endl;
	this->raw = raw;
	this->weight = weight;
	left = 0;
	right = 0;
}

//-------------------------------------------------------

Tree::Tree(){
	this->tree = 0;
	this->max_depth = 0;
}

Tree::Tree(const unsigned int feq[]){

	this->max_depth = 0;
	//memset(code, 0, sizeof(code));

	// ����Ҷ�ӽ��
	priority_queue<Node*,vector<Node*>,Node::Compare> queue;

	for (int i = 0; i < 256; i++){
		if (0 != feq[i]){
			Node *node = new Node((char)i, feq[i]);
			queue.push(node);
		}
	}

	// ������������
	while (queue.size()>1)
	{
		Node *node1 = queue.top();	queue.pop();
		Node *node2 = queue.top();	queue.pop();

		unsigned int newWeight = node1->weight + node2->weight;
		Node *node = new Node(0,newWeight);
		node->left = node1;
		node->right = node2;
		
		queue.push(node);
	}

	this->tree = queue.top();
}

Tree::Tree(vector<Coding> code){
	//this->code = code;
}

void Tree::_GetDepth(Node *tree,int depth){
	
	if (0 == tree){
		if (depth > this->max_depth)
			this->max_depth = depth-1;
		return;
	}
	else{
		depth++;
		_GetDepth(tree->left, depth);
		_GetDepth(tree->right, depth);
	}
}

int Tree::GetDepth(){
	
	Node *tmp = 0;
	int depth = 0;
	tmp = tree;

	if (0 == max_depth){
		_GetDepth(tree, depth);
	}

	return max_depth;
}

void Tree::_SetCoding(vector<Coding> &code,Node *tree, Coding _code, Node::Direction dir){

	//�ж������ĸ��������0���ұ�1
	switch (dir)
	{
	case Node::LEFT:
		_code.AddBit(Coding::Binary::Zero);
		break;
	case Node::RIGHT:
		_code.AddBit(Coding::Binary::One);
		break;
	case Node::ROOT://ROOT
		//ֻ��һ���ַ������������������ֵ�
		if ((0 == tree->left) ||
			(0 == tree->right)) {
			_code.AddBit(Coding::Binary::One);
			_code.SetChar(tree->raw);
			code.push_back(_code);
			return;
		}
		break;
	}
	
	//Ҷ�ӣ������ܳ���ֻ��һ�ߵ�
	if ((0 == tree->left) &&
		(0 == tree->right)){

		//�����ַ�����ӵ�һ���ַ��б�
		_code.SetChar(tree->raw);
		code.push_back(_code);
	}
	else{
		_SetCoding(code,tree->left, _code, Node::Direction::LEFT);
		_SetCoding(code,tree->right, _code, Node::Direction::RIGHT);
	}
}

void Tree::GetCode(vector<Coding> &code){
	Coding _code;
	Node *tmp = tree;
	_SetCoding(code,tmp, _code, Node::Direction::ROOT);
	cout << "H";
}
