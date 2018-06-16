#pragma once
#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

#include <string>
#include "Professor.h"
#include "Student.h"

// Check weather 'str' can convert to integer number or not. If yes, returns true. If no, returns false.
bool checkDigit(std::string str);

// If 'str1' contains 'str2', return true. Otherwise, return false.
bool checkSubStr(std::string str1, std::string str2);

// If Professor contains the desired data: return true. Otherwise, return false.
bool checkSubStr(Professor P, std::string subStr);

// If Student contains the desired data: return true. Otherwise, return false.
bool checkSubStr(Student S, std::string str);

// If str2[] is in str1[], return true. Otherwise, return false.
bool checkSubStr(std::string str1[], std::string str2[], int size, int index1[], int index2[], int &count);

// If str1[] contains 'str', return true. Otherwise, return false.
bool checkSubStr(std::string str1[], std::string str, int size);

// Sort in ascending order.
void swap(int *a, int *b);

#endif // !COMMON_FUNC_H
