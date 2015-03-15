#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <cstdlib>
#include <stdio.h>

boost::mutex			m_add;
boost::mutex			m_print;
boost::mutex			m_cond;
boost::condition_variable 	active_workers;
int				active_workers_count;
int				state = 0;
const int			state_boundary = 1020;

void add_random(int name)
{
	active_workers_count +=1;
	std::cout << "init: " << name << std::endl;
	int contribution = 0;
	
	while(state < state_boundary)
	{
		//int random = rand() % 100;
		m_add.lock();
		int random = 1;
		state += random;
		contribution += random;
		m_add.unlock();
		usleep(1000);
	}
	m_print.lock();
	std::cout << name << " contrib: " << contribution << std::endl;
	m_print.unlock();
	active_workers_count -= 1;
}

void print_result(int name)
{
	boost::mutex::scoped_lock lock(m_cond);
	while(active_workers_count > 0)
	{
		active_workers.wait(lock);
	}
	m_print.lock();
	std::cerr << name << " result: " << state << std::endl;
	m_print.unlock();
}

int main()
{

	boost::thread_group adder_threads;
	for (int i = 0; i < 10; ++i)
	{
		adder_threads.create_thread(boost::bind(add_random, i));
	}

	boost::thread_group printer_threads;
	for (int i = 0; i < 2; ++i)
	{
		std::string name = "result"+i;
		printer_threads.create_thread(boost::bind(print_result,i));
	}
	
	adder_threads.join_all();
	active_workers.notify_all();

	printer_threads.join_all();

	return 0;
}
