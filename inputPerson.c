#include "meet.h"

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
        fflush(stdin);
        gets(gender);
        if(!strcmp(gender,"Male")) {
            person->gender = Male;
            break;
        }
        if(!strcmp(gender,"Female")) {
            person->gender = Female;
            break;
        }
        printf("%s",ERRORGENDER);
    }
}

void inputDate(sPerson *person) {
    sDate date;

    printf("Enter date:\n");
    date.day =  getNum("----Enter day: ",ERRORDAY,1,31);
    date.month =  getNum("----Enter month: ",ERRORMONTH,1,12);

    //can't allow people who are too old or too young on a dating site can we
    date.year =  getNum("----Enter year: ",ERRORYEAR,1900,2002);
    person->dateOfBirth = date;
}

void inputStatus(sPerson *person) {
    char personStatus[LEN];
    while(1) {
        printf("Enter engagement status (Single , Engaged , Married): ");
        fflush(stdin);
        gets(personStatus);

        if(!strcmp(personStatus,"Single")) {
            person->status = Single;
            break;
        }
        if(!strcmp(personStatus,"Engaged")) {
            person->status = Engaged;
            break;
        }
        if(!strcmp(personStatus,"Married")) {
            person->status = Married;
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
    fflush(stdin);
    scanf("%d",&numQuestions);

    person->questionsCount = 0;
    person->maxQuestionResult = 0;
    questionsSize = numQuestions;

    if(NULL == (person->questions = (sQuestion *)malloc(questionsSize * sizeof(sQuestion)))) {
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
            fflush(stdin);
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
            printf("--------Enter answer text: ");
            fflush(stdin);
            gets(answer.text);

            //asnwer weight cannot be negative
            while(1) {
                printf("--------Enter answer weight: ");
                fflush(stdin);
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
        if(NULL == (person->questions = (sQuestion *)realloc(person->questions, questionsSize* sizeof(sQuestion)))) {
            printf("%s",ERRORMEMALLOC);
            exit(5);
        }
    } else {
        person->questions[person->questionsCount++] = *question;
    }
}

double getNum(char *inputMessage,char *errorMessage,double minVal,double maxVal) {
    double num;
    while(1) {
        printf("%s",inputMessage);
        fflush(stdin);
        scanf("%lf",&num);
        if(num < minVal || num > maxVal) {
            printf("%s",errorMessage);
        } else {
            break;
        }
    }

    return num;
}
