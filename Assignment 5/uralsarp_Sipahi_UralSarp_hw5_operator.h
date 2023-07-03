#include <iostream>
#include <string>
#include <ostream>

using namespace std;


struct Money{
	string currency;
	double amount;
};


class Wallet{

private:
	Money *arr;
	int size;

public:
	Wallet(); //constructor
	Wallet(const Wallet &);  //deep copy constructor
	Wallet(int); //constructor with given size
	~Wallet(); //destructor
	Wallet operator+(const Money &) const; // + operator for 1 wallet 1 money object
	Wallet operator+(const Wallet &) const; // + operator for 2 wallet objects
	Wallet operator+=(const Wallet &);
	const Wallet & operator=(const Wallet &); // = operator
	Wallet operator-(const Money & rhs) const; // - operator

	int getSize() const;
	string getCurrency(int index) const;
	double getAmount(int index) const;
	
};


ostream &operator<<(ostream&out, const Wallet &rhs); // << operator
bool operator==(Wallet & lhs, Wallet & rhs); // == operator
bool operator >=(Wallet & lhs, Money rhs); // >= operator
bool operator <=(Money lhs, Wallet &rhs); // <= operator
