#include "meet.h"

void seedData(int n) {
    int i,j,k,indexName,indexGender,indexStatus,indexDescriptions,countQuestions,indexQuestion,indexAnswer;
    double maxAnswerWeight;
    sPerson person;
    sQuestion question;
    sAnswer answer;
    srand(time(NULL));

    char *maleNames[] = {"Dimitar","Ivan","Stoqn","Pesho","Grigor","Georgi","Kiro","Nikola","Daniel",
                         "Kostadin","Hristo","Marin","Momchil","Boris","Mihail","Stanislav","Elon Musk","Slavi Trifonov"
                        };

    char *femaleNames[] = {"Ivanka","Dimitrinka","Milka","Stanislava","Anita","Daniela","Sasha","Teodora","Qnica","Krasimira","Sonq"};
    char *descriptions[] = {
        "Hello, I am a student from Sofia. Very interested in engineering.",
        "I am from a small city called Haskovo, recently moved to Sofia care to show me around?",
        "Hey, how about we go out and you get to listen to my unfunny jokes?",
        "Beautiful, artistic and knowledgeable, reminds me of you.",
        "If I had a cent every time someone mispronounced my name I would be a millionaire",
        "Grad student from Mississippi, here for 2 weeks wanna go out?",
        "Nothing serious",
        "You think I look gay in my picture, wait till you see me in real life!",
        "Roses are red, violets are blue, what would I do if I can't couldn't go out with you!",
        "Roses are red,violets are blue,white wine costs less,Than dinner for two.",
        "Roses are red,the earth is wide,you’d look much better,with me by your side."
    };

    char *questions[] = {
        "Do you drink?",
        "Do you smoke?",
        "Where are you from?",
        "What is your job?",
        "Why did you choose you profession?",
        "Why did you make an account?",
        "Why is a married person on this platform?",
        "What is your your favorite song to work to?",
        "Do you do sports?",
        "You like playing games?",
        "Favorite book?",
        "Favorite television show?",
        "What is the most beautiful place in your city?",
        "When are going on a date?",
        "If we went on a date, where would we go?",
        "Pineapple on pizza yes or no?",
        "Who's your favorite singer and why is it Galena?",
        "Between 10 and 100 how many coffees do you drink a day?"
    };

    char *answers[]= {
        "Yes",
        "No",
        "Everyday",
        "Always",
        "Every once in a while",
        "Often",
        "Sometimes",
        "Once in a blue moon",
        "Rarely",
        "Nicely",
        "Yesterday",
        "Sofiq",
        "Varna",
        "Burgas",
        "Dobrich",
        "Programmer",
        "Student",
        "Teacher",
        "Unemployed",
    };

    for(i = 0; i < n; i++) {
        indexGender = generateRandNum(0,1);
        person.gender = indexGender;
        if(person.gender == Male) {
            indexName = generateRandNum(0,17);
            strcpy(person.name,maleNames[indexName]);
        } else if(person.gender == Female) {
            indexName = generateRandNum(0,10);
            strcpy(person.name,femaleNames[indexName]);
        }

        indexStatus = generateRandNum(0,2);
        person.status = indexStatus;
        indexDescriptions = generateRandNum(0,10);
        strcpy(person.interests,descriptions[indexDescriptions]);

        person.dateOfBirth.day = generateRandNum(1,31);
        person.dateOfBirth.month = generateRandNum(1,12);
        person.dateOfBirth.year = generateRandNum(1900,2002);

        countQuestions = generateRandNum(0,3);
        person.questionsCount = 0;
        person.maxQuestionResult = 0;

        //printf("%d\n",questionsSize);
        //printf("Person: %d %d\n",i,person.questionsCount);
        if(NULL == (person.questions = (sQuestion *)malloc(questionsSize * sizeof(sQuestion)))) {
            printf("%s",ERRORMEMALLOC);
            exit(4);
        }

        for(j = 0; j < countQuestions; j++) {
            indexQuestion = generateRandNum(0,17);
            strcpy(question.text,questions[indexQuestion]);
            question.weight = generateRandNum(10,100) * 0.01;

            //printf("----%s %lf\n",question.text,question.weight);
            maxAnswerWeight = INT_MIN;
            for(k = 0; k < NUMOFANSWERS; k++) {
                indexAnswer = generateRandNum(0,18);
                strcpy(answer.text,answers[indexAnswer]);
                answer.weight = generateRandNum(10,100);
                question.answers[k] = answer;
                //printf("--------%s %d\n",answer.text,answer.weight);

                if(answer.weight > maxAnswerWeight) {
                    maxAnswerWeight = answer.weight;
                }
            }

            addQuestion(&person,&question);
            person.maxQuestionResult += question.weight * maxAnswerWeight;
        }

        person.ID = rand() % MAXID;
        if(!findPerson(person.ID)) {
            addElementAtEnd(&person);
            totalPeople++;
        }
    }
}

int generateRandNum(int lower,int upper) {
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}
