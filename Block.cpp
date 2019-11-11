#include <iostream>
#include <string>
#include "Block.hpp"
using std::cout;
using std::string;
using std::endl;
void Block::UBlock(int S, int A, string P, string B){
	size = S; 
	startA =A;
	PID = P;
	Bid = B;
}

Block::Block(int S, int A){
	size =S;
	startA =A;
}
void Block::PBlock(){
	cout << "Block Address: " << startA << "  Block Size: " << size << endl;
}
