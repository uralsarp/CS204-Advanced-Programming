#include <iostream>
#include <sstream>
#include <string>




struct SubSeqNode
{
int value;
SubSeqNode * next;
SubSeqNode::SubSeqNode() //default constructor
{ 
}

SubSeqNode::SubSeqNode(int n, SubSeqNode * p) //default constructor with 2 parameters
	: value(n),next(p)
{};
};

struct SubSeqHeadNode
{
int size; // number of elements in the subsequence
SubSeqNode * sHead; // head of the subsequence list
SubSeqHeadNode * next;

SubSeqHeadNode::SubSeqHeadNode() //default constructor
{ 
}
SubSeqHeadNode::SubSeqHeadNode(int n, SubSeqNode * h, SubSeqHeadNode * p) //constructor with 3 parameters
	: size(n),sHead(h),next(p)
{};
};

class SubSeqsList
{
public:
SubSeqsList(); //default constructor

void AddToList(SubSeqHeadNode *p);

void PrintList();//display the entire structure

//void updateList(int num); does not work

bool inList(int num); //function to check if a specific number is in the data structure or not

//SubSeqHeadNode *clone(SubSeqHeadNode *p,SubSeqNode *nnum) const; doesnt work

void SubSeqsList::arrange(); // function to delete the SubSeqHeadNode which is not connected to any SubSeqNode. (check delFromList func for further info)

void SubSeqsList::delFromList(int num);//delete one or more subsequence list(s) from the data structure,

void deleteAll();// function to delete the entire data structure

private:
SubSeqHeadNode * hHead;

};
