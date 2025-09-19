#include <iostream>
#include "StudentManager/StudentManager.h"

int main(int argc, char* argv[])
{
	Student student(5, "Alex", "电子信息");

	StudentManager::getInstance()->updateStudent(student);
	StudentManager::deleteInstance();

	//student_manager->insertStudent(student);
	//student_manager->updateStudent(student);
	//student_manager->deleteStudent(5);

	return 0;
}