#include "Dek.h"
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

//PushBack — добавление в конец очереди; 2
//PushFront — добавление в начало очереди; 2
//PopBack — выборка из конца очереди; 2
//PopFront — выборка из начала очереди; 2
//IsEmpty — проверка наличия элементов; 2
//Clear — очистка. 2
//Swap - перестановка
//replace - изменение значения 

const char* pushBack = "/pushBack";
const char* pushFront = "/pushFront";
const char* popBack = "/popBack";
const char* popFront = "/popFront";
const char* isEmpty = "/isEmpty";
const char* clear = "/clear";
const char* swap = "/swap";
const char* replace = "/replace";

const int CommandQuantity = 7;

int ChoiseIndex = 0;
int ChoiseFlag = 0;
int tempChoise = 0;

const int Tab = 9;
const int Enter = 13;
const int BackSpace = 8;

void Replace(struct Dek* dek, int ChoiseIndex, int* len) {
    int number;
    printf("Введите новое значение элемента стека: %d", &number);
    dek[ChoiseIndex].number = number;
}

void Swap(struct Dek* dek, int tempIndex, int ChoiseIndex) {
    int temp = dek[tempIndex].number;
    dek[tempIndex].number = dek[ChoiseIndex].number;
    dek[ChoiseIndex].number = temp;
    printf("элементы поменяны\n");
}

void PushBack(int* len, struct Dek** dek) {
    int number;
    printf("Введите число: ");
    scanf("%d", &number);

    struct Dek* tempMassive = (struct Dek*)malloc(*len * sizeof(struct Dek));
    for (int i = 0; i < *len; i++) {
        tempMassive[i] = (*dek)[i];
    }
    free(*dek);
    *dek = (struct Dek*)malloc((*len + 1) * sizeof(struct Dek));
    for (int i = 0; i < *len; i++) {
        (*dek)[i] = tempMassive[i];
    }
    (*dek)[*len].number = number;
    (*len)++;
    free(tempMassive);
}

void PushFront(int* len, struct Dek** dek) {
    int number;
    printf("Введите число: ");
    scanf("%d", &number);

    struct Dek* tempMassive = (struct Dek*)malloc(*len * sizeof(struct Dek));
    for (int i = 0; i < *len; i++) {
        tempMassive[i] = (*dek)[i];
    }
    free(*dek);
    *dek = (struct Dek*)malloc((*len + 1) * sizeof(struct Dek));
    (*dek)[0].number = number;
    for (int i = 0; i < *len; i++) {
        (*dek)[i + 1] = tempMassive[i];
    }
    (*len)++;
    free(tempMassive);
}

void PopBack(int len, struct Dek* dek) {
    ChoiseIndex = len - 1;
    if (ChoiseFlag == 0) {
        tempChoise = ChoiseIndex;
        ChoiseFlag = 1;
    }
    else {
        Swap(dek, tempChoise, ChoiseIndex);
    }
}

void PopFront(int len, struct Dek* dek) {
    ChoiseIndex = 0;
    if (ChoiseFlag == 0) {
        tempChoise = ChoiseIndex;
        ChoiseFlag = 1;
    }
    else {
        Swap(dek, tempChoise, ChoiseIndex);
    }
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

void Clear(int len, struct Dek* dek) {
    for (int i = 0; i < len; i++) {
        dek[i].number = 0;
    }
}

void PrintMassive(int len, struct Dek* dek) {
    printf("Содержимое дека:\n");
    for (int i = 0; i < len; i++) {
        printf("[%d] %d\n", i, dek[i].number);
    }
    printf("\n");
}