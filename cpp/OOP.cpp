#include<stdio.h>
#include<iostream>


template< class T>
class AbstractClass
{

	public:

	T value_;

	AbstractClass(T value):
	value_(value)
	{
		std::cerr << "constructor in abstract class " << std::endl;
	}

	virtual ~AbstractClass() {}


	T getValue() const
	{
		std::cerr << "getter in abstract class " << std::endl;
		return this->value_;
	}

	virtual void setValue(T value) = 0;


};


template< class T>
class ConcreteClass : public AbstractClass<T>
{
	public:
	ConcreteClass(T value): AbstractClass<T>(value)
	{
		std::cerr << "constructor in concrete class " << std::endl;
	}
	
	~ConcreteClass() {
		//this->value_ = 0;
	}

	T getValue() const
	{
		std::cerr << "getter in concrete class" << std::endl;
		return this->value_;
	}

	void setValue(T value )
	{
		AbstractClass<T>::value_ = value;
	}

	T& operator+ (const ConcreteClass<T>& cc) const
	{
		T result = this->value_ + cc.getValue();
		return result;
	}
};



int main()
{
	ConcreteClass<int>* cc = new ConcreteClass<int>(1);
	int d =  cc->getValue();

	ConcreteClass<int>* cc2 = new ConcreteClass<int>(2);
	//int result = (*cc)+(*cc2);

	delete cc;
	delete cc2;

	std::cerr << "getter1 = " << cc->getValue() << std::endl;
	std::cerr << "result =" <<(*cc)+(*cc2) << std::endl;


	return 0;
}
