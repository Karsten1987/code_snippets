#include <stdio.h>
#include <iostream>

class A
{

	protected:
	int state_;
	
	public:
	A(): state_(0)
	{
		std::cerr << "default constructor" << std::endl;
	}

	int getState() const
	{
		std::cerr << "getstate in A " << std::endl;
		return state_;
	}

	virtual void setState(int i)
	{
		state_ = i;
	}

	void operator+ (int i)
	{
		state_ += i;
		std::cerr << "new state now: " << state_ << std::endl;
	}
};

class B : public A
{
	public:
	B()
	{
		std::cerr << "new b is initialized" << std::endl;
	}

	int getState() const
	{
		std::cerr << "this is get state from b" << std::endl;
		return state_; 
	}
};

int main()
{
	A a_inst;
	a_inst.getState();
	
	B b_inst;
	A* p_a = &b_inst;
	p_a->getState();
	
}


