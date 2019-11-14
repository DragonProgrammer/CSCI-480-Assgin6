//
/******************************
 * CSCI 480-2 - Assignment 6 - Fall 2019
 * Programmer Michael Peterson
 * Z1838929
 * section 2
 * TA: Jingwan Li
 * Due 11/13
 *
 * Header file for Assignment 6
 * **********************************/
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
bool operator < (Block const rhs){return startA < rhs.startA;} //overloau operator for sort
};

#endif
