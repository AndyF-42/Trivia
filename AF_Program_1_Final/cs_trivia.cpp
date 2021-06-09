//cs_trivia.cpp

#include "cs_trivia.h"

// Andy Fleischer - CS 163 - Program #1 - 4/9/2021
// -----------------------------------------------  
// This class is an Abstract Data Type used to store 
// a list of categories of trivia questions, each with
// a list of trivia questions and answers.
// The client program can add trivia questions, display
// all questions of a category, remove categories, and
// select random questions and check their answers.

category_node::~category_node()
{
    length = 0;
    delete [] category; //remove category from memory 
    
    trivia_node* current_triv = questions; //remove questions
    while (current_triv)
    {
        current_triv->item.question = NULL;
        delete [] current_triv->item.question;
        current_triv->item.answer = NULL;
        delete [] current_triv->item.answer;
        current_triv->item.asked = false;

        trivia_node* temp = current_triv->next;
        delete current_triv;
        current_triv = temp;
    }
    category = NULL;
}

cs_trivia::cs_trivia()
{
    last_asked = NULL;
    head = NULL;
}

cs_trivia::~cs_trivia()
{
    last_asked = NULL; //not dynamically allocated, don't need to delete 

    category_node* current_cat = head;
    while (current_cat)
    {
        category_node* temp = current_cat->next; //go to next
        delete current_cat; //call category_node destructor
        current_cat = temp;
    }
    head = NULL;
}

int cs_trivia::add_question(char question[], char answer[], char category[])
{
    if (!question || !answer || !category)
        return 0; //error: bad inputs

    //create the node for the question
    trivia_node* temp = new trivia_node;
    temp->item.question = new char[strlen(question) + 1];
    strcpy(temp->item.question, question);
    temp->item.answer = new char[strlen(answer) + 1];
    strcpy(temp->item.answer, answer);
    temp->item.asked = false;
    temp->next = NULL;

    if (!head) //no existing questions
    {
        head = new category_node;
        head->category = new char[strlen(category) + 1];
        strcpy(head->category, category);
        head->questions = temp;
        head->next = NULL;
        head->length = 1;
        return 1;
    }

    category_node* current_cat = head;
    while (current_cat->next && strcmp(current_cat->category, category) != 0) //loop through until before the last category or at the matching category
        current_cat = current_cat->next;

    if (strcmp(current_cat->category, category) == 0) //category exists
    {
        current_cat->length++;
        trivia_node* current_triv = current_cat->questions;
        if (!current_triv) //technically will never happen
        {
            current_cat->questions = temp;
            return 1;
        }
        while (current_triv->next)
            current_triv = current_triv->next;
        current_triv->next = temp;
        return 1;
    }
   
    //category does not exist yet 
    category_node* new_cat = new category_node;
    new_cat->category = new char[strlen(category) + 1];
    strcpy(new_cat->category, category);
    new_cat->questions = temp;
    new_cat->next = NULL;
    new_cat->length = 1;
    current_cat->next = new_cat;

    return 1;
}

int cs_trivia::display_category(char category[]) const
{
    if (!head || !category)
        return 0; //error: no questions or bad input

    category_node* current_cat = head;
    while (current_cat && strcmp(current_cat->category, category) != 0) //loop through categories, search for match
        current_cat = current_cat->next;

    if (!current_cat)
        return 0; //error: category not found

    trivia_node* current_triv = current_cat->questions;
    while (current_triv) //loop through questions
    {
        std::cout << "    Q: " << current_triv->item.question << std::endl;
        current_triv = current_triv->next;
    }
    return 1;
}

int cs_trivia::display_all() const
{
    if (!head)
        return 0; //error: nothing to display

    category_node* current_cat = head;
    while (current_cat) //loop through categories
    {
        std::cout << "Category: " << current_cat->category << std::endl;
        std::cout << "Length: " << current_cat->length << std::endl;
        trivia_node* current_triv = current_cat->questions;
        while (current_triv) //loop through questions
        {
            std::cout << "    Q: " << current_triv->item.question << std::endl;
            std::cout << "    A: " << current_triv->item.answer << std::endl;
            if (current_triv->item.asked)
                std::cout << "    Asked\n" << std::endl;
            else
                std::cout << "    Not asked\n" << std::endl;
            current_triv = current_triv->next;
        }
        current_cat = current_cat->next;
    }
    return 1; 
}

int cs_trivia::remove_category(char category[])
{
    if (!head || !category)
        return 0; //error: no categories or bad input

    if (strcmp(head->category, category) == 0) //if head is the match, update head
    {
        category_node* temp = head->next;
        delete head;
        head = temp;
        return 1;
    }

    category_node* current_cat = head;
    while (current_cat->next && strcmp(current_cat->next->category, category) != 0) //loop through categories, search for match
        current_cat = current_cat->next;

    if (!current_cat->next)
        return 0; //error: could not find category
    else
    {
        category_node* temp = current_cat->next->next;
        delete current_cat->next;
        current_cat->next = temp;
    }
    return 1;
}

int cs_trivia::select_question(char category[])
{
    if (!category)
        return 0; //error: bad input

    category_node* current_cat = head;
    while (current_cat && strcmp(current_cat->category, category) != 0)
        current_cat = current_cat->next;

    if (!current_cat)
        return 0; //error: could not find category

    srand(time(0)); //choose a random number and go to that spot in the list of questions
    int random = rand() % current_cat->length;
    trivia_node* selection = current_cat->questions;
    for (int i = 0; i < random; i++)
        selection = selection->next;

    trivia_node* starting = selection; //store the question we started on
    while (selection->item.asked)
    {
        selection = selection->next;
        if (!selection) //if we went to the end, loop to front
            selection = current_cat->questions;
        if (selection == starting) //looped all around
            return 2; //error: all questions have been asked
    }

    std::cout << selection->item.question << std::endl;
    selection->item.asked = true;
    last_asked = selection;
    return 1;
}

bool cs_trivia::check_answer(char answer[])
{
    if (!answer || strlen(last_asked->item.answer) != strlen(answer)) //bad data or not same length, must be wrong (following loop does not check different lengths)
        return false;

    for (size_t i = 0; i < strlen(last_asked->item.answer); i++)
        if (std::tolower(last_asked->item.answer[i]) != std::tolower(answer[i])) //change both to lower and compare
             return false;
    return true;
}
