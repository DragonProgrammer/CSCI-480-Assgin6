// Author micheal peterson
// assignment 6
// class 480-2
// Due 11/13

#include <iostream>
#include <string>
#include <iomanip>
#include "Block.hpp"
using std::setw;
using std::cout;
using std::string;
using std::endl;
Block::Block(int A, int S, string P, string B){ //constructor of In_use
	size = S; 
	startA =A;
	PID = P;
	BID = B;
}
Block::Block(int A, int S){  //constructer for Available
	size =S;
	startA =A;
}
void Block::PBlock(){  // Output for Available
	cout << "Start Address = " << setw(8) << startA << " Size = " << setw(8) <<size << endl;
}
void Block::PBlockU(){ // output for In_use
	cout << "Start Address: " << setw(8) << startA << " Size = " << size << " Process ID =  " << PID << " Block ID = " << BID << endl;
}
