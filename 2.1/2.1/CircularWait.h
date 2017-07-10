#pragma once
#include "thread.h"

std::mutex mtx1, mtx2, mtx3;

/*
This file elminate the circular wait condition required for deadlock. I require all threads to grab resources in an
increasing order (mtx1->mtx2->mtx3). Since all threads have this restriction, deadlock is removed.
*/
void Thread_1()
{
	// Solves deadlock problem
	mtx1.lock();
	mtx2.lock();
	mtx3.lock();
	std::cout << "Thread_1 doing work" << std::endl;
	mtx3.unlock();
	mtx2.unlock();
	mtx1.unlock();
}

void Thread_2()
{
	mtx1.lock();
	mtx2.lock();
	mtx3.lock();
	std::cout << "Thread_2 doing work" << std::endl;
	mtx3.unlock();
	mtx2.unlock();
	mtx1.unlock();
}

void Thread_3()
{
	mtx1.lock();
	mtx2.lock();
	mtx3.lock();
	std::cout << "Thread_3 doing work" << std::endl;
	mtx3.unlock();
	mtx2.unlock();
	mtx1.unlock();

}

void ExecuteThreads_4()
{
	std::thread t1(Thread_1);
	std::thread t2(Thread_2);
	std::thread t3(Thread_3); 

	t1.join();
	t2.join();
	t3.join();

	std::cout << "Finished" << std::endl;
}
#pragma once
