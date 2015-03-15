#include <stdio.h>
#include <iostream>
#include <boost/shared_ptr.hpp>

class A
{
	public:
	int m_int;
	int* p_int;
	boost::shared_ptr<int> boost_int;

	A(){}

	A(int i):
	m_int(i),
	p_int(new int[2]),
	boost_int(new int(i))
	{
		p_int[0] = i;
		p_int[1] = i*2;
		std::cerr << "concrete constructor" << std::endl;
	}

	void print_me(std::string prefix) const
	{
		std::cerr << "****************" << prefix << " ***********" << std::endl;
		std::cerr << prefix << " m_int " << m_int << std::endl;
		std::cerr << prefix << " p_int0 " << p_int[0] << std::endl;
		std::cerr << prefix << " p_int1 " << p_int[1] << std::endl;
		std::cerr << prefix << " boost_int " << *boost_int << std::endl;
	} 

};

int main()
{

	// base init
	A my_a(2);

	// assignment operator
	A my_b;
	my_b = my_a;

	// copy constructor
	A my_c = my_a;

	// delete init
	//delete[]  my_a.p_int;
	//my_a.p_int = NULL;

	my_a.print_me("my_a");
	my_b.print_me("my_b");
	my_c.print_me("my_c");

	// change base class
	my_a.m_int = 30;
	my_a.p_int[1] = 30 ;
	my_a.boost_int = boost::shared_ptr<int>(new int(30));


	my_a.print_me("my_a");
	my_b.print_me("my_b");
	my_c.print_me("my_c");


}



