#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__
#include<string>
using std::string;

class Block{
	public:
	int size;
	int startA;
	string PID;
	string BID;
	Block(int A, int S);// initialize unused blocks
Block(int A, int S, string P, string B); //construct used block
void PBlock();
void PBlockU();
void SetB(int A, int S);
bool operator < (Block const rhs){return startA < rhs.startA;}
};

#endif
