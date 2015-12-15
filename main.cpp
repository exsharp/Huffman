#include <iostream>
#include <fstream>
using namespace std;

#include "huffman.h"

int main(int argc,char *argv[]){
	//ofstream os;
	//os.open("C:\\Users\\zfliu\\Desktop\\fuck\\output.txt");
	//cout.rdbuf(os.rdbuf());

	if (argc > 1){
		string filename(argv[1]); //= "C:\\Users\\zfliu\\Desktop\\aa.hfm";
		Huffman huffman(filename);
		huffman.run();
	}
	else{
		cout << "Usage:" << "Huffman.exe XXX.XXX" << endl;
		cout << "This EXE can auuto detect what type of file" << endl;
	}

	system("pause");
}
