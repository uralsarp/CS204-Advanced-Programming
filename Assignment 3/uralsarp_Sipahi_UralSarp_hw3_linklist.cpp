#include <iostream>
#include "uralsarp_Sipahi_UralSarp_hw3_linklist.h"
using namespace std;

SubSeqsList::SubSeqsList(){
	int garbage=1;
	hHead=new SubSeqHeadNode (garbage,NULL,NULL);
}

void SubSeqsList::delFromList(int num){ //If a number occurs in a list find its corresponding SubSeqNode and delete its SubSeqNode assign it to NULL. With another function (arrange()) its SubSeqHeadNode will be deleted as well.
	if (hHead->next != NULL){
		SubSeqHeadNode *temp = hHead->next;
		while (temp!=NULL){
			SubSeqNode *stemp = temp->sHead;
			while (stemp!=NULL){
				if (stemp->value==num){
					delete stemp;
					temp->sHead=NULL; //delete the SubSeqNode then assign SubSeqHeadNode to NULL. (assign() function will take care of the SubSeqHeadNode's pointing to NULL.)
					break; 
				}
				stemp=stemp->next;

			}
			temp=temp->next;
		}
	}
	
	else{
		 cout << "List is empty!" << endl;
    }
}

void SubSeqsList::arrange(){ //Delete the SubSeqHeadNode which is not connected to any SubSeqNode.
	if (hHead->next != NULL){
		SubSeqHeadNode *ptr=hHead;
		while (ptr->next->sHead != NULL){
			ptr=ptr->next;
		}
		SubSeqHeadNode*temp=ptr->next;
		ptr->next=ptr->next->next;
		delete temp;
		
	}
}

void SubSeqsList::AddToList(SubSeqHeadNode *p){ //add the SubSeqHeadNode to the list
	if (hHead->next==NULL){
		hHead->next = p;
	}
	else{
		bool check=false; //check if the node has been added in the middle of the list.
		SubSeqHeadNode *temp = hHead;
		while (temp->next!=NULL){
			if (temp->next->sHead->value > p->sHead->value && check==false){ //sort the nodes 
				p->next=temp->next;
				temp->next=p;
				check=true;
			}
			temp=temp->next;
		}
		if (check==false){
			temp->next=p;
		}
	}
}

void SubSeqsList::PrintList(){ //prints the data structure
	if (hHead->next != NULL){
		SubSeqHeadNode *temp = hHead->next;
		while (temp!=NULL){
			cout<<temp->size<<"|";
			SubSeqNode *stemp = temp->sHead;
			while (stemp!=NULL){
				if (stemp->next != NULL){
					cout<<stemp->value;
					cout<<"-->";
				}
				else{
					cout<<stemp->value<<endl;
				}
				stemp=stemp->next;
			}
			temp=temp->next;
		}
	}
    else{
        cout << "List is empty!" << endl;
    }
}

bool SubSeqsList::inList(int num){ //function to check if a particular number is in the data structure or not
	if (hHead->next != NULL){
		SubSeqHeadNode *temp = hHead->next;
		while (temp!=NULL){
			SubSeqNode *stemp = temp->sHead;
			while (stemp!=NULL){
				if (stemp->value==num){
					return true;
				}
				stemp=stemp->next;
			}
			temp=temp->next;
		}
		return false;
	}
    else{
        return false;
    }

}
/*void SubSeqsList::updateList(int num){
	if (hHead->next != NULL){
		SubSeqHeadNode *temp = hHead->next;
		SubSeqNode *nnum = new SubSeqNode(num,NULL);
		while (temp!=NULL){
			SubSeqNode *stemp = temp->sHead;
			while (stemp!=NULL){
				if (stemp->next == NULL && stemp->value<num){
					SubSeqHeadNode *clonehead=clone(temp,nnum);
				}
				stemp=stemp->next;
			}
			temp=temp->next;
		}
	
	}
	
}
*/
/*
SubSeqHeadNode * SubSeqsList::clone(SubSeqHeadNode *p,SubSeqNode *nnum) const{
	
	SubSeqHeadNode* headClone = new SubSeqHeadNode (p->size,p->sHead,NULL);
	SubSeqNode* ptr = p->sHead;
	SubSeqHeadNode* ptrClone = headClone;
	while (ptr!=NULL){
		ptrClone->sHead= new SubSeqNode(ptr->value,NULL);
		ptr=ptr->next;
		ptrClone->sHead=ptrClone->sHead->next;
	}
	while (ptrClone->sHead!=NULL && ptrClone->sHead->next!=nnum){
		if (ptrClone->sHead->next==NULL){
			ptrClone->sHead->next=nnum;
		}
		else{
			ptrClone->sHead=ptrClone->sHead->next;
		}
	}
	return ptrClone;
}
*/

void SubSeqsList::deleteAll(){
	if (hHead->next != NULL){
		while (hHead->next!=NULL){
			SubSeqHeadNode *temp=hHead;
			SubSeqHeadNode *ttemp=hHead->next;
			while (ttemp->sHead!=NULL){
				SubSeqNode *stemp = ttemp->sHead;
				ttemp->sHead=ttemp->sHead->next;
				delete stemp;
			}
			hHead=hHead->next;
			delete temp;
		}
	}
}