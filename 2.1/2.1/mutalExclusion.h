#pragma once
#include "thread.h"
#include <string>
/*
As described in the textbook, reading files is an operation that does require a thread to have exclusive access
to the data, which would then remove the mutal exclusion condition for deadlock. This file creates to read-only threads
and has both thread read from a file; since both threads are defined as read-only, no mutuex locks are needed and the
mutal exclusion condition is removed. 

*/

void ThreadY() //read only thread
{
	std::ifstream read;
	std::string out; 
	std::cout << "Thread A \n" << std::endl;
	read.open("example.txt");
	while (!read.eof())
	{
		std::getline(read, out);
		std::cout << out;
		std::cout << "\n";
	}
}

void ThreadZ() //another read only thread
{
	std::ifstream read;
	std::string out;
	std::cout << "Thread B \n" << std::endl;
	read.open("example.txt");
	while (!read.eof())
	{
		std::getline(read, out);
		std::cout << out;
		std::cout << "\n";
	}

}

void ExecuteThreads_1()
{
	std::thread t1(ThreadY);
	std::thread t2(ThreadZ);

	t1.join();
	t2.join();

	std::cout << "Finished" << std::endl;
}