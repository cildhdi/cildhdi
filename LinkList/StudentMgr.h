#ifndef _STUDENTMGR_H_
#define _STUDENTMGR_H_

#define _CRT_SECURE_NO_WARNINGS
#include "LinkList.h"
#include <string>
#include <fstream>

struct Student
{
	int _num;       //学生编号
	std::string _name; //学生姓名
	int _grade;     //学生年级
	int _chinese;   //语文成绩
	int _math;      //数学成绩
	int _english;   //英语成绩
	bool operator==(const Student& rhs)
	{
		return _num == rhs._num;
	}
	bool operator!=(const Student& rhs)
	{
		return !(*this == rhs);
	}
};

class StudentMgr
{
public:
	using DataType = ll::LinkList<Student>;
private:
	DataType _data;
	std::string _file_name;
public:
	StudentMgr(const std::string& file_name);
	void ShowMenu();//1.显示菜
	int GetChoice();//2.获取用户选择的菜单的编号
	Student CreateStudent();//3.创建一个节点,它会返回一个新创建的学生信息节点的指针
	bool AddStudent(const Student& student);//4.把学生信息节点加入到链表中
	//PSTUDENT GetPrevAddr(int num);//5.返回指定编号学生节点的上一个节点的指针
	void ShowAll();//6.显示所有学生信息
	void ShowStudent(int num);//7.显示编号为num的学生信息
	int ShowStudentCount();//8.显示信息数量
	void ModityStudent(int num);//9.修改学生信息，num为要修改的学生编号
	bool Question(const char *pstr);//10.获取用户的选择
	int GetInputNum();//11.获取用户输入的学生编号
	void DelStudent(int num);//12.删除编号为num的学生信息
	void DelAll();//13.删除所有的学生信息
	void SaveToFile();//14.把学生信息保存到文件当中
	void LoadFromFile();//15.从文件中读取学生信息
	int Loop();
};

#endif