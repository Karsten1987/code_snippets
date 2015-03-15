#include <stdio.h>
#include <iostream>

class A
{

	public:
	virtual void f(){
		std::cerr << "parent class print" << std::endl;
	}

	void g(){
		std::cerr << "i will call f" << std::endl;
		this->f();
	}

};


class B:public A
{

        public:
        void f(){
                std::cerr << "kid class print" << std::endl;
        }
};



int main()
{
	B coolkid;
	coolkid.g();
	
	return 0;
}
