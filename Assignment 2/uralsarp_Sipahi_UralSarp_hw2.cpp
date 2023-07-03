#include <iostream>
#include <sstream>
#include <string>


using namespace std;

struct node{

	int value;
	node* next;
	node::node() //default constructor
	{ 
	}
	node::node(int n, node * p) //constructor with 2 parameters
		   : value(n),next(p)
	{};

};
/* Begin: code taken from ptrfunc.cpp (updated slightly) */ 
void DisplayList (node * head){
	
	node * temp = head;
    while (temp != NULL) {
		cout << temp ->value << " ";
		temp = temp->next;
	}
	cout << endl;
}
/* End: code taken from ptrfunc.cpp */ 

bool inList(node * head,int num){ //function to check if the number is already in the list.

	node * temp = head;
    while (temp != NULL) {
		if (temp->value == num){
			return true;
		}
		temp = temp->next;
	}
	return false;

}

/* Begin: code taken from 2.2-pointers-linkedlists lecture slide */
void deleteAllNode (node * head){
	node *temp;				
	while (head != NULL){				
      temp = head->next;			
      delete head;
      head = temp;
	}

}
/* End: code taken from 2.2-pointers-linkedlists lecture slide */ 

/* Begin: code taken from ptrfunc.cpp */ 
void DeleteOneNode (node * toBeDeleted, node * & head)
/* pre: toBeDeleted points to the node to be deleted from the list
   post: deletes the node pointed by toBeDeleted, updates head if changes */
{
	node * ptr;
		
	if (toBeDeleted == head)  //if the node to be deleted is the first node
	{
		head = head->next;
		delete toBeDeleted;
	}
	else  //if the node to be deleted is in the middle or at the end
	{
		ptr = head;
		while (ptr->next != toBeDeleted)
			ptr = ptr->next;
		//after while ptr point to the node just before toBeDeleted

		//connect the previous node to the next node and delete
		ptr->next = toBeDeleted->next;
		delete toBeDeleted;
	}
}
/* End: code taken from ptrfunc.cpp */ 

int main(){

	string line,mode;
	cout<<"Please enter the order mode (A/D): ";
	getline(cin,line);
	istringstream strstream(line);
	strstream>>mode; //getting the first string of the line

	while (mode!="A" && mode!="D"){
		cout<<"Please enter the order mode again (A/D): ";
		getline(cin,line);
		istringstream strstream(line);
		strstream>>mode;
		mode;
	}

	string numbers;
	cout<<"Please enter the numbers in a line: ";
	getline(cin,numbers);
	if (numbers==""){
		cout<<"The list is empty at the end of the program and nothing is deleted"<<endl;
	}

	istringstream str(numbers);
	int num;

	str>>num;
	node *head=new node(num,NULL);
	node *temp;
	cout<<endl;

	cout<<"Next number is: "<<num<<endl;
	cout<<"Deleted nodes: None"<<endl;
	cout<<"Appended: "<<num<<endl;
	cout<<"List content: ";
	DisplayList(head);

	if (mode=="A"){

		while (str>>num){
			cout<<endl;
			cout<<"Next number: "<<num<<endl;
			if (num < head->value){
				cout<<"Deleted nodes: ";
				DisplayList(head); // displays the values before the num
				deleteAllNode(head->next); // delete all the nodes except the head
				head->value=num; //change head node's value
				head->next=NULL;
				cout<<"Appended: "<<num<<endl;
				cout<<"List content: ";
				DisplayList(head);
			}
			else if (inList(head,num)){
				cout<<num<<" is already in the list!"<<endl;
				cout<<"List content: ";
				DisplayList(head);
			}
			else{
				temp=head;
				while ((temp->next!=NULL) && (temp->next->value < num)){
					temp=temp->next;
				}
				if ((temp->next!=NULL) && (temp->next->value >= num)){
					cout<<"Deleted nodes: ";
					cout<<temp->next->value<<endl; //print the node to be deleted which comes just before the num's node
					DeleteOneNode(temp->next,head); //delete the node
				}
				else{
					cout<<"Deleted nodes: None"<<endl;
				}
				temp->next=new node(num,NULL);
				cout<<"Appended: "<<num<<endl;
				cout<<"List content: ";
				DisplayList(head);
			}
		}
		cout<<endl;
		cout<<"All the nodes are deleted at the end of the program: ";
		DisplayList(head);
		deleteAllNode(head);
		
	}
	
	if (mode=="D"){
		while (str>>num){
			cout<<endl;
			cout<<"Next number: "<<num<<endl;

			if (num > head->value){
				cout<<"Deleted nodes: ";
				DisplayList(head); // displays the values before the num
				deleteAllNode(head->next); // delete all the nodes except the head
				head->value=num; //change head node's value
				head->next=NULL;
				cout<<"Appended: "<<num<<endl;
				cout<<"List content: ";
				DisplayList(head);
			}

			else if(inList(head,num)){
				cout<<num<<" is already in the list!"<<endl;
				cout<<"List content: ";
				DisplayList(head);
			}

			else{
				temp=head;
				while (temp->next != NULL && temp->next->value > num){ 
					temp=temp->next;
				}
				if ((temp->next!=NULL) && (temp->next->value <= num)){ 
					cout<<"Deleted nodes: ";
					cout<<temp->next->value<<endl; //print the node to be deleted which comes just before the num's node
					DeleteOneNode(temp->next,head); //delete the node
				}
				else{
					cout<<"Deleted nodes: None"<<endl;
				}
				temp->next=new node(num,NULL);
				cout<<"Appended: "<<num<<endl;
				cout<<"List content: ";
				DisplayList(head);
			}

		}
		cout<<endl;
		cout<<"All the nodes are deleted at the end of the program: ";
		DisplayList(head);
		deleteAllNode(head);
	}
	return 0;
}