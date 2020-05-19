#include "meet.h"

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
