#include <iostream>
#include <sstream>
#include <string>
#include "uralsarp_Sipahi_UralSarp_hw3_linklist.h"

using namespace std;
//Ural Sarp Sipahi 28093
int main(){
	string numbers;
	cout<<"Please enter the numbers in a line: ";
	getline(cin,numbers);
	if (numbers==""){
		cout<<"The list is empty!"<<endl;
	}
	else{

		istringstream str(numbers);
		int num;
		str>>num;
		SubSeqsList list;
		SubSeqNode *head=new SubSeqNode(num,NULL);
		SubSeqHeadNode *sHead= new SubSeqHeadNode(1,head,NULL);
		list.AddToList(sHead);
		cout<<"Subsequence(s) containing "<<num <<" has/have been added."<<endl;

		
		
		while (str>>num){
			if (num<0){
				int delnum=abs(num);//number to be deleted
				if (list.inList(delnum)){
					list.delFromList(delnum);//delete num from subsequences
					list.arrange(); //function to deal with the empty head nodes
					cout<<"Subsequence(s) containing "<<delnum <<" has/have been deleted."<<endl;
				}
				else{
					cout<<"There is no subsequence that contains "<<delnum<<" to be deleted."<<endl;
				}
			}
			else{
				if (list.inList(num)){
					cout<<num<<" is already in the list!"<<endl;
				}
				else{
						SubSeqNode *otherhead = new SubSeqNode(num,NULL);
						SubSeqHeadNode *otherhHead = new SubSeqHeadNode(1,otherhead,NULL);
						list.AddToList(otherhHead); //add the node to the list
						cout<<"Subsequence(s) containing "<<num <<" has/have been added."<<endl;
				}
			}
		}
		cout<<"FINAL CONTENT"<<endl;
		list.PrintList();
		list.deleteAll();
	}

	
	return 0;
}