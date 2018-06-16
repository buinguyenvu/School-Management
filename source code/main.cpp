#include <iostream>
#include <string>
#include "Student.h"
#include "Administrator.h"
#include "Professor.h"
#include "commonFunc.h"
using namespace std;

int main() {
	Student S; Professor P; Administrator A;
	int option;
	string str;
	LOOP:
	do {
		system("cls");
		cout << "\n\n1. Student\n2. Professor\n3. Administrator\n4. Exit\n\n";
		cout << "You can only enter number!!\n\nEnter your option: ";
		getline(cin, str);
		if (checkDigit(str) == true) {
			option = stoi(str);
			switch (option) {
			case 1:
				S.login();
				break;
			case 2:
				P.login();
				break;
			case 3:
				A.login();
				break;
			case 4:
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
