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
	setWindowTitle(QStringLiteral("上海大学学生管理"));
	resize(1000, 800);

	QAction* load_file = new QAction(QStringLiteral("载入文件"), this);
	load_file->setShortcuts(QKeySequence::Open);
	load_file->setStatusTip(QStringLiteral("载入文件"));
	connect(load_file, &QAction::triggered, this, &StudentMgr::LoadFile);

	QAction* save_file = new QAction(QStringLiteral("立即保存"), this);
	save_file->setShortcuts(QKeySequence::Save);
	save_file->setStatusTip(QStringLiteral("立即保存"));
	connect(save_file, &QAction::triggered, this, &StudentMgr::SaveFile);

	QMenu* file = menuBar()->addMenu(QStringLiteral("文件"));
	file->addAction(load_file);
	file->addAction(save_file);

	QAction* find_by_num = new QAction(QStringLiteral("通过学号查找"), this);
	find_by_num->setStatusTip(QStringLiteral("通过学号查找"));
	connect(find_by_num, &QAction::triggered, this, &StudentMgr::FindStudentByNum);

	QAction* find_by_name = new QAction(QStringLiteral("通过姓名查找"), this);
	find_by_num->setStatusTip(QStringLiteral("通过姓名查找"));
	connect(find_by_name, &QAction::triggered, this, &StudentMgr::FindStudentByName);

	QMenu* find = menuBar()->addMenu(QStringLiteral("查找"));
	find->addAction(find_by_num);
	find->addAction(find_by_name);

	QMenu* sort_menu = menuBar()->addMenu(QStringLiteral("排序设置"));
	sort_menu->addSection("选择排序列");
	QString strs[] = {
		QStringLiteral("学号"),
		QStringLiteral("姓名"),
		QStringLiteral("性别"),
		QStringLiteral("年级"),
		QStringLiteral("语文成绩"),
		QStringLiteral("数学成绩"),
		QStringLiteral("英语成绩") };
	for (int index = Student::Field::NUM; index <= Student::Field::ENGLISH; index++)
	{
		QAction* action = new QAction(QStringLiteral("按照") + strs[index] + QStringLiteral("排序"));
		connect(action, &QAction::triggered, [&, index]()
		{
			_sort_column = index;
			Sort();
		});
		sort_menu->addAction(action);
	}
	sort_menu->addSection("升降序");
	QAction* action = new QAction(QStringLiteral("升序"));
	connect(action, &QAction::triggered, [&]()
	{
		_sort_order = Qt::SortOrder::AscendingOrder;
		Sort();
	});
	sort_menu->addAction(action);

	action = new QAction(QStringLiteral("降序"));
	connect(action, &QAction::triggered, [&]()
	{
		_sort_order = Qt::SortOrder::DescendingOrder;
		Sort();
	});
	sort_menu->addAction(action);


	QAction* add_student = new QAction(QStringLiteral("添加学生"), this);
	add_student->setShortcuts(QKeySequence::New);
	add_student->setStatusTip(QStringLiteral("添加学生"));
	connect(add_student, &QAction::triggered, this, &StudentMgr::AddStudent);

	QAction* delete_student = new QAction(QStringLiteral("一键退学"), this);
	delete_student->setShortcuts(QKeySequence::Delete);
	delete_student->setStatusTip(QStringLiteral("删除学生"));
	connect(delete_student, &QAction::triggered, this, &StudentMgr::DeleteStudent);

	QAction* modify_student = new QAction(QStringLiteral("修改学生信息"), this);
	modify_student->setStatusTip(QStringLiteral("修改学生信息"));
	connect(modify_student, &QAction::triggered, this, &StudentMgr::ModifyStudent);

	QMenu* student_operate = menuBar()->addMenu(QStringLiteral("学生操作"));
	student_operate->addAction(add_student);
	student_operate->addAction(delete_student);
	student_operate->addAction(modify_student);

	QAction* about_us = new QAction(QStringLiteral("关于小组"));
	about_us->setStatusTip(QStringLiteral("关于小组"));
	connect(about_us, &QAction::triggered, [this]()
	{
		QMessageBox::about(this, QStringLiteral("关于我们"), QStringLiteral("成员：\n                    邓泽远\n                    荀嘉皓\n                    丁晗\n                    杨磊"));
	});

	QAction* about_qt = new QAction(QStringLiteral("关于Qt"));
	about_qt->setStatusTip(QStringLiteral("关于Qt"));
	connect(about_qt, &QAction::triggered, [this]()
	{
		QMessageBox::aboutQt(this);
	});

	QMenu* about = menuBar()->addMenu(QStringLiteral("关于"));
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
	_model->setItem(size, Student::Field::NUM, new QStandardItem(QStringLiteral("学号")));
	_model->setItem(size, Student::Field::NAME, new QStandardItem(QStringLiteral("姓名")));
	_model->setItem(size, Student::Field::SEX, new QStandardItem(QStringLiteral("性别(男/女)")));
	_model->setItem(size, Student::Field::GRADE, new QStandardItem(QStringLiteral("年级")));
	_model->setItem(size, Student::Field::CHINESE, new QStandardItem(QStringLiteral("语文")));
	_model->setItem(size, Student::Field::MATH, new QStandardItem(QStringLiteral("数学")));
	_model->setItem(size, Student::Field::ENGLISH, new QStandardItem(QStringLiteral("英语")));
	_table->selectRow(size);
}

void StudentMgr::FindStudentByNum()
{
	QString num = QInputDialog::getText(this, QStringLiteral("提示"), QStringLiteral("请输入学号:"));
	for (size_t i = 0; i < _model->rowCount(); i++)
	{
		if (_model->item(i, Student::Field::NUM)->text().compare(num) == 0)
		{
			_table->selectRow(i);
			return;
		}
	}
	QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("未找到"));
}

void StudentMgr::FindStudentByName()
{
	QString name = QInputDialog::getText(this, QStringLiteral("提示"), QStringLiteral("请输入姓名:"));
	for (size_t i = 0; i < _model->rowCount(); i++)
	{
		if (_model->item(i, Student::Field::NAME)->text().compare(name) == 0)
		{
			_table->selectRow(i);
			return;
		}
	}
	QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("未找到"));
}

void StudentMgr::DeleteStudent()
{
	QModelIndexList list = _table->selectionModel()->selectedRows();
	std::vector<int> indexes;
	for (size_t i = 0; i < list.size(); i++)
		indexes.push_back(list.at(i).row());
	std::sort(indexes.begin(), indexes.end(), std::greater<int>());
	QString msg = QStringLiteral("您已成功劝退以下学生：\n");
	for (size_t i = 0; i < indexes.size(); i++)
	{
		msg += (_model->item(indexes.at(i), Student::Field::NAME)->text() + "(" + _model->item(indexes.at(i), Student::Field::NUM)->text() + ")\n");
		_model->removeRow(indexes.at(i));
	}
	QMessageBox::information(this, QStringLiteral("成功"), msg);
	SaveFile();
}

void StudentMgr::ModifyStudent()
{
	QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("你可以直接通过查找来定位学生并编辑"));
}

void StudentMgr::LoadStudentsToModel()
{
	_model->clear();
	_model->setHorizontalHeaderItem(Student::Field::NUM, new QStandardItem(QStringLiteral("学号")));
	_model->setHorizontalHeaderItem(Student::Field::NAME, new QStandardItem(QStringLiteral("姓名")));
	_model->setHorizontalHeaderItem(Student::Field::SEX, new QStandardItem(QStringLiteral("性别")));
	_model->setHorizontalHeaderItem(Student::Field::GRADE, new QStandardItem(QStringLiteral("年级")));
	_model->setHorizontalHeaderItem(Student::Field::CHINESE, new QStandardItem(QStringLiteral("语文")));
	_model->setHorizontalHeaderItem(Student::Field::MATH, new QStandardItem(QStringLiteral("数学")));
	_model->setHorizontalHeaderItem(Student::Field::ENGLISH, new QStandardItem(QStringLiteral("英语")));
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
	_model->setItem(size, Student::Field::SEX, new QStandardItem(student._sex == 1 ? QStringLiteral("男") : QStringLiteral("女")));
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
	student._sex = _model->item(row, Student::Field::SEX)->text() == QStringLiteral("男") ? 1 : 0;
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

