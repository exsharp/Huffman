#include <iostream>
#include <fstream>
using namespace std;

#include "huffman.h"

int main(){
	//ofstream os;
	//os.open("C:\\Users\\zfliu\\Desktop\\fuck\\output.txt");
	//cout.rdbuf(os.rdbuf());

	//string filename = "C:\\Users\\zfliu\\Desktop\\fuck\\aaa.cpp";
	//string filename = "C:\\Users\\zfliu\\Desktop\\fuck\\aaa.hfm";
	//string filename = "C:\\Users\\zfliu\\Desktop\\fuck\\main.exe";
	string filename = "C:\\Users\\zfliu\\Desktop\\fuck\\main.hfm";
	Huffman huffman(filename);
	huffman.run();
	system("pause");
}
