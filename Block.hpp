#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

using std::string;

class Block{
	public:
	int size;
	int startA;
	string PID;
	string BID;
	Block(int S, int A);// initialize unused blocks
void UBlock(int S, int A, string P, string B); //construct used block
void PBlock();
};

#endif
