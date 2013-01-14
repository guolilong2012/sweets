#include <iostream>

using namespace std;

class Complex
{
	friend ostream & operator <<(ostream &, const Complex &);

public:
	Complex(double real, double img):real(real), img(img){}
	Complex & operator +=(const Complex &b)
	{
		real += b.real;
		img += b.img;
		return *this;
	}

private:
	double real, img;
	//private变量，从外面不能直接访问。
};

ostream & operator <<(ostream &o, const Complex &a)
{
	o << a.real << '+' << a.img << 'i';
	//Complex类的友元类，可以直接访问Complex的private成员。
	return o;
}

int main(void)
{
	Complex a(1, 2), b(3, 4);
	a += b;
	cout << a << endl;

	return 0;
}
