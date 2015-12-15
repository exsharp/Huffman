#include <iostream>
#include <fstream>
using namespace std;

#include "huffman.h"

int main(int argc,char *argv[]){
	//ofstream os;
	//os.open("C:\\Users\\zfliu\\Desktop\\fuck\\output.txt");
	//cout.rdbuf(os.rdbuf());

	if (argc > 1){
		string filename(argv[1]);// = "C:\\Users\\zfliu\\Desktop\\fuck\\main.hfm";
		Huffman huffman(filename);
		huffman.run();
	}
	else{
		assert("Can't open file in main");
	}
	system("pause");
}
