#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PrintItog(int massive[], int Len) {
    char CheckWays;
    char ItogWays[256] = "Itog.txt";
    printf("Считать итоговый путь с клавиатуры или подставить стандартный? [Y/N] \n");
    scanf(" %c", &CheckWays);
    if (CheckWays == 'Y' || CheckWays == 'y') {
        printf("Введите путь в формате C:/...\n");
        scanf("%s", ItogWays);
    }
    FILE* ItogFile = fopen(ItogWays, "a");
    if (ItogFile != NULL) {
        for (int i = 0; i < Len; i++) {
            fprintf(ItogFile, "%d ", massive[i]);
        }
        fclose(ItogFile);
    }
    else {
        printf("Ошибка, не правильно введен итоговый путь!\n");
    }
}

void SelectionSort(int Len, int massive[]) {
    int Min, index;
    for (int i = 0; i < Len - 1; i++) {
        Min = massive[i];
        index = i;
        for (int j = i + 1; j < Len; j++) {
            if (massive[j] < Min) {
                Min = massive[j];
                index = j;
            }
        }
        if (Min < massive[i]) {
            massive[index] = massive[i];
            massive[i] = Min;
        }
    }
    PrintItog(massive, Len);
}

int GetMax(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > mx) { mx = arr[i]; }
    }
    return mx;
}

void CountSort(int massive[], int Len, int exp) {
    int* output = (int*)malloc(Len * sizeof(int));
    int i, count[10] = { 0 };
    int minValue = INT_MAX; // Ищем минимальное значение
    for (i = 0; i < Len; i++) {
        if (massive[i] < minValue) {
            minValue = massive[i];
        }
    }
    int offset = abs(minValue);  // Абсолютное значение минимума
    for (i = 0; i < Len; i++) { count[((massive[i] + offset) / exp) % 10]++;}
    for (i = 1; i < 10; i++) { count[i] += count[i - 1]; }
    for (i = Len - 1; i >= 0; i--) {
        output[count[((massive[i] + offset) / exp) % 10] - 1] = massive[i];
        count[((massive[i] + offset) / exp) % 10]--;
    }
    for (i = 0; i < Len; i++) { massive[i] = output[i]; }
    free(output);
}

void RadixSort(int massive[], int Len) {
    int m = GetMax(massive, Len);
    printf("1");
    for (int exp = 1; m / exp > 0; exp *= 10) {
        printf("2");
        CountSort(massive, Len, exp);
    }
    PrintItog(massive, Len);
}

int main() {
    char Ways[256] = "test.txt";
    char CheckWays;

    printf("Считать путь с клавиатуры или подставить стандартный? [Y/N] \n");
    scanf(" %c", &CheckWays);
    if (CheckWays == 'Y' || CheckWays == 'y') {
        printf("Введите путь в формате C:/...\n");
        scanf("%s", &Ways);
    }
    FILE* file = fopen(Ways, "r");
    if (file != NULL) {
        int Len = 0;
        int temp;
        while (fscanf(file, "%d", &temp) == 1) {
            Len++;
        }
        rewind(file);
        int* massive = (int*)malloc(Len * sizeof(int));

        int k = 0;
        while (fscanf(file, "%d", &massive[k]) == 1) {
            k++;
        }

        fclose(file);
        while (1) {
            printf("Выберите тип сортировки\n");
            printf("Для cортировки 'Выбором' нажмите S\n");
            printf("Для 'поразрядной по младшим' нажмите R\n");
            char Sort;
            scanf(" %c", &Sort);
            if (Sort == 'S' || Sort == 's') {
                SelectionSort(Len, massive);
                free(massive);
                return 0;
            }
            if (Sort == 'R' || Sort == 'r') {
                RadixSort(massive, Len);
                free(massive);
                return 0;
            }
        }
    }
    else {
        printf("Не удалось открыть файл\n");
        return 0;
    }
}
