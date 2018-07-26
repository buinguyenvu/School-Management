#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <climits>
#include "Student.h"
#include "commonFunc.h"
using namespace std;

#define SIZE 300
string tempCID[SIZE];
string tempTID[SIZE];
string tempSID[SIZE];
string courses[SIZE];
string teachers[SIZE];
string credit[SIZE];
int index;

void Student::login() {
	system("cls");
	cout << "\n\t\t\t\t\t\tSTUDENT LOGIN\n\n";
	bool checkUsername = false;
	bool checkPassword = false;
	do {
		cout << "Login:\n\n";
		cout << "Username: ";
		string name; cin >> name;
		cout << "Password: ";
		string pass; cin >> pass;

		Student S;
		ifstream userFile("user.csv");
		string username, password, type;
		if (userFile.is_open()) {
			while (userFile.is_open()) {
				getline(userFile, username, ',');
				getline(userFile, password, ',');
				getline(userFile, type, '\n');
				if (type == "student") {
					if (username == name) {
						checkUsername = true;
						if (password == pass) {
							checkPassword = true;
							S.studentOption(name, pass);
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
			cout << "\n\t\t\t\t\t\tSTUDENT LOGIN\n";
			cout << "Incorrect username or password, please type again!!\n";
		}
	} while (checkUsername == false || checkPassword == false);
}

int Student::studentOption(string username, string password) {
	Student S;
	int option;
	string str;
	LOOP:
	do {
		system("cls");
		cout << "\n\t\t\t\t\t\tSTUDENT OPTIONS\n\n";
		cout << "\n1. Change Password\n2. Register course\n3. Un-course\n4. View Profile:\n\tView GPA\n\tView all registered course (including other semesters)\n\tView courses within a semester\n5. View Courses in university\n6. Logout\n\n";
		cout << "You can only enter number!!\n\nEnter your option: ";
		cin >> str;
		cin.ignore(32767, '\n');
		if (checkDigit(str) == true) {
			option = stoi(str);
			switch (option) {
			case 1:
				S.changePassword(username, password);
				break;
			case 2:
				S.registerCourse(username);
				break;
			case 3:
				S.unCourse(username);
				break;
			case 4:
				S.viewProfile(username);
				break;
			case 5:
				cout << "Enter name of Course you want to search for: ";
				getline(cin, str);
				S.uniCourses(str);
				break;
			case 6:
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

int Student::changePassword(string username, string &password) {
	system("cls");
	cout << "\n\t\t\t\t\t\tCHANGE STUDENT PASSWORD\n\n";
	string name, pass, type;
	ifstream UserFile("user.csv");
	ofstream trashFile("trashData.txt");
	if (UserFile.is_open()) {
		while (UserFile.is_open()) {
			getline(UserFile, name, ',');
			getline(UserFile, pass, ',');
			getline(UserFile, type, '\n');
			if (username != name && name != "") {
				trashFile << name << "," << pass << "," << type << endl;
			}
			if (username == name && type == "student") {
				string newpassword;
				do {
					cout << "\n\nConfirm your password: ";
					cin >> pass;
					if (password == pass) {
						system("cls");
						cout << "\n\t\t\t\t\t\tCHANGE STUDENT PASSWORD\n\n";
						cout << "\n\nConfirm your password: " << pass << endl;
						cout << "Type your new password: ";
						cin >> newpassword;
						if (username != "")
							trashFile << username << "," << newpassword << "," << "student" << endl;
					}
					else {
						system("cls");
						cout << "\n\t\t\t\t\t\tCHANGE STUDENT PASSWORD\n\n";
						cout << "Wrong password!!";
					}
				} while (pass != password);
				password = newpassword;
			}
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
		cout << "Unable to open file\n";
		system("pause");
		return 0;
	}

	remove("user.csv");
	rename("trashData.txt", "user.csv");

	cout << "\n\nPassword is updated!!\n\n";
	system("pause");
	return 0;
}

int Student::registerCourse(string username) {
	system("cls");
	cout << "\n\t\t\t\t\t\tREGISTER COURSE\n\n";

	cout << "Enter semester ID: ";
	string semes; getline(cin, semes);

	cout << "Available Courses:\n\n";
	
	string CID, TID, CourseName, NumberStu, Slot, Credit, SID, Score, SemesID;
	ifstream courseFile("course.csv");
	if (courseFile.is_open()) {
		while (courseFile.is_open()) {
			getline(courseFile, CID, ',');
			getline(courseFile, TID, ',');
			getline(courseFile, CourseName, ',');
			getline(courseFile, NumberStu, ',');
			getline(courseFile, Slot, ',');
			getline(courseFile, Credit, '\n');
			
			if (!courseFile.eof()) {
				cout << "\t" << setw(20) << left << CID
					<< setw(15) << left << TID
					<< setw(30) << left << CourseName
					<< setw(30) << left << NumberStu
					<< setw(15) << left << Slot
					<< setw(10) << left << Credit << endl;
			}

			if (courseFile.eof())
				break;
		}
		courseFile.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}

	cout << "\t**********************************************************************************************************\n";
	cout << "\n\tEnter Course's ID: ";
	string co; getline(cin, co);
	cout << "\n\tEnter Teacher's ID: ";
	string te; getline(cin, te);
	Student S;
	index = -1;

	ifstream objectFile2("object.csv");
	if (objectFile2.is_open()) {
		while (objectFile2.is_open()) {
			getline(objectFile2, CID, ',');
			getline(objectFile2, SID, ',');
			getline(objectFile2, TID, ',');
			getline(objectFile2, Score, ',');
			getline(objectFile2, SemesID, '\n');
			if (!objectFile2.eof()) {
				if (!CID.empty()) {
					if (SID == username && SemesID == semes) {
						index++;
						tempCID[index] = CID;
					}
				}
			}
			if (objectFile2.eof())
				break;
		}
		objectFile2.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}
	
	bool check = false;
	int tmpCredit;
	ifstream courseFile2("course.csv");
	if (courseFile2.is_open()) {
		while (courseFile2.is_open()) {
			getline(courseFile2, CID, ',');
			getline(courseFile2, TID, ',');
			getline(courseFile2, CourseName, ',');
			getline(courseFile2, NumberStu, ',');
			getline(courseFile2, Slot, ',');
			getline(courseFile2, Credit, '\n');
			if (!courseFile2.eof()) {
				if (!CID.empty()) {
					for (int i = 0; i <= index; i++) {
						if (CID == co && TID == te) {
							S.StudentCredit += stoi(Credit);
							tmpCredit = stoi(Credit);
							check = true;
						}
					}
				}
			}
			if (courseFile2.eof()) {
				break;
			}
		}
		courseFile2.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}
	if (check == false) {
		cout << "Wrong information!! Try again!!\n";
		system("pause");
		return 0;
	}
	if ((20 - S.StudentCredit) < tmpCredit) {
		cout << "You can not register more!! You have " << S.StudentCredit << " credits now!!\n";
		system("pause");
		return 0;
	}

	ofstream trashFile("trashData.txt");
	ifstream courseFile1("course.csv");
	if (courseFile1.is_open()) {
		while (courseFile1.is_open()) {
			getline(courseFile1, CID, ',');
			getline(courseFile1, TID, ',');
			getline(courseFile1, CourseName, ',');
			getline(courseFile1, NumberStu, ',');
			getline(courseFile1, Slot, ',');
			getline(courseFile1, Credit, '\n');
			if (!courseFile1.eof()) {
				if (!CID.empty()) {
					if (checkSubStr(CID, co) == true && checkSubStr(TID, te) == true) {
						int tmp = stoi(NumberStu);
						NumberStu = to_string(tmp + 1);
					}
					trashFile << CID << "," << TID << "," << CourseName << "," << NumberStu << "," << Slot << "," << Credit << endl;
				}
			}
			if (courseFile1.eof())
				break;
		}
		courseFile1.close();
		trashFile.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}
	remove("course.csv");
	rename("trashData.txt", "course.csv");

	ofstream trashFile1("trashData.txt");
	ifstream objectFile("object.csv");
	if (objectFile.is_open()) {
		while (objectFile.is_open()) {
			getline(objectFile, CID, ',');
			getline(objectFile, SID, ',');
			getline(objectFile, TID, ',');
			getline(objectFile, Score, ',');
			getline(objectFile, SemesID, '\n');
			if (!objectFile.eof()) {
				if (!CID.empty()) {
					if (CID == co && SID == username && SemesID == semes) {
						cout << "You already registered that course!!\n";
						system("pause");
						return 0;
					}
					trashFile1 << CID << "," << SID << "," << TID << "," << Score << "," << SemesID << endl;
				}
			}
			if (objectFile.eof()) {
				trashFile1 << co << "," << username << "," << te << ",NULL," << semes << endl;
				break;
			}
		}
		objectFile.close();
		trashFile1.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}

	ifstream trashFile2("trashData.txt");
	ofstream objectFile1("object.csv");
	if (trashFile2.is_open()) {
		while (trashFile2.is_open()) {
			getline(trashFile2, CID, ',');
			getline(trashFile2, SID, ',');
			getline(trashFile2, TID, ',');
			getline(trashFile2, Score, ',');
			getline(trashFile2, SemesID, '\n');
			if (!trashFile2.eof()) {
				if (!CID.empty())
					objectFile1 << CID << "," << SID << "," << TID << "," << Score << "," << SemesID << endl;
			}
			if (trashFile2.eof())
				break;
		}
		trashFile2.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}

	cout << "\nRegister successful!!\n";
	system("pause");
	return 0;
}

int Student::unCourse(string username) {
	system("cls");
	cout << "\n\t\t\t\t\t\tUN-COURSE\n\n";
	string CID, TID, CourseName, NumberStu, Slot, Credit, SID, Score, SemesID;
	string te;
	bool check = false;
	cout << "\tAll registered courses!!\n";
	cout << "\t" << setw(20) << left << "Course ID"
		<< setw(20) << left << "Student ID"
		<< setw(20) << left << "Teacher ID"
		<< setw(20) << left << "Score"
		<< setw(20) << left << "Semester ID" << endl;
	cout << "\t**************************************************************************************************************\n";
	ifstream objectFile("object.csv");
	if (objectFile.is_open()) {
		while (objectFile.is_open()) {
			getline(objectFile, CID, ',');
			getline(objectFile, SID, ',');
			getline(objectFile, TID, ',');
			getline(objectFile, Score, ',');
			getline(objectFile, SemesID, '\n');
			if (!objectFile.eof()) {
				if (!CID.empty()) {
					if (SID == username && Score == "NULL") {
						cout << "\t" << setw(20) << left << CID
							<< setw(20) << left << SID
							<< setw(20) << left << TID
							<< setw(20) << left << Score
							<< setw(20) << left << SemesID << endl;
						check = true;
					}
				}
			}
			if (objectFile.eof()) {
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
	if (check == false) {
		cout << "\n\nYou have not registered any course yet!!\n\n";
		system("pause");
		return 0;
	}
	cout << "\nEnter Course's ID: ";
	string cid; getline(cin, cid);

	ifstream objectFile1("object.csv");
	ofstream trashFile("trashData.txt");
	if (objectFile1.is_open()) {
		while (objectFile1.is_open()) {
			getline(objectFile1, CID, ',');
			getline(objectFile1, SID, ',');
			getline(objectFile1, TID, ',');
			getline(objectFile1, Score, ',');
			getline(objectFile1, SemesID, '\n');
			if (!objectFile1.eof()) {
				if (!CID.empty()) {
					if (CID == cid && Score == "NULL" && SID == username) {
						te = TID;
					}
					else {
						trashFile << CID << "," << SID << "," << TID << "," << Score << "," << SemesID << endl;
					}
				}
			}
			if (objectFile1.eof())
				break;
		}
		objectFile1.close();
		trashFile.close();
	}
	else {
		system("cls");
		cout << "\n\t\t\t\t\t\tUN-COURSE\n\n";
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}
	remove("object.csv");
	rename("trashData.txt", "object.csv");
	
	ifstream courseFile("course.csv");
	ofstream trashFile1("trashData.txt");
	if (courseFile.is_open()) {
		while (courseFile.is_open()) {
			getline(courseFile, CID, ',');
			getline(courseFile, TID, ',');
			getline(courseFile, CourseName, ',');
			getline(courseFile, NumberStu, ',');
			getline(courseFile, Slot, ',');
			getline(courseFile, Credit, '\n');

			if (!courseFile.eof()) {
				if (!CID.empty()) {
					if (CID == cid && TID == te) {
						int tmp = stoi(NumberStu);
						NumberStu = to_string(tmp - 1);
					}
					trashFile1 << CID << "," << TID << "," << CourseName << "," << NumberStu << "," << Slot << "," << Credit << endl;
				}
			}

			if (courseFile.eof())
				break;
		}
		courseFile.close();
		trashFile1.close();
	}
	else {
		system("cls");
		cout << "\n\t\t\t\t\t\tUN-COURSE\n\n";
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}
	
	ifstream trashFile2("trashData.txt");
	ofstream courseFile1("course.csv");
	if (trashFile2.is_open()) {
		while (trashFile2.is_open()) {
			getline(trashFile2, CID, ',');
			getline(trashFile2, TID, ',');
			getline(trashFile2, CourseName, ',');
			getline(trashFile2, NumberStu, ',');
			getline(trashFile2, Slot, ',');
			getline(trashFile2, Credit, '\n');
			if (!trashFile2.eof()) {
				if (!CID.empty())
					courseFile1 << CID << "," << TID << "," << CourseName << "," << NumberStu << "," << Slot << "," << Credit << endl;
			}
			if (trashFile2.eof())
				break;
		}
		trashFile2.close();
		courseFile1.close();
	}
	else {
		system("cls");
		cout << "\n\t\t\t\t\t\tUN-COURSE\n\n";
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}

	cout << "Un-course succeed!!\n";
	system("pause");
	return 0;
}

int Student::viewProfile(string username) {
	system("cls");
	cout << "\n\t\t\t\t\t\tVIEW PROFILE OPTION\n\n";
	Student S;
	int option;
	string str;
LOOP:
	do {
		system("cls");
		cout << "\n1. View GPA in a semester\n2. View all registered courses (including other semesters)\n3. View courses during semester\n4. Exit\n\n";
		cout << "You can only enter number!!\nEnter your option: ";
		cin >> str;
		if (checkDigit(str) == true) {
			option = stoi(str);
			switch (option) {
			case 1:
				S.viewGPA(username);
				break;
			case 2:
				S.viewRegisteredCourses(username);
				break;
			case 3:
				S.viewCoursesSem(username);
				break;
			case 4:
				return 0;
			default:
				system("cls");
				cout << "Invalid option!!\n";
				system("pause");
			}
			goto LOOP;
		}
		else
			goto LOOP;
	} while (1);
	return 0;
}

int Student::viewGPA(string username) {
	system("cls");
	cout << "\n\t\t\t\t\t\tVIEW GPA\n\n";
	cout << "Select semester you want to see GPA: \n";
	string semes; cin >> semes;
	ifstream objectFile("object.csv");
	ifstream courseFile("course.csv");
	ofstream trashFile("trashData.txt");
	string CID, SID, TID, Score, SemesID, CourseName, NumberStu, Slot, Credit;
	double GPA = 0;
	int countSemester = 0, totalCredit = 0;
	bool check = false;
	index = -1;
	// Reference info from 'course.csv'.
	if (courseFile.is_open()) {
		while (courseFile.is_open()) {
			getline(courseFile, CID, ',');
			getline(courseFile, TID, ',');
			getline(courseFile, CourseName, ',');
			getline(courseFile, NumberStu, ',');
			getline(courseFile, Slot, ',');
			getline(courseFile, Credit, '\n');

			if (!courseFile.eof()) {
				index++;
				courses[index] = CID;
				credit[index] = Credit;
			}

			if (courseFile.eof())
				break;
		}
		courseFile.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}

	if (objectFile.is_open()) {
		while (objectFile.is_open()) {
			getline(objectFile, CID, ',');
			getline(objectFile, SID, ',');
			getline(objectFile, TID, ',');
			getline(objectFile, Score, ',');
			getline(objectFile, SemesID, '\n');
			if (!objectFile.eof()) {
				for (int i = 1; i < index + 1; i++) {
					if (CID == courses[i]) {
						trashFile << CID << "," << SID << "," << TID << "," << Score << "," << SemesID << "," << credit[i] << endl;
						break;
					}
				}
			}
			if (objectFile.eof()) {
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
	trashFile.close();

	// Reference info from 'trashData.txt'.
	index = -1;
	string semesters[SIZE];
	double arrGPA[SIZE] = {};
	int arrTotalCredit[SIZE] = {};
	bool check1 = false;
	ifstream trashFile1("trashData.txt");
	if (trashFile1.is_open()) {
		while (trashFile1.is_open()) {
			getline(trashFile1, CID, ',');
			getline(trashFile1, SID, ',');
			getline(trashFile1, TID, ',');
			getline(trashFile1, Score, ',');
			getline(trashFile1, SemesID, ',');
			getline(trashFile1, Credit, '\n');
			index++;
			semesters[index] = SemesID;
			tempSID[index] = SID;
			// Check overlapped semesters
			for (int i = 0; i < index; i++) {
				for (int j = i + 1; j <= index; j++) {
					if (semesters[i] == semesters[j]) {
						semesters[j] = "";
						break;
					}
				}
			}
			// Solid the 'semesters[]'
			for (int i = 0; i < index; i++) {
				for (int j = i + 1; j <= index; j++) {
					if (semesters[i] == "" && semesters[j] != "") {
						string tmp = semesters[j];
						semesters[j] = semesters[i];
						semesters[i] = semesters[j];
						break;
					}
				}
			}

			for (int i = countSemester; i <= index; i++)
				if (semesters[i] != "" && username == tempSID[i])
					countSemester++;
			
			if (!trashFile1.eof()) {
				if (semes != "a" && semes != "A") {
					if (SID == username && SemesID == semes) {
						if (Score != "NULL") {
							GPA += stod(Score) * stod(Credit);
							totalCredit += stoi(Credit);
							check = true;
						}
						if (Score == "NULL") {
							check1 = true;
						}
					}
				}
				if (semes == "a" || semes == "A") {
					check = true;
					if (SID == username) {
						for (int i = 0; i <= countSemester; i++) {
							if (SemesID == semesters[i]) {
								arrGPA[i] += stod(Score) * stoi(Credit);
								arrTotalCredit[i] += stoi(Credit);
								break;
							}
						}
					}
				}
			}
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
	if (check1 == true) {
		cout << "You have not finished your semester yet!!\n\nYour current GPA is: ";
		cout << (double)GPA / totalCredit << endl;
		system("pause");
		return 0;
	}
	if (semes != "a" && semes != "A") {
		if (check == false)
			cout << "There is no semester has that name!! Please try again!!\n";
		else {
			cout << "\t" << setw(15) << left << "Semester ID" << setw(15) << left << fixed << "GPA" << endl;
			cout << "\t" << setw(15) << left << semes << setw(15) << left << fixed << setprecision(2) << (double)GPA / totalCredit << endl;
		}
	}
	
	if (semes == "a" || semes == "A") {
		if (check == false)
			cout << "There is no semester has that name!! Please try again!!\n";
		else {
			cout << "\t" << setw(15) << left << "Semester ID" << setw(15) << left << fixed << "GPA" << endl << endl;
			for (int i = 0; i <= countSemester; i++) {
				if (semesters[i] != "" && tempSID[i] == username) {
					cout << "\t" << setw(15) << left << semesters[i] << setw(15) << left << fixed << setprecision(2) << (double)arrGPA[i] / arrTotalCredit[i] << endl;
				}
			}
			for (int i = 0; i <= countSemester; i++) {
				if (semesters[i] != "" && tempSID[i] == username)
					GPA += (arrGPA[i] / arrTotalCredit[i]);
			}
			cout << "...................................................................." << endl;
			cout << "\t" << setw(15) << left << "All Semester" << setw(15) << left << fixed << "GPA" << endl;
			cout << "\t" << setw(15) << left << " " << setw(15) << left << fixed << setprecision(2) << (double)GPA / countSemester << endl;
		}
	}

	system("pause");
	return 0;
}

int Student::viewRegisteredCourses(string username) {
	system("cls");
	cout << "\n\t\t\t\t\t\tREGISTERED COURSES\n\n";
	string CID, SID, TID, Score, SemesID;
	index = -1;
	string semesters[SIZE];
	string scores[SIZE];
	ifstream objectFile("object.csv");
	if (objectFile.is_open()) {
		while (objectFile.is_open()) {
			getline(objectFile, CID, ',');
			getline(objectFile, SID, ',');
			getline(objectFile, TID, ',');
			getline(objectFile, Score, ',');
			getline(objectFile, SemesID, '\n');
			if (!objectFile.eof()) {
				index++;
				tempCID[index] = CID;
				tempSID[index] = SID;
				tempTID[index] = TID;
				scores[index] = Score;
				semesters[index] = SemesID;
			}
			if (objectFile.eof()) {
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

	// Sort semesters in ascending order.
	//bool swapped;
	//for (int i = 0; i < index - 1; i++) {
	//	swapped = false;
	//	for (int j = 0; j < index - i - 1; j++) {
	//		if (semesters[j] > semesters[j + 1]) {
	//			swap(&semesters[j], &semesters[j + 1]);
	//		}
	//	}
	//	// IF no two elements were swapped by inner loop, then break
	//	if (swapped == false)
	//		break;
	//}
	cout << "\n\t" << setw(20) << left << "Course ID"
		<< setw(20) << left << "Student ID"
		<< setw(20) << left << "Teacher ID"
		<< setw(20) << left << "Score"
		<< setw(20) << left << "Semester ID" << endl;
	cout << "\t****************************************************************************************************\n";
	for (int i = 0; i <= index; i++) {
		if(tempSID[i] == username)
			cout << "\n\t" << setw(20) << left << tempCID[i]
				<< setw(20) << left << tempSID[i]
				<< setw(20) << left << tempTID[i]
				<< setw(20) << left << scores[i]
				<< setw(20) << left << semesters[i] << endl;
	}
	system("pause");
	return 0;
}

int Student::viewCoursesSem(string username) {
	system("cls");
	cout << "\n\t\t\t\t\t\tVIEW COURSES DURING THE SEMESTER\n\n";
	cout << "Select semester: ";
	string semes; cin >> semes;
	system("cls");
	cout << "\t" << setw(15) << left << "Course_ID" 
		<< setw(15) << left << "Teacher_ID" 
		<< setw(15) << left << "Score" 
		<< setw(15) << left << "Semester_ID" << endl;

	ifstream objectFile("object.csv");
	string CID, SID, TID, Score, SemesID;
	if (objectFile.is_open()) {
		while (objectFile.is_open()) {
			getline(objectFile, CID, ',');
			getline(objectFile, SID, ',');
			getline(objectFile, TID, ',');
			getline(objectFile, Score, ',');
			getline(objectFile, SemesID, '\n');
			if (!objectFile.eof()) {
				if (semes == SemesID && username == SID) {
					cout << "\t" << setw(15) << left << CID << setw(15) << left << TID << setw(15) << left << Score << setw(15) << left << SemesID << endl;
				}
			}
			if (objectFile.eof()) {
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
	system("pause");
	return 0;
}

int Student::uniCourses(string str) {
	system("cls");
	cout << "\n\t\t\t\t\t\tALL COURSES IN SCHOOL\n\n";
	ifstream courseFile("course.csv");
	if (courseFile.is_open()) {
		bool check = false;
		string CID, TID, Name, NumStu, Slot, Credit;
		cout << "\n\t" << setw(20) << left << "CourseID" 
			<< setw(15) << left << "TeacherID" 
			<< setw(30) << left << "Name" 
			<< setw(30) << left << "Number of Student" 
			<< setw(15) << left << "Slot" 
			<< setw(10) << left << "Credit" << endl;
		cout << "\t***************************************************************************************************************\n";
		while (courseFile.is_open()) {
			getline(courseFile, CID, ',');
			getline(courseFile, TID, ',');
			getline(courseFile, Name, ',');
			getline(courseFile, NumStu, ',');
			getline(courseFile, Slot, ',');
			getline(courseFile, Credit, '\n');
			if (checkSubStr(Name, str) == true) {
				check = true;
				cout << "\t" << setw(20) << left << CID
					<< setw(15) << left << TID
					<< setw(30) << left << Name
					<< setw(30) << left << NumStu
					<< setw(15) << left << Slot
					<< setw(10) << left << Credit << endl;
			}
			if (courseFile.eof()) {
				if (check == false)
					cout << "Cannot find that course!!\n";
				cout << endl;
				system("pause");
				break;
			}
		}
		courseFile.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}
	return 0;
}
