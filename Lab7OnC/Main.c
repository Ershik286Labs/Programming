#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

const int maxLenCommand = 100;

struct Dek {
    int number;
    int* leftEnd;
    int* rightEnd;
};

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

void Replace(struct Dek* dek, int ChoiseIndex, int *len) {
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
            int massiveSubstitution[7];
            int max = 0;
            int maxIndex = 0;
            for (int i = 0; i < 7; i++) {
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
                PushBack(len, dek);
            }
            else if (strcmp(command, pushFront) == 0) {
                PushFront(len, dek);
            }
            else if (strcmp(command, popBack) == 0) {
                PopBack(*len, *dek);
            }
            else if (strcmp(command, popFront) == 0) {
                PopFront(*len, *dek);
            }
            else if (strcmp(command, isEmpty) == 0) {
                IsEmpty(*len, *dek);
            }
            else if (strcmp(command, clear) == 0) {
                Clear(*len, *dek);
            }
            else if (strcmp(command, swap) == 0) {
                if (ChoiseFlag == 1) {
                    Swap(*dek, tempChoise, ChoiseIndex);
                    ChoiseFlag = 0;
                }
            }
            else if (strcmp(command, replace) == 0) {
                if (ChoiseFlag == 1) {
                    Replace(*dek, ChoiseIndex, *len);
                }
            }
            else {
                printf("Неизвестная команда\n");
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
    int len = 1;
    struct Dek* dek = (struct Dek*)malloc(len * sizeof(struct Dek));
    dek[0].number = 0;
    dek[0].leftEnd = NULL;
    dek[0].rightEnd = NULL;

    while (1) {
        Input(&len, &dek);
    }
    free(dek);
    return 0;
}