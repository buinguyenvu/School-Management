#pragma once

#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>

class Administrator {
public:
	// Check login.
	void login();

	// Show menu, choose one of them.
	int adminOption(std::string username, std::string password);

	// Add Professor.
	int addProfessor();
	// Delete as much as possible Professors with the same keyword by either ID, Name, Day of Birth, Telephone Number or Hometown.
	int deleteProfessor(std::string str);
	// Search as much as possible Professors with the same keyword by either ID, Name, Day of Birth, Telephone Number or Hometown.
	void professorSearch(std::string str, bool &find);

	// Add Student.
	int addStudent();
	// Delete as much as possible Students with the same keyword by either ID, Name, Day of Birth or Hometown.
	int deleteStudent(std::string str);
	// Search as much as possible Students with the same keyword by either ID, Name, Day of Birth or Hometown.
	void studentSearch(std::string str, bool &find);

	// Change Password.
	int changePassword(std::string username, std::string &password);

	// Search all users. (1): Search all Students, (2): Search all Professors.
	void searchAll();
};

#endif // !ADMIN_H