//main.cpp

#include "cs_trivia.h"
using namespace std;

// Andy Fleischer - CS 163 - Program #1 - 4/6/2021
// -----------------------------------------------  
// This is an example of an application for implementing
// the ADT. It does not have thorough input checking
// and the functions are to test and run the functions
// in the ADT.

void add(cs_trivia* list);
void check(cs_trivia* list);
void display_all(cs_trivia* list);
void display_category(cs_trivia* list);
void help();
void remove(cs_trivia* list);
void select(cs_trivia* list);

int main()
{
    cs_trivia* list = new cs_trivia();

    cout << "---------------------" << endl;
    cout << "Welcome to cs_trivia!" << endl;
    cout << "---------------------" << endl;
    help();

    char input[10];
    while (strcmp(input, "quit") != 0) //continue taking user input until they say quit
    {
        cout << ">> ";
        cin.get(input, 20);
        cin.get();
        if (strcmp(input, "add") == 0)
            add(list);
        else if (strcmp(input, "check") == 0)
            check(list);
        else if (strcmp(input, "dall") == 0)
            display_all(list);
        else if (strcmp(input, "dcat") == 0)
            display_category(list);
        else if (strcmp(input, "help") == 0)
            help();
        else if (strcmp(input, "remove") == 0)
            remove(list);
        else if (strcmp(input, "select") == 0)
            select(list);
        else if (strcmp(input, "quit") != 0)
            cout << "Invalid command." << endl;
    }

    delete list;

    return 0;
}

void add(cs_trivia* list) //add a trivia question
{
    char category[20];
    char question[100];
    char answer[100];

    cout << "Category: ";
    cin.get(category, 20);
    cin.get();
    cout << "Question: ";
    cin.get(question, 100);
    cin.get();
    cout << "Answer: ";
    cin.get(answer, 100);
    cin.get();

    if (list->add_question(question, answer, category))
        cout << "Added." << endl;
    else
        cout << "Error occured when adding question." << endl;    
}

void check(cs_trivia* list) //check if given answer matches last question asked
{
    char answer[100];

    cout << "Answer: ";
    cin.get(answer, 100);
    cin.get();

    if (list->check_answer(answer))
        cout << "Correct!" << endl;
    else
        cout << "Wrong!" << endl;
}

void display_all(cs_trivia* list) //display all questions
{
    if (!list->display_all())
        cout << "No questions." << endl;
}

void display_category(cs_trivia* list) //display all questions from one category
{
    char category[20];

    cout << "Category: ";
    cin.get(category, 20);
    cin.get();

    if (!list->display_category(category))
        cout << "Could not find category \"" << category << "\"." << endl;
}

void help() //show valid commands
{
    cout << "Valid commands are:" << endl;
    cout << "  add    - Add a new trivia question" << endl;
    cout << "  check  - Checks if given answer is correct for the last question asked" << endl;
    cout << "  dall   - Display all questions, answers, and if they have been asked from all categories" << endl;
    cout << "  dcat   - Display all questions of a single category" << endl;
    cout << "  help   - List these commands" << endl;
    cout << "  remove - Remove a given category" << endl;
    cout << "  select - Display a random question from a category" << endl;
    cout << "  quit   - Stop the program" << endl;
}

void remove(cs_trivia* list) //remove all questions from a given category
{
    char category[20];

    cout << "Category: ";
    cin.get(category, 20);
    cin.get();

    if (list->remove_category(category))
        cout << "Removed." << endl;
    else
        cout << "Could not find category \"" << category << "\"." << endl;
}

void select(cs_trivia* list) //select and display a random question
{
    char category[20];

    cout << "Category: ";
    cin.get(category, 20);
    cin.get();

    int result = list->select_question(category);
    if (!result)
        cout << "Could not find category \"" << category << "\"." << endl;
    else if (result == 2)
        cout << "All questions in that category have been asked." << endl;
}
