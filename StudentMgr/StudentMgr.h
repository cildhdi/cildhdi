#ifndef _YL_STUDENTMGR_H_
#define _YL_STUDENTMGR_H_

#include <QtWidgets/QMainWindow>
#include <QMenuBar>
#include <QTableView>
#include <QTableWidgetItem>
#include <QStandardItemModel>
#include <forward_list>
#include "Student.h"

class StudentMgr : public QMainWindow
{
	Q_OBJECT

public:
	StudentMgr(QWidget *parent = Q_NULLPTR);
private:
	void LoadFile();
	void SaveFile();
	void AddStudent();
	void FindStudentByNum();
	void FindStudentByName();
	void DeleteStudent();
	void ModifyStudent();
	void LoadStudentsToModel();
	void SaveModelToStudents();
	void AddStudentToModel(const Student& student);
	Student GetStudentFromModel(size_t row);
	void Sort();
private:
	std::forward_list<Student> _students;
	QTableView* _table;
	QStandardItemModel* _model;
	const std::string _file_name = "student.txt";
	int _sort_column = Student::Field::NUM;
	Qt::SortOrder _sort_order = Qt::AscendingOrder;
};


#endif


