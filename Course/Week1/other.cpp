#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <bitset>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;
#define S 1E-10
#define t(i) T##i()
#define scanf_s scanf
#define printf_s printf
void T1()
{
	while (true)
	{
		printf_s("��������:");
		double num;
		scanf_s("%lf", &num);
		if (fabs(num) < S)
			break;
		printf_s(num > 0 ? "����\n" : "����\n");
	}
}

void T2()
{
	int sum1 = 0, sum2 = 0;
	for (int i = 1; i < 101; i++)
		i % 2 != 0 ? sum1 += i : sum2 += i;
	printf_s("�����ͣ�%d,ż���ͣ�%d\n", sum1, sum2);
}

int rec(int num)
{
	if (num == 1)
		return 1;
	return num * rec(num - 1);
}

void T3()
{
	printf_s("1��2��3������10=%d\n", rec(10));
}

void T4()
{
	const double Pi = 3.141592;
	printf_s("����Բ�뾶��");
	double radio = 0.0f;
	scanf_s("%lf", &radio);
	printf_s("���=%lf\n", pow(radio, 2) * Pi);
}

void T5()
{
	double a = 0, b = 0, c = 0;
	printf_s("�������������߳���");
	scanf_s("%lf%lf%lf", &a, &b, &c);
	double p = (a + b + c) / (double)2;
	printf_s("���=%lf", sqrt(p * (p - a) * (p - b) * (p - c)));
}

void T10()
{
	int num = 0;
	cout << "����һ������:";
	cin >> num;
	std::bitset<32> bs(num);
	ostringstream oss;
	oss << bs;
	string str = oss.str();
	int tag = 0;
	for (int i = 0; str[i] == '0'; i++)
		tag = i;
	str = str.substr(tag + 1, str.size() - tag);
	reverse(str.begin(), str.end());
	cout << endl
		 << "�����������:" << str;
}
int main()
{
	t(10);
	system("pause");
	return 0;
}
