#pragma once
#ifndef __STUDENTMANAGER_H__
#define __STUDENTMANAGER_H__

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <format>
#include <mysql.h>

typedef struct Student
{
	int student_id;
	std::string student_name;
	std::string class_id;
};

class StudentManager
{
private:
	MYSQL* mysql;
	const std::string host = "127.0.0.1";
	const std::string user = "root";
	const std::string pw = "6213";
	const std::string database_name = "student";
	const int port = 3306;

public:
	StudentManager();
	virtual ~StudentManager();
	static StudentManager* pStudentManager;	// 类内声明
	static StudentManager* getInstance();		// 获取单实例
	static void deleteInstance();	// 释放单实例，进程退出时调用
	bool insertStudent(Student& stu);
	bool deleteStudent(int student_id);
	bool updateStudent(Student& stu);
	std::vector<Student> getStudent(std::string condination = "");
};

#endif // !__STUDENTMANAGER_H__
