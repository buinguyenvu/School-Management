#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <climits>
#include "Professor.h"
#include "commonFunc.h"
using namespace std;

void Professor::login() {
	system("cls");
	cout << "\n\t\t\t\t\t\tPROFESSOR LOGIN\n\n";
	bool checkUsername = false;
	bool checkPassword = false;
	do {
		cout << "Login:\n\n";
		cout << "Username: ";
		string name; cin >> name;
		cout << "Password: ";
		string pass; cin >> pass;

		Professor P;
		ifstream userFile("user.csv");
		string username, password, type;
		if (userFile.is_open()) {
			while (userFile.is_open()) {
				getline(userFile, username, ',');
				getline(userFile, password, ',');
				getline(userFile, type, '\n');
				if (type == "teacher") {
					if (username == name) {
						checkUsername = true;
						if (password == pass) {
							checkPassword = true;
							P.professorOption(name, pass);
							break;
						}
					}
				}
				if (userFile.eof())
					break;
			}
			userFile.close();
		}
		else {
			system("cls");
			cout << "Unable to open file\n";
			system("pause");
		}
		if (checkUsername != true || checkPassword != true) {
			system("cls");
			cout << "\n\t\t\t\t\t\tPROFESSOR LOGIN\n";
			cout << "Incorrect username or password, please type again!!\n";
		}
	} while (checkUsername == false || checkPassword == false);
}

int Professor::professorOption(string username, string password) {
	Professor P;
	int option;
	string str;
	int tmp;
	LOOP:
	do {
		system("cls");
		cout << "\n\t\t\t\t\t\tPROFESSOR OPTIONS\n\n";
		cout << "\n1. Change password\n2. Open Courses\n3. Summarize students's score each opened course\n4. Modify students's score each opened course\n5. Logout\n\n";
		cout << "Enter your option: ";
		cin >> str;
		cin.ignore(32767, '\n');
		if (checkDigit(str) == true) {
			option = stoi(str);
			switch (option) {
			case 1:
				P.changePassword(username, password);
				break;
			case 2:
				P.openCourse(username);
				break;
			case 3:
				P.sumStuScore(username);
				cout << "Do you want to modify student's Score?\n1. Yes\n2. No\n";
				do {
					do {
						getline(cin, str);
					} while (checkDigit(str) == false);
					tmp = stoi(str);
					if (tmp == 1) {
						P.modScore(username, 1);
						break;
					}
					if (tmp == 2) {
						break;
					}
				} while (1);
				break;
			case 4:
				P.modScore(username, 2);
				break;
			case 5:
				return 0;
				break;
			default:
				system("cls");
				cout << "Invalid option!!\n";
				system("pause");
				break;
			}
			goto LOOP;
		}
		else goto LOOP;
	} while (1);
	return 0;
}

int Professor::changePassword(string username, string &password) {
	system("cls");
	cout << "\n\t\t\t\t\t\tCHANGE PROFESSOR PASSWORD\n\n";
	string name, pass, type;
	ifstream UserFile("user.csv");
	ofstream trashFile("trashData.txt");
	if (UserFile.is_open()) {
		while (UserFile.is_open()) {
			getline(UserFile, name, ',');
			getline(UserFile, pass, ',');
			getline(UserFile, type, '\n');
			if (username == name && type == "teacher") {
				string newpass;
				do {
					cout << "\n\nConfirm your password: ";
					cin >> pass;
					if (password == pass) {
						system("cls");
						cout << "\n\t\t\t\t\t\tCHANGE PROFESSOR PASSWORD\n\n";
						cout << "\n\nConfirm your password: " << password << endl;
						cout << "Type your new password: ";
						cin >> newpass;
						if (username != "")
							trashFile << username << "," << newpass << "," << "teacher" << endl;
						break;
					}
					else {
						system("cls");
						cout << "\n\t\t\t\t\t\tCHANGE PROFESSOR PASSWORD\n\n";
						cout << "Wrong password!!";
					}
				} while (pass != password);
				password = newpass;
			}
			if (username != name && name != "")
				trashFile << name << "," << pass << "," << type << endl;
			if (UserFile.eof())
				break;
		}
		UserFile.close();
		trashFile.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}
	remove("user.csv");
	rename("trashData.txt", "user.csv");

	// Phase 2:
	ofstream UserFile1("user.csv");
	ifstream trashFile1("trashData.txt");
	if (trashFile1.is_open()) {
		while (trashFile1.is_open()) {
			getline(trashFile1, name, ',');
			getline(trashFile1, pass, ',');
			getline(trashFile1, type, '\n');
			if (name != "")
				UserFile1 << name << "," << pass << "," << type << endl;
			if (trashFile1.eof())
				break;
		}
		trashFile1.close();
		UserFile1.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}
	remove("user.csv");
	rename("trashData.txt", "user.csv");

	cout << "\n\nPassword is updated!!\n\n";
	system("pause");
	return 0;
}

int Professor::openCourse(string username) {
	system("cls");
	cout << "\n\t\t\t\t\t\tOPEN COURSE\n\n";
	cout << "Enter semester you want to open course: ";
	string str; getline(cin, str);

	ifstream objectFile("object.csv");
	if (objectFile.is_open()) {
		string CID, SID, TID, Score, SemesID;
		string courses[5];
		int countCourse = -1;
		while (objectFile.is_open()) {
			getline(objectFile, CID, ',');
			getline(objectFile, SID, ',');
			getline(objectFile, TID, ',');
			getline(objectFile, Score, ',');
			getline(objectFile, SemesID, '\n');
			if (TID == username && str == SemesID) {
				if (CID != "") {
					countCourse++;
					courses[countCourse] = CID;
				}
			}
			if (objectFile.eof()) {
				if (countCourse == 4) {
					cout << "\n\t" << setw(15) << left << "Course ID\n";
					for (int i = 0; i <= countCourse; i++)
						cout << "\n\t" << courses[i];
					cout << "\nCannot open more course!! You already had 5 courses!!\n\n";
					system("pause");
					return 0;
				}
				break;
			}
		}
		objectFile.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}

	string cid, name, slot, credit;
	cout << "Enter Course's ID: "; getline(cin, cid);
	cout << "Enter Course's Name: "; getline(cin, name);
	cout << "Enter Course's Slot: "; getline(cin, slot);
	cout << "Enter Course's Credit: "; getline(cin, credit);

	ifstream courseFile("course.csv");
	ofstream trashFile("trashData.txt");
	if (courseFile.is_open()) {
		string CID, TID, CourseName, NumberStu, Slot, Credit;
		while (courseFile.is_open()) {
			getline(courseFile, CID, ',');
			getline(courseFile, TID, ',');
			getline(courseFile, CourseName, ',');
			getline(courseFile, NumberStu, ',');
			getline(courseFile, Slot, ',');
			getline(courseFile, Credit, '\n');
			if (!courseFile.eof()) {
				if (!CID.empty()) {
					trashFile << CID << "," << TID << "," << CourseName << "," << NumberStu << "," << Slot << "," << Credit << endl;
				}
			}
			if (courseFile.eof()) {
				trashFile << cid << "," << username << "," << name << ",0," << slot << "," << credit << endl;
				cout << "Course is added!!\n";
				system("pause");
				break;
			}
		}
		courseFile.close();
		trashFile.close();
		remove("course.csv");
		rename("trashData.txt", "course.csv");
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
	}
	return 0;
}

void Professor::sumStuScore(string username) {
	system("cls");
	cout << "\n\t\t\t\t\t\tSUMMARIZE STUDENTS' SCORE\n\n";
	cout << "\n\nEnter semester you want to summarize: ";
	string semes; getline(cin, semes);
	cout << "Enter Course's ID you want to summarize: ";
	string cid; getline(cin, cid);
	
	ifstream objectFile("object.csv");
	if (objectFile.is_open()) {
		string CID, SID, TID, Score, SemesID;
		cout << "\n\t" << setw(20) << left << "CourseID"
			<< setw(20) << left << "StudentID"
			<< setw(30) << left << "TeacherID"
			<< setw(30) << left << "Score"
			<< setw(10) << left << "SemesterID" << endl;
		cout << "\t***************************************************************************************************************\n";
		while (objectFile.is_open()) {
			getline(objectFile, CID, ',');
			getline(objectFile, SID, ',');
			getline(objectFile, TID, ',');
			getline(objectFile, Score, ',');
			getline(objectFile, SemesID, '\n');
			if (!objectFile.eof()) {
				if (!CID.empty()) {
					if(CID == cid && TID == username && SemesID == semes)
						cout << "\t" << setw(20) << left << CID
						<< setw(20) << left << SID
						<< setw(30) << left << TID
						<< setw(30) << left << Score
						<< setw(10) << left << SemesID << endl;
				}
			}
			if (objectFile.eof()) {
				cout << endl;
				break;
			}
		}
		objectFile.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
	}

}

int Professor::modScore(std::string username, int choice) {
	if (choice == 2) {
		system("cls");
		cout << "\n\t\t\t\t\t\tMODIFY STUDENT'S SCORE\n\n";
	}
	cout << "Enter Semester ID: ";
	string semesID; cin >> semesID;
	cout << "Enter Course ID: ";
	string course; cin >> course;
	cout << "Enter Student ID: ";
	string stuID; cin >> stuID;
	string newScore;
	ifstream objectFile("object.csv");
	ofstream trashFile("trashData.txt");
	string CID, SID, TID, Score, SemesID;
	if (objectFile.is_open()) {
		bool check = false;
		cout << "\t" << setw(15) << left << "Course_ID"
			<< setw(15) << left << "Teacher_ID"
			<< setw(15) << left << "Score"
			<< setw(15) << left << "Semester_ID" << endl;
		cout << "\t************************************************************\n";
		while (objectFile.is_open()) {
			getline(objectFile, CID, ',');
			getline(objectFile, SID, ',');
			getline(objectFile, TID, ',');
			getline(objectFile, Score, ',');
			getline(objectFile, SemesID, '\n');
			if (CID == course && TID == username && SID == stuID && semesID == SemesID) {
				check = true;
				cout << "\t" << setw(15) << left << CID
					<< setw(15) << left << TID
					<< setw(15) << left << Score
					<< setw(15) << left << SemesID << endl;
				cout << "Enter new Score: ";
				cin >> newScore;
				trashFile << CID << "," << SID << "," << TID << "," << newScore << "," << SemesID << endl;
				cout << "Updated\n";
				cout << "\t" << setw(15) << left << "Course_ID"
					<< setw(15) << left << "Teacher_ID"
					<< setw(15) << left << "Score"
					<< setw(15) << left << "Semester_ID" << endl;
				cout << "\t************************************************************\n";
				cout << "\t" << setw(15) << left << CID
					<< setw(15) << left << TID
					<< setw(15) << left << newScore
					<< setw(15) << left << SemesID << endl;
			}
			else {
				if (!CID.empty())
					trashFile << CID << "," << SID << "," << TID << "," << Score << "," << SemesID << endl;
			}
			if (objectFile.eof()) {
				if (check == false) {
					cout << "Incorect information!! Check again!!\n";
					system("pause");
					return 0;
				}
				break;
			}
		}
		objectFile.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}
	
	ofstream objectFile1("object.csv");
	ifstream trashFile1("trashData.txt");
	if (trashFile1.is_open()) {
		while (trashFile1.is_open()) {
			getline(trashFile1, CID, ',');
			getline(trashFile1, SID, ',');
			getline(trashFile1, TID, ',');
			getline(trashFile1, Score, ',');
			getline(trashFile1, SemesID, '\n');
			if (!CID.empty())
				objectFile1 << CID << "," << SID << "," << TID << "," << Score << "," << SemesID << endl;
			if (trashFile1.eof())
				break;
		}
		trashFile1.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}
	system("pause");
	return 0;
}
