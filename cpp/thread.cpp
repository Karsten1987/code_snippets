#include <boost/thread.hpp>

boost::mutex	m_write;
boost::mutex 	m_read;
int 		state;

void readerApi(std::string name)
{
	while(true)
	{
	m_read.lock();
	if (state % 2 ==0)
	{
		std::cout << name <<" cool:" << state << std::endl;
	}
	else
	{
		std::cout <<name << " wrong:" << std::endl;
	}
	m_read.unlock();
	usleep(100000);
	}

}
void writerApi(std::string name)
{
	while(true)
	{
		m_write.lock();
		state++;
		usleep(10000);
		state++;	
		usleep(100000);
		m_write.unlock();
	}
}

int main()
{
	state = 0;

	boost::thread readerThread1(readerApi, "reader1");
	boost::thread readerThread2(readerApi, "reader2");
	boost::thread writerThread1(writerApi, "writer1");
	boost::thread writerThread2(writerApi, "writer2");


	std::cout << boost::thread::hardware_concurrency() << std::endl;	
	
	readerThread1.join();
	readerThread2.join();
	writerThread1.join();
	writerThread2.join();

	return 0;  
}

