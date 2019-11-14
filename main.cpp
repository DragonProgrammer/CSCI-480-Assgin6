#include "Block.hpp"
#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <string.h> // to compare argv
#include <iterator>
#include <algorithm>
using std::cout;
using std::ifstream;
using std::endl;
using std::list;
using std::string;
using std::cerr;
// using std::vector;
#define Kb 1024
#define Mb (1024 * 1024)

list<Block> Available;
list<Block> In_use;

int Usize(){
int	total = 0;
	for (auto A :In_use){
		total += A.size;
	}
	return total;
}
int Asize(){
int	total = 0;
	for (auto A :Available){
		total += A.size;
	}
	return total;
}

// might not need to pass address
void Buse(int S, string P, string B, auto Spot){
      In_use.push_front(Block(Spot->startA, S, P, B));
      int NS, NA;
      NS = Spot->size - S;    //  cout << V.size << "   " << NS << endl;
      if (NS < 0) {
        cout << "NS is less than";
        exit(0);
      } else if (NS > 0) {
        NA = Spot->startA + S;   //	cout << V.startA << "   " << NA << endl;
        Spot->size = NS;
        Spot->startA = NA;
            	return;
      } else if (NS == 0) {
       Available.erase(Spot); // remove H
       return;
      }
}

void CheckB(int S, string P, string B) {
  int Check = S;
  auto Spot =Available.begin();
  auto tempL = Spot;
 bool Found = false; 
  
  for (auto &V : Available) { // iterating ththro the list and using a referance instead of copying the item
    if (Check == V.size) { // if the block fits
    	  // cout << "exact size" << endl;
	   
	    Buse(S, P,B, Spot);
   return;
    } else if (Check < V.size && (tempL->size > V.size || !Found)){
	    tempL = Spot;
	    Found = true;
    }
    Spot++;
  }
  if (Found){
	  cout << "Found a block of size " << tempL->size << endl;
	  Buse(S, P, B, tempL);
    cout << "Success in allocating a block" << endl << endl; // copy this line
	  return;}
  cout << "Unable to comply as no block of adaquate size is available" << endl <<endl;
}

void Merge(){
	for(auto i=Available.begin(), j=std::next(i,1);
			j != Available.end();
			i++,j++){ // looping with a pointer to the next element
		int test =i->size+i->startA, newS=i->size+j->size;
//		cout << test << "   " << j->startA <<endl;
		if (test == j->startA && newS <= (4*Mb)){
			cout << "Merging two blocks at " << i->startA << " and " << j->startA <<endl;
			i->size = newS;
			Available.erase(j);
		//	j=std::next(i,1);    old merge
		return Merge();
		}
	}
}
void Terminate(string P){
	cout << "Transaction:   request to termainate process " << P <<endl;
bool found = false;
	for (auto &T : In_use){
		if ( P == T.PID){
		found = true;
			Available.push_back(Block(T.startA, T.size));
			Available.sort();
			Merge();
								}
	}
		Available.sort();
//		cout << In_use.size() <<endl;
	//	In_use.remove(P); // this line will brobably be the error
if(found){	In_use.remove_if([&P](Block B){return B.PID == P;});
cout << "Success in terminating a process" << endl << endl;}
else { cout << "Unable to comply as the indicated process could not be found" <<endl <<endl;}
//		cout << In_use.size() <<endl;
}
void DAlocate(string P, string B){
	cout << "Transaction: request to dealocate block ID " << B << " for process " << P <<endl;
	auto Spot=In_use.begin();
	for (auto &D : In_use){
		if (P == D.PID && B == D.BID){
			Available.push_back(Block(D.startA, D.size));
			In_use.erase(Spot);
			Available.sort();
			Merge();
			cout << "Success in dealocating a block" <<endl <<endl;
			return;
		}
		Spot++;
	}	
cout << "Unable to comply as the indicated block cannot be found." << endl <<endl;
}

void CheckA(int S, string P, string B) {
	int Check = S;
  auto Spot =Available.begin();
  for (auto &V : Available) { // iterating ththro the list and using a referance instead of copying the item
    if (Check <= V.size) { // if the block fits
    cout << "Found a block of size " << V.size << endl; //copy this line 	
    	    Buse(S, P,B, Spot);
    cout << "Success in allocating a block" << endl << endl; // copy this line
   return;
    }
    Spot++;
  }
  cout << "Unable to comply as no block of adaquate size is available" << endl << endl;
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
  cout << "List of available blocks" << endl;
  for (auto e : Available) {
    e.PBlock();
  }
  cout << "Total size of the list = " << Asize() <<endl << endl;;
  cout << "List of blocks in use " << endl;
  if (In_use.size() == 0)
	  cout << "(none)" <<endl;
  for (auto e : In_use) {
    e.PBlockU();
  }
  cout << "Total size of the list = " << Usize() <<endl;
  cout << endl;
}



int main(int argc,char**argv) {
	if(argc!=2){
		cerr<<"Needs 1 rg"<<endl;
		return 1;}

ifstream Infile;
Infile.open("testdata");
char Case;
int Size;
string PID, BID;
// read in the first leter of the line
 if (0==strcmp(argv[1], "-F")){
  cout << "Simulation of Memory Managment using the First-Fit algorithm" << endl << endl << "Begining the run" << endl << endl;}
  else {
  cout << "Simulation of Memory Managment using the Best-Fit algorithm" << endl << endl << "Begining the run" << endl << endl;
}
InitA();
PrintL();
while(Infile>>Case)
//	cout << "Transaction: ";
		switch (Case) {
			case 'A':
		Infile >>  PID >>  Size >>  BID;
cout << "Transaction: request to allocate " << Size << " bytes for process " << PID << ", block ID " << BID << endl;
 if (0==strcmp(argv[1], "-F")){
	 CheckA(Size, PID, BID);}
  else {
 CheckB(Size, PID, BID);
}
PrintL();

break;
			case 'L':
		Infile >>  PID >>  Size >>  BID;
//check command line arge
cout << "Transaction: request to load process " << PID << ", block ID " << BID << " using " << Size << " bytes" << endl;
 if (0==strcmp(argv[1], "-F")){
	 CheckA(Size, PID, BID);}
  else {
 CheckB(Size, PID, BID);
}
PrintL();

break;
		case 'D':
//read in PID, BID
Infile >> PID >> BID;
DAlocate(PID, BID);
Merge();
PrintL();
break;
		case 'T':
Infile >> PID;
Terminate(PID);
//Merge();
PrintL();
break;
		case '?':
cout << "End of the run" << endl << endl;
PrintL();
return 0;
	}
}
