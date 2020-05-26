#include "meet.h"

void personMenu() {
    int option;
    int ID;
    sPerson person;

    while(1) {
        printf("%s",MENU);
        fflush(stdin);
        scanf("%d",&option);

        switch (option) {
        case 1:
            person = inputPerson();
            if(!findPerson(person.ID)) {
                addElementAtEnd(&person);
                totalPeople++;
            } else {
                printf("%s",EXISTINGID);
            }
            break;
        case 2:
            printAllPeople(head);
            break;
        case 3:
            askPersonQuestions();
            break;
        case 4:
            printf("Enter ID: ");
            scanf("%d",&ID);
            fflush(stdin);
            removePerson(ID);
            break;
        case 0:
            printf("%s",ENDING);
            DeleteList();
            return;
        default:
            break;
        }
    }
}

int findPerson(unsigned int id) {
    sNode *ptemp = head;
    while(NULL != ptemp) {
        if(ptemp->person.ID == id) {
            return 1;
        }
        ptemp = ptemp->next;
    }

    return 0;
}

void addElementAtEnd(sPerson *person) {
    sNode * pnewElement = createElement(person);
    sNode * ptemp = head;

    //If list is empty
    if(NULL == head) {
        head = pnewElement;
        return;
    }

    while(NULL != ptemp->next) {
        ptemp = ptemp->next;
    }

    ptemp->next = pnewElement;
    totalPeople++;
}


sNode * createElement(sPerson *person) {
    sNode* tempP = (sNode *)malloc(sizeof(sNode));
    if(NULL == tempP) {
        printf("Error!");
        exit(8);
    }

    tempP->next = NULL;
    tempP->person = *person;
    return tempP;
}

void askPersonQuestions() {
    sPerson *person;
    srand(time(NULL));

    if(totalPeople == 0) {
        printf("%s",NOPEOPLE);
        return;
    }

    while(1) {
        int index = rand() % totalPeople;
        person = getPerson(index);
        if(NULL != person) {
            break;
        }
    }

    printPerson(person,0);
    sQuestion question;
    sAnswer answer;
    int i,j,answerIndex;
    double totalWeight = 0;

    if(person->questionsCount == 0) {
        printf("Person has no questions\n");
        return;
    }

    for(i = 0; i < person->questionsCount; i++) {
        question = person->questions[i];

        printf("----Question %s\n",question.text);
        printf("--------Answers:\n");

        for(j = 0; j < NUMOFANSWERS; j++) {
            answer = question.answers[j];
            printf("--------Answer %d: %s\n",j+1,answer.text);
        }

        //if the user picked an invalid answer index ask him again
        while(1) {
            printf("Pick one answer: ");
            fflush(stdin);
            scanf("%d",&answerIndex);
            if(answerIndex >=1 && answerIndex <=4) {
                break;
            } else {
                printf("%s",ERRORANSWERINDEX);
            }
        }

        answerIndex--;
        totalWeight += question.weight * question.answers[answerIndex].weight;
    }

    printf("User Result: %lf/%lf\n",totalWeight,person->maxQuestionResult);
    if(totalWeight == person->maxQuestionResult) {
        printf("Congrats! you have perfectly answered %s's questions!\n",person->name);
    } else if(totalWeight >= person->maxQuestionResult * 80 / 100) {
        printf("You have succeeded at answering some of %s's questions.\n",person->name);
    } else {
        printf("You have failed at answering %s's questions try again!\n",person->name);
    }
}

sPerson * getPerson(int index) {
    sNode *ptemp = head;
    while(NULL != ptemp) {
        //we have found the person we need
        if(index == 0) {
            return &ptemp->person;
        }
        index--;
        ptemp = ptemp->next;
    }
    return NULL;
}

void removePerson(int ID) {
    sNode *ptemp = head;
    sNode *ptemp2;

    if(NULL == head) {
        printf("%s",LISTEMPTY);
        return;
    }

    //remove head
    if(head->person.ID == ID) {
        head = head->next;
        free(ptemp->person.questions);
        free(ptemp);
        totalPeople--;
        return;
    }

    //since we are not removing the head we can safely make the check for the next element in line
    //we check for the next element, because if the current happends to be the one we are looking for we won't be able to rearrange the connections
    //from the previous to the next element

    while(NULL != ptemp->next) {
        if(ptemp->next->person.ID == ID) {
            //we have to remove the next element
            //the current's next element shoud be equal to the next element's next
            ptemp2 = ptemp->next;
            ptemp->next = ptemp->next->next;
            free(ptemp2->person.questions);
            free(ptemp2);
            totalPeople--;
            printf("%d\n",totalPeople);
            return;
        }
        ptemp = ptemp->next;
    }
}

void DeleteList(void) {
    sNode * temp;
    while(head != NULL) {
        temp = head;
        head = head->next;
        free(temp->person.questions);
        free(temp);
    }
}
