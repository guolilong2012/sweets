#include <iostream>

using namespace std;

class A
{
public:
	static int i; //不分配空间
};

int A::i; //分配空间
//static也可以修饰成员函数，没有隐含的参数指针this, static成员函数只能访问static成员变量

int main(void)
{
	A a, b; //不分配空间

	a.i = 10;
	b.i = 20;
	cout << a.i << endl << b.i << endl;
	A::i = 30;
	cout << a.i << endl << b.i << endl;

	return 0;
}
