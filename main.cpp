#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

#include "huffman.h"
#include "Schedule.h"

int main(){
	string filename = "C:\\Users\\zfliu\\Desktop\\text.txt";
	//string filename = "C:\\Users\\zfliu\\Desktop\\ue_english.exe";
	//string filename = "C:\\Users\\zfliu\\Desktop\\go.exe";
	Huffman huffman(filename);
	huffman.Encode();
	//huffman.Decode();
}
