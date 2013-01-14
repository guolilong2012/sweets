#ifndef TEMPLATE_H
#define TEMPLATE_H
//模板本质上就是一种宏定义，因此模板类和模板函数的定义都应该放在头文件中.
template <class T, int max> struct Buffer
{
	T v[max];
};

template <class T> T power(T a, int exp)
{
	T ans = a;
	while (--exp > 0) {
		ans *= a;
	}

	return (ans);
}

#endif
