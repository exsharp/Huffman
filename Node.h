#ifndef _NODE_H_
#define _NODE_H_

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

#endif
