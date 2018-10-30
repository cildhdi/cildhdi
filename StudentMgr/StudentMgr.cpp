#include "StudentMgr.h"
#include <QAction>
#include <QKeySequence>
#include <QMessageBox>
#include <QInputDialog>
#include <QHeaderView>
#include <fstream>

StudentMgr::StudentMgr(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(QStringLiteral("�Ϻ���ѧѧ������"));
	resize(1000, 800);

	QAction* load_file = new QAction(QStringLiteral("�����ļ�"), this);
	load_file->setShortcuts(QKeySequence::Open);
	load_file->setStatusTip(QStringLiteral("�����ļ�"));
	connect(load_file, &QAction::triggered, this, &StudentMgr::LoadFile);

	QAction* save_file = new QAction(QStringLiteral("��������"), this);
	save_file->setShortcuts(QKeySequence::Save);
	save_file->setStatusTip(QStringLiteral("��������"));
	connect(save_file, &QAction::triggered, this, &StudentMgr::SaveFile);

	QMenu* file = menuBar()->addMenu(QStringLiteral("�ļ�"));
	file->addAction(load_file);
	file->addAction(save_file);

	QAction* find_by_num = new QAction(QStringLiteral("ͨ��ѧ�Ų���"), this);
	find_by_num->setStatusTip(QStringLiteral("ͨ��ѧ�Ų���"));
	connect(find_by_num, &QAction::triggered, this, &StudentMgr::FindStudentByNum);

	QAction* find_by_name = new QAction(QStringLiteral("ͨ����������"), this);
	find_by_num->setStatusTip(QStringLiteral("ͨ����������"));
	connect(find_by_name, &QAction::triggered, this, &StudentMgr::FindStudentByName);

	QMenu* find = menuBar()->addMenu(QStringLiteral("����"));
	find->addAction(find_by_num);
	find->addAction(find_by_name);

	QMenu* sort_menu = menuBar()->addMenu(QStringLiteral("��������"));
	sort_menu->addSection("ѡ��������");
	QString strs[] = {
		QStringLiteral("ѧ��"),
		QStringLiteral("����"),
		QStringLiteral("�Ա�"),
		QStringLiteral("�꼶"),
		QStringLiteral("���ĳɼ�"),
		QStringLiteral("��ѧ�ɼ�"),
		QStringLiteral("Ӣ��ɼ�") };
	for (int index = Student::Field::NUM; index <= Student::Field::ENGLISH; index++)
	{
		QAction* action = new QAction(QStringLiteral("����") + strs[index] + QStringLiteral("����"));
		connect(action, &QAction::triggered, [&, index]()
		{
			_sort_column = index;
			Sort();
		});
		sort_menu->addAction(action);
	}
	sort_menu->addSection("������");
	QAction* action = new QAction(QStringLiteral("����"));
	connect(action, &QAction::triggered, [&]()
	{
		_sort_order = Qt::SortOrder::AscendingOrder;
		Sort();
	});
	sort_menu->addAction(action);

	action = new QAction(QStringLiteral("����"));
	connect(action, &QAction::triggered, [&]()
	{
		_sort_order = Qt::SortOrder::DescendingOrder;
		Sort();
	});
	sort_menu->addAction(action);


	QAction* add_student = new QAction(QStringLiteral("���ѧ��"), this);
	add_student->setShortcuts(QKeySequence::New);
	add_student->setStatusTip(QStringLiteral("���ѧ��"));
	connect(add_student, &QAction::triggered, this, &StudentMgr::AddStudent);

	QAction* delete_student = new QAction(QStringLiteral("һ����ѧ"), this);
	delete_student->setShortcuts(QKeySequence::Delete);
	delete_student->setStatusTip(QStringLiteral("ɾ��ѧ��"));
	connect(delete_student, &QAction::triggered, this, &StudentMgr::DeleteStudent);

	QAction* modify_student = new QAction(QStringLiteral("�޸�ѧ����Ϣ"), this);
	modify_student->setStatusTip(QStringLiteral("�޸�ѧ����Ϣ"));
	connect(modify_student, &QAction::triggered, this, &StudentMgr::ModifyStudent);

	QMenu* student_operate = menuBar()->addMenu(QStringLiteral("ѧ������"));
	student_operate->addAction(add_student);
	student_operate->addAction(delete_student);
	student_operate->addAction(modify_student);

	QAction* about_us = new QAction(QStringLiteral("����С��"));
	about_us->setStatusTip(QStringLiteral("����С��"));
	connect(about_us, &QAction::triggered, [this]()
	{
		QMessageBox::about(this, QStringLiteral("��������"), QStringLiteral("��Ա��\n                    ����Զ\n                    �����\n                    ����\n                    ����"));
	});

	QAction* about_qt = new QAction(QStringLiteral("����Qt"));
	about_qt->setStatusTip(QStringLiteral("����Qt"));
	connect(about_qt, &QAction::triggered, [this]()
	{
		QMessageBox::aboutQt(this);
	});

	QMenu* about = menuBar()->addMenu(QStringLiteral("����"));
	about->addAction(about_us);
	about->addAction(about_qt);

	_table = new QTableView(this);
	_model = new QStandardItemModel;
	_table->setModel(_model);
	_table->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	LoadFile();
	LoadStudentsToModel();
	setCentralWidget(_table);
	statusBar();
}

void StudentMgr::LoadFile()
{
	_students.clear();
	std::ifstream ifs(_file_name, std::ios::in);
	Student student;
	while (ifs >> student._num >> student._name >> student._sex >> student._grade >> student._chinese >> student._math >> student._english)
		_students.push_front(student);
	LoadStudentsToModel();
}

void StudentMgr::SaveFile()
{
	SaveModelToStudents();
	std::ofstream ofs(_file_name, std::ios::out);
	std::for_each(_students.begin(), _students.end(), [&](const Student& student)
	{
		ofs << student._num << " " << student._name << " " << student._sex << " " << student._grade << " "
			<< student._chinese << " " << student._math << " " << student._english << std::endl;
	});
}

void StudentMgr::AddStudent()
{
	size_t size = _model->rowCount();
	_model->setItem(size, Student::Field::NUM, new QStandardItem(QStringLiteral("ѧ��")));
	_model->setItem(size, Student::Field::NAME, new QStandardItem(QStringLiteral("����")));
	_model->setItem(size, Student::Field::SEX, new QStandardItem(QStringLiteral("�Ա�(��/Ů)")));
	_model->setItem(size, Student::Field::GRADE, new QStandardItem(QStringLiteral("�꼶")));
	_model->setItem(size, Student::Field::CHINESE, new QStandardItem(QStringLiteral("����")));
	_model->setItem(size, Student::Field::MATH, new QStandardItem(QStringLiteral("��ѧ")));
	_model->setItem(size, Student::Field::ENGLISH, new QStandardItem(QStringLiteral("Ӣ��")));
	_table->selectRow(size);
}

void StudentMgr::FindStudentByNum()
{
	QString num = QInputDialog::getText(this, QStringLiteral("��ʾ"), QStringLiteral("������ѧ��:"));
	for (size_t i = 0; i < _model->rowCount(); i++)
	{
		if (_model->item(i, Student::Field::NUM)->text().compare(num) == 0)
		{
			_table->selectRow(i);
			return;
		}
	}
	QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("δ�ҵ�"));
}

void StudentMgr::FindStudentByName()
{
	QString name = QInputDialog::getText(this, QStringLiteral("��ʾ"), QStringLiteral("����������:"));
	for (size_t i = 0; i < _model->rowCount(); i++)
	{
		if (_model->item(i, Student::Field::NAME)->text().compare(name) == 0)
		{
			_table->selectRow(i);
			return;
		}
	}
	QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("δ�ҵ�"));
}

void StudentMgr::DeleteStudent()
{
	QModelIndexList list = _table->selectionModel()->selectedRows();
	std::vector<int> indexes;
	for (size_t i = 0; i < list.size(); i++)
		indexes.push_back(list.at(i).row());
	std::sort(indexes.begin(), indexes.end(), std::greater<int>());
	QString msg = QStringLiteral("���ѳɹ�Ȱ������ѧ����\n");
	for (size_t i = 0; i < indexes.size(); i++)
	{
		msg += (_model->item(indexes.at(i), Student::Field::NAME)->text() + "(" + _model->item(indexes.at(i), Student::Field::NUM)->text() + ")\n");
		_model->removeRow(indexes.at(i));
	}
	QMessageBox::information(this, QStringLiteral("�ɹ�"), msg);
	SaveFile();
}

void StudentMgr::ModifyStudent()
{
	QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("�����ֱ��ͨ����������λѧ�����༭"));
}

void StudentMgr::LoadStudentsToModel()
{
	_model->clear();
	_model->setHorizontalHeaderItem(Student::Field::NUM, new QStandardItem(QStringLiteral("ѧ��")));
	_model->setHorizontalHeaderItem(Student::Field::NAME, new QStandardItem(QStringLiteral("����")));
	_model->setHorizontalHeaderItem(Student::Field::SEX, new QStandardItem(QStringLiteral("�Ա�")));
	_model->setHorizontalHeaderItem(Student::Field::GRADE, new QStandardItem(QStringLiteral("�꼶")));
	_model->setHorizontalHeaderItem(Student::Field::CHINESE, new QStandardItem(QStringLiteral("����")));
	_model->setHorizontalHeaderItem(Student::Field::MATH, new QStandardItem(QStringLiteral("��ѧ")));
	_model->setHorizontalHeaderItem(Student::Field::ENGLISH, new QStandardItem(QStringLiteral("Ӣ��")));
	std::for_each(_students.begin(), _students.end(), [&](const Student& student)
	{
		AddStudentToModel(student);
	});
}

void StudentMgr::SaveModelToStudents()
{
	_students.clear();
	for (size_t row = 0; row < _model->rowCount(); row++)
		_students.push_front(GetStudentFromModel(row));
}

void StudentMgr::AddStudentToModel(const Student& student)
{
	size_t size = _model->rowCount();
	_model->setItem(size, Student::Field::NUM, new QStandardItem(QString::number(student._num)));
	_model->setItem(size, Student::Field::NAME, new QStandardItem(student._name.c_str()));
	_model->setItem(size, Student::Field::SEX, new QStandardItem(student._sex == 1 ? QStringLiteral("��") : QStringLiteral("Ů")));
	_model->setItem(size, Student::Field::GRADE, new QStandardItem(QString::number(student._grade)));
	_model->setItem(size, Student::Field::CHINESE, new QStandardItem(QString::number(student._chinese)));
	_model->setItem(size, Student::Field::MATH, new QStandardItem(QString::number(student._math)));
	_model->setItem(size, Student::Field::ENGLISH, new QStandardItem(QString::number(student._english)));
}

Student StudentMgr::GetStudentFromModel(size_t row)
{
	Student student;
	student._num = _model->item(row, Student::Field::NUM)->text().toInt();
	student._name = _model->item(row, Student::Field::NAME)->text().toStdString();
	student._sex = _model->item(row, Student::Field::SEX)->text() == QStringLiteral("��") ? 1 : 0;
	student._grade = _model->item(row, Student::Field::GRADE)->text().toInt();
	student._chinese = _model->item(row, Student::Field::CHINESE)->text().toInt();
	student._math = _model->item(row, Student::Field::MATH)->text().toInt();
	student._english = _model->item(row, Student::Field::ENGLISH)->text().toInt();
	return student;
}

void StudentMgr::Sort()
{
	_model->sort(_sort_column, _sort_order);
}

