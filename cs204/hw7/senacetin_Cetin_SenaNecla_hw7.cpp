//Sena Necla Cetin 21120 CS204 HW7		May 12, 2017

#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <chrono>
#include <random>
#include <iomanip>
using namespace std;

mutex myMutex;
ifstream input;
ofstream output;
string ofile, ifile;
int minWaitW, maxWaitW, minWaitD, maxWaitD, countW, countD, balance=0;

// Generates random numbers in a thread-safe manner in the range  (min, max).
int random_range(const int & min, const int & max)
{
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min,max);
	return distribution(generator);
}

void withdraw(int threadID)
{
	this_thread::sleep_for(chrono::seconds(random_range(minWaitW, maxWaitW)));

	for(int i=0; i<countW; i++)
	{
		input >> balance;
		if(balance > 0)
		{
			balance--;
			output << balance;
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout << "Withdrawal thread "<< threadID << " successfully withdrawn 1 TL; balance is "<< balance << ", " << put_time(ptm,"%X") << endl;
		}
		else
		{
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout << "Withdrawal thread " << threadID << " failed to withdraw 1 TL; balance is " << balance << ", " << put_time(ptm,"%X") << endl;
		}
	}
}

void deposit()
{
	this_thread::sleep_for(chrono::seconds(random_range(minWaitD, maxWaitD)));
	input >> balance;
	balance++;
	output << balance;
	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	struct tm *ptm = new struct tm; 
	localtime_s(ptm, &tt); 
	cout << "1 TL has been deposited: balance is " << balance << ", " << put_time(ptm,"%X") << endl;
}

int main()
{
	cout << "Please, enter file name in which balance will be stored:\n";
	cin >> ofile;
	output.open(ofile);
	output << balance;
	cout << "Please, enter min and max waiting times between withdrawal transactions per thread (in seconds):\n";
	cin >> minWaitW >> maxWaitW;
	cout << "Please, enter min and max waiting times between deposit transactions (in seconds):\n";
	cin >> minWaitD >> maxWaitD;
	cout << "Please enter the total number of withdrawal transactions per thread:\n";
	cin >> countW;
	cout << "Please enter the total number of deposit transactions:\n";
	cin >> countD;

	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	struct tm *ptm = new struct tm; 
	localtime_s(ptm, &tt); 
	cout << "Simulation starts at " << put_time(ptm,"%X") << endl;

	thread thr0(deposit);
	thread thr1(withdraw, 0);
	thread thr2(withdraw, 1);
	thread thr3(withdraw, 2);

	thr0.join();
	thr1.join();
	thr2.join();
	thr3.join();

	tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	localtime_s(ptm, &tt); 
	cout << "Simulation ends at " << put_time(ptm,"%X") << endl;

	input.close();
	output.close();

	cin.get();
	cin.ignore();
	return 0;
}
