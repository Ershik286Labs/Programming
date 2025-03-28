#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "Dek.h"

const int CommandQuantity = 7;

void Clear(int* len, struct Dek** dek, int ChoiseIndex) {
    int size = *len - 1;

    struct Dek* tempMassive = (struct Dek*)malloc((*len) * sizeof(struct Dek));
    if (ChoiseIndex == 0) { // Choise start element
        for (int i = 0; i < *len; i++) {
            tempMassive[i].number = (*dek)[i].number;
        }
        (*len)--; // Decrement len *before* reallocation
        if (*len > 0) { // Only reallocate if len > 0, otherwise you'll malloc(0)
            struct Dek* newDek = (struct Dek*)malloc((*len) * sizeof(struct Dek));
            for (int i = 0; i < *len; i++) { //Changed from *len -1 to *len
                newDek[i].number = tempMassive[i + 1].number;
                newDek[i].leftEnd = 0;
                newDek[i].rightEnd = *len - 1;
            }
            free(*dek); // Free the *old* dek before reassigning
            *dek = newDek;
        }
        else {
            free(*dek);
        }

    }
    else if (ChoiseIndex == (*len - 1)) { // Choise end element
        for (int i = 0; i < *len; i++) {
            tempMassive[i].number = (*dek)[i].number;
        }
        printf("%d", size);
        (*len)--; // Decrement len *before* reallocation
        *dek = (struct Dek*)malloc((*len) * sizeof(struct Dek));

        for (int i = 0; i < *len; i++) {
            (*dek)[i].number = tempMassive[i].number;
            (*dek)[i].leftEnd = 0;
            (*dek)[i].rightEnd = *len - 1;
        }
    }
    free(tempMassive);
}

void Replace(struct Dek* dek, int ChoiseIndex, int* len) {
    int number;
    printf("Введите новое значение элемента стека: %d", &number);
    dek[ChoiseIndex].number = number;
}

void Swap(struct Dek* dek, int tempIndex, int ChoiseIndex) {
    int temp = dek[tempIndex].number;
    dek[tempIndex].number = dek[ChoiseIndex].number;
    dek[ChoiseIndex].number = temp;
    printf("Элементы поменяны\n");
}

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

void PopBack(int len, struct Dek* dek, int ChoiseIndex, int ChoiseFlag, int tempChoise) {
    ChoiseIndex = len - 1;
    if (ChoiseFlag == 0) {
        tempChoise = ChoiseIndex;
        ChoiseFlag = 1;
    }
    else if (ChoiseFlag == 1) ChoiseFlag = 2;
    printf("%d, %d", ChoiseIndex, ChoiseFlag);
}

void PopFront(int len, struct Dek* dek, int ChoiseIndex, int ChoiseFlag, int tempChoise) {
    ChoiseIndex = 0;
    if (ChoiseFlag == 0) {
        tempChoise = ChoiseIndex;
        ChoiseFlag = 1;
    }
    else if (ChoiseFlag == 1) ChoiseFlag = 2;
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

void PrintMassive(int len, struct Dek* dek) {
    printf("Содержимое дека:\n");
    for (int i = 0; i < len; i++) {
        printf("[%d] %d\n", i, dek[i].number);
    }
    printf("\n");
}
