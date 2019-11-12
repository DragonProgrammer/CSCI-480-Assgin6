#include <iostream>
#include <string>
#include "Block.hpp"
using std::cout;
using std::string;
using std::endl;
Block::Block(int A, int S, string P, string B){
	size = S; 
	startA =A;
	PID = P;
	BID = B;
}
//void SetB(int A, int S){
//	size = S;
//	startA = A; }
Block::Block(int A, int S){
	size =S;
	startA =A;
}
void Block::PBlock(){
	cout << "Block Address: " << startA << "  Block Size: " << size << endl;
}
void Block::PBlockU(){
	cout << "Block Address: " << startA << "  Block Size: " << size << "   Process ID: " << PID << "   Process name: " << BID << endl;
}
