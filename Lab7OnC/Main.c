#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

const int maxLenCommand = 100;

const int keyUp = 72;
const int keyDown = 80;

struct Dek {
    int number;
    int* leftEnd;
    int* rightEnd;
};

char MassiveHistoryCommand[40][100];

int countHistoryCommand = 0;

void HistoryCommand (char* command[]) {
    countHistoryCommand = countHistoryCommand > 39 ? 0 : countHistoryCommand + 1;
    for (int i = 1; i < countHistoryCommand + 1; i++) {
        strcpy(MassiveHistoryCommand[i], MassiveHistoryCommand[i - 1]);
    }
    strcpy(MassiveHistoryCommand[0], command);
}

//PushBack — добавление в конец очереди; 2
//PushFront — добавление в начало очереди; 2
//PopBack — выборка из конца очереди; 2
//PopFront — выборка из начала очереди; 2
//IsEmpty — проверка наличия элементов; 2
//Clear — очистка. 2
//Swap - перестановка
//replace - изменение значения 

const char* help = "/help";
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

int choiseCommand = 0;

void clear(int* len, struct Dek** dek) {
    struct Dek* tempMassive = (struct Dek*)malloc((*len - 1) * sizeof(struct Dek));
    if (ChoiseIndex == 0) { //Choise start element
        for (int i = 0; i < *len - 1; i++) {
            (*dek)[i].number = (*dek)[i + 1].number;
            tempMassive[i].number = (*dek)[i].number;
        }
        *len = *len - 1;
        *dek = (struct Dek*)malloc((*len) * sizeof(struct Dek));
        for (int i = 0; i < *len - 1; i++) {
            (*dek)[i].number = tempMassive[i].number;
            (*dek)[i].leftEnd = 0;
            (*dek)[i].rightEnd = *len - 1;
        }
    }
    if (ChoiseIndex == len - 1) { //Choise end element
        for (int i = 0; i < *len - 1; i++) {
            tempMassive[i].number = (*dek)[i].number;
        }
        *len = *len - 1;
        *dek = (struct Dek*)malloc((*len) * sizeof(struct Dek));
        for (int i = 0; i < *len - 1; i++) {
            (*dek)[i].number = tempMassive[i].number;
            (*dek)[i].leftEnd = 0;
            (*dek)[i].rightEnd = *len - 1;
        }
    }
}

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

void Replace(struct Dek* dek, int ChoiseIndex, int *len) {
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
    //free(*dek);
    *dek = (struct Dek*)malloc((*len + 1) * sizeof(struct Dek));
    for (int i = 0; i < *len; i++) {
        (*dek)[i].number = tempMassive[i].number;
    }
    (*dek)[*len].number = number;
    //printf(" введенное число: / %d, %d\n", (*dek)[*len].number, *len);
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
    if (ChoiseFlag == 1) ChoiseFlag = 2;
}

void PopFront(int len, struct Dek* dek) {
    ChoiseIndex = 0;
    if (ChoiseFlag == 0) {
        tempChoise = ChoiseIndex;
        ChoiseFlag = 1;
    }
    if (ChoiseFlag == 1) ChoiseFlag = 2;
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

void Input(int* len, struct Dek** dek) {
    system("cls");
    PrintMassive(*len, *dek);

    char command[100] = { "" };
    int count = 0;

    //printf("Введите команду: ");
    while (1) {
        char k = getch();
        //printf("%d", (int)k);
        if ((int)k == keyUp) {
            system("cls");
            choiseCommand = (choiseCommand + 1) % 40;
            strcpy(command, MassiveHistoryCommand[choiseCommand]);
            PrintMassive(*len, *dek);
            printf("%s", command);
        }
        if ((int)k == keyDown) {
            system("cls");
            choiseCommand--;
            choiseCommand = choiseCommand < 0 ? 0 : choiseCommand;
            strcpy(command, MassiveHistoryCommand[choiseCommand]);
            PrintMassive(*len, *dek);
            printf("%s", command);
        }

        if ((int)k == BackSpace) {
            if (count > 0) {
                count--;
                command[count] = '\0';
                system("cls");
                PrintMassive(*len, *dek);
                printf("%s", command);
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
            system("cls");
            PrintMassive(*len, *dek);
            printf("%s", command);
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
                PopBack(*len, *dek);
            }
            else if (strcmp(command, popFront) == 0) {
                HistoryCommand(command);
                PopFront(*len, *dek);
            }
            else if (strcmp(command, isEmpty) == 0) {
                HistoryCommand(command);
                IsEmpty(*len, *dek);
            }
            else if (strcmp(command, clear) == 0) {
                HistoryCommand(command);
                Clear(*len, *dek);
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
                PrintMassive(*len, *dek);
                //printf("%s", command);
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
    struct Dek* dek = (struct Dek*)malloc( len * sizeof(struct Dek));

    while (1) {
        Input(&len, &dek);
    }
    free(dek);
    return 0;
}
