#include "Node.h"

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
