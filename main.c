#include "main.h"

int main() {
    runProgram();
    return 0;
}

void runProgram() {
    char fileName[] = FILENAME;
    srand(time(NULL));
    writeDataInFile(fileName);
    readDataFromFile(fileName);
    personMenu();
}

void writeDataInFile(char *fileName) {
    FILE *fp;
    sPerson person;

    if((fp = fopen(fileName,"wb")) == NULL) {
        printf("%s",ERROROPENING);
        exit(1);
    }

    printf("Enter number of people: ");
    scanf("%d",&totalPeople);

    for(int i = 0; i < totalPeople; i++) {
        printf("Person %d\n",i+1);
        person = inputPerson();
        if(fwrite(&person,sizeof(sPerson),1,fp) != 1) {
            printf("%s",ERRORWRITE);
            exit(2);
        }
    }

    if(fclose(fp) == EOF) {
        printf("%s",ERRORCLOSING);
        exit(3);
    }
}

void readDataFromFile(char *fileName) {
    FILE *fp;
    sPerson person;

    if((fp = fopen(fileName,"rb")) == NULL) {
        printf("%s",ERROROPENING);
        exit(6);
    }

    //can't have two people with same ID
    while(!feof(fp)) {
        //can't read another person end loop
        if(fread(&person,sizeof(sPerson),1,fp) != 1) {
            break;
        }
        if(!findPerson(person.ID)) {
            addElementAtEnd(&person);
        } else {
            printf("%s",EXISTINGID);
        }
    }

    if(fclose(fp) == EOF) {
        printf("%s",ERRORCLOSING);
        exit(7);
    }
}

void personMenu() {
    int option;
    int ID;
    sPerson person;

    while(1) {
        printf("%s",MENU);
        scanf("%d",&option);
        fflush(stdin);

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
            printAllPeople();
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

sPerson inputPerson() {
    sPerson person;

    fflush(stdin);
    printf("Enter ID: ");
    scanf("%d",&person.ID);
    fflush(stdin);

    printf("Enter full name: ");
    gets(person.name);
    fflush(stdin);

    inputGender(&person);
    inputDate(&person);

    fflush(stdin);
    printf("Enter a description of yourself:");
    gets(person.interests);

    inputStatus(&person);
    inputQuestions(&person);
    return person;
}

void inputGender(sPerson *person) {
    char gender[LEN];

    //put it in a endless loop to make sure the right amount is processed
    while(1) {
        printf("Enter gender(Male/or Female): ");
        gets(gender);
        fflush(stdin);
        if(!strcmp(gender,"Male")) {
            person->gender = (Gender)0;
            break;
        }
        if(!strcmp(gender,"Female")) {
            person->gender = (Gender)1;
            break;
        }
        printf("%s",ERRORGENDER);
    }
}

void inputDate(sPerson *person) {
    sDate date;

    //can't allow people who are too old or too young on a dating site can we
    while(1) {
        printf("Enter date: (DD.MM.YYYY): ");
        scanf("%d.%d.%d",&date.day,&date.month,&date.year);

        if(date.day < 1 || date.day > 31) {
            printf("%s",ERRORDAY);
            continue;
        }
        if(date.month < 1 || date.month > 12) {
            printf("%s",ERRORMONTH);
            continue;
        }
        if(date.year < 1900) {
            printf("%s",ERROROLD);
            continue;
        }
        if(date.year > 2002) {
            printf("%s",ERRORYOUNG);
            continue;
        }
        break;
    }

    person->dateOfBirth = date;
}

void inputStatus(sPerson *person) {
    char personStatus[LEN];
    while(1) {
        printf("Enter engagement status (Single , Engaged , Married): ");
        gets(personStatus);
        fflush(stdin);

        if(!strcmp(personStatus,"Single")) {
            person->status = (Status)0;
            break;
        }
        if(!strcmp(personStatus,"Engaged")) {
            person->status = (Status)1;
            break;
        }
        if(!strcmp(personStatus,"Married")) {
            person->status = (Status)2;
            break;
        }
        printf("%s",ERRORSTATUS);
    }
}

void inputQuestions(sPerson *person) {
    int numQuestions;
    sQuestion question;
    sAnswer answer;
    double maxAnswerWeight;

    printf("Enter number of questions:");
    scanf("%d",&numQuestions);

    person->questionsCount = 0;
    person->maxQuestionResult = 0;
    questionsSize = numQuestions;

    if((person->questions = (sQuestion *)malloc(questionsSize * sizeof(sQuestion))) == NULL) {
        printf("%s",ERRORMEMALLOC);
        exit(4);
    }

    for(int i = 0; i < numQuestions; i++) {
        printf("----Question %d\n",i+1);
        fflush(stdin);
        printf("----Enter question text: ");
        gets(question.text);

        //the question weight must be from 0 to 1
        while(1) {
            printf("----Enter question weight: (between 0 and 1): ");
            scanf("%lf",&question.weight);
            if(!(question.weight < 0 || question.weight > 1)) {
                break;
            }
            printf("%s",ERRORQUESTIONWEIGHT);
        }

        //try to get the maximum wieght of all 4 answers to determine the max multiplication of the current wieght of question and answer
        maxAnswerWeight = INT_MIN;
        printf("--------Enter answers:\n");
        for(int j = 0; j < NUMOFANSWERS; j++) {
            printf("--------Answer %d\n",j+1);
            fflush(stdin);
            printf("--------Enter answer text: ");
            gets(answer.text);
            fflush(stdin);

            //asnwer weight cannot be negative
            while(1) {
                printf("--------Enter answer weight: ");
                scanf("%d",&answer.weight);
                if(answer.weight >= 0) {
                    break;
                } else {
                    printf("%s",ERRORANSWERWEIGHT);
                }
            }
            question.answers[j] = answer;

            if(answer.weight > maxAnswerWeight) {
                maxAnswerWeight = answer.weight;
            }
        }

        addQuestion(person,&question);
        person->maxQuestionResult += question.weight * maxAnswerWeight;
    }
}

void addQuestion(sPerson *person,sQuestion *question) {
    if(person->questionsCount == questionsSize) {
        questionsSize += SIZEINCREMENT;
        if((person->questions = (sQuestion *)realloc(person->questions, questionsSize* sizeof(sQuestion))) == NULL) {
            printf("Problem with reallocating memory\n");
            exit(5);
        }
    } else {
        person->questions[person->questionsCount++] = *question;
    }
}

int findPerson(unsigned int id) {
    sNode *ptemp = head;
    while(ptemp != NULL) {
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
    if(head == NULL) {
        head = pnewElement;
        return;
    }

    while(ptemp->next != NULL) {
        ptemp = ptemp->next;
    }

    ptemp->next = pnewElement;
}

sNode * createElement(sPerson *person) {
    sNode* tempP = (sNode *)malloc(sizeof(sNode));
    if(tempP == NULL) {
        printf("Error!");
        exit(8);
    }

    tempP->next = NULL;
    tempP->person = *person;
    return tempP;
}

void askPersonQuestions() {
    int index = rand() % totalPeople;

    sPerson person;
    getPerson(index,&person);
    printPerson(&person,0);
    sQuestion question;
    sAnswer answer;
    int i,j,answerIndex;
    double totalWeight = 0;

    if(person.questionsCount == 0){
        printf("Person has no questions\n");
        return;
    }

    for(i = 0; i < person.questionsCount; i++) {
        question = person.questions[i];

        printf("----Question %s\n",question.text);
        printf("--------Answers:\n");

        for(j = 0; j < NUMOFANSWERS; j++) {
            answer = question.answers[j];
            printf("--------Answer %d: %s\n",j+1,answer.text);
        }

        //if the user picked an invalid answer index ask him again
        while(1) {
            printf("Pick one answer: ");
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

    printf("User Result: %lf/%lf\n",totalWeight,person.maxQuestionResult);
    if(totalWeight == person.maxQuestionResult) {
        printf("Congrats! you have perfectly answered %s's questions!\n",person.name);
    } else {
        printf("You have failed at answering %s's questions try again!\n",person.name);
    }
}

void getPerson(int index,sPerson *person) {
    sNode *ptemp = head;
    while(ptemp != NULL) {
        //we have found the person we need
        if(index == 0) {
         *person = ptemp->person;
        }
        index--;
        ptemp = ptemp->next;
    }
}

void printAllPeople() {
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

    printf("Gender %s\n",gender);
    printf("Date of birth %02d.%02d.%d\n",person->dateOfBirth.day,person->dateOfBirth.month,person->dateOfBirth.year);
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

void removePerson(int ID) {
    sNode *ptemp = head;

    if(head == NULL) {
        printf("%s",LISTEMPTY);
        return;
    }

    //remove head
    if(head != NULL && head->person.ID == ID) {
        head = head->next;
        totalPeople--;
        return;
    }

    //since we are not removing the head we can safely make the check for the next element in line
    //we check for the next element, because if the current happends to be the one we are looking for we won't be able to rearrange the connections
    //from the previous to the next element

    while(ptemp->next != NULL) {
        if(ptemp->next->person.ID == ID) {
            //we have to remove the next element
            //the current's next element shoud be equal to the next element's next
            ptemp->next = ptemp->next->next;
            totalPeople--;
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
        free(temp);
    }
}
