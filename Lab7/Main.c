#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <ctype.h> 

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
const char* list = "/list";
const char* clear = "/clear";

void Help() {
    printf("%s - показать все возможные команды\n", help);
    printf("%s - положить элемент в конец дека\n", pushBack);
    printf("%s - положить элемент в начало дека\n", pushFront);
    printf("%s - взять элемент в конце дека\n", popBack);
    printf("%s - взять элемент в начале дека\n", popFront);
    printf("%s - проверить наличие элемента в деке\n", isEmpty);
    printf("%s - очистить дек\n", clear);
}

int countHistoryCommand = 0;

void HistoryCommand(char* command[]) {
    if (countHistoryCommand < 40) {
        countHistoryCommand++;
    }
    for (int i = 0; i < countHistoryCommand; i++) {
        if (strcmp(command, MassiveHistoryCommand[i]) == 0) return; //command is empty in History
    }
    char tempMassive[40][100];
    for (int i = 0; i < countHistoryCommand; i++) {
        strcpy(tempMassive[i], MassiveHistoryCommand[i]);
    }
    strcpy(MassiveHistoryCommand[0], command);
    for (int i = 1; i < countHistoryCommand; i++) {
        strcpy(MassiveHistoryCommand[i], tempMassive[i - 1]);
    }
}

const int Tab = 9;
const int Enter = 13;
const int BackSpace = 8;

int choiseCommand = 0;

int AutoSubstitution(char* command, int count, int NumberCommand) {
    const char* newCommand;
    switch (NumberCommand) {
    case 0: newCommand = pushBack; break;
    case 1: newCommand = pushFront; break;
    case 2: newCommand = popBack; break;
    case 3: newCommand = popFront; break;
    case 4: newCommand = isEmpty; break;
    case 5: newCommand = help; break;
    case 6: newCommand = list; break;
    case 7: newCommand = clear; break;
    default: return 0;
    }
    int k1 = 0;
    int len = count < (int)strlen(newCommand) ? count : (int)strlen(newCommand);

    for (int i = 0; i < len; i++) {
        if (command[i] == newCommand[i]) k1++;
    }
    return k1;
}

void Input(int* len, struct Dek** dek) {
    //PrintMassive(*len, *dek);
    char command[100] = { "" };
    int count = 0;
    while (1) {
        //Print(*len, *dek, command);
        char k = getch();
        if ((int)k == keyUp) {
            for (int i = 0; i < count; i++) {
                printf("\b \b");
            }
            choiseCommand--;
            choiseCommand = choiseCommand < 0 ? 0 : choiseCommand;
            strcpy(command, MassiveHistoryCommand[choiseCommand]);
            count = strlen(command);
            for (int i = 0; i < count; i++) {
                printf("\b \b");
            }
            fflush(stdout);
            printf("%s", command);
            continue;
        }
        if ((int)k == keyDown) {
            for (int i = 0; i < count; i++) {
                printf("\b \b");
            }
            choiseCommand = (choiseCommand + 1) % 40;
            strcpy(command, MassiveHistoryCommand[choiseCommand]);
            count = strlen(command);
            for (int i = 0; i < count; i++) {
                printf("\b \b");
            }
            fflush(stdout);
            printf("%s", command);
            continue;
        }
        if ((int)k == BackSpace) {
            if (count > 0) {
                count--;
                command[count] = '\0';

                // Выводим backspace, пробел и снова backspace для удаления символа
                printf("\b \b");
                fflush(stdout); // Force output
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
            case 5: fullCommand = help; break;
            case 6: fullCommand = list; break;
            case 7: fullCommand = clear; break;
            default: fullCommand = ""; break;
            }
            strcpy(command, fullCommand);
            count = strlen(command);
            for (int i = 0; i < count; i++) {
                printf("\b \b");
                fflush(stdout);
            }
            printf("%s", command);
        }
        else if ((int)k == Enter) {
            printf("\n");
            if (strcmp(command, pushBack) == 0) {
                PushBack(len, dek);
            }
            else if (strcmp(command, pushFront) == 0) {
                PushFront(len, dek);
            }
            else if (strcmp(command, popBack) == 0) {
                PopBack(len, dek);
            }
            else if (strcmp(command, popFront) == 0) {
                PopFront(len, dek);
            }
            else if (strcmp(command, isEmpty) == 0) {
                IsEmpty(*len, *dek);
            }
            else if (strcmp(command, help) == 0) {
                Help();
            }
            else if (strcmp(command, clear) == 0) {
                Clear(*dek, len);
            }
            else if (strcmp(command, list) == 0) PrintMassive(*len, *dek);
            else {
                printf("Неизвестная команда\n\n");
                break;
            }
            HistoryCommand(command);
            break;
        }
        else if (count < maxLenCommand - 1) {
            command[count] = k;
            count++;
            printf("%c", k);
        }
    }
}

int main() {
    int len = 0;
    struct Dek* dek = (struct Dek*)malloc(len * sizeof(struct Dek));
    while (1)
        Input(&len, &dek);
    free(dek);
    return 0;
}
