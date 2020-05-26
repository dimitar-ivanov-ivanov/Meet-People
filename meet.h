#ifndef MEET_H_INCLUDED
#define MEET_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "messages.h"

#define LEN 50
#define INTEREST 250
#define NUMOFANSWERS 4
#define SIZEINCREMENT 5
#define MINQUESTIONWEIGHT 0
#define MAXQUESTIONWEIGHT 1
#define MINANSWERWEIGHT 0
#define MAXANSWERWEIGHT 100
#define MAXID 5000
#define FILENAME "people.bin"

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
void seedData(int n);
int generateRandNum(int lower,int upper);
void personMenu();
sPerson inputPerson();
void inputGender(sPerson *person);
void inputDate(sPerson *person);
void inputStatus(sPerson *person);
void inputQuestions(sPerson *person);
void addQuestion(sPerson *person,sQuestion *question);
double getNum(char *inputMessage,char *errorMessage,double minVal,double maxVal);
void getString(char *inputMessage,char *errorMessage,int n,char *validVals[],char str[LEN]);
int numInRange(double a,double b,double c);
void printAllPeople(sNode *head);
void printPerson(sPerson *person,int restriction);
int findPerson(unsigned int id);
void addElementAtEnd(sPerson *person);
sNode * createElement(sPerson *person);
void removePerson(int ID);
void askPersonQuestions();
sPerson * getPerson(int index);
void DeleteList(void);

extern sNode *head;
extern int totalPeople;
extern int questionsSize;

#endif // MEET_H_INCLUDED
