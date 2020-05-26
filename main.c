#include "meet.h"

sNode *head = NULL;
int totalPeople = 0;
int questionsSize = 5;

int main() {
    runProgram();
    return 0;
}

void runProgram() {
    char fileName[] = FILENAME;
    char str[LEN];
    char *validVals[] = {"Yes","No"};
    getString("Wish to add people randomly? (Yes/No): ",ERRORSTARTUP,2,validVals,str);
    if(strcpy(str,"Yes")) {
        int n = getNum("How many people to add: ",ERRORPEOPLENUM,0,20);
        seedData(n);
    } else {
        writeDataInFile(fileName);
        readDataFromFile(fileName);
    }

    personMenu();
}
