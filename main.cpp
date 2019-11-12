#include "Block.hpp"
#include <iostream>
#include <list>
#include <string>
using std::cout;
using std::endl;
using std::list;
using std::string;
// using std::vector;
#define Kb 1024
#define Mb (1024 * 1024)

list<Block> Available;
list<Block> In_use;

// might not need to pass address
// void Buse(int S, string P, string B, Block &H){
//}
void DAlocate(string P, string B){
	cout << "Dealocate process with PID of: " << P <<endl;
	auto Spot=In_use.begin();
	for (auto &D : In_use){
		if (P == D.PID && B == D.BID){
			Available.push_back(Block(D.startA, D.size));
			In_use.erase(Spot);
			Available.sort();
		}
		Spot++;
	}	
}


void CheckA(int S, string P, string B) {
  int Check = S;
  auto Spot =Available.begin();
  for (auto &V : Available) { // iterating ththro the list and using a referance instead of copying the item
    if (Check <= V.size) { // if the block fits
      //		Buse(S, P,B, V);
      In_use.push_back(Block(V.startA, S, P, B));
      int NS, NA;
      NS = V.size - S;
    //  cout << V.size << "   " << NS << endl;
      if (NS < 0) {
        cout << "NS is less than";
        exit(0);
      } else if (NS > 0) {
        NA = V.startA + S;
       //	cout << V.startA << "   " << NA << endl;
        V.size = NS;
        V.startA = NA;
       
       	return;
      } else if (NS == 0) {
       Available.erase(Spot); // remove H
       return;
      }
    } // exit the funciton
    Spot++;
  }
  cout << "none available" << endl;
}
void InitA() {

  // set up link to have
  // Start Address = 3145728 Size = 1048576
  // Start Address = 4194304 Size = 2097152
  // Start Address = 6291456 Size = 2097152
  // Start Address = 8388608 Size = 4194304
  // Start Address = 12582912 Size = 4194304
  Available.push_back(Block((3 * Mb), (1 * Mb)));
  Available.push_back(Block((4 * Mb), (2 * Mb)));
  Available.push_back(Block((6 * Mb), (2 * Mb)));
  Available.push_back(Block((8 * Mb), (4 * Mb)));
  Available.push_back(Block((12 * Mb), (4 * Mb)));
}
void PrintL() {
  //	int s =Available.size();
  cout << "Available Blocks:" << endl;
  for (auto e : Available) {
    e.PBlock();
  }
  cout << "Used Blocks: " << endl;
  for (auto e : In_use) {
    e.PBlock();
  }
}
int main() {
  InitA();
  PrintL();
  CheckA((.5 * Mb), "Art", "Process");
  PrintL();
  CheckA(Mb, "Art2", "Process");
  PrintL();
  CheckA((2 * Mb), "Art3", "Process");
  PrintL();
  DAlocate("Art2", "Process");
  PrintL();
  return 0;
}
