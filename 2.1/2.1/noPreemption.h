#pragma once
#include "thread.h"
#include <condition_variable>

std::mutex mutexQ;
std::condition_variable cv; 
bool ready = false;
/*
Using some of the std libaray defined data structures and functions I remove the no preemption condition required for deadlock.
Both thread are trying to acess mutexQ however, threadAA blocks threadBB until the variable ready == true. ThreadBB then stops 
running and waits for the signal from threadAA and then continues execution. Simply, both threads are running but I define the 
threads that threadAA can block threadBB, thus getting rid of the no preemption condition. 

*/

void ThreadAA() 
{
	std::cout << "Thread A \n";
	std::lock_guard<std::mutex> lock(mutexQ);
	std::cout << "Notifiying \n";
	cv.notify_one();
	ready = true; 
	std::cout << "Notifying again \n";
	cv.notify_one();

}

void ThreadBB()
{
	// Creates deadlock problem
	std::cout << "Thread B \n";
	std::unique_lock<std::mutex> lock(mutexQ);
	std::cout << "Thread B Waiting \n";
	cv.wait(lock, [] {return ready == true; });
	std::cout << "Thread B Finished Waiting \n";


}

//I prempt thread A buy using a condition variable which causes threadB to stall until
//the condition variable is modified in thread A
void ExecuteThreads_3()
{
	std::thread t1(ThreadAA); 
	//std::cout << "Wait \n";
	std::thread t2(ThreadBB);

	t1.join();
	t2.join();

	std::cout << "Finished" << std::endl;
}
/*
http://en.cppreference.com/w/cpp/thread/condition_variable
http://en.cppreference.com/w/cpp/thread/condition_variable/wait
http://en.cppreference.com/w/cpp/thread/lock_guard
http://en.cppreference.com/w/cpp/thread/unique_lock
*/