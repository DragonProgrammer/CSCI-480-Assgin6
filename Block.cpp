#include <iostream>
#include <string>
#include "Block.hpp"
using std::cout;
//using std::string;
using std::endl;


Block::Block(int S, int A){
	size =S;
	startA =A;
//	PID = NULL;
//	BID = NULL;
}
void Block::PBlock(){
	cout << "Block Address: " << startA << "  Block Size: " << size << endl;
}
