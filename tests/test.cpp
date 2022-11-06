// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code_1/MovieTree.hpp"
#include "test_helpers.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>

using namespace std;


class test_x : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test_x::total_grade = 0;
double test_x::max_grade = 100;



/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////
TEST_F(test_x, InsertMovie){
    string result;
    string expected;
       
    int len = 0;
    int ranking[] ={};
    string name[] = {};
    int year[] = {};
    float rating[] = {};
    
    result = test_InsertMovieCollection(name,ranking, year, rating, len,'\0','\0');
    expected = "[GRADER] Printing movie inventory:\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
    
    int len1= 5;
    int ranking1[]={6, 55, 60, 58, 94};
    string name1[] = {"Pulp Fiction","Casablanca","Coco (I)","City Lights","Children of Heaven"};
    int year1[]={1994,1942,2017,1931,1997};
    float rating1[] = {8.9,8.5,8.4,8.5,8.3};
    
    result = test_InsertMovieCollection(name1,ranking1, year1, rating1, len1,'P','C');
    expected = "[GRADER] Adding:(6, Pulp Fiction, 1994, 8.9)\n[GRADER] Adding:(55, Casablanca, 1942, 8.5)\n[GRADER] Adding:(60, Coco (I), 2017, 8.4)\n[GRADER] Adding:(58, City Lights, 1931, 8.5)\n[GRADER] Adding:(94, Children of Heaven, 1997, 8.3)\n[GRADER] Printing movie inventory:\nMovies starting with letter: C\n >> Casablanca 8.5\n >> Children of Heaven 8.3\n >> City Lights 8.5\n >> Coco (I) 8.4\nMovies starting with letter: P\n >> Pulp Fiction 8.9\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
    result = test_InsertMovieCollection(name1,ranking1, year1, rating1, 1,'\0','P');
    expected = "[GRADER] Adding:(6, Pulp Fiction, 1994, 8.9)\n[GRADER] Printing movie inventory:\nMovies starting with letter: P\n >> Pulp Fiction 8.9\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
    
    int len2= 8;
    int ranking2[]={6, 55, 60, 58, 94,11,40,85};
    string name2[] = {"Pulp Fiction","Casablanca","Coco (I)","City Lights","Children of Heaven", "Fight Club", "Memento", "Toy Story"};
    int year2[]={1994,1942,2017,1931,1997,1999, 2000, 2010};
    float rating2[] = {8.9,8.5,8.4,8.5,8.3,8.8,8.5,8,3};
    
    result = test_InsertMovieCollection(name2,ranking2, year2, rating2, len2,'F','M');
    expected = "[GRADER] Adding:(6, Pulp Fiction, 1994, 8.9)\n[GRADER] Adding:(55, Casablanca, 1942, 8.5)\n[GRADER] Adding:(60, Coco (I), 2017, 8.4)\n[GRADER] Adding:(58, City Lights, 1931, 8.5)\n[GRADER] Adding:(94, Children of Heaven, 1997, 8.3)\n[GRADER] Adding:(11, Fight Club, 1999, 8.8)\n[GRADER] Adding:(40, Memento, 2000, 8.5)\n[GRADER] Adding:(85, Toy Story, 2010, 8)\n[GRADER] Printing movie inventory:\nMovies starting with letter: C\n >> Casablanca 8.5\n >> Children of Heaven 8.3\n >> City Lights 8.5\n >> Coco (I) 8.4\nMovies starting with letter: F\n >> Fight Club 8.8\nMovies starting with letter: M\n >> Memento 8.5\nMovies starting with letter: P\n >> Pulp Fiction 8.9\nMovies starting with letter: T\n >> Toy Story 8\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
    result = test_InsertMovieCollection(name2,ranking2, year2, rating2, len2,'P','T');
    expected = "[GRADER] Adding:(6, Pulp Fiction, 1994, 8.9)\n[GRADER] Adding:(55, Casablanca, 1942, 8.5)\n[GRADER] Adding:(60, Coco (I), 2017, 8.4)\n[GRADER] Adding:(58, City Lights, 1931, 8.5)\n[GRADER] Adding:(94, Children of Heaven, 1997, 8.3)\n[GRADER] Adding:(11, Fight Club, 1999, 8.8)\n[GRADER] Adding:(40, Memento, 2000, 8.5)\n[GRADER] Adding:(85, Toy Story, 2010, 8)\n[GRADER] Printing movie inventory:\nMovies starting with letter: C\n >> Casablanca 8.5\n >> Children of Heaven 8.3\n >> City Lights 8.5\n >> Coco (I) 8.4\nMovies starting with letter: F\n >> Fight Club 8.8\nMovies starting with letter: M\n >> Memento 8.5\nMovies starting with letter: P\n >> Pulp Fiction 8.9\nMovies starting with letter: T\n >> Toy Story 8\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
}



TEST_F(test_x, ShowMovie){
    string result;
    string expected;
       
    int len = 0;
    int ranking[] ={};
    string name[] = {};
    int year[] = {};
    float rating[] = {};
    
    result = test_showMovieCollection(name,ranking, year, rating, len);
    expected = "[GRADER] Printing movie inventory:\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
    
    
    int len1= 5;
    int ranking1[]={6, 55, 60, 58, 94};
    string name1[] = {"Pulp Fiction","Casablanca","Coco (I)","City Lights","Children of Heaven"};
    int year1[]={1994,1942,2017,1931,1997};
    float rating1[] = {8.9,8.5,8.4,8.5,8.3};
    
    result = test_showMovieCollection(name1,ranking1, year1, rating1, len1);
    expected = "[GRADER] Adding:(6, Pulp Fiction, 1994, 8.9)\n[GRADER] Adding:(55, Casablanca, 1942, 8.5)\n[GRADER] Adding:(60, Coco (I), 2017, 8.4)\n[GRADER] Adding:(58, City Lights, 1931, 8.5)\n[GRADER] Adding:(94, Children of Heaven, 1997, 8.3)\n[GRADER] Printing movie inventory:\nMovies starting with letter: C\n >> Casablanca 8.5\n >> Children of Heaven 8.3\n >> City Lights 8.5\n >> Coco (I) 8.4\nMovies starting with letter: P\n >> Pulp Fiction 8.9\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
    
    result = test_showMovieCollection(name1,ranking1, year1, rating1, 1);
    expected = "[GRADER] Adding:(6, Pulp Fiction, 1994, 8.9)\n[GRADER] Printing movie inventory:\nMovies starting with letter: P\n >> Pulp Fiction 8.9\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
    
    
    int len2= 8;
    int ranking2[]={6, 55, 60, 58, 94,11,40,85};
    string name2[] = {"Pulp Fiction","Casablanca","Coco (I)","City Lights","Children of Heaven", "Fight Club", "Memento", "Toy Story"};
    int year2[]={1994,1942,2017,1931,1997,1999, 2000, 2010};
    float rating2[] = {8.9,8.5,8.4,8.5,8.3,8.8,8.5,8,3};
    
    result = test_showMovieCollection(name2,ranking2, year2, rating2, len2);
    expected = "[GRADER] Adding:(6, Pulp Fiction, 1994, 8.9)\n[GRADER] Adding:(55, Casablanca, 1942, 8.5)\n[GRADER] Adding:(60, Coco (I), 2017, 8.4)\n[GRADER] Adding:(58, City Lights, 1931, 8.5)\n[GRADER] Adding:(94, Children of Heaven, 1997, 8.3)\n[GRADER] Adding:(11, Fight Club, 1999, 8.8)\n[GRADER] Adding:(40, Memento, 2000, 8.5)\n[GRADER] Adding:(85, Toy Story, 2010, 8)\n[GRADER] Printing movie inventory:\nMovies starting with letter: C\n >> Casablanca 8.5\n >> Children of Heaven 8.3\n >> City Lights 8.5\n >> Coco (I) 8.4\nMovies starting with letter: F\n >> Fight Club 8.8\nMovies starting with letter: M\n >> Memento 8.5\nMovies starting with letter: P\n >> Pulp Fiction 8.9\nMovies starting with letter: T\n >> Toy Story 8\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
}


TEST_F(test_x, removeMovie){
    string result;
    string expected;
       
    int len = 0;
    int ranking[] ={};
    string name[] = {};
    int year[] = {};
    float rating[] = {};
    
    result = test_RemoveMovieNode(name,ranking, year, rating, len,"Man on Wire", false);
    expected = "[GRADER] Deleting: Man on Wire\nMovie not found.\n[GRADER] Printing movie inventory:\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
    
    int len1= 5;
    int ranking1[]={6, 55, 60, 58, 94};
    string name1[] = {"Pulp Fiction","Casablanca","Coco (I)","City Lights","Children of Heaven"};
    int year1[]={1994,1942,2017,1931,1997};
    float rating1[] = {8.9,8.5,8.4,8.5,8.3};
    
    result = test_RemoveMovieNode(name1,ranking1, year1, rating1, len1,"Pulp Fiction", true);
    expected ="[GRADER] Adding:(6, Pulp Fiction, 1994, 8.9)\n[GRADER] Adding:(55, Casablanca, 1942, 8.5)\n[GRADER] Adding:(60, Coco (I), 2017, 8.4)\n[GRADER] Adding:(58, City Lights, 1931, 8.5)\n[GRADER] Adding:(94, Children of Heaven, 1997, 8.3)\n[GRADER] Deleting: Pulp Fiction\n[GRADER] Printing movie inventory:\nMovies starting with letter: C\n >> Casablanca 8.5\n >> Children of Heaven 8.3\n >> City Lights 8.5\n >> Coco (I) 8.4\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
    
    int len2= 8;
    int ranking2[]={6, 55, 60, 58, 94,11,40,85};
    string name2[] = {"Pulp Fiction","Casablanca","Coco (I)","City Lights","Children of Heaven", "Fight Club", "Memento", "Toy Story"};
    int year2[]={1994,1942,2017,1931,1997,1999, 2000, 2010};
    float rating2[] = {8.9,8.5,8.4,8.5,8.3,8.8,8.5,8,3};
    
    result = test_RemoveMovieNode(name2,ranking2, year2, rating2, len2,"Toy Story", true);
    expected ="[GRADER] Adding:(6, Pulp Fiction, 1994, 8.9)\n[GRADER] Adding:(55, Casablanca, 1942, 8.5)\n[GRADER] Adding:(60, Coco (I), 2017, 8.4)\n[GRADER] Adding:(58, City Lights, 1931, 8.5)\n[GRADER] Adding:(94, Children of Heaven, 1997, 8.3)\n[GRADER] Adding:(11, Fight Club, 1999, 8.8)\n[GRADER] Adding:(40, Memento, 2000, 8.5)\n[GRADER] Adding:(85, Toy Story, 2010, 8)\n[GRADER] Deleting: Toy Story\n[GRADER] Printing movie inventory:\nMovies starting with letter: C\n >> Casablanca 8.5\n >> Children of Heaven 8.3\n >> City Lights 8.5\n >> Coco (I) 8.4\nMovies starting with letter: F\n >> Fight Club 8.8\nMovies starting with letter: M\n >> Memento 8.5\nMovies starting with letter: P\n >> Pulp Fiction 8.9\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
    result = test_RemoveMovieNode(name2,ranking2, year2, rating2, len2,"Toy Story", true);
    expected ="[GRADER] Adding:(6, Pulp Fiction, 1994, 8.9)\n[GRADER] Adding:(55, Casablanca, 1942, 8.5)\n[GRADER] Adding:(60, Coco (I), 2017, 8.4)\n[GRADER] Adding:(58, City Lights, 1931, 8.5)\n[GRADER] Adding:(94, Children of Heaven, 1997, 8.3)\n[GRADER] Adding:(11, Fight Club, 1999, 8.8)\n[GRADER] Adding:(40, Memento, 2000, 8.5)\n[GRADER] Adding:(85, Toy Story, 2010, 8)\n[GRADER] Deleting: Toy Story\n[GRADER] Printing movie inventory:\nMovies starting with letter: C\n >> Casablanca 8.5\n >> Children of Heaven 8.3\n >> City Lights 8.5\n >> Coco (I) 8.4\nMovies starting with letter: F\n >> Fight Club 8.8\nMovies starting with letter: M\n >> Memento 8.5\nMovies starting with letter: P\n >> Pulp Fiction 8.9\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
    
    result = test_RemoveMovieNode(name2,ranking2, year2, rating2, len2,"Casablanca", false);
    expected ="[GRADER] Adding:(6, Pulp Fiction, 1994, 8.9)\n[GRADER] Adding:(55, Casablanca, 1942, 8.5)\n[GRADER] Adding:(60, Coco (I), 2017, 8.4)\n[GRADER] Adding:(58, City Lights, 1931, 8.5)\n[GRADER] Adding:(94, Children of Heaven, 1997, 8.3)\n[GRADER] Adding:(11, Fight Club, 1999, 8.8)\n[GRADER] Adding:(40, Memento, 2000, 8.5)\n[GRADER] Adding:(85, Toy Story, 2010, 8)\n[GRADER] Deleting: Casablanca\n[GRADER] Printing movie inventory:\nMovies starting with letter: C\n >> Children of Heaven 8.3\n >> City Lights 8.5\n >> Coco (I) 8.4\nMovies starting with letter: F\n >> Fight Club 8.8\nMovies starting with letter: M\n >> Memento 8.5\nMovies starting with letter: P\n >> Pulp Fiction 8.9\nMovies starting with letter: T\n >> Toy Story 8\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
    
    result = test_RemoveMovieNode(name2,ranking2, year2, rating2, len2,"City Lights", false);
    expected ="[GRADER] Adding:(6, Pulp Fiction, 1994, 8.9)\n[GRADER] Adding:(55, Casablanca, 1942, 8.5)\n[GRADER] Adding:(60, Coco (I), 2017, 8.4)\n[GRADER] Adding:(58, City Lights, 1931, 8.5)\n[GRADER] Adding:(94, Children of Heaven, 1997, 8.3)\n[GRADER] Adding:(11, Fight Club, 1999, 8.8)\n[GRADER] Adding:(40, Memento, 2000, 8.5)\n[GRADER] Adding:(85, Toy Story, 2010, 8)\n[GRADER] Deleting: City Lights\n[GRADER] Printing movie inventory:\nMovies starting with letter: C\n >> Casablanca 8.5\n >> Children of Heaven 8.3\n >> Coco (I) 8.4\nMovies starting with letter: F\n >> Fight Club 8.8\nMovies starting with letter: M\n >> Memento 8.5\nMovies starting with letter: P\n >> Pulp Fiction 8.9\nMovies starting with letter: T\n >> Toy Story 8\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
}

TEST_F(test_x, removeBSTNode){
    string result;
    string expected;
    
    
    int len1= 5;
    int ranking1[]={6, 55, 60, 58, 94};
    string name1[] = {"Pulp Fiction","Casablanca","Coco (I)","City Lights","Children of Heaven"};
    int year1[]={1994,1942,2017,1931,1997};
    float rating1[] = {8.9,8.5,8.4,8.5,8.3};
    
    result = test_RemoveBSTNode(name1,ranking1, year1, rating1, len1,'P', true);
    expected ="[GRADER] Adding:(6, Pulp Fiction, 1994, 8.9)\n[GRADER] Adding:(55, Casablanca, 1942, 8.5)\n[GRADER] Adding:(60, Coco (I), 2017, 8.4)\n[GRADER] Adding:(58, City Lights, 1931, 8.5)\n[GRADER] Adding:(94, Children of Heaven, 1997, 8.3)\n[GRADER] Deleting BST node with title: P\n[GRADER] Printing movie inventory:\nMovies starting with letter: C\n >> Casablanca 8.5\n >> Children of Heaven 8.3\n >> City Lights 8.5\n >> Coco (I) 8.4\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
    
    
    int len2= 9;
    int ranking2[]={6, 55, 60, 58, 94,11,40,85, 23};
    string name2[] = {"Pulp Fiction","Casablanca","Coco (I)","City Lights","Children of Heaven", "Fight Club", "Memento", "Toy Story", "Annie"};
    int year2[]={1994,1942,2017,1931,1997,1999, 2000, 2010, 2002};
    float rating2[] = {8.9,8.5,8.4,8.5,8.3,8.8,8.5,8,3,4};
    
    
    result = test_RemoveBSTNode(name2,ranking2, year2, rating2, len2,'C', false);
    expected ="[GRADER] Adding:(6, Pulp Fiction, 1994, 8.9)\n[GRADER] Adding:(55, Casablanca, 1942, 8.5)\n[GRADER] Adding:(60, Coco (I), 2017, 8.4)\n[GRADER] Adding:(58, City Lights, 1931, 8.5)\n[GRADER] Adding:(94, Children of Heaven, 1997, 8.3)\n[GRADER] Adding:(11, Fight Club, 1999, 8.8)\n[GRADER] Adding:(40, Memento, 2000, 8.5)\n[GRADER] Adding:(85, Toy Story, 2010, 8)\n[GRADER] Adding:(23, Annie, 2002, 3)\n[GRADER] Deleting BST node with title: C\n[GRADER] Printing movie inventory:\nMovies starting with letter: A\n >> Annie 3\nMovies starting with letter: F\n >> Fight Club 8.8\nMovies starting with letter: M\n >> Memento 8.5\nMovies starting with letter: P\n >> Pulp Fiction 8.9\nMovies starting with letter: T\n >> Toy Story 8\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
    
}

TEST_F(test_x, getSuccesor){
    
    string result;
    string expected;
    
    
    int len2= 9;
    int ranking2[]={6, 55, 60, 58, 94,11,40,85, 23};
    string name2[] = {"Pulp Fiction","Casablanca","Coco (I)","City Lights","Children of Heaven", "Fight Club", "Memento", "Toy Story", "Annie"};
    int year2[]={1994,1942,2017,1931,1997,1999, 2000, 2010, 2002};
    float rating2[] = {8.9,8.5,8.4,8.5,8.3,8.8,8.5,8,3,4};
    
    
    result = test_GetSuccessor(name2,ranking2, year2, rating2, len2,'C', false);
    // expected ="[GRADER] Adding:(6, Pulp Fiction, 1994, 8.9)\n[GRADER] Adding:(55, Casablanca, 1942, 8.5)\n[GRADER] Adding:(60, Coco (I), 2017, 8.4)\n[GRADER] Adding:(58, City Lights, 1931, 8.5)\n[GRADER] Adding:(94, Children of Heaven, 1997, 8.3)\n[GRADER] Adding:(11, Fight Club, 1999, 8.8)\n[GRADER] Adding:(40, Memento, 2000, 8.5)\n[GRADER] Adding:(85, Toy Story, 2010, 8)\n[GRADER] Adding:(23, Annie, 2002, 3)\n[GRADER] Deleting BST node with title: C\n[GRADER] Printing movie inventory:\nMovies starting with letter: A\n >> Annie 3\nMovies starting with letter: F\n >> Fight Club 8.8\nMovies starting with letter: M\n >> Memento 8.5\nMovies starting with letter: P\n >> Pulp Fiction 8.9\nMovies starting with letter: T\n >> Toy Story 8\n\n[GRADER] No leaked memory (Good).\n";
    expected = "[GRADER] Adding:(6, Pulp Fiction, 1994, 8.9)\n[GRADER] Adding:(55, Casablanca, 1942, 8.5)\n[GRADER] Adding:(60, Coco (I), 2017, 8.4)\n[GRADER] Adding:(58, City Lights, 1931, 8.5)\n[GRADER] Adding:(94, Children of Heaven, 1997, 8.3)\n[GRADER] Adding:(11, Fight Club, 1999, 8.8)\n[GRADER] Adding:(40, Memento, 2000, 8.5)\n[GRADER] Adding:(85, Toy Story, 2010, 8)\n[GRADER] Adding:(23, Annie, 2002, 3)\n[GRADER] Getting successor of node C\n[GRADER] Successor is : F\n\n[GRADER] No leaked memory (Good).\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
}


TEST_F(test_x, rightRotation){
    
    string result;
    string expected;
       
    int len = 4;
    int ranking[] ={15,15,15,3};
    string name[] = {"dumbo","cabin boy", "bolt", "avengers endgame"};
    int year[] = {2019, 1994, 2008, 2019};
    float rating[] = {6.5, 5.5, 6.5, 8.5}; 
    
    result = test_RightRotation(name,ranking, year, rating, len,'c');
    expected = "[GRADER] Adding:(15, dumbo, 2019, 6.5)\n[GRADER] Adding:(15, cabin boy, 1994, 5.5)\n[GRADER] Adding:(15, bolt, 2008, 6.5)\n[GRADER] Adding:(3, avengers endgame, 2019, 8.5)\nRotation successful\nMovies starting with letter: a\n >> avengers endgame 8.5\nMovies starting with letter: b\n >> bolt 6.5\nMovies starting with letter: c\n >> cabin boy 5.5\nMovies starting with letter: d\n >> dumbo 6.5\n\n[GRADER] No leaked memory (Good).\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    
    result = test_RightRotation(name,ranking, year, rating, len,'d');
    expected = "[GRADER] Adding:(15, dumbo, 2019, 6.5)\n[GRADER] Adding:(15, cabin boy, 1994, 5.5)\n[GRADER] Adding:(15, bolt, 2008, 6.5)\n[GRADER] Adding:(3, avengers endgame, 2019, 8.5)\nRotation successful\nMovies starting with letter: a\n >> avengers endgame 8.5\nMovies starting with letter: b\n >> bolt 6.5\nMovies starting with letter: c\n >> cabin boy 5.5\nMovies starting with letter: d\n >> dumbo 6.5\n\n[GRADER] No leaked memory (Good).\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    
    
    int len3= 8;
    int ranking3[]={6, 55, 58, 60, 94,11,40,85};
    string name3[] = {"Pulp Fiction","Avengers","Dumbo","Bolt","City Lights", "Fight Club", "Memento", "Toy Story"};
    int year3[]={1994,1942,1931,2017,1997,1999, 2000, 2010};
    float rating3[] = {8.9,8.5,8.5,8.4,8.3,8.8,8.5,8,3};
    
    result = test_RightRotation(name3,ranking3, year3, rating3, len3,'D');
    expected = "[GRADER] Adding:(6, Pulp Fiction, 1994, 8.9)\n[GRADER] Adding:(55, Avengers, 1942, 8.5)\n[GRADER] Adding:(58, Dumbo, 1931, 8.5)\n[GRADER] Adding:(60, Bolt, 2017, 8.4)\n[GRADER] Adding:(94, City Lights, 1997, 8.3)\n[GRADER] Adding:(11, Fight Club, 1999, 8.8)\n[GRADER] Adding:(40, Memento, 2000, 8.5)\n[GRADER] Adding:(85, Toy Story, 2010, 8)\nRotation successful\nMovies starting with letter: A\n >> Avengers 8.5\nMovies starting with letter: B\n >> Bolt 8.4\nMovies starting with letter: C\n >> City Lights 8.3\nMovies starting with letter: D\n >> Dumbo 8.5\nMovies starting with letter: F\n >> Fight Club 8.8\nMovies starting with letter: M\n >> Memento 8.5\nMovies starting with letter: P\n >> Pulp Fiction 8.9\nMovies starting with letter: T\n >> Toy Story 8\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
}



TEST_F(test_x, TestMain)
{
    string desired = readFileIntoString("../tests/output/output1.txt");
    string resp = exec("./run_app_1 ../tests/input/movies1.csv ../tests/input/input1.txt");
          
    ASSERT_EQ(desired, resp);
    add_points_to_grade(6.25);
    
    string desired2 = readFileIntoString("../tests/output/output2.txt");
    string resp2 = exec("./run_app_1 ../tests/input/movies2.csv ../tests/input/input2.txt");
    ASSERT_EQ(desired2, resp2);
    add_points_to_grade(6.25);
    
    string desired3 = readFileIntoString("../tests/output/output3.txt");
    string resp3 = exec("./run_app_1 ../tests/input/movies3.csv ../tests/input/input3.txt");
    ASSERT_EQ(desired3, resp3);
    add_points_to_grade(6.25);
    
    string desired4 = readFileIntoString("../tests/output/output4.txt");
    string resp4 = exec("./run_app_1 ../tests/input/movies4.csv ../tests/input/input4.txt");
    ASSERT_EQ(desired4, resp4);
    add_points_to_grade(6.25);
}