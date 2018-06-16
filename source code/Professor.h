#pragma once

#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <iostream>
#include <string>

class Professor {
public:
	std::string ProfessorID;
	std::string ProfessorName;
	std::string ProfessorDOB;
	std::string ProfessorTel;
	std::string ProfessorHometown;

	// Check login.
	void login();

	// Show menu. Choose one of them.
	int professorOption(std::string username, std::string password);

	// Change Password.
	int changePassword(std::string username, std::string &password);

	// Summarize Students' scores.
	void sumStuScore(std::string username);

	// Open Course.
	int openCourse(std::string username);

	// Modify a specific Student's score within a specific Course and specific Semester.
	int modScore(std::string username, int choice);
};

#endif // !PROFESSOR_H