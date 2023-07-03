#include <iostream>
#include "uralsarp_Sipahi_UralSarp_hw5_operator.h"


using namespace std;

// constructor
Wallet::Wallet(){ //constructor
	size = 0;
	arr = NULL;
}

Wallet::Wallet(const Wallet & copy){ //deep copy constructor
	size = copy.size;
	arr = new Money[size]; // deep copy

	for(int i = 0; i < size; i++){
		arr[i].amount = copy.arr[i].amount;
		arr[i].currency = copy.arr[i].currency;
	}
}

Wallet::Wallet(int psize){ // constructor with size parameter
	arr = new Money[psize];
	size = psize;
}


Wallet::~Wallet(){ //destructor
	size = 0;
	delete[] arr;
}


Wallet Wallet::operator+(const Money & rhs) const{ // + operator

	if (size==0){ // if the wallet is empty
		Wallet copy(size+1);
		copy.arr[0].amount=rhs.amount;
		copy.arr[0].currency=rhs.currency;

		return copy;
	}
	else{
		Wallet copy(*this);

		bool inWallet=false;

		for (int i=0; i<copy.size;i++){
			if (rhs.currency==copy.arr[i].currency){
				copy.arr[i].amount+=rhs.amount;
				inWallet=true; 
			}
		}

		if (inWallet==false){ // if the currency is not in the wallet already
			Wallet othercopy(size+1); //create new object with the size of the existing wallet + 1 in order to add the money object
			for (int i=0;i<size;i++){
				othercopy.arr[i].amount=copy.arr[i].amount; //copy lhs's content into othercopy
				othercopy.arr[i].currency=copy.arr[i].currency;
			}
			othercopy.arr[size].amount=rhs.amount; //add the money object to the end of the othercopy object
			othercopy.arr[size].currency=rhs.currency;

			
			return othercopy;
		}

		return copy;
	}
	
}
Wallet Wallet::operator+(const Wallet & rhs) const{ // + operator
	Wallet copy(*this); //make a copy of the lhs

	int totalsize=copy.size+rhs.size;
	int same=0; //counter for the amount of the same currencies

	for (int i=0; i<copy.size; i++){ //deal with the matching currencies first
		for (int j=0; j<rhs.size; j++){
			if (copy.arr[i].currency==rhs.arr[j].currency){ //if there is a currency in both wallets add them up together in the copy
				copy.arr[i].amount=copy.arr[i].amount+rhs.arr[j].amount; //add the matching currencies up inside the copy object
				same++;
			}
		}
	}
	int newsize;
	newsize=totalsize-same;
	Wallet newcopy(newsize); //generate a new copy with the size of the wallet to be returned

	for (int i=0; i<copy.size; i++){ // copy the "copy" of lhs to the newcopy that will be returned at the end of the function
		newcopy.arr[i].currency=copy.arr[i].currency;
		newcopy.arr[i].amount=copy.arr[i].amount;
	}
	
	int copysize=copy.size;
	for (int i=0; i<rhs.size; i++){
		bool notIn=true;
		for (int j=0; j<copysize; j++){
			if (rhs.arr[i].currency==newcopy.arr[j].currency){
				notIn=false;
			}
		}
		if (notIn==true){
			newcopy.arr[copysize].amount=rhs.arr[i].amount;
			newcopy.arr[copysize].currency=rhs.arr[i].currency;
			copysize++;
		}
	}

	return newcopy;
}

Wallet Wallet::operator+=(const Wallet & rhs){

	Wallet copy(*this); //make a copy of the lhs

	int totalsize=copy.size+rhs.size;
	int same=0; //counter for the amount of the same currencies

	for (int i=0; i<copy.size; i++){ //deal with the matching currencies first
		for (int j=0; j<rhs.size; j++){
			if (copy.arr[i].currency==rhs.arr[j].currency){ //if there is a currency in both wallets add them up together in the copy
				copy.arr[i].amount=copy.arr[i].amount+rhs.arr[j].amount; //add the matching currencies up inside the copy object
				same++;
			}
		}
	}
	int newsize;
	newsize=totalsize-same; //subtract the matching currencies
	Wallet newcopy(newsize); //generate a new copy with the size of the wallet to be returned

	for (int i=0; i<copy.size; i++){ // copy the "copy" of lhs to the newcopy that will be returned at the end of the function
		newcopy.arr[i].currency=copy.arr[i].currency;
		newcopy.arr[i].amount=copy.arr[i].amount;
	}
	
	int copysize=copy.size;
	for (int i=0; i<rhs.size; i++){
		bool notIn=true;
		for (int j=0; j<copysize; j++){
			if (rhs.arr[i].currency==newcopy.arr[j].currency){
				notIn=false;
			}
		}
		if (notIn==true){ //add the rhs's unique wallet items to lhs (the ones that do not match)
			newcopy.arr[copysize].amount=rhs.arr[i].amount;
			newcopy.arr[copysize].currency=rhs.arr[i].currency;
			copysize++;
		}
	}

	delete [] arr;
	size=newsize;
	arr=new Money [size];

	for (int i=0; i<size ; i++){ 
		arr[i].amount=newcopy.arr[i].amount;
		arr[i].currency=newcopy.arr[i].currency;
	}

	return *this;
}


const Wallet & Wallet::operator=(const Wallet &rhs){ // = operator
	if (this != &rhs){ //if both objects are not the same
		size=0;
		delete[] arr; //delete lhs

		size = rhs.size;
		arr = new Money[size];

		for (int i=0; i<size; i++){
			arr[i].amount=rhs.arr[i].amount; //put rhs's amount to lhs
			arr[i].currency=rhs.arr[i].currency; //put rhs's currencies to lhs
		}
	}
	return *this;
}




Wallet Wallet::operator-(const Money & rhs) const{

	Wallet copy(*this);

	bool isZero=false;
	for (int i=0; i<size ; i++){
		if (copy.arr[i].currency==rhs.currency && copy.arr[i].amount>=rhs.amount){ // if lhs and rhs's currencies are the same and rhs's value is smaller or equal to lhs's subtract.
			copy.arr[i].amount=copy.arr[i].amount-rhs.amount;
			if (copy.arr[i].amount==0){ // if there is a currency with 0 value
				isZero=true;
			}
		}	
	}

	if (isZero==true){ // if there is a currency with 0 value
		Wallet othercopy(size-1); //create new object with the size of the existing wallet - 1 in order to subtract the money object with 0 amount
		int j=0;
		for (int i=0;i<size;i++){
			if (copy.arr[i].amount!=0){
				othercopy.arr[j].amount=copy.arr[i].amount; //copy lhs's content into othercopy
				othercopy.arr[j].currency=copy.arr[i].currency;
				j++;
			}
		}

		return othercopy;
	}

	return copy;
}

ostream &operator<<(ostream&out, const Wallet &rhs){
	for (int i=0;i<rhs.getSize();i++){
		if (i!=rhs.getSize()-1)
			out<<rhs.getCurrency(i)<<" "<<rhs.getAmount(i)<<" - ";
		else
			out<<rhs.getCurrency(i)<<" "<<rhs.getAmount(i);
	}
	return out;
}



bool operator==(Wallet & lhs, Wallet & rhs){
	bool notFound=true;
	if (lhs.getSize()==rhs.getSize()){  
		for (int i=0; i<lhs.getSize(); i++){
			for (int j=0; j<rhs.getSize(); j++){
				if ((lhs.getCurrency(i)==rhs.getCurrency(j)) && (lhs.getAmount(i)==rhs.getAmount(j))){ //if the rhs's currency exists in the lhs
					notFound=false;
				}
			}
			if (notFound==true){
				return false;
			}
			else
				continue;
		}
	}
	else{   //if lhs and rhs's size is not the same return false
		return false;
	}
}

bool operator >=(Wallet & lhs, Money rhs){
	bool notFound=true; //if the currency exists in the wallet or not
	for (int i=0; i<lhs.getSize();i++){ 
		if (lhs.getCurrency(i)==rhs.currency){
			notFound=false; //currency exists in the wallet
			if(lhs.getAmount(i)>=rhs.amount){ 
				return true;
			}
			else{
				return false;
			}
		}
	}
	if (notFound==true){ //if currency does not exist in the wallet
		return false;
	}
	else
		return true;
}


bool operator <=(Money lhs, Wallet &rhs){
	bool notFound=true; //if the currency exists in the wallet or not
	for (int i=0; i<rhs.getSize();i++){ 
		if (rhs.getCurrency(i)==lhs.currency){
			notFound=false; //currency exists in the wallet
			if(lhs.amount<=rhs.getAmount(i)){
				return true;
			}
			else{
				return false;
			}
		}
	}
	if (notFound==true){ //if currency does not exist in the wallet
		return false;
	}
	else 
		return true;
}

int Wallet::getSize() const{ //function to return the Wallet objects size
	return size;
}

double Wallet::getAmount(int index) const{
	return arr[index].amount;

}

string Wallet::getCurrency(int index) const{
	return arr[index].currency;

}