#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

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
};

#endif
