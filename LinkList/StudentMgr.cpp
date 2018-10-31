#include "StudentMgr.h"

void StudentMgr::LoadFromFile()
{
	_data.clear();
	std::ifstream ifs(_file_name, std::ios::in);
	Student student;
	while (ifs >> student._num >> student._name >> student._grade >> student._chinese >> student._math >> student._english)
		_data.push_front(student);
	printf("文件读取完毕！学生信息%d条。\n", _data.size());
}

int StudentMgr::Loop()
{
	while (true)
	{
		switch (GetChoice())
		{
		case 0: exit(0);
		case 1: printf("你选择了菜单1\n"); AddStudent(CreateStudent()); break;
		case 2: printf("你选择了菜单2\n"); DelStudent(GetInputNum()); break;
		case 3: printf("你选择了菜单3\n"); ShowStudent(GetInputNum()); break;
		case 4: printf("你选择了菜单4\n"); ModityStudent(GetInputNum()); break;
		case 5: printf("你选择了菜单5\n"); DelAll(); break;
		case 6: printf("你选择了菜单6\n"); ShowAll(); break;
		case 7: printf("你选择了菜单7\n"); ShowStudentCount(); break;
		case 8: printf("你选择了菜单8\n"); LoadFromFile(); break;
		case 9: printf("你选择了菜单9\n"); SaveToFile(); break;
		}
		system("pause");
	}
	return 0;
}

StudentMgr::StudentMgr(const std::string& file_name) : _file_name(file_name)
{
}

void StudentMgr::ShowMenu()
{
	system("cls");
	printf("-------------------------上海大学学生成绩管理系统-------------------------\n");
	printf("\n\t1.添加学生信息    2.删除某个学生信息    3.显示某个学生信息\n");
	printf("\t4.修改学生信息    5.删除所有学生信息    6.显示所有学生信息\n");
	printf("\t7.显示信息数量    8.读取文件学生信息    9.保存学生信息至文件\n");
	printf("\t0.退出系统\n");
	printf("\n-------------------------------------------------------------------------\n");
}

int StudentMgr::GetChoice()
{
	int num;//保存用户选择的菜单编号
	ShowMenu();
	printf("请选择菜单(0-9):");
	while (scanf("%d", &num) != 1 || num < 0 || num > 9)
	{
		ShowMenu();
		printf("选择菜单错误，请重新选择(0-9):");
		fflush(stdin);//清空输入缓冲区
	}
	return num;
}

Student StudentMgr::CreateStudent()
{
	Student student, *pstu = &student;
	printf("请输入学生的编号(整型)：");
	while (scanf("%d", &pstu->_num) != 1 && std::find(_data.begin(), _data.end(), student) != _data.end())
	{
		printf("学生编号输入错误或已经存在，请重新输入学生的编号(整型)：");
		fflush(stdin);
	}
	char name[10] = { 0 };
	printf("请输入学生的姓名(小于10字符)：");
	scanf("%10s", name);
	pstu->_name = name;
	printf("请输入学生的年级(1-4)：");
	while (scanf("%d", &pstu->_grade) != 1 || pstu->_grade < 1 || pstu->_grade > 4)
	{
		printf("年级输入错误，请重新输入学生的年级(1-4)：");
		fflush(stdin);
	}
	printf("请输入学生的语文成绩(0-100)：");
	while (scanf("%d", &pstu->_chinese) != 1 || pstu->_chinese < 0 || pstu->_chinese > 100)
	{
		printf("成绩输入错误！请重新输入学生的语文成绩(0-100)：");
		fflush(stdin);
	}
	printf("请输入学生的数学成绩(0-100)：");
	while (scanf("%d", &pstu->_math) != 1 || pstu->_math < 0 || pstu->_math > 100)
	{
		printf("成绩输入错误，请重新输入学生的数学成绩(0-100)：");
		fflush(stdin);
	}
	printf("请输入学生的英语成绩(0-100)：");
	while (scanf("%d", &pstu->_english) != 1 || pstu->_english < 0 || pstu->_english > 100)
	{
		printf("成绩输入错误，请重新输入学生的英语成绩(0-100)：");
		fflush(stdin);
	}
	printf("添加成功!\n");
	return student;
}

bool StudentMgr::AddStudent(const Student & student)
{
	DataType::Iterator it = std::find(_data.begin(), _data.end(), student);
	if (it != _data.end())
	{
		printf("编号为%d的学生信息已经存在！\n", student._num);
		return false;
	}
	else
	{
		_data.push_front(student);
		return true;
	}
}

void StudentMgr::ShowAll()
{
	printf("--------------------------------------------------------------------\n");
	printf("  编号      姓名      年级      语文成绩      数学成绩      英语成绩\n");
	printf("--------------------------------------------------------------------\n");
	for (DataType::Iterator it = _data.begin(); it != _data.end(); it++)
	{
		printf("%4d", it->_num);
		printf("%10s", it->_name.c_str());
		printf("%10d", it->_grade);
		printf("%13d", it->_chinese);
		printf("%13d", it->_math);
		printf("%13d\n", it->_english);
	}
	printf("--------------------------------------------------------------------\n");
}

void StudentMgr::ShowStudent(int num)
{
	DataType::Iterator it = std::find_if(_data.begin(), _data.end(), [num](const Student& stu)
	{
		return stu._num == num;
	});
	if (it == _data.end())
	{
		printf("没有编号为%d的学生信息。\n", num);
	}
	else
	{
		printf("--------------------------------------------------------------------\n");
		printf("  编号      姓名      年级      语文成绩      数学成绩      英语成绩\n");
		printf("--------------------------------------------------------------------\n");
		printf("%4d", it->_num);
		printf("%10s", it->_name.c_str());
		printf("%10d", it->_grade);
		printf("%13d", it->_chinese);
		printf("%13d", it->_math);
		printf("%13d\n", it->_english);
		printf("--------------------------------------------------------------------\n");
	}
}

int StudentMgr::ShowStudentCount()
{
	printf("\n当前共有%d位学生信息。\n", _data.size());
	return _data.size();
}

void StudentMgr::ModityStudent(int num)
{
	DataType::Iterator it = std::find_if(_data.begin(), _data.end(), [num](const Student& stu)
	{
		return stu._num == num;
	});
	if (it == _data.end())
	{
		printf("没有编号为%d的学生信息。\n", num);
		return;
	}
	printf("当前学生的姓名为%s,", it->_name.c_str());
	if (Question("确定要修改吗？"))
	{
		printf("请输入学生的姓名(小于10字符)：");
		char name[10] = { 0 };
		scanf("%10s", name);
		it->_name = name;
	}
	printf("当前学生的年级为%d,", it->_grade);
	if (Question("确定要修改吗？"))
	{
		printf("请输入学生的年级(1-4)：");
		while (scanf("%d", &it->_grade) != 1 || it->_grade < 1 || it->_grade > 4)
		{
			printf("年级输入错误，请重新输入学生的年级：");
			fflush(stdin);
		}
	}
	printf("当前学生的语文成绩为%d,", it->_chinese);
	if (Question("确定要修改吗？"))
	{
		printf("请输入学生的语文成绩(0-100)：");
		while (scanf("%d", &it->_chinese) != 1 || it->_chinese < 0 || it->_chinese > 100)
		{
			printf("成绩输入错误！请重新输入学生的语文成绩(0-100)：");
			fflush(stdin);
		}
	}
	printf("当前学生的数学成绩为%d,", it->_math);
	if (Question("确定要修改吗？"))
	{
		printf("请输入学生的数学成绩(0-100)：");
		while (scanf("%d", &it->_math) != 1 || it->_math < 0 || it->_math > 100)
		{
			printf("成绩输入错误！请重新输入学生的数学成绩(0-100)：");
			fflush(stdin);
		}
	}
	printf("当前学生的英语成绩为%d,", it->_english);
	if (Question("确定要修改吗？"))
	{
		printf("请输入学生的英语成绩(0-100)：");
		while (scanf("%d", &it->_english) != 1 || it->_english < 0 || it->_english > 100)
		{
			printf("成绩输入错误！请重新输入学生的英语成绩(0-100)：");
			fflush(stdin);
		}
	}
	printf("修改完毕！\n");
}

bool StudentMgr::Question(const char * pstr)
{
	char answer;
	printf("%s请选择（y or n）：", pstr);
	while (1 != scanf(" %c", &answer) || (answer != 'y' && answer != 'n'))
	{
		printf("输入错误！%s请重新选择（y or n）：", pstr);
		fflush(stdin);//清空输入缓冲区,C库函数
	}
	return answer == 'y';
}

int StudentMgr::GetInputNum()
{
	int num;
	printf("请输入学生的编号(整型)：");
	while (scanf("%d", &num) != 1)
	{
		printf("编号输入错误！请重新输入学生的编号(整型)：");
		fflush(stdin);
	}
	return num;
}

void StudentMgr::DelStudent(int num)
{
	DataType::Iterator it = std::find_if(_data.begin(), _data.end(), [num](const Student& stu)
	{
		return stu._num == num;
	});
	if (it != _data.end())
	{
		if (!Question("确定要删除该学生信息吗？"))
			return;
		_data.remove(it);
		printf("删除了编号为%d的学生信息。\n", num);
	}
	else
		printf("没有找到编号为%d的学生信息。\n", num);
}

void StudentMgr::DelAll()
{
	if (!Question("确定要删除当前所有的学生信息吗？"))
		return;
	_data.clear();
}

void StudentMgr::SaveToFile()
{
	int i = 0, count = _data.size();
	std::ofstream ofs(_file_name, std::ios::out);
	for (DataType::Iterator it = _data.begin(); it != _data.end(); it++)
	{
		ofs << it->_num << " " << it->_name << " " << it->_grade << " " << it->_chinese << " " << it->_math << " " << it->_english << std::endl;
	}
	if (i == count)
		printf("成功的写入了%d条学生信息。\n", count);
	else
		printf("应写入%d条学生信息，实际写入%d条学生信息。\n", count, i);
}
