#ifndef _YL_STUDENT_H_
#define _YL_STUDENT_H_

#include <string>

struct Student
{
	int _num;       //ѧ�����
	std::string _name; //ѧ������
	int _sex;
	int _grade;     //ѧ���꼶
	int _chinese;   //���ĳɼ�
	int _math;      //��ѧ�ɼ�
	int _english;   //Ӣ��ɼ�

	enum Field
	{
		NUM, NAME, SEX, GRADE, CHINESE, MATH, ENGLISH
	};
	bool operator==(const Student& rhs)
	{
		return _num == rhs._num;
	}
	bool operator!=(const Student& rhs)
	{
		return !(*this == rhs);
	}
};


#endif
