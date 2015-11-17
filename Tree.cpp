#include "Tree.h"
#include "huffman.h"

Tree::Tree(){
	this->tree = 0;
	this->max_depth = 0;
}

Tree::Tree(const unsigned int feq[]){

	this->max_depth = 0;
	//memset(code, 0, sizeof(code));

	// 构建叶子结点
	priority_queue<Node*,vector<Node*>,Node::Compare> queue;

	for (int i = 0; i < 256; i++){
		if (0 != feq[i]){
			Node *node = new Node((char)i, feq[i]);
			queue.push(node);
		}
	}

	// 构建哈夫曼树
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

	//判断这是哪个方向，左边0，右边1
	switch (dir)
	{
	case Node::LEFT:
		_code.AddBit(Coding::Binary::Zero);
		break;
	case Node::RIGHT:
		_code.AddBit(Coding::Binary::One);
		break;
	case Node::ROOT://ROOT
		//只有一个字符的情况，基本不会出现滴
		if ((0 == tree->left) ||
			(0 == tree->right)) {
			_code.AddBit(Coding::Binary::One);
			_code.SetChar(tree->raw);
			code.push_back(_code);
			return;
		}
		break;
	}
	
	//叶子，不可能出现只有一边的
	if ((0 == tree->left) &&
		(0 == tree->right)){

		//设置字符并添加到一个字符列表
		_code.SetChar(tree->raw);
		code.push_back(_code);
	}
	else{
		_SetCoding(code,tree->left, _code, Node::Direction::LEFT);
		_SetCoding(code,tree->right, _code, Node::Direction::RIGHT);
	}
}

void Tree::GetCodeTable(vector<Coding> &code){
	Coding _code;
	Node *tmp = tree;
	_SetCoding(code,tmp, _code, Node::Direction::ROOT);
}

Tree::Tree(const vector<Coding> &_code){
	this->tree = new Node;
	this->tmp = this->tree;
	for (int i = 0; i < _code.size(); i++){
		Coding code = _code.at(i);
		Node *pt = this->tree;
		queue<Coding::Binary> qu = code.GetStream();
		while (!qu.empty()){
			Coding::Binary ele = qu.front();
			qu.pop();
			switch (ele)
			{
			case Coding::Zero:
				if (pt->left == 0){
					Node *tmp = new Node;
					pt->left = tmp;
					pt = tmp;
				}
				else{
					pt = pt->left;
				}
				break;
			case Coding::One:
				if (pt->right == 0){
					Node *tmp = new Node;
					pt->right = tmp;
					pt = tmp;
				}
				else{
					pt = pt->right;
				}
				break;
			default:
				break;
			}
		}
		pt->raw = code.GetChar();
	}
}

bool Tree::GetCode(Coding::Binary bin, uchar &ch){
	switch (bin)
	{
	case Coding::Zero:
		tmp = tmp->left;
		break;
	case Coding::One:
		tmp = tmp->right;
		break;
	default:
		break;
	}
	if ((tmp->left == 0) &&
		(tmp->right == 0)){
		ch = tmp->raw;
		tmp = tree;
		return true;
	}
	else{
		return false;
	}
}
