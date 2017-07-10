#include "thread.h"
/*
thread.h create a deadlock because threadA and threadB are holding locks that each other want.
This file outlines how to get rid of deadlock through the elimination of the hold and wait condition.
Now that the locks are in order ABBA and ABAB, whichever thread begins execution will run to completion before
the next thread can begin; thus, no thread will ever be waiting for a resource when it is holding a resource that
another thread is waiting for


*/
std::mutex mutexA, mutexB;
void Thread1()
{
	// Solves deadlock problem
	mutexA.lock();
	std::cout << "Thread A" << std::endl;
	mutexB.lock();
	mutexB.unlock();
	mutexA.unlock();
}

void Thread2()
{
	// Solves deadlock problem
	mutexA.lock();
	std::cout << "Thread B" << std::endl;
	mutexB.lock();
	mutexA.unlock();
	mutexB.unlock();
}

void ExecuteThreads_2()
{
	std::thread t1(Thread1);
	std::thread t2(Thread2);

	t1.join();
	t2.join();

	std::cout << "Finished" << std::endl;
}
#pragma once
