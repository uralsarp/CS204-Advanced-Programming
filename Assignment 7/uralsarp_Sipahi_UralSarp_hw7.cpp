#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <random>
#include <time.h>
#include "uralsarp_Sipahi_UralSarp_hw7_HW7DynIntQueue.h"


using namespace std;

HW7DynIntQueue fillingQueue;
HW7DynIntQueue packagingQueue;

mutex myMutex, myMutex2, coutMutex;

int packed=0; //tracker for the number of boxes packed
int filled=0; //tracker for the number of boxes filled

int random_range(const int & min, const int & max) {
    static mt19937 generator(time(0));
    uniform_int_distribution<int> distribution(min,max);
    return distribution(generator);
}

void producer(int total_box_count,int min, int max){


	for(int i = 1; i <= total_box_count ; i++){

		coutMutex.lock();
		int incremented = random_range(min, max); //generate a random waiting time to sleep the thread
		coutMutex.unlock();

		this_thread::sleep_for(chrono::seconds(incremented)); //sleep the thread
		int qSize; //queue's current size
		myMutex.lock();
		if (fillingQueue.getCurrentSize()<total_box_count){  
			fillingQueue.enqueue(i); //put boxes into the filling queue
			qSize=fillingQueue.getCurrentSize(); //take queue's current size
			myMutex.unlock();


			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 

			coutMutex.lock();
			cout <<"Producer has enqueued a new box "<< i << " to filling queue (filling queue size is "<<qSize<<"): "<< put_time(ptm,"%X") <<endl;
			coutMutex.unlock();

		}
		else{
			myMutex.unlock();
			i--;
		}
	}
}

void filler(int consId,int total_box_count, int min, int max){
	int item;

	while (filled<total_box_count){

		coutMutex.lock();
		int incremented = random_range(min, max); //generate a random waiting time to sleep the thread
		coutMutex.unlock();

		int qSize; //queue's current size
		myMutex.lock();
		if (!fillingQueue.isEmpty()){  
			fillingQueue.dequeue(item); //fill the boxes 
			filled++;
			qSize=fillingQueue.getCurrentSize(); //take filling queue's current size
			myMutex.unlock();

			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 

			coutMutex.lock();
			cout <<"Filler "<< consId << " started filling the box "<<item<<" (filling queue size is "<< qSize<<"): "<< put_time(ptm,"%X") <<endl;
			coutMutex.unlock();

			this_thread::sleep_for(chrono::seconds(incremented)); //sleep the thread

			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			localtime_s(ptm, &tt); 

			coutMutex.lock();
			cout <<"Filler "<< consId << " finished filling the box "<<item<<": "<< put_time(ptm,"%X") <<endl;
			coutMutex.unlock();	

			int qSize2;
			myMutex2.lock();
			if (packagingQueue.getCurrentSize()<total_box_count){
				packagingQueue.enqueue(item);  //put the filled boxes into the packaging queue
				qSize2=packagingQueue.getCurrentSize(); //take packaging queue's current size
				myMutex2.unlock();

				coutMutex.lock();
				cout <<"Filler "<< consId << " put box "<<item<<" into packaging queue (packaging queue size is "<< qSize2<<"): "<< put_time(ptm,"%X") <<endl;
				coutMutex.unlock();
			}
			else{
				myMutex2.unlock();
			}	
			
		}
		else{
			myMutex.unlock();
		}
	}

}

void packager(int consId,int total_box_count, int min, int max){

	int item;
	while (packed<total_box_count){

		coutMutex.lock();
		int incremented = random_range(min, max); //generate a random waiting time to sleep the thread
		coutMutex.unlock();

		int qSize; //queue's current size
		myMutex.lock();
		if (!packagingQueue.isEmpty()){  
			packagingQueue.dequeue(item);  //pack the boxes
			packed++;
			qSize=packagingQueue.getCurrentSize();
			myMutex.unlock();

			
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 

			coutMutex.lock();
			cout <<"Packager "<< consId << " started packaging the box "<<item<<" (packaging queue size is "<< qSize<<"): "<< put_time(ptm,"%X") <<endl;
			coutMutex.unlock();

			this_thread::sleep_for(chrono::seconds(incremented)); //sleep the thread

			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			localtime_s(ptm, &tt); 

			coutMutex.lock();
			cout <<"Packager "<< consId << " finished packaging the box "<<item<<": "<< put_time(ptm,"%X") <<endl;
			coutMutex.unlock();
		}
		else{
			myMutex.unlock();
		}
	}	
	
}


int main(){
	int total_box_count;
	cout<<"Please enter the total number of items: ";
	cin>>total_box_count;

	int min_production, max_production; //producer range
	cout<<"Please enter the min-max waiting time range of producer: "<<endl;
	cout<<"Min: ";
	cin>>min_production;
	cout<<"Max: ";
	cin>>max_production;

	int min_filling_time, max_filling_time; //filler range
	cout<<"Please enter the min-max waiting time range of filler workers: "<<endl;
	cout<<"Min: ";
	cin>>min_filling_time;
	cout<<"Max: ";
	cin>>max_filling_time;

	int min_packaging_time, max_packaging_time; //packager range
	cout<<"Please enter the min-max waiting time range of packager workers: "<<endl;
	cout<<"Min: ";
	cin>>min_packaging_time;
	cout<<"Max: ";
	cin>> max_packaging_time;


	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	struct tm *ptm = new struct tm; 
	localtime_s(ptm, &tt); 
	cout <<"Simulation starts "<< put_time(ptm,"%X") <<endl; //this code block displays the starting time of simulation


	thread thr0(producer, total_box_count,min_production,max_production);
	thread thr1(filler, 1, total_box_count, min_filling_time, max_filling_time); //1st filler thread
	thread thr2(filler, 2, total_box_count, min_filling_time, max_filling_time); //2nd filler thread
	thread thr3(packager, 1, total_box_count, min_packaging_time, max_packaging_time); //1st packager thread
	thread thr4(packager, 2, total_box_count, min_packaging_time, max_packaging_time); //2nd packager thread

	thr0.join();
	thr1.join();
	thr2.join();
	thr3.join();
	thr4.join();

	tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	localtime_s(ptm, &tt); 
	cout <<"Simulation ends: "<< put_time(ptm,"%X") <<endl; //this code block displays the ending time of simulation

	return 0;
}