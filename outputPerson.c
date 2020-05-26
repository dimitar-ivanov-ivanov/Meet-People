#include "meet.h"

void printAllPeople(sNode *head) {
    sNode * ptemp = head;
    if(ptemp == NULL) {
        printf("%s",NOPEOPLE);
        return;
    }

    while(ptemp != NULL) {
        printPerson(&ptemp->person,1);
        printf("---------------------------------------------------------------------------\n");
        ptemp = ptemp->next;
    }
}

void printPerson(sPerson *person,int restriction) {
    sQuestion question;
    sAnswer answer;
    char gender[LEN];
    char status[LEN];

    printf("Name: %s\n",person->name);
    printf("ID: %d\n",person->ID);
    if(person->gender == Male) {
        strcpy(gender,"Male");
    } else if(person->gender == Female) {
        strcpy(gender,"Female");
    }

    printf("Gender: %s\n",gender);
    printf("Date of birth: %02d.%02d.%d\n",person->dateOfBirth.day,person->dateOfBirth.month,person->dateOfBirth.year);
    printf("Description: %s\n",person->interests);

    if(person->status == Single) {
        strcpy(status,"Single");
    } else if(person->status == Engaged) {
        strcpy(status,"Engaged");
    } else if(person->status == Married) {
        strcpy(status,"Married");
    }

    printf("Engagement status: %s\n",status);

    //restriction is 0 if we are asking the person and we want to show his information but not the questions and answers with their respective weight
    if(restriction == 0) {
        return;
    }

    for(int i = 0; i < person->questionsCount; i++) {
        question = person->questions[i];
        printf("----Question: %s\n",question.text);
        printf("----Question weight: %0.2lf\n",question.weight);

        for(int j = 0; j < NUMOFANSWERS; j++) {
            answer = question.answers[j];
            printf("--------Answer: %s\n",answer.text);
            printf("--------Answer weight: %d\n",answer.weight);
        }
    }
}

