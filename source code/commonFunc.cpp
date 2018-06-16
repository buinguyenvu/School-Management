#include <iostream>
#include <string>
#include <iomanip>
#include "commonFunc.h"
#include "Professor.h"
#include "Student.h"
#include "Administrator.h"

bool checkDigit(std::string str) {
	for (unsigned int i = 0; i < str.length(); i++) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

bool checkSubStr(Student S, std::string str) {
	if (S.StudentID.find(str) != std::string::npos) {
		return true;
	}
	else if (S.StudentName.find(str) != std::string::npos) {
		return true;
	}
	else if (S.StudentDOB.find(str) != std::string::npos) {
		return true;
	}
	else if (S.StudentHometown.find(str) != std::string::npos) {
		return true;
	}
	return false;
}

bool checkSubStr(std::string str1, std::string str2) {
	if (str1.find(str2) != std::string::npos)
		return true;
	return false;
}

bool checkSubStr(Professor P, std::string str) {
	if (P.ProfessorID.find(str) != std::string::npos) {
		return true;
	}
	else if (P.ProfessorName.find(str) != std::string::npos) {
		return true;
	}
	else if (P.ProfessorDOB.find(str) != std::string::npos) {
		return true;
	}
	else if (P.ProfessorTel.find(str) != std::string::npos) {
		return true;
	}
	else if (P.ProfessorHometown.find(str) != std::string::npos) {
		return true;
	}
	return false;
}

bool checkSubStr(std::string str1[], std::string str2[], int size, int index1[], int index2[], int &count) {
	bool find = false;
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (str1[i].find(str2[j]) != std::string::npos) {
				find = true;
				count++;
				// Store the indexes
				index1[i] = i;
				index2[j] = j;
			}
		}
	}
	return find;
}

bool checkSubStr(std::string str1[], std::string str, int size) {
	for (int i = 0; i < size; i++) {
		if (str1[i].find(str) != std::string::npos)
			return true;
	}
	return false;
}

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}