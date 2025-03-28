#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#include "Dek.h"

const int maxLenCommand = 100;
const int keyUp = 72;
const int keyDown = 80;

void Input(int* len, struct Dek** dek);

int ChoiseIndex;
int ChoiseFlag = 0;
int tempChoise;

char MassiveHistoryCommand[40][100];

const char* help = "/help";
const char* pushBack = "/pushBack";
const char* pushFront = "/pushFront";
const char* popBack = "/popBack";
const char* popFront = "/popFront";
const char* isEmpty = "/isEmpty";
const char* clear = "/clear";
const char* swap = "/swap";
const char* replace = "/replace";

void Help() {
    printf("%s - показать все возможные команды\n", help);
    printf("%s - положить элемент в конец дека\n", pushBack);
    printf("%s - положить элемент в начало дека\n", pushFront);
    printf("%s - взять элемент в конце дека\n", popBack);
    printf("%s - взять элемент в начале дека\n", popFront);
    printf("%s - проверить наличие элемента в деке\n", isEmpty);
    printf("%s - удалить выбранный элемент\n", clear);
    printf("%s - переставить элементы\n", swap);
    printf("%s - заменить значение элемента дека\n", replace);
}

int countHistoryCommand = 0;

void HistoryCommand(char* command[]) {
    countHistoryCommand = countHistoryCommand > 39 ? 0 : countHistoryCommand + 1;
    for (int i = 1; i < countHistoryCommand + 1; i++) {
        strcpy(MassiveHistoryCommand[i], MassiveHistoryCommand[i - 1]);
    }
    strcpy(MassiveHistoryCommand[0], command);
}

const int Tab = 9;
const int Enter = 13;
const int BackSpace = 8;

int choiseCommand = 0;

int AutoSubstitution(char* command, int count, int NumberCommand) {
    const char* Function;
    switch (NumberCommand) {
    case 0: Function = pushBack; break;
    case 1: Function = pushFront; break;
    case 2: Function = popBack; break;
    case 3: Function = popFront; break;
    case 4: Function = isEmpty; break;
    case 5: Function = clear; break;
    case 6: Function = swap; break;
    case 7: Function = help; break;
    default: return 0;
    }
    int k1 = 0;
    int len = count < (int)strlen(Function) ? count : (int)strlen(Function);

    for (int i = 0; i < len; i++) {
        if (command[i] == Function[i]) k1++;
    }
    return k1;
}

void Print(int len, struct Dek* dek, char command[]) {
    system("cls");
    PrintMassive(len, dek);
    printf("%s", command);
}

void Input(int* len, struct Dek** dek) {
    PrintMassive(*len, *dek);
    char command[100] = { "" };
    int count = 0;
    while (1) {
        Print(*len, *dek, command);
        char k = getch();
        if ((int)k == keyUp) {
            choiseCommand = (choiseCommand + 1) % 40;
            strcpy(command, MassiveHistoryCommand[choiseCommand]);
        }
        if ((int)k == keyDown) {
            choiseCommand--;
            choiseCommand = choiseCommand < 0 ? 0 : choiseCommand;
            strcpy(command, MassiveHistoryCommand[choiseCommand]);
        }
        if ((int)k == BackSpace) {
            if (count > 0) {
                count--;
                command[count] = '\0';
            }
        }
        else if ((int)k == Tab) {
            int massiveSubstitution[8];
            int max = 0;
            int maxIndex = 0;
            for (int i = 0; i < 8; i++) {
                massiveSubstitution[i] = AutoSubstitution(command, count, i);
                if (massiveSubstitution[i] > max) {
                    max = massiveSubstitution[i];
                    maxIndex = i;
                }
            }
            const char* fullCommand;
            switch (maxIndex) {
            case 0: fullCommand = pushBack; break;
            case 1: fullCommand = pushFront; break;
            case 2: fullCommand = popBack; break;
            case 3: fullCommand = popFront; break;
            case 4: fullCommand = isEmpty; break;
            case 5: fullCommand = clear; break;
            case 6: fullCommand = swap; break;
            case 7: fullCommand = help; break;
            default: fullCommand = ""; break;
            }
            strcpy(command, fullCommand);
            count = strlen(command);
        }
        else if ((int)k == Enter) {
            printf("\n");
            if (strcmp(command, pushBack) == 0) {
                HistoryCommand(command);
                PushBack(len, dek);
            }
            else if (strcmp(command, pushFront) == 0) {
                HistoryCommand(command);
                PushFront(len, dek);
            }
            else if (strcmp(command, popBack) == 0) {
                HistoryCommand(command);
                PopBack(*len, *dek, ChoiseIndex, ChoiseFlag, tempChoise);
            }
            else if (strcmp(command, popFront) == 0) {
                HistoryCommand(command);
                PopFront(*len, *dek, ChoiseIndex, ChoiseFlag, tempChoise);
            }
            else if (strcmp(command, isEmpty) == 0) {
                HistoryCommand(command);
                IsEmpty(*len, *dek);
            }
            else if (strcmp(command, clear) == 0) {
                HistoryCommand(command);
                Clear(len, dek, ChoiseIndex);
            }
            else if (strcmp(command, swap) == 0) {
                if (ChoiseFlag == 2) {
                    HistoryCommand(command);
                    Swap(*dek, tempChoise, ChoiseIndex);
                    ChoiseFlag = 0;
                }
                else {
                    printf("сначала выберите 2 элемента\n");
                }
            }
            else if (strcmp(command, replace) == 0) {
                if (ChoiseFlag == 1) {
                    HistoryCommand(command);
                    Replace(*dek, ChoiseIndex, *len);
                }
            }
            else if (strcmp(command, help) == 0) {
                printf("\n");
                Help();
            }
            else {
                printf("Неизвестная команда");
            }
            break;
        }
        else if (count < maxLenCommand - 1) {
            command[count] = k;
            count++;
            printf("%c", k);
        }
    }
    getchar(); // Очистка буфера ввода
}

int main() {
    int len = 0;
    struct Dek* dek = (struct Dek*)malloc(len * sizeof(struct Dek));
    while (1)
        Input(&len, &dek);
    free(dek);
    return 0;
}
