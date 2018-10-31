#include "StudentMgr.h"

void StudentMgr::LoadFromFile()
{
	_data.clear();
	std::ifstream ifs(_file_name, std::ios::in);
	Student student;
	while (ifs >> student._num >> student._name >> student._grade >> student._chinese >> student._math >> student._english)
		_data.push_front(student);
	printf("�ļ���ȡ��ϣ�ѧ����Ϣ%d����\n", _data.size());
}

int StudentMgr::Loop()
{
	while (true)
	{
		switch (GetChoice())
		{
		case 0: exit(0);
		case 1: printf("��ѡ���˲˵�1\n"); AddStudent(CreateStudent()); break;
		case 2: printf("��ѡ���˲˵�2\n"); DelStudent(GetInputNum()); break;
		case 3: printf("��ѡ���˲˵�3\n"); ShowStudent(GetInputNum()); break;
		case 4: printf("��ѡ���˲˵�4\n"); ModityStudent(GetInputNum()); break;
		case 5: printf("��ѡ���˲˵�5\n"); DelAll(); break;
		case 6: printf("��ѡ���˲˵�6\n"); ShowAll(); break;
		case 7: printf("��ѡ���˲˵�7\n"); ShowStudentCount(); break;
		case 8: printf("��ѡ���˲˵�8\n"); LoadFromFile(); break;
		case 9: printf("��ѡ���˲˵�9\n"); SaveToFile(); break;
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
	printf("-------------------------�Ϻ���ѧѧ���ɼ�����ϵͳ-------------------------\n");
	printf("\n\t1.���ѧ����Ϣ    2.ɾ��ĳ��ѧ����Ϣ    3.��ʾĳ��ѧ����Ϣ\n");
	printf("\t4.�޸�ѧ����Ϣ    5.ɾ������ѧ����Ϣ    6.��ʾ����ѧ����Ϣ\n");
	printf("\t7.��ʾ��Ϣ����    8.��ȡ�ļ�ѧ����Ϣ    9.����ѧ����Ϣ���ļ�\n");
	printf("\t0.�˳�ϵͳ\n");
	printf("\n-------------------------------------------------------------------------\n");
}

int StudentMgr::GetChoice()
{
	int num;//�����û�ѡ��Ĳ˵����
	ShowMenu();
	printf("��ѡ��˵�(0-9):");
	while (scanf("%d", &num) != 1 || num < 0 || num > 9)
	{
		ShowMenu();
		printf("ѡ��˵�����������ѡ��(0-9):");
		fflush(stdin);//������뻺����
	}
	return num;
}

Student StudentMgr::CreateStudent()
{
	Student student, *pstu = &student;
	printf("������ѧ���ı��(����)��");
	while (scanf("%d", &pstu->_num) != 1 && std::find(_data.begin(), _data.end(), student) != _data.end())
	{
		printf("ѧ��������������Ѿ����ڣ�����������ѧ���ı��(����)��");
		fflush(stdin);
	}
	char name[10] = { 0 };
	printf("������ѧ��������(С��10�ַ�)��");
	scanf("%10s", name);
	pstu->_name = name;
	printf("������ѧ�����꼶(1-4)��");
	while (scanf("%d", &pstu->_grade) != 1 || pstu->_grade < 1 || pstu->_grade > 4)
	{
		printf("�꼶�����������������ѧ�����꼶(1-4)��");
		fflush(stdin);
	}
	printf("������ѧ�������ĳɼ�(0-100)��");
	while (scanf("%d", &pstu->_chinese) != 1 || pstu->_chinese < 0 || pstu->_chinese > 100)
	{
		printf("�ɼ������������������ѧ�������ĳɼ�(0-100)��");
		fflush(stdin);
	}
	printf("������ѧ������ѧ�ɼ�(0-100)��");
	while (scanf("%d", &pstu->_math) != 1 || pstu->_math < 0 || pstu->_math > 100)
	{
		printf("�ɼ������������������ѧ������ѧ�ɼ�(0-100)��");
		fflush(stdin);
	}
	printf("������ѧ����Ӣ��ɼ�(0-100)��");
	while (scanf("%d", &pstu->_english) != 1 || pstu->_english < 0 || pstu->_english > 100)
	{
		printf("�ɼ������������������ѧ����Ӣ��ɼ�(0-100)��");
		fflush(stdin);
	}
	printf("��ӳɹ�!\n");
	return student;
}

bool StudentMgr::AddStudent(const Student & student)
{
	DataType::Iterator it = std::find(_data.begin(), _data.end(), student);
	if (it != _data.end())
	{
		printf("���Ϊ%d��ѧ����Ϣ�Ѿ����ڣ�\n", student._num);
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
	printf("  ���      ����      �꼶      ���ĳɼ�      ��ѧ�ɼ�      Ӣ��ɼ�\n");
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
		printf("û�б��Ϊ%d��ѧ����Ϣ��\n", num);
	}
	else
	{
		printf("--------------------------------------------------------------------\n");
		printf("  ���      ����      �꼶      ���ĳɼ�      ��ѧ�ɼ�      Ӣ��ɼ�\n");
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
	printf("\n��ǰ����%dλѧ����Ϣ��\n", _data.size());
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
		printf("û�б��Ϊ%d��ѧ����Ϣ��\n", num);
		return;
	}
	printf("��ǰѧ��������Ϊ%s,", it->_name.c_str());
	if (Question("ȷ��Ҫ�޸���"))
	{
		printf("������ѧ��������(С��10�ַ�)��");
		char name[10] = { 0 };
		scanf("%10s", name);
		it->_name = name;
	}
	printf("��ǰѧ�����꼶Ϊ%d,", it->_grade);
	if (Question("ȷ��Ҫ�޸���"))
	{
		printf("������ѧ�����꼶(1-4)��");
		while (scanf("%d", &it->_grade) != 1 || it->_grade < 1 || it->_grade > 4)
		{
			printf("�꼶�����������������ѧ�����꼶��");
			fflush(stdin);
		}
	}
	printf("��ǰѧ�������ĳɼ�Ϊ%d,", it->_chinese);
	if (Question("ȷ��Ҫ�޸���"))
	{
		printf("������ѧ�������ĳɼ�(0-100)��");
		while (scanf("%d", &it->_chinese) != 1 || it->_chinese < 0 || it->_chinese > 100)
		{
			printf("�ɼ������������������ѧ�������ĳɼ�(0-100)��");
			fflush(stdin);
		}
	}
	printf("��ǰѧ������ѧ�ɼ�Ϊ%d,", it->_math);
	if (Question("ȷ��Ҫ�޸���"))
	{
		printf("������ѧ������ѧ�ɼ�(0-100)��");
		while (scanf("%d", &it->_math) != 1 || it->_math < 0 || it->_math > 100)
		{
			printf("�ɼ������������������ѧ������ѧ�ɼ�(0-100)��");
			fflush(stdin);
		}
	}
	printf("��ǰѧ����Ӣ��ɼ�Ϊ%d,", it->_english);
	if (Question("ȷ��Ҫ�޸���"))
	{
		printf("������ѧ����Ӣ��ɼ�(0-100)��");
		while (scanf("%d", &it->_english) != 1 || it->_english < 0 || it->_english > 100)
		{
			printf("�ɼ������������������ѧ����Ӣ��ɼ�(0-100)��");
			fflush(stdin);
		}
	}
	printf("�޸���ϣ�\n");
}

bool StudentMgr::Question(const char * pstr)
{
	char answer;
	printf("%s��ѡ��y or n����", pstr);
	while (1 != scanf(" %c", &answer) || (answer != 'y' && answer != 'n'))
	{
		printf("�������%s������ѡ��y or n����", pstr);
		fflush(stdin);//������뻺����,C�⺯��
	}
	return answer == 'y';
}

int StudentMgr::GetInputNum()
{
	int num;
	printf("������ѧ���ı��(����)��");
	while (scanf("%d", &num) != 1)
	{
		printf("��������������������ѧ���ı��(����)��");
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
		if (!Question("ȷ��Ҫɾ����ѧ����Ϣ��"))
			return;
		_data.remove(it);
		printf("ɾ���˱��Ϊ%d��ѧ����Ϣ��\n", num);
	}
	else
		printf("û���ҵ����Ϊ%d��ѧ����Ϣ��\n", num);
}

void StudentMgr::DelAll()
{
	if (!Question("ȷ��Ҫɾ����ǰ���е�ѧ����Ϣ��"))
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
		printf("�ɹ���д����%d��ѧ����Ϣ��\n", count);
	else
		printf("Ӧд��%d��ѧ����Ϣ��ʵ��д��%d��ѧ����Ϣ��\n", count, i);
}
