#include <iostream>
#include <fstream>
using namespace std;

#include "huffman.h"

int main(){
	//string filename = "C:\\Users\\zfliu\\Desktop\\ue_english.exe";
	//string filename = "C:\\Users\\zfliu\\Desktop\\go.exe";
	//string filename = "C:\\Users\\zfliu\\Desktop\\text.hfm";

	//string filename = "C:\\Users\\zfliu\\Desktop\\aaa.cpp";
	string filename = "C:\\Users\\zfliu\\Desktop\\aaa.hfm";
	Huffman huffman(filename);
	huffman.run();
}
