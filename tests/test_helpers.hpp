#ifndef TEST_H__
#define TEST_H__
#include <string>
#include <iostream>
#include <fstream>
#include <array>

using namespace std;

// TODO add detailed explanation on what the function should do
std::string exec(const char* cmd);
std::string readFileIntoString(std::string fileName);
string test_showMovieCollection(string* name,int* ranking, int* year, float* rating, int len);
string test_InsertMovieCollection(string* name,int* ranking, int* year, float* rating, int len, char parent, char child);
string test_RemoveMovieNode(string* name,int* ranking, int* year, float* rating, int len, string del, bool isEmptyHead);
string test_GetSuccessor(string* name,int* ranking, int* year, float* rating, int len, char del, bool isEmptyHead);
string test_RemoveBSTNode(string* name,int* ranking, int* year, float* rating, int len, char del, bool isEmptyHead);
string test_RightRotation(string* name,int* ranking, int* year, float* rating, int len, char r);

#endif // TEST_H__