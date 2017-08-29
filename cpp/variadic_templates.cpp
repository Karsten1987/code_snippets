#include <iostream>
#include <tuple>
using namespace std;

class CallMe
{
public:
	CallMe(int a, std::string s)
	{
		std::cout << "a = " << a << " s = " << s << std::endl;
	}
};


class Blub
{
public:
	Blub()
	{}
	
	template<class C, typename ... Args>
	C* call(const std::tuple<Args...> & tuple)
	{
		return call_impl<C>(tuple, std::index_sequence_for<Args...>{});
	}
	
	template<class C, typename ... Args, size_t ... Is>
	C* call_impl(const std::tuple<Args...> & tuple, index_sequence<Is...>)
	{
		return new C(get<Is>(tuple)...);
	}
};

template<class B>
class PrintMeBase
{
public:
	void
	print() const
	{
		std::cout << "Base CLass printing" << std::endl;
	}
};

template<class A, class B>
class PrintMe : public PrintMeBase<B>
{
};

template<class A>
class PrintMe<A, int> : public PrintMeBase<int>
{
public:
	template<typename ... Args>
	void
	print(Args... args) const
	{
		print_internal(args...);
	}
	
	void
	print_internal() const
	{
		std::cout << "Printing for int void" << std::endl;
	}
	
	void
	print_internal(int i) const
	{
		std::cout << "Printing for int " << i << std::endl;
	}
};

template<class A>
class TemplateFun
{
public:
	TemplateFun()
	{}
	
	template<typename ... Args>
	void
	do_something(Args ... args);
};

template<class A, class B>
class TemplateChildFun : public TemplateFun<A>
{
public:
	TemplateChildFun():
	TemplateFun<A>()
	{}
	
	template<typename ... Args>
	void
	do_something(Args ... args)
	{
		std::cout << "yuhuu" << std::endl;
	}
};

int main() {
	// your code goes here
	PrintMe<float, float> print_base;
	PrintMe<float, int> print_int;
	
	print_base.print();
	print_int.print();
	print_int.print(13);
	
	Blub b;
	std::tuple<int, std::string> args_list = std::make_tuple(13, "Hello World");
	b.call<CallMe>(args_list);
	
	TemplateFun<int> * tf = new TemplateChildFun<int, int>();
	tf->do_something();
	
	return 0;
}
