//cs_trivia.h

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sys/time.h>
#include <cctype>

// Andy Fleischer - CS 163 - Program #1 - 4/6/2021
// -----------------------------------------------  
// This class is an Abstract Data Type used to store 
// a list of categories of trivia questions, each with
// a list of trivia questions and answers.
// The client program can add trivia questions, display
// all questions of a category, remove categories, and
// select random questions and check their answers.

struct trivia //the data of a trivia question not related to data structure
{
    char* question;
    char* answer;
    bool asked;
};

struct trivia_node //node for trivia question
{
    trivia item;
    trivia_node* next;
};

struct category_node //node for category (holds a head trivia node)
{
    ~category_node();

    int length; //used for efficiency in select_question
    char* category;
    trivia_node* questions;
    category_node* next;
};

class cs_trivia
{
    public:
	    cs_trivia(); //default constructor (Task 1) 
        ~cs_trivia(); //destructor (Task 2)

	    //the following methods will return 0 if executed successfully or 1 if an error occured 
        int add_question(char question[], char answer[], char category[]); //adds a question given a trivia struct and category (Task 3)
        int display_category(char category[]) const; //displays all questions of a given category (Task 4)
        int display_all() const; //displays all questions (Task 5)
        int remove_category(char to_remove[]); //remove the given category and all associated questions (Task 6)
        int select_question(char category[]); //displays a random unused question of a given category, returning 2 if all questions have been used (Task 7)
	    //-------------------------------------------------------------------------------------
        bool check_answer(char guess[]); //returns true if the given guess matches the last question asked, otherwise false (Task 8)

    private:
        category_node* head; //head of category LLL
        trivia_node* last_asked; //pointer to the last question asked (used for check_answer method)
};
