#include <list>
#include <iostream>
#include "Block.hpp"
using std::list;
using std::cout;
//using std::vector;
#define Kb 1024
#define Mb (1024*1024)

list<Block> Available;
list<Block> In_use;

void InitA(){
	
// set up link to have
// Start Address = 3145728 Size = 1048576
// Start Address = 4194304 Size = 2097152
// Start Address = 6291456 Size = 2097152
// Start Address = 8388608 Size = 4194304
// Start Address = 12582912 Size = 4194304
Available.push_back(Block(314,40));
//Available[1] = Block((4*Mb),(2*Mb));
//Available[2] = Block((6*Mb),(2*Mb));
//Available[3] = Block((8*MB),(4*MB));
//Available[4] = Block((12*MB),(4*MB));
}
void PrintL(){
//	int s =Available.size();
	for (auto e : Available){
	e.PBlock();
	}
}
int main(){
	InitA();
	PrintL();
	return 0;
}
