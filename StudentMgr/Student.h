#ifndef _YL_STUDENT_H_
#define _YL_STUDENT_H_

#include <string>

struct Student
{
	int _num;       //学生编号
	std::string _name; //学生姓名
	int _sex;
	int _grade;     //学生年级
	int _chinese;   //语文成绩
	int _math;      //数学成绩
	int _english;   //英语成绩

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
