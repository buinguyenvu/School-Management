#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <climits>
#include "Administrator.h"
#include "commonFunc.h"
using namespace std;

void Administrator::login() {
	system("cls");
	cout << "\n\t\t\t\t\t\tADMIN LOGIN\n\n";
	bool checkUsername = false;
	bool checkPassword = false;
	do {
		cout << "Login:\n\n";
		cout << "Username: ";
		string name; cin >> name;
		cout << "Password: ";
		string pass; cin >> pass;

		Administrator A;
		ifstream userFile("user.csv");
		string username, password, type;
		if (userFile.is_open()) {
			while (userFile.is_open()) {

				getline(userFile, username, ',');
				getline(userFile, password, ',');
				getline(userFile, type, '\n');

				if (name == username && type == "admin") {
					checkUsername = true;
					if (pass == password) {
						checkPassword = true;
						A.adminOption(name, pass);
						break;
					}
				}

				if (userFile.eof())
					break;
			}
			userFile.close();
		}
		else {
			system("cls");
			cout << "Unable to open file!!\n";
			system("pause");
		}
		if (checkUsername != true || checkPassword != true) {
			system("cls");
			cout << "\n\t\t\t\t\t\tADMIN LOGIN\n";
			cout << "Incorrect username or password, please type again!!\n";
		}
	} while (checkUsername == false || checkPassword == false);
}

int Administrator::adminOption(string username, string password) {
	Administrator A;
	int option;
	string str;
	string optionStr;
	bool find = false;
	int tmp;
	LOOP:
	do {
		system("cls");
		cout << "\n\t\t\t\t\t\tADMIN OPTIONS\n\n";
		cout << "\n1. Add Professor\n2. Delete Professor\n3. Search Professor\n4. Add Student\n5. Delete Student\n6. Search Student\n7. Change Password\n8. Search All\n9. Logout\n";
		cout << "You can only enter number!!\n\nEnter your option: ";
		cin >> str;
		cin.ignore(32767, '\n');
		if (checkDigit(str) == true) {
			option = stoi(str);
			switch (option) {
			case 1:
				A.addProfessor();
				break;
			case 2:
				cout << "Delete Professor's information: ";
				getline(cin, str);
				A.deleteProfessor(str);
				break;
			case 3:
				cout << "Search Professor's information: ";
				getline(cin, str);
				find = false;
				A.professorSearch(str, find);
				if (find == true) {
					cout << "Do you want to delete someone?\n1. Yes\n2. Delete all people on the screen\n3. No\n\n";
					do {
						do {
							getline(cin, optionStr);
						} while (checkDigit(optionStr) == false);
						tmp = stoi(optionStr);
						if (tmp == 1) {
							cout << "Delete Professor's information: ";
							getline(cin, str);
							A.deleteProfessor(str);
							break;
						}
						if (tmp == 2) {
							A.deleteProfessor(str);
							break;
						}
						if (tmp == 3)
							break;
					} while (1);
				}
				break;
			case 4:
				A.addStudent();
				break;
			case 5:
				cout << "Delete Student's information: ";
				getline(cin, str);
				A.deleteStudent(str);
				break;
			case 6:
				cout << "Search Student's information: ";
				getline(cin, str);
				find = false;
				A.studentSearch(str, find);
				if (find == true) {
					cout << "Do you want to delete someone?\n1. Yes\n2. Delete all people on the screen\n3. No\n\n";
					do {
						do {
							getline(cin, optionStr);
						} while (checkDigit(optionStr) == false);
						tmp = stoi(optionStr);
						if (tmp == 1) {
							cout << "Delete Student's information: ";
							getline(cin, str);
							A.deleteStudent(str);
							break;
						}
						if (tmp == 2) {
							A.deleteStudent(str);
							break;
						}
						if (tmp == 3)
							break;
					} while (1);
				}
				break;
			case 7:
				A.changePassword(username, password);
				break;
			case 8:
				A.searchAll();
				break;
			case 9:
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

int Administrator::addProfessor() {
	system("cls");
	cout << "\n\t\t\t\t\t\tADD PROFESSOR\n\n";
	Professor P;
	cout << "Enter Professor's ID: ";
	getline(cin, P.ProfessorID);
	cout << "Enter Professor's Name: ";
	getline(cin, P.ProfessorName);
	cout << "Enter Professor's Day of Birth(yyyy/mm/dd): ";
	getline(cin, P.ProfessorDOB);
	cout << "Enter Professor's Telephone number: ";
	getline(cin, P.ProfessorTel);
	cout << "Enter Professor's Hometown: ";
	getline(cin, P.ProfessorHometown);

	string ID = P.ProfessorID;
	string Name = P.ProfessorName;
	string DOB = P.ProfessorDOB;
	string Tel = P.ProfessorTel;
	string Hometown = P.ProfessorHometown;
	ifstream ProfessorFile("teacher.csv");
	ofstream trashFile("trashData.txt");
	bool check = false;
	if (ProfessorFile.is_open()) {
		while (ProfessorFile.is_open()) {
			getline(ProfessorFile, P.ProfessorID, ',');
			getline(ProfessorFile, P.ProfessorName, ',');
			getline(ProfessorFile, P.ProfessorDOB, ',');
			getline(ProfessorFile, P.ProfessorTel, ',');
			getline(ProfessorFile, P.ProfessorHometown, '\n');

			if (checkSubStr(P.ProfessorID, ID) == true) {
				cout << "The Profressor already existed!!\n";
				system("pause");
				return 0;
			}
			else {
				if (!P.ProfessorID.empty())
					trashFile << P.ProfessorID << "," << P.ProfessorName << "," << P.ProfessorDOB << "," << P.ProfessorTel << "," << P.ProfessorHometown << endl;
				else {
					check = true;
					trashFile << ID << "," << Name << "," << DOB << "," << Tel << "," << Hometown << endl;
				}
			}

			if (ProfessorFile.eof())
				break;
		}
		ProfessorFile.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
	}
	trashFile.close();
	remove("teacher.csv");
	rename("trashData.txt", "teacher.csv");

	// Phase 2:
	ifstream userFile("user.csv");
	ofstream trashFile2("trashData.txt");
	string name, pass, type;
	bool check1 = false;
	if (userFile.is_open()) {
		while (userFile.is_open()) {
			getline(userFile, name, ',');
			getline(userFile, pass, ',');
			getline(userFile, type, '\n');

			if (!name.empty())
				trashFile2 << name << "," << pass << "," << type << endl;

			if (userFile.eof()) {
				trashFile2 << ID << "," << ID << "," << "teacher" << endl;
				check1 = true;
				break;
			}
		}
		userFile.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
	}
	trashFile2.close();
	remove("user.csv");
	rename("trashData.txt", "user.csv");

	ifstream trashFile1("trashData.txt");
	ofstream userFile1("user.csv");
	if (trashFile1.is_open()) {
		while (trashFile1.is_open()) {
			getline(trashFile1, name, ',');
			getline(trashFile1, pass, ',');
			getline(trashFile1, type, '\n');
			if (!name.empty())
				userFile1 << name << "," << pass << "," << type << endl;
			if (trashFile1.eof())
				break;
		}
		trashFile1.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
	}
	userFile1.close();
	if (check == true && check1 == true)
		cout << "The Professor is added!!\n";
	system("pause");
	return 0;
}

int Administrator::deleteProfessor(string str) {
	system("cls");
	cout << "\n\t\t\t\t\t\tDELETE PROFESSOR\n\n";
	Professor P;

	string storeArray[30000];
	int count = -1;

	ifstream ProfessorFile("teacher.csv");
	ofstream trashFile("trashData.txt");
	bool check = false;
	if (ProfessorFile.is_open()) {
		cout << "\n\t" << setw(10) << left << "Prof_ID"
			<< setw(30) << left << "Prof_Name"
			<< setw(15) << left << "Prof_DOB"
			<< setw(20) << left << "Prof_Tel"
			<< setw(50) << left << "Prof_Hometown" << endl;
		cout << "\t" << "*****************************************************************************************************************************";
		while (ProfessorFile.is_open()) {
			getline(ProfessorFile, P.ProfessorID, ',');
			getline(ProfessorFile, P.ProfessorName, ',');
			getline(ProfessorFile, P.ProfessorDOB, ',');
			getline(ProfessorFile, P.ProfessorTel, ',');
			getline(ProfessorFile, P.ProfessorHometown, '\n');

			// Lines contain inputed information set to empty
			if (checkSubStr(P, str) == true) {
				check = true;
				count++;
				storeArray[count] = P.ProfessorID;
				cout << "\n\t" << setw(10) << left << P.ProfessorID
					<< setw(30) << left << P.ProfessorName
					<< setw(15) << left << P.ProfessorDOB
					<< setw(20) << left << P.ProfessorTel
					<< setw(50) << left << P.ProfessorHometown << endl;
				P.ProfessorID = P.ProfessorID.replace(P.ProfessorID.begin(), P.ProfessorID.end(), "");
				P.ProfessorName = P.ProfessorName.replace(P.ProfessorName.begin(), P.ProfessorName.end(), "");
				P.ProfessorDOB = P.ProfessorDOB.replace(P.ProfessorDOB.begin(), P.ProfessorDOB.end(), "");
				P.ProfessorTel = P.ProfessorTel.replace(P.ProfessorTel.begin(), P.ProfessorTel.end(), "");
				P.ProfessorHometown = P.ProfessorHometown.replace(P.ProfessorHometown.begin(), P.ProfessorHometown.end(), "");
			}

			// Do not write blank lines to file
			if (!P.ProfessorID.empty()) {
				trashFile << P.ProfessorID << "," << P.ProfessorName << "," << P.ProfessorDOB << "," << P.ProfessorTel << "," << P.ProfessorHometown << endl;
			}
			if (ProfessorFile.eof())
				break;
		}
		ProfessorFile.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}
	trashFile.close();
	remove("teacher.csv");
	rename("trashData.txt", "teacher.csv");

	// Phase 2:
	ifstream userFile("user.csv");
	ofstream trashFile2("trashData.txt");
	string name, pass, type;
	bool check1 = false;
	if (userFile.is_open()) {
		while (userFile.is_open()) {
			getline(userFile, name, ',');
			getline(userFile, pass, ',');
			getline(userFile, type, '\n');
			for (int i = 0; i < count + 1; i++) {
				if (checkSubStr(name, storeArray[i]) == true && type == "teacher") {
					check1 = true;
					name = name.replace(name.begin(), name.end(), "");
					pass = pass.replace(pass.begin(), pass.end(), "");
					type = type.replace(type.begin(), type.end(), "");
					break;
				}
			}
			if (!name.empty())
				trashFile2 << name << "," << pass << "," << type << endl;
			if (userFile.eof())
				break;
		}
		userFile.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}
	trashFile2.close();
	remove("user.csv");
	rename("trashData.txt", "user.csv");

	ifstream trashFile3("trashData.txt");
	ofstream userFile1("user.csv");
	if (trashFile3.is_open()) {
		while (trashFile3.is_open()) {
			getline(trashFile3, name, ',');
			getline(trashFile3, pass, ',');
			getline(trashFile3, type, '\n');
			if (!name.empty())
				userFile1 << name << "," << pass << "," << type << endl;
			if (trashFile3.eof())
				break;
		}
		trashFile3.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}
	userFile1.close();
	remove("user.csv");
	rename("trashData.txt", "user.csv");

	if (check == true && check1 == true)
		cout << "The Professor is deleted!!\n";
	else
		cout << "Try again!!\n";
	system("pause");
	return 0;
}

void Administrator::professorSearch(string str, bool &find) {
	Professor P;
	ifstream ProfessorFile("teacher.csv");
	if (ProfessorFile.is_open()) {
		cout << "\n\t" << setw(10) << left << "Prof_ID"
			<< setw(30) << left << "Prof_Name"
			<< setw(15) << left << "Prof_DOB"
			<< setw(20) << left << "Prof_Tel"
			<< setw(50) << left << "Prof_Hometown" << endl;
		cout << "\t" << "*****************************************************************************************************************************";
		while (ProfessorFile.is_open()) {
			getline(ProfessorFile, P.ProfessorID, ',');
			getline(ProfessorFile, P.ProfessorName, ',');
			getline(ProfessorFile, P.ProfessorDOB, ',');
			getline(ProfessorFile, P.ProfessorTel, ',');
			getline(ProfessorFile, P.ProfessorHometown, '\n');

			if (!ProfessorFile.eof()) {
				if (checkSubStr(P, str) == true) {
					cout << "\n\t" << setw(10) << left << P.ProfessorID
						<< setw(30) << left << P.ProfessorName
						<< setw(15) << left << P.ProfessorDOB
						<< setw(20) << left << P.ProfessorTel
						<< setw(50) << left << P.ProfessorHometown << endl;
					find = true;
				}
			}

			if (ProfessorFile.eof()) {
				if (find == false) {
					system("cls");
					cout << "Cannot find Professor!!\n";
					system("pause");
				}
				break;
			}
		}
		ProfessorFile.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
	}
}

int Administrator::addStudent() {
	system("cls");
	cout << "\n\t\t\t\t\t\tADD STUDENT\n\n";
	Student S;
	system("cls");
	cout << "Enter Student's ID: ";
	getline(cin, S.StudentID);
	cout << "Enter Student's Name: ";
	getline(cin, S.StudentName);
	cout << "Enter Student's Day of Birth(yyyy-mm-dd): ";
	getline(cin, S.StudentDOB);
	cout << "Enter Student's Hometown: ";
	getline(cin, S.StudentHometown);

	string ID = S.StudentID;
	string Name = S.StudentName;
	string DOB = S.StudentDOB;
	string Hometown = S.StudentHometown;
	ifstream ProfessorFile("student.csv");
	ofstream trashFile("trashData.txt");
	bool check = false;
	if (ProfessorFile.is_open()) {
		while (ProfessorFile.is_open()) {
			getline(ProfessorFile, S.StudentID, ',');
			getline(ProfessorFile, S.StudentName, ',');
			getline(ProfessorFile, S.StudentDOB, ',');
			getline(ProfessorFile, S.StudentHometown, '\n');

			if (S.StudentID == ID) {
				cout << "The Student already existed!!\n";
				system("pause");
				return 0;
			}
			else {
				if (!S.StudentID.empty())
					trashFile << S.StudentID << "," << S.StudentName << "," << S.StudentDOB << "," << S.StudentHometown << endl;
				else {
					trashFile << ID << "," << Name << "," << DOB << "," << Hometown << endl;
					check = true;
				}
			}

			if (ProfessorFile.eof())
				break;
		}
		ProfessorFile.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
	}
	trashFile.close();
	remove("student.csv");
	rename("trashData.txt", "student.csv");

	// Phase 2:
	ifstream userFile("user.csv");
	ofstream trashFile2("trashData.txt");
	string name, pass, type;
	bool check1 = false;
	bool check2 = false;
	if (userFile.is_open()) {
		while (userFile.is_open()) {
			getline(userFile, name, ',');
			getline(userFile, pass, ',');
			getline(userFile, type, '\n');

			if (!name.empty())
				trashFile2 << name << "," << pass << "," << type << endl;
			if (name == ID) {
				check1 = false;
				break;
			}
			if (userFile.eof()) {
				check1 = true;
				trashFile2 << ID << "," << ID << "," << "student" << endl;
				break;
			}
		}
		userFile.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
	}
	trashFile2.close();

	ifstream trashFile1("trashData.txt");
	ofstream userFile1("user.csv");
	if (trashFile1.is_open()) {
		while (trashFile1.is_open()) {
			getline(trashFile1, name, ',');
			getline(trashFile1, pass, ',');
			getline(trashFile1, type, '\n');
			if (!name.empty())
				userFile1 << name << "," << pass << "," << type << endl;
			if (trashFile1.eof())
				break;
		}
		trashFile1.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
	}
	userFile1.close();
	if (check == true && check1 == true)
		cout << "Student is added!!\n";
	system("pause");
	return 0;
}

int Administrator::deleteStudent(string str) {
	system("cls");
	cout << "\n\t\t\t\t\t\tDELETE STUDENT\n\n";
	Student S;
	string storeArray[30000];
	int count = -1;

	ifstream StudentFile("student.csv");
	ofstream trashFile("trashData.txt");
	bool check = false;
	if (StudentFile.is_open()) {
		cout << "\n\t" << setw(10) << left << "Stu_ID"
			<< setw(30) << left << "Stu_Name"
			<< setw(15) << left << "Stu_DOB"
			<< setw(50) << left << "Stu_Hometown" << endl;
		cout << "\t" << "*********************************************************************************************************";
		while (StudentFile.is_open()) {
			getline(StudentFile, S.StudentID, ',');
			getline(StudentFile, S.StudentName, ',');
			getline(StudentFile, S.StudentDOB, ',');
			getline(StudentFile, S.StudentHometown, '\n');

			// Lines contain inputed information set to empty
			if (checkSubStr(S, str) == true) {
				check = true;
				count++;
				storeArray[count] = S.StudentID;
				cout << "\n\t" << setw(10) << left << S.StudentID
								<< setw(30) << left << S.StudentName
								<< setw(15) << left << S.StudentDOB
								<< setw(50) << left << S.StudentHometown << endl;
				S.StudentID = S.StudentID.replace(S.StudentID.begin(), S.StudentID.end(), "");
				S.StudentName = S.StudentName.replace(S.StudentName.begin(), S.StudentName.end(), "");
				S.StudentDOB = S.StudentDOB.replace(S.StudentDOB.begin(), S.StudentDOB.end(), "");
				S.StudentHometown = S.StudentHometown.replace(S.StudentHometown.begin(), S.StudentHometown.end(), "");
			}

			// Do not write blank lines to file
			if (!S.StudentID.empty()) {
				trashFile << S.StudentID << "," << S.StudentName << "," << S.StudentDOB << "," << S.StudentHometown << endl;
			}
			if (StudentFile.eof())
				break;
		}
		StudentFile.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}
	trashFile.close();
	remove("student.csv");
	rename("trashData.txt", "student.csv");

	//ofstream StudentFile1("student.csv");
	//ifstream trashFile1("trashData.txt");
	//if (trashFile1.is_open()) {
	//	while (trashFile1.is_open()) {
	//		getline(trashFile1, S.StudentID, ',');
	//		getline(trashFile1, S.StudentName, ',');
	//		getline(trashFile1, S.StudentDOB, ',');
	//		getline(trashFile1, S.StudentHometown, '\n');
	//		// Do not write blank lines to file
	//		if (!S.StudentID.empty()) {
	//			StudentFile1 << S.StudentID << "," << S.StudentName << "," << S.StudentDOB << "," << S.StudentHometown << endl;
	//		}
	//		if (StudentFile.eof())
	//			break;
	//	}
	//	StudentFile.close();
	//}
	//else {
	//	system("cls");
	//	cout << "Unable to open file!! Check again!!\n";
	//	system("pause");
	//}
	//trashFile.close();

	// Phase 2:
	ifstream userFile("user.csv");
	ofstream trashFile2("trashData.txt");
	string name, pass, type;
	bool check1 = false;
	if (userFile.is_open()) {
		while (userFile.is_open()) {
			getline(userFile, name, ',');
			getline(userFile, pass, ',');
			getline(userFile, type, '\n');
			for (int i = 0; i < count + 1; i++) {
				if (checkSubStr(name, storeArray[i]) == true && type == "student") {
					check1 = true;
					name = name.replace(name.begin(), name.end(), "");
					pass = pass.replace(pass.begin(), pass.end(), "");
					type = type.replace(type.begin(), type.end(), "");
				}
			}
			if (!name.empty())
				trashFile2 << name << "," << pass << "," << type << endl;
			if (userFile.eof())
				break;
		}
		userFile.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}
	trashFile2.close();
	remove("user.csv");
	rename("trashData.txt", "user.csv");

	ifstream trashFile3("trashData.txt");
	ofstream userFile1("user.csv");
	if (trashFile3.is_open()) {
		while (trashFile3.is_open()) {
			getline(trashFile3, name, ',');
			getline(trashFile3, pass, ',');
			getline(trashFile3, type, '\n');
			if (!name.empty())
				userFile1 << name << "," << pass << "," << type << endl;
			if (trashFile3.eof())
				break;
		}
		trashFile3.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
		return 0;
	}
	userFile1.close();
	remove("user.csv");
	rename("trashData.txt", "user.csv");

	if (check == true && check1 == true)
		cout << "The Student is deleted!!\n";
	else
		cout << "Try again!!\n";
	system("pause");
	return 0;
}

void Administrator::studentSearch(string str, bool &find) {
	Student S;
	ifstream StudentFile("student.csv");
	if (StudentFile.is_open()) {
		cout << "\n\t" << setw(10) << left << "Stu_ID"
			<< setw(30) << left << "Stu_Name"
			<< setw(15) << left << "Stu_DOB"
			<< setw(50) << left << "Stu_Hometown" << endl;
		cout << "\t" << "*********************************************************************************************************";
		while (StudentFile.is_open()) {
			getline(StudentFile, S.StudentID, ',');
			getline(StudentFile, S.StudentName, ',');
			getline(StudentFile, S.StudentDOB, ',');
			getline(StudentFile, S.StudentHometown, '\n');

			if (!StudentFile.eof()) {
				if (checkSubStr(S, str) == true) {
					cout << "\n\t" << setw(10) << left << S.StudentID
						<< setw(30) << left << S.StudentName
						<< setw(15) << left << S.StudentDOB
						<< setw(50) << left << S.StudentHometown << endl;
					find = true;
				}
			}

			if (StudentFile.eof()) {
				if (find == false) {
					system("cls");
					cout << "Cannot find Student!!\n";
					system("pause");
				}
				break;
			}
		}
		StudentFile.close();
	}
	else {
		system("cls");
		cout << "Unable to open file!! Check again!!\n";
		system("pause");
	}
}

int Administrator::changePassword(string username, string &password) {
	system("cls");
	cout << "\n\t\t\t\t\t\tCHANGE ADMIN PASSWORD\n\n";
	ifstream UserFile("user.csv");
	ofstream trashFile("trashData.txt");
	string name, pass, type;
	if (UserFile.is_open()) {
		while (UserFile.is_open()) {
			getline(UserFile, name, ',');
			getline(UserFile, pass, ',');
			getline(UserFile, type, '\n');
			if (username != name && name != "") {
				trashFile << name << "," << pass << "," << type << endl;
			}
			if (username == name && type == "admin") {
				string newpassword;
				do {
					cout << "\n\nConfirm your password: ";
					cin >> pass;
					if (password == pass) {
						system("cls");
						cout << "\n\t\t\t\t\t\tCHANGE ADMIN PASSWORD\n\n";
						cout << "\n\nConfirm your password: " << pass << endl;
						cout << "Type your new password: ";
						cin >> newpassword;
						if (username != "")
							trashFile << username << "," << newpassword << "," << "admin" << endl;
					}
					else {
						system("cls");
						cout << "\n\t\t\t\t\t\tCHANGE ADMIN PASSWORD\n\n";
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
}

void Administrator::searchAll() {
	system("cls");
	cout << "\n\t\t\t\t\t\tSEARCH ALL USER\n\n";
	cout << "1. Show all Students\n2. Show all Professors\n\n";
	int n;
	string option;
	do {
		do {
			getline(cin, option);
		} while (checkDigit(option) == false);
		n = stoi(option);
		if (n == 1) {
			Student S;
			ifstream StudentFile("student.csv");
			ofstream trashFile("trashData.txt");
			if (StudentFile.is_open()) {
				while (StudentFile.is_open()) {
					getline(StudentFile, S.StudentID, ',');
					getline(StudentFile, S.StudentName, ',');
					getline(StudentFile, S.StudentDOB, ',');
					getline(StudentFile, S.StudentHometown, '\n');
					if (!StudentFile.eof())
						trashFile << S.StudentID << "," << S.StudentName << "," << S.StudentDOB << "," << S.StudentHometown << endl;
					if (StudentFile.eof()) {
						break;
					}
				}
				StudentFile.close();
			}
			else {
				system("cls");
				cout << "Unable to open file!! Check again!!\n";
				system("pause");
			}
			trashFile.close();
			ifstream trashFile1("trashData.txt");
			if (trashFile1.is_open()) {
				while (trashFile1.is_open()) {
					getline(trashFile1, S.StudentID, ',');
					getline(trashFile1, S.StudentName, ',');
					getline(trashFile1, S.StudentDOB, ',');
					getline(trashFile1, S.StudentHometown, '\n');

					if (!trashFile1.eof())
						cout << "\t" << setw(10) << left << S.StudentID
						<< setw(30) << left << S.StudentName
						<< setw(15) << left << S.StudentDOB
						<< setw(50) << left << S.StudentHometown << endl << endl;

					if (trashFile1.eof()) {
						system("pause");
						break;
					}
				}
				StudentFile.close();
			}
			else {
				system("cls");
				cout << "Unable to open file!! Check again!!\n";
				system("pause");
			}
			break;
		}
		if (n == 2) {
			Professor P;
			ifstream ProfessorFile("teacher.csv");
			ofstream trashFile("trashData.txt");
			if (ProfessorFile.is_open()) {
				while (ProfessorFile.is_open()) {
					getline(ProfessorFile, P.ProfessorID, ',');
					getline(ProfessorFile, P.ProfessorName, ',');
					getline(ProfessorFile, P.ProfessorDOB, ',');
					getline(ProfessorFile, P.ProfessorTel, ',');
					getline(ProfessorFile, P.ProfessorHometown, '\n');
					if (!ProfessorFile.eof())
						trashFile << P.ProfessorID << "," << P.ProfessorName << "," << P.ProfessorDOB << "," << P.ProfessorTel << "," << P.ProfessorHometown << endl;

					if (ProfessorFile.eof()) {
						break;
					}
				}
				ProfessorFile.close();
			}
			else {
				system("cls");
				cout << "Unable to open file!! Check again!!\n";
				system("pause");
			}
			trashFile.close();
			ifstream trashFile1("trashData.txt");
			if (trashFile1.is_open()) {
				while (trashFile1.is_open()) {
					getline(trashFile1, P.ProfessorID, ',');
					getline(trashFile1, P.ProfessorName, ',');
					getline(trashFile1, P.ProfessorDOB, ',');
					getline(trashFile1, P.ProfessorTel, ',');
					getline(trashFile1, P.ProfessorHometown, '\n');

					if (!trashFile1.eof())
						cout << "\t" << setw(10) << left << P.ProfessorID
						<< setw(30) << left << P.ProfessorName
						<< setw(15) << left << P.ProfessorDOB
						<< setw(20) << left << P.ProfessorTel
						<< setw(50) << left << P.ProfessorHometown << endl << endl;

					if (trashFile1.eof()) {
						system("pause");
						break;
					}
				}
				ProfessorFile.close();
			}
			else {
				system("cls");
				cout << "Unable to open file!! Check again!!\n";
				system("pause");
			}
			break;
		}
	} while (1);
}
