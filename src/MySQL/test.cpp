#include <iostream>
#include <string>
#include <mysql.h>

const std::string host = "127.0.0.1";
const std::string user = "root";
const std::string pw = "6213";
const std::string database_name = "student";
const int port = 3306;

struct Student
{
	int student_id;
	std::string student_name;
	std::string class_id;
};
int main(int argc, char* argv[])
{
	// 初始化数据库
	MYSQL* mysql;		// 数据库句柄
	mysql = mysql_init(NULL);

	// 设计字符编码
	mysql_options(mysql, MYSQL_SET_CHARSET_NAME, "GBK");

	if (!mysql_real_connect(mysql, host.c_str(), user.c_str(), pw.c_str(), database_name.c_str(), port, NULL, 0))
	{
		std::cerr << "Failed to connect to MySQL database: " << mysql_error(mysql) << std::endl;
		return -1;
	}
	else
	{
		std::cout << "Successed to connect to MySQL database" << std::endl;
	}

	// 查询数据
	std::string select_info = "select * from students;";
	int ret = mysql_real_query(mysql, select_info.c_str(), select_info.size());
	if (ret != 0)
	{
		std::cout << "mysql_real_query faied! " << std::endl;
	}
	else
	{
		std::cout << "mysql_real_query success! " << std::endl;
	}

	// 获取结果集
	MYSQL_RES* res;		// 查询结果集
	res = mysql_store_result(mysql);

	// 给ROW赋值，判断ROW是否为空，不为空就打印数据
	MYSQL_ROW row;		// 记录结构体
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		std::cout << row[0] << " "
			<< row[1] << " "
			<< row[2] << " "
			<< std::endl;
	}

	// 释放结果集
	mysql_free_result(res);

	// 关闭数据库
	mysql_close(mysql);
	mysql_library_end();

	system("pause");
	return 0;
}