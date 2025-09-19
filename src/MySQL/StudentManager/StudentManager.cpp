#include <iostream>
#include "StudentManager.h"

StudentManager::StudentManager()
{
	std::cout << "Initalize the Class: StudentManager~" << std::endl;

	// 初始化数据库句柄
	this->mysql = mysql_init(NULL);
	if (nullptr == this->mysql)
	{
		std::cerr << "MySQL对象初始化失败~" << mysql_error(this->mysql) << std::endl;
	}

	// 设计字符编码
	mysql_options(this->mysql, MYSQL_SET_CHARSET_NAME, "GBK");

	if (nullptr == mysql_real_connect(this->mysql,
		this->host.c_str(), this->user.c_str(), this->pw.c_str(),
		this->database_name.c_str(), this->port, NULL, 0))
	{
		std::cerr << "MySQL数据库引擎无法建立连接~" << mysql_error(this->mysql) << std::endl;
	}
}

StudentManager::~StudentManager()
{
	// 关闭数据库
	mysql_close(this->mysql);
	mysql_library_end();

	std::cout << "Destory the Class: StudentManager~" << std::endl;
}

// 代码一运行就初始化创建实例 ，本身就线程安全（类外定义并初始化，不必再加static关键字）
StudentManager* StudentManager::pStudentManager = new (std::nothrow) StudentManager();

StudentManager* StudentManager::getInstance()
{
	return pStudentManager;
}

void StudentManager::deleteInstance()
{
	if (pStudentManager)
	{
		delete pStudentManager;
		pStudentManager = nullptr;
		std::cout << "删除单例模式中的指针~" << std::endl;
	}
}

bool StudentManager::insertStudent(Student& stu)
{
	std::string message =
		std::format("INSERT INTO students (student_id,student_name,class_id) VALUES({},'{}','{}');",
			stu.student_id, stu.student_name.c_str(), stu.class_id.c_str());

	// 成功返回0，失败返回1
	if (mysql_real_query(this->mysql, message.c_str(), message.size()))
	{
		std::cerr << "insert failed! " << mysql_error(this->mysql) << std::endl;
		return false;
	}
	return true;
}

bool StudentManager::deleteStudent(int student_id)
{
	std::string message =
		std::format("DELETE FROM students WHERE student_id={};", student_id);

	// 成功返回0，失败返回1
	if (mysql_real_query(this->mysql, message.c_str(), message.size()))
	{
		std::cerr << "update failed! " << mysql_error(this->mysql) << std::endl;
		return false;
	}
	return true;
}

bool StudentManager::updateStudent(Student& stu)
{
	std::string message =
		std::format("UPDATE students SET student_name='{}',class_id='{}' WHERE student_id={};",
			stu.student_name.c_str(), stu.class_id.c_str(), stu.student_id);

	// 成功返回0，失败返回1
	if (mysql_real_query(this->mysql, message.c_str(), message.size()))
	{
		std::cerr << "update failed! " << mysql_error(this->mysql) << std::endl;
		return false;
	}
	return true;
}

std::vector<Student> StudentManager::getStudent(std::string condination)
{
	std::vector<Student> student_vector;

	std::string message =
		std::format("SELECT * FROM students {};",
			condination.c_str());

	// 成功返回0，失败返回1
	if (mysql_real_query(this->mysql, message.c_str(), message.size()))
	{
		std::cerr << "get failed! " << mysql_error(this->mysql) << std::endl;
	}

	// 获取结果集
	MYSQL_RES* res = mysql_store_result(this->mysql);

	// 给ROW赋值，判断ROW是否为空，不为空就打印数据
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		Student stu;
		stu.student_id = atoi(row[0]);
		stu.student_name = row[1];
		stu.class_id = row[2];

		student_vector.push_back(stu);
	}
	return student_vector;
}