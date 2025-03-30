#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "Dek.h"

const int CommandQuantity = 7;

void PushBack(int* len, struct Dek** dek) {
    int number;
    printf("Введите число: ");
    scanf("%d", &number);

    struct Dek* tempMassive = (struct Dek*)malloc(*(len) * sizeof(struct Dek));
    for (int i = 0; i < *len; i++) {
        tempMassive[i].number = (*dek)[i].number;
    }
    *dek = (struct Dek*)malloc((*len + 1) * sizeof(struct Dek));
    (*dek)[*len].number = number;
    (*dek)[*len].leftEnd = 0;
    (*dek)[*len].rightEnd = *len;
    for (int i = 0; i < *len; i++) {
        (*dek)[i].number = tempMassive[i].number;
        (*dek)[i].leftEnd = 0;
        (*dek)[i].rightEnd = *len - 1;
    }
    (*len)++;
    free(tempMassive);
}

void PushFront(int* len, struct Dek** dek) {
    int number;
    printf("Введите число: ");
    scanf("%d", &number);

    struct Dek* tempMassive = (struct Dek*)malloc(*len * sizeof(struct Dek));
    for (int i = 0; i < *len; i++) {
        tempMassive[i].number = (*dek)[i].number;
    }
    free(*dek);
    *dek = (struct Dek*)malloc((*len + 1) * sizeof(struct Dek));
    (*dek)[0].number = number;
    for (int i = 1; i < *len + 1; i++) {
        (*dek)[i].number = tempMassive[i - 1].number;
        (*dek)[i].leftEnd = 0;
        (*dek)[i].rightEnd = *len - 1;
    }
    (*len)++;
    free(tempMassive);
}

void PopBack(int* len, struct Dek* dek) {
    int size = *len - 1;

    struct Dek* tempMassive = (struct Dek*)malloc((*len) * sizeof(struct Dek));
    for (int i = 0; i < *len; i++) {
        tempMassive[i].number = (dek)[i].number;
    }
    //printf("%d", size);
    (*len)--;
    dek = (struct Dek*)malloc((*len) * sizeof(struct Dek));

    for (int i = 0; i < *len; i++) {
        (dek)[i].number = tempMassive[i].number;
        (dek)[i].leftEnd = 0;
        (dek)[i].rightEnd = *len - 1;
    }
    free(tempMassive);
}
void PopFront(int* len, struct Dek** dek) {
    int size = *len - 1;
    struct Dek* tempMassive = (struct Dek*)malloc((*len) * sizeof(struct Dek));
    for (int i = 0; i < *len; i++) {
        tempMassive[i].number = (*dek)[i].number;
    }
    (*len)--;
    struct Dek* newDek = (struct Dek*)malloc((*len) * sizeof(struct Dek));

    for (int i = 0; i < *len; i++) {
        newDek[i].number = tempMassive[i + 1].number;
        newDek[i].leftEnd = 0;
        newDek[i].rightEnd = *len - 1;
    }
    free(*dek);  // Освобождаем старую память, на которую указывал dek в вызывающем коде
    *dek = newDek; // Теперь dek указывает на новый массив
    free(tempMassive); // Освобождаем временный массив
}

void IsEmpty(int len, struct Dek* dek) {
    int number;
    printf("Введите число: ");
    scanf("%d", &number);
    for (int i = 0; i < len; i++) {
        if (dek[i].number == number) {
            printf("Выбранное число есть в структуре, его номер: %d\n", i);
            return;
        }
    }
    printf("Выбранного числа нет в структуре.\n");
}

void Clear(struct Dek** dek, int* len) {
    *len = 0;
    *dek = (struct Dek*)malloc((*len) * sizeof(struct Dek));
}

void PrintMassive(int len, struct Dek* dek) {
    printf("Содержимое дека:\n");
    for (int i = 0; i < len; i++) {
        printf("[%d] %d\n", i, dek[i].number);
    }
    printf("\n");
}
