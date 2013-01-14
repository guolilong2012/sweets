class A
{
public:
	A(int size):SIZE(size){};
	//不可
	//A(int size){SIZE = size;};
	const int SIZE;
};

int main(void)
{
	A a(100);
	A b(200);

	const int i = 10;
	//不可const int i;
	//i = 10;

	return 0;
}
