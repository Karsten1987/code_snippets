#include <stdio.h>
#include <boost/thread.hpp>
#include <cstdlib>
#include <queue>

std::queue<int> queue;
boost::mutex m_queue;
boost::condition_variable cond_queue_empty;

const int MAX_ITERATION = 100000;
const int MAX_QUEUE_SIZE = 10000;


void producer()
{
	for (int i = 0; i <= MAX_ITERATION; ++i)
	{
		int random = rand() % 100;
		queue.push(random);
		cond_queue_empty.notify_one();
	}
	std::cerr << "finished pushing " << std::endl;
}

void consumer()
{
	boost::mutex::scoped_lock lock(m_queue);
	for (int i = 0; i<= MAX_ITERATION; ++i)
	{
		while(queue.empty() == true)
		{
			cond_queue_empty.wait(lock);		
		}
		int value = queue.front();
		queue.pop();
		std::cerr << "popped: " << value << std::endl;
	}
}


int main()
{	
	boost::thread producer1(producer);
	boost::thread producer2(producer);

	boost::thread consumer1(consumer);
	boost::thread consumer2(consumer);
	boost::thread consumer3(consumer);
	
	producer1.join();
	producer2.join();
	
	consumer1.interrupt();
	consumer2.interrupt();
	consumer3.interrupt();
	
	return 0;
}
