#include <iostream>
#include <string>
#include <iomanip>
#include "Block.hpp"
using std::setw;
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
	cout << "Start Address = " << setw(8) << startA << " Size = " << setw(8) <<size << endl;
}
void Block::PBlockU(){
	cout << "Start Address: " << setw(8) << startA << " Size = " << size << " Process ID =  " << PID << " Block ID = " << BID << endl;
}
