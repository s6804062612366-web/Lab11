#include <stdio.h>
#include <stdlib.h>

#define NO_SCORE 5
#define STU_COUNT 10

typedef struct {
    char name[16];
    char surname[20];
    int score[NO_SCORE];
    float total;
} Student;

void readStudentData(Student *);
void findTotalScore(Student *);
float findAverage(Student);
void findLessThanTen(Student);

int main() {
    Student std;
    float avg;
    FILE *fp;

    fp = fopen("./lab11/no2/std10.dat","w");
    if (fp == NULL) {
        printf("Cannot create file\n");
        return 1;
    }

    for (int i = 0; i < STU_COUNT; i++) {
        printf("Student No.%d\n", i + 1);
        readStudentData(&std);
        fwrite(&std,sizeof(Student), 1, fp);
    }
    fclose(fp);

    fp = fopen("./lab11/no2/std10.dat","r");
    if (fp == NULL) {
        printf("Cannot read file\n");
        return 1;
    }

    while (fread(&std, sizeof(Student), 1, fp)) {
        findTotalScore(&std);

        avg = findAverage(std);
        printf("\n\nAverage score is %.2f", avg);

        findLessThanTen(std);
    }
    fclose(fp);
    return 0;
}

void readStudentData(Student *pStd) {
    int i;
    printf("Enter student data\n");

    printf("\tName : ");
    scanf("%s", pStd->name);
    printf("\tSurname : ");
    scanf("%s", pStd->surname);

    for (i = 0; i < NO_SCORE; i++) {
        printf("\tScore %d : ", i + 1);
        scanf("%d", &pStd->score[i]);
    }
}

void findTotalScore(Student *pStd) {
    int i;
    pStd->total = 0.0;
    printf("\nStudent: %s %s", pStd->name, pStd->surname);
    printf("\n\tScores: ");
    for (i = 0; i < NO_SCORE; i++) {
        printf("%4d", pStd->score[i]);
        pStd->total += pStd->score[i];
    }
    printf("\n\tTotal score is %.2f", pStd->total);
}

float findAverage(Student s) {
    return (s.total / NO_SCORE);
}

void findLessThanTen(Student s) {
    int i, count = 0;
    printf("\n\nScore less than 10");
    
    for (i = 0; i < NO_SCORE; i++) {
        if (s.score[i] < 10) {
            printf("\n\tTest no.%d - %d", i + 1, s.score[i]);
            count++;
        }
    }

    if (count == 0) {
        printf(" -> None");
    }
}