#include <iostream>
#include <string>

using std::cout;
//using std::string;
using std::endl;

class Block{
	public:
	int size;
	int startA;
//	string PID;
//	string BID;
	Block(int S, int A);// initialize unused blocks
//	Block(int S, int A, string P, string B){}; //construct used block
void PBlock();
};

Block::Block(int S, int A){
	size =S;
	startA =A;
//	PID = NULL;
//	BID = NULL;
}
void Block::PBlock(){
	cout << "Block Address: " << startA << "  Block Size: " << size << endl;
}
