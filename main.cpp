/******************************
 * CSCI 480-2 - Assignment 6 - Fall 2019
 * Programmer Michael Peterson
 * Z1838929
 * section 2
 * TA: Jingwan Li
 * Due 11/13
 *
 *Main file for Assignment 6. Take data from file and uses them to allocate, delocate and terminate processes in simulations of first fit and best fit Memory managment.
 * **********************************/
  


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
#define Kb 1024
#define Mb (1024 * 1024)
// lists for avalalbe and used memory blocks
list<Block> Available;
list<Block> In_use;
// get the total bytes of for in use list
int Usize(){
int	total = 0;
	for (auto A :In_use){
		total += A.size;
	}
	return total;
}
int Asize(){ // and total byts of available list
int	total = 0;
	for (auto A :Available){
		total += A.size;
	}
	return total;
}
// function to create a block in In_use and shrink a selected block in Available
void Buse(int S, string P, string B, auto Spot){
      In_use.push_front(Block(Spot->startA, S, P, B));
      int NS, NA; // creates temporary numbers for what the new Size and Adress of avalable will be
      NS = Spot->size - S;    
      if (NS < 0) {
        cout << "NS is less than";
        exit(0);
      } else if (NS > 0) {// changes the block in vailable
        NA = Spot->startA + S;   
        Spot->size = NS;
        Spot->startA = NA;
            	return;
      } else if (NS == 0) {
       Available.erase(Spot); // or removes it if all of block used
       return;
      }
}
// best fit function
void CheckB(int S, string P, string B) {
  int Check = S; //creates a value to check size with
  auto Spot =Available.begin(); //creates  pointer to a block
  auto tempL = Spot; //creates a temprary pointer to check against for best fit
 bool Found = false; //says it has not found a fit yet
  
  for (auto &V : Available) { // iterating ththro the list
    if (Check == V.size) { // if the process fits exactly fits exactly
	   
	    Buse(S, P,B, Spot); //creat In_use and leave passing the iterater as the pointer
   return;
    } else if (Check < V.size && (tempL->size > V.size || !Found)){ // if process fits and we have either not found one or the last one we found is bigger
	    tempL = Spot; //set the temp pointer as the new spot
	    Found = true; //and saying we found 1
    }
    Spot++;
  }
  if (Found){ //outside of loop if we found a fit create In_use passing temp
	  cout << "Found a block of size " << tempL->size << endl;
	  Buse(S, P, B, tempL);
    cout << "Success in allocating a block" << endl << endl; // copy this line
	  return;}
  cout << "Unable to comply as no block of adaquate size is available" << endl <<endl; //orsay no found big enough
}

void Merge(){ // loop throu a sorted Available linking blocks whose end adress is the same as the nexed's start and whose total size is not more then 4Mb
	for(auto i=Available.begin(), j=std::next(i,1);
			j != Available.end();
			i++,j++){ // looping with a pointer to the next element
		int test =i->size+i->startA, newS=i->size+j->size; //creates the vaules to check
		if (test == j->startA && newS <= (4*Mb)){
			cout << "Merging two blocks at " << i->startA << " and " << j->startA <<endl;
			i->size = newS;// chages the size pf the first block
			Available.erase(j); // erases the second block
		return Merge();//recurse call through Available
		}
	}
}
void Terminate(string P){ // removes several things with the Same PID
	cout << "Transaction:   request to termainate process " << P <<endl;
bool found = false; //start with none found
	for (auto &T : In_use){ //sicle throu In_use for PID
		if ( P == T.PID){ //for each found
		found = true; // set as found 
			Available.push_back(Block(T.startA, T.size)); //ad blocks start and size to Available
			Available.sort(); //sort available
			Merge(); //and merge
								}
	}
		Available.sort();
if(found){	In_use.remove_if([&P](Block B){return B.PID == P;});//if found remove all
cout << "Success in terminating a process" << endl << endl;}
else { cout << "Unable to comply as the indicated process could not be found" <<endl <<endl;}
}
void DAlocate(string P, string B){//remove from In_use a process with a specific PID BID pair
	cout << "Transaction: request to dealocate block ID " << B << " for process " << P <<endl;
	auto Spot=In_use.begin(); //create a pointer
	for (auto &D : In_use){ //iterate through loop until found
		if (P == D.PID && B == D.BID){
			Available.push_back(Block(D.startA, D.size)); //add it back tp Available
			In_use.erase(Spot); //remove that block from IN_use
			Available.sort(); //sort and merg
			Merge();
			cout << "Success in dealocating a block" <<endl <<endl;
			return;
		}
		Spot++;
	}	
cout << "Unable to comply as the indicated block cannot be found." << endl <<endl;
}

void CheckA(int S, string P, string B) { //first fit algirithm loops through availble untill it finds a big enoph block and adds it to in Uss
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
//create initial Avalable blocks
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
void PrintL() { //print function for printeing each block in the available and inuse lists with thire sizes
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
	if(argc!=2){// check that the argument for deciding if it is First or best fit was pased
		cerr<<"Needs 1 rg"<<endl;
		return 1;}

ifstream Infile; // create and open the file for system comand simulation
Infile.open("testdata");
char Case;// chreat variable to read values from file
int Size;
string PID, BID;
 if (0==strcmp(argv[1], "-F")){// depending on argv print the aprpreit header
  cout << "Simulation of Memory Managment using the First-Fit algorithm" << endl << endl << "Begining the run" << endl << endl;}
  else {
  cout << "Simulation of Memory Managment using the Best-Fit algorithm" << endl << endl << "Begining the run" << endl << endl;
}
InitA();
PrintL();
while(Infile>>Case) //wile it can read in a line take the first chacter 
		switch (Case) {// look at first character to decide if:
			case 'A': // you allocateing a IN_use block with the values from the rest of the line
		Infile >>  PID >>  Size >>  BID;
cout << "Transaction: request to allocate " << Size << " bytes for process " << PID << ", block ID " << BID << endl;
 if (0==strcmp(argv[1], "-F")){ //and check which for of fit to use
	 CheckA(Size, PID, BID);}
  else {
 CheckB(Size, PID, BID);
}
PrintL();

break;
			case 'L': //or are loading (same as alocate whith diferant output header
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
		case 'D': //dealocating a block with the specific values in the rest of line
//read in PID, BID
Infile >> PID >> BID;
DAlocate(PID, BID);
PrintL();
break;
		case 'T': //terminating a process with the folwing PID
Infile >> PID;
Terminate(PID);
PrintL();
break;
		case '?'://or ending the run
cout << "End of the run" << endl << endl;
PrintL();
return 0;
	}
}
