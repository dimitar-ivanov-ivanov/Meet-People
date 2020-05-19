#include "meet.h"

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
