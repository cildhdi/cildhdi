#ifndef _STUDENTMGR_H_
#define _STUDENTMGR_H_

#define _CRT_SECURE_NO_WARNINGS
#include "LinkList.h"
#include <string>
#include <fstream>

struct Student
{
	int _num;       //ѧ�����
	std::string _name; //ѧ������
	int _grade;     //ѧ���꼶
	int _chinese;   //���ĳɼ�
	int _math;      //��ѧ�ɼ�
	int _english;   //Ӣ��ɼ�
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
	void ShowMenu();//1.��ʾ��
	int GetChoice();//2.��ȡ�û�ѡ��Ĳ˵��ı��
	Student CreateStudent();//3.����һ���ڵ�,���᷵��һ���´�����ѧ����Ϣ�ڵ��ָ��
	bool AddStudent(const Student& student);//4.��ѧ����Ϣ�ڵ���뵽������
	//PSTUDENT GetPrevAddr(int num);//5.����ָ�����ѧ���ڵ����һ���ڵ��ָ��
	void ShowAll();//6.��ʾ����ѧ����Ϣ
	void ShowStudent(int num);//7.��ʾ���Ϊnum��ѧ����Ϣ
	int ShowStudentCount();//8.��ʾ��Ϣ����
	void ModityStudent(int num);//9.�޸�ѧ����Ϣ��numΪҪ�޸ĵ�ѧ�����
	bool Question(const char *pstr);//10.��ȡ�û���ѡ��
	int GetInputNum();//11.��ȡ�û������ѧ�����
	void DelStudent(int num);//12.ɾ�����Ϊnum��ѧ����Ϣ
	void DelAll();//13.ɾ�����е�ѧ����Ϣ
	void SaveToFile();//14.��ѧ����Ϣ���浽�ļ�����
	void LoadFromFile();//15.���ļ��ж�ȡѧ����Ϣ
	int Loop();
};

#endif