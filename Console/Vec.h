// Vec.h				尚缺少部分函数模板的实现
#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <cstring>
template <typename T> class VECTOR;
template <typename T>
std::ostream & operator<<(std::ostream &out, const VECTOR<T> &v);
template <typename T>
std::istream & operator>>(std::istream &in, VECTOR<T> &v);
template <typename T> class VECTOR			// 向量类模板（描述）必须将成员函数的实现全写入头文件中！
{
public:
	VECTOR(int size = 0, const T *x = NULL);	// ① 构造函数（含默认的构造函数、转换构造函数）
	VECTOR(const VECTOR &v);				// ② 拷贝构造函数（实现深拷贝构造）
	virtual ~VECTOR();						// ③ 析构函数（虚函数）
	VECTOR & operator=(const VECTOR &v);	// ④ 赋值运算符函数（实现深赋值运算）

	VECTOR(VECTOR&& other);
	VECTOR& operator=(VECTOR&& other);

	T & operator[](int index) const throw(int);
	// 方括号运算符函数（引用返回，可作左值）;下表越界时抛掷异常
	int getsize() const;					// 获取向量的维数（常量成员函数）
	void resize(int size);					// 调整向量的维数（尽量保留原有的数据）

	VECTOR   operator+ (const VECTOR &v) const throw(char);	// 向量相加
	VECTOR & operator+=(const VECTOR &v) throw(char);
	VECTOR   operator- (const VECTOR &v) const throw(char);	// 向量相减
	VECTOR & operator-=(const VECTOR &v) throw(char);
	T		 operator* (const VECTOR &v) const throw(char);	// 向量点乘向量
	VECTOR   operator* (const T &v) const throw(char);
	VECTOR & operator*= (const T &v) const throw(char);	// 向量点乘数

	friend std::ostream & operator<<(std::ostream &out, const VECTOR &v);
	friend std::istream & operator>>(std::istream &in, VECTOR &v);

protected:								// 受保护的（以便派生类的访问属性）
	int num;									// 向量的维数
	T *p;										// 指针（仅sizeof(void*)字节，即4字节），资源在堆空间
};

//===== 友元函数（模板）
template <typename T>
std::ostream & operator<<(std::ostream &out, const VECTOR<T> &v)
{
	if (v.num == 0)
		out << "()";
	else
	{
		out << '(' << v.p[0];
		for (int i = 1; i < v.num; ++i)
			out << ", " << v.p[i];
		out << ')';
	}
	return out;
}

template <typename T>
std::istream & operator>>(std::istream &in, VECTOR<T> &v)	// 具有自动扩展容器容量的功能
{
	const int M = 1024, N = 1024;		// N取最小值1是为了调试，实际使用时取1024
	char str[M], ch;
	T buffer[N];					// 设置缓冲区，存放N个T型数据
	int i, j, k;

	in.getline(str, M, '(');		// 过滤掉'('及之前的所有字符
	while (true)						// 过滤掉左圆括号之后的空白字符
	{
		ch = in.peek();				// 偷看下一个字符，看是否为空白字符
		if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
			in.get(ch);				// 若是空白字符，则过滤掉（即读取后不用）
		else
			break;					// 直到遇到非空白字符，结束本while循环
	}

	if (in.peek() == ')')				// 偷看下一个字符，若是')'
	{
		in.get(ch);
		v.resize(0);				// 将对象v的维数设置成 0 维
		return in;					// 退出本函数，输入为 0 维向量
	}

	for (k = 0; ch != ')'; k++)
	{
		for (i = 0; i < N && ch != ')'; ++i)
			in >> buffer[i] >> ch;
		v.resize(k*N + i);			// 利用了resize函数的"尽量保留了原有数据"的功能
		for (j = 0; j < i; j++)
			v[k*N + j] = buffer[j];	// 利用了方括号运算符
	}
	return in;
}

//===== 成员函数（模板）
template <typename T>
VECTOR<T>::VECTOR(VECTOR&& other)
{
	p = other.p;
	other.p = nullptr;
	other.num = 0;
}
template <typename T>
VECTOR<T>& VECTOR<T>::operator=(VECTOR&& other)
{
	delete[] p;
	p = other.p;
	other.p = nullptr;
	other.num = 0;
}


template <typename T>
VECTOR<T>::VECTOR(int size, const T *x)
{
	num = size;
	p = new T[num];
	if (p != NULL)
	{
		for (int i = 0; i < num; ++i)
			p[i] = x[i];
	}
}

template<typename T>
int VECTOR<T>::getsize() const
{
	return num;
}

template<typename T>
void VECTOR<T>::resize(int size)
{
	if (size == num) return;
	else if (size < num) num = size;
	else
	{
		T* tmp = new T[size];
		if (tmp != NULL)
		{
			for (int i = 0; i < num; ++i)
				tmp[i] = p[i];
			for (int i = num; i < size; ++i)
				tmp[i] = 0;
			delete[] p;
			p = tmp;
		}
		num = size;
	}
}

template <typename T>
VECTOR<T>::VECTOR(const VECTOR<T> &v)
{
	num = v.num;
	int len = num;
	p = new T[len];
	if (p != NULL)
	{
		for (int i = 0; i < len; ++i)
			p[i] = v.p[i];
	}
}

template <typename T>
VECTOR<T>::~VECTOR()
{
	delete[]p;
}

template <typename T>
VECTOR<T> &VECTOR<T>::operator=(const VECTOR<T> &v)
{
	if (this == &v) return *this;
	delete[] p;
	num = v.num;
	int len = num;
	p = new T[len];
	if (p != NULL)
	{
		for (int i = 0; i < len; ++i)
			p[i] = v.p[i];
	}
	return *this;
}

template <typename T>
T & VECTOR<T>::operator[](int index) const throw(int)// 方括号运算符函数（引用返回，可作左值）
{
	if (index < 0 || index >= num)
		throw - 1;
	return p[index];
}

template <typename T>
VECTOR<T> VECTOR<T>::operator+(const VECTOR<T> &v) const throw(char)	// 向量相加
{
	if (num != v.num)
		throw '1';
	VECTOR<T> x(*this);
	for (int i = 0; i < num; ++i)
		x.p[i] += v.p[i];
	return x;
}

template <typename T>
VECTOR<T> &VECTOR<T>::operator+=(const VECTOR<T> &v) throw(char)	// 向量相加2
{
	if (num != v.num)
		throw '2';
	(*this) = (*this) + v;
	return (*this);
}

template <typename T>
VECTOR<T> VECTOR<T>::operator-(const VECTOR<T> &v) const throw(char)	// 向量相减
{
	if (num != v.num)
		throw '3';
	VECTOR<T> x(*this);
	for (int i = 0; i < num; ++i)
		x.p[i] -= v.p[i];
	return x;
}

template <typename T>
VECTOR<T> &VECTOR<T>::operator-=(const VECTOR<T> &v) throw(char)	// 向量相减2
{
	if (num != v.num)
		throw '4';
	(*this) = (*this) - v;
	return (*this);
}

template <typename T>
T VECTOR<T>::operator*(const VECTOR<T> &v)const throw(char) //点乘
{
	if (num != v.num)
		throw '5';
	T x = 0;
	for (int i = 0; i < num; ++i)
		x += p[i] * v.p[i];
	return x;
}

template <typename T>
VECTOR<T> VECTOR<T>::operator*(const T &v)const throw(char) //点乘数
{
	VECTOR<T> x(*this);
	for (int i = 0; i < num; ++i)
	{
		x.p[i] *= v;
	}
	return x;
}

template <typename T>
VECTOR<T> &VECTOR<T>::operator*=(const T &v)const throw(char) //点乘数
{
	(*this) = (*this)*v;
	return (*this);
}

#endif

