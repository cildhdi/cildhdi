// Vec.h				��ȱ�ٲ��ֺ���ģ���ʵ��
#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <cstring>
template <typename T> class VECTOR;
template <typename T>
std::ostream & operator<<(std::ostream &out, const VECTOR<T> &v);
template <typename T>
std::istream & operator>>(std::istream &in, VECTOR<T> &v);
template <typename T> class VECTOR			// ������ģ�壨���������뽫��Ա������ʵ��ȫд��ͷ�ļ��У�
{
public:
	VECTOR(int size = 0, const T *x = NULL);	// �� ���캯������Ĭ�ϵĹ��캯����ת�����캯����
	VECTOR(const VECTOR &v);				// �� �������캯����ʵ��������죩
	virtual ~VECTOR();						// �� �����������麯����
	VECTOR & operator=(const VECTOR &v);	// �� ��ֵ�����������ʵ���ֵ���㣩

	VECTOR(VECTOR&& other);
	VECTOR& operator=(VECTOR&& other);

	T & operator[](int index) const throw(int);
	// ��������������������÷��أ�������ֵ��;�±�Խ��ʱ�����쳣
	int getsize() const;					// ��ȡ������ά����������Ա������
	void resize(int size);					// ����������ά������������ԭ�е����ݣ�

	VECTOR   operator+ (const VECTOR &v) const throw(char);	// �������
	VECTOR & operator+=(const VECTOR &v) throw(char);
	VECTOR   operator- (const VECTOR &v) const throw(char);	// �������
	VECTOR & operator-=(const VECTOR &v) throw(char);
	T		 operator* (const VECTOR &v) const throw(char);	// �����������
	VECTOR   operator* (const T &v) const throw(char);
	VECTOR & operator*= (const T &v) const throw(char);	// ���������

	friend std::ostream & operator<<(std::ostream &out, const VECTOR &v);
	friend std::istream & operator>>(std::istream &in, VECTOR &v);

protected:								// �ܱ����ģ��Ա�������ķ������ԣ�
	int num;									// ������ά��
	T *p;										// ָ�루��sizeof(void*)�ֽڣ���4�ֽڣ�����Դ�ڶѿռ�
};

//===== ��Ԫ������ģ�壩
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
std::istream & operator>>(std::istream &in, VECTOR<T> &v)	// �����Զ���չ���������Ĺ���
{
	const int M = 1024, N = 1024;		// Nȡ��Сֵ1��Ϊ�˵��ԣ�ʵ��ʹ��ʱȡ1024
	char str[M], ch;
	T buffer[N];					// ���û����������N��T������
	int i, j, k;

	in.getline(str, M, '(');		// ���˵�'('��֮ǰ�������ַ�
	while (true)						// ���˵���Բ����֮��Ŀհ��ַ�
	{
		ch = in.peek();				// ͵����һ���ַ������Ƿ�Ϊ�հ��ַ�
		if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
			in.get(ch);				// ���ǿհ��ַ�������˵�������ȡ���ã�
		else
			break;					// ֱ�������ǿհ��ַ���������whileѭ��
	}

	if (in.peek() == ')')				// ͵����һ���ַ�������')'
	{
		in.get(ch);
		v.resize(0);				// ������v��ά�����ó� 0 ά
		return in;					// �˳�������������Ϊ 0 ά����
	}

	for (k = 0; ch != ')'; k++)
	{
		for (i = 0; i < N && ch != ')'; ++i)
			in >> buffer[i] >> ch;
		v.resize(k*N + i);			// ������resize������"����������ԭ������"�Ĺ���
		for (j = 0; j < i; j++)
			v[k*N + j] = buffer[j];	// �����˷����������
	}
	return in;
}

//===== ��Ա������ģ�壩
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
T & VECTOR<T>::operator[](int index) const throw(int)// ��������������������÷��أ�������ֵ��
{
	if (index < 0 || index >= num)
		throw - 1;
	return p[index];
}

template <typename T>
VECTOR<T> VECTOR<T>::operator+(const VECTOR<T> &v) const throw(char)	// �������
{
	if (num != v.num)
		throw '1';
	VECTOR<T> x(*this);
	for (int i = 0; i < num; ++i)
		x.p[i] += v.p[i];
	return x;
}

template <typename T>
VECTOR<T> &VECTOR<T>::operator+=(const VECTOR<T> &v) throw(char)	// �������2
{
	if (num != v.num)
		throw '2';
	(*this) = (*this) + v;
	return (*this);
}

template <typename T>
VECTOR<T> VECTOR<T>::operator-(const VECTOR<T> &v) const throw(char)	// �������
{
	if (num != v.num)
		throw '3';
	VECTOR<T> x(*this);
	for (int i = 0; i < num; ++i)
		x.p[i] -= v.p[i];
	return x;
}

template <typename T>
VECTOR<T> &VECTOR<T>::operator-=(const VECTOR<T> &v) throw(char)	// �������2
{
	if (num != v.num)
		throw '4';
	(*this) = (*this) - v;
	return (*this);
}

template <typename T>
T VECTOR<T>::operator*(const VECTOR<T> &v)const throw(char) //���
{
	if (num != v.num)
		throw '5';
	T x = 0;
	for (int i = 0; i < num; ++i)
		x += p[i] * v.p[i];
	return x;
}

template <typename T>
VECTOR<T> VECTOR<T>::operator*(const T &v)const throw(char) //�����
{
	VECTOR<T> x(*this);
	for (int i = 0; i < num; ++i)
	{
		x.p[i] *= v;
	}
	return x;
}

template <typename T>
VECTOR<T> &VECTOR<T>::operator*=(const T &v)const throw(char) //�����
{
	(*this) = (*this)*v;
	return (*this);
}

#endif

