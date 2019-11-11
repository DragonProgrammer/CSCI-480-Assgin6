#include <list>
#include <iostream>
#include "Block.hpp"
#include <string>
using std::string;
using std::list;
using std::cout;
using std::endl;
//using std::vector;
#define Kb 1024
#define Mb (1024*1024)

list<Block> Available;
list<Block> In_use;

//might not need to pass address
void Buse(int S, string P, string B, Block &H){
	In_use.push_back(Block(H.startA, S, P, B));
	int NS, NA;
	NS = H.size - S;
	cout << H.size << "   " << NS << endl;
	if (NS <0 ){
		cout << "NS is less than";
		exit(0);
	} else if (NS > 0){
		NA = H.size + S;
		H.size = NS;
		H.startA = NA;
	} else if (NS == 0){
		//remove H
	}
}
void CheckA(int S, string P, string B){
	int Check = S;
	for(auto V : Available){
		if(Check < V.size){ //if the block fits
			Buse(S, P,B, V);
			return;}	// exit the funciton
	}
	cout << "none available" << endl;
}
void InitA(){
	
// set up link to have
// Start Address = 3145728 Size = 1048576
// Start Address = 4194304 Size = 2097152
// Start Address = 6291456 Size = 2097152
// Start Address = 8388608 Size = 4194304
// Start Address = 12582912 Size = 4194304
Available.push_back(Block((3*Mb),(1*Mb)));
Available.push_back(Block((4*Mb),(2*Mb)));
Available.push_back(Block((6*Mb),(2*Mb)));
Available.push_back(Block((8*Mb),(4*Mb)));
Available.push_back(Block((12*Mb),(4*Mb)));
}
void PrintL(){
//	int s =Available.size();
	cout << "Available Blocks:" << endl;
	for (auto e : Available){
	e.PBlock();
	}
	cout << "Used Blocks: " << endl;
	for (auto e : In_use){
	e.PBlock();
	}
}
int main(){
	InitA();
	PrintL();
	CheckA((.5*Mb),"Art", "Process");
	PrintL();
	return 0;
}
