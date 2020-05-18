#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define LEN 50
#define INTEREST 250
#define NUMOFANSWERS 4
#define SIZEINCREMENT 5
#define FILENAME "people.txt"
#define ERROROPENING "Error opening file\n"
#define ERRORCLOSING "Error closing file\n"
#define ERRORWRITE "Error trying to write person in file\n"
#define ERRORGENDER "Incorrect gender\n"
#define ERRORSTATUS "Incorrect status\n"
#define ERRORDAY "Incorrect day\n"
#define ERRORMONTH "Incorrect month\n"
#define ERROROLD "Incorrect year (too old)\n"
#define ERRORYOUNG "Incorrect year (too young)\n"
#define ERRORMEMALLOC "Problem with allocating memory\n"
#define ERRORQUESTIONWEIGHT "Question weight should be between 0 and 1\n"
#define ERRORANSWERWEIGHT "Answer wight cannot be lower than 0\n"
#define MENU "Choose option:\n1. Add person\n2. Print all people\n3. Answers a person's questions\n4. Remove person by ID\n0. End menu\n"
#define ERRORANSWERINDEX "Answer index must be between 0 and 4\n"
#define EXISTINGID "ID alredy exists\n"
#define LISTEMPTY "List empty"
#define NOPEOPLE "No people\n"
#define ENDING "Ending program.\n"

typedef enum {Male = 0, Female = 1} Gender;
typedef enum {Single=0, Engaged=1, Married=2} Status;

typedef struct date {
    int day;
    int month;
    int year;
} sDate;

typedef struct answer {
    char text[LEN];
    int weight;
} sAnswer;

typedef struct question {
    char text[LEN];
    double weight;
    sAnswer answers[NUMOFANSWERS];
} sQuestion;

typedef struct person {
    int ID;
    char name[LEN];
    Gender gender;
    sDate dateOfBirth;
    char interests[INTEREST];
    Status status;
    sQuestion *questions;
    int questionsCount;
    double maxQuestionResult;
} sPerson;

typedef struct node {
    sPerson person;
    struct node *next;
} sNode;

void runProgram();
void writeDataInFile(char *fileName);
void readDataFromFile(char *fileName);
void personMenu();
sPerson inputPerson();
void inputGender(sPerson *person);
void inputDate(sPerson *person);
void inputStatus(sPerson *person);
void inputQuestions(sPerson *person);
void addQuestion(sPerson *person,sQuestion *question);
void printAllPeople();
void printPerson(sPerson *person,int restriction);
int findPerson(unsigned int id);
void addElementAtEnd(sPerson *person);
sNode * createElement(sPerson *person);
void removePerson(int ID);
void askPersonQuestions();
void getPerson(int index,sPerson *person);
void DeleteList(void);

sNode *head = NULL;
int totalPeople;
int questionsSize;
