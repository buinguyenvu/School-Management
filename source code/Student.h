#pragma once

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

class Student {
public:
	std::string StudentID;
	std::string StudentName;
	std::string StudentDOB;
	std::string StudentHometown;
	int StudentCredit = 0;

	// Check login.
	void login();

	// Show menu. Choose one of them.
	int studentOption(std::string username, std::string password);

	// Change Password.
	int changePassword(std::string username, std::string &password);

	// Register course.
	int registerCourse(std::string username);
	// Un-course.
	int unCourse(std::string username);

	// Show menu of contents. Choose one of them.
	int viewProfile(std::string username);

	// Show GPA.
	int viewGPA(std::string username);
	// Show registered courses.
	int viewRegisteredCourses(std::string username);
	// Show courses of Student during a specific semester.
	int viewCoursesSem(std::string username);

	// Find many courses with the same key word by name.
	int uniCourses(std::string str);
};

#endif // !STUDENT_H