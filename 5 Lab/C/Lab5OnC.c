#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PrintItog(int massive[], int Len) {
    char CheckWays;
    char ItogWays[256] = "output.txt";
    printf("Считать итоговый путь с клавиатуры или подставить стандартный? [Y/N] \n");
    scanf(" %c", &CheckWays);
    if (CheckWays == 'Y' || CheckWays == 'y') {
        printf("Введите путь в формате C:/...\n");
        scanf("%s", &ItogWays);
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
            if (massive[j] < Min) {//компаратор
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

int getMax(int array[], int n) {
    int max = array[0];
    for (int i = 1; i < n; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

void countingSort(int array[], int n, int place, int offset) {
    int* output = (int*)malloc(n * sizeof(int));
    int count[10] = { 0 };

    // Calculate count of elements
    for (int i = 0; i < n; i++) {
        int index = ((array[i] + offset) / place) % 10;
        count[index]++;
    }
    // Calculate cumulative count
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    // Place the elements in sorted order
    for (int i = n - 1; i >= 0; i--) {
        int index = ((array[i] + offset) / place) % 10;
        output[count[index] - 1] = array[i];
        count[index]--;
    }
    // Copy the sorted elements into original array
    for (int i = 0; i < n; i++) {
        array[i] = output[i];
    }
    free(output);
}

void RadixSort(int array[], int n) {
    int maxElement = getMax(array, n);

    // Find minimum element to calculate offset
    int minElement = array[0];
    for (int i = 1; i < n; i++) {
        if (array[i] < minElement) {
            minElement = array[i];
        }
    }
    int offset = abs(minElement);

    // Apply counting sort to sort elements based on place value
    for (int place = 1; maxElement / place > 0; place *= 10) {
        countingSort(array, n, place, offset);
    }
}

int main() {
    char Ways[256] = "input.txt";//стандартный путь к файлу
    char CheckWays;

    printf("Считать путь с клавиатуры или подставить стандартный? [Y/N] \n");
    scanf(" %c", &CheckWays);
    if (CheckWays == 'Y' || CheckWays == 'y') {
        printf("Введите путь в формате C:/...\n");
        scanf("%s", &Ways);
    }
    FILE* file = fopen(Ways, "r");
    if (file != NULL) {
        int Len = 0;//счетчик чисел
        int temp;
        while (fscanf(file, "%d", &temp) == 1) {//функция, возвращает int значение, 
            Len++;
        }
        rewind(file);//переместились в начало
        int* massive = (int*)malloc(Len * sizeof(int));

        int k = 0;
        while (fscanf(file, "%d", &massive[k]) == 1) {
            k++;
        }

        fclose(file);
        while (1) {
            system("cls");
            printf("Выберите тип сортировки\n");
            printf("Для cортировки 'Выбором' нажмите S\n");
            printf("Для 'поразрядной по младшим' нажмите R\n");
            char Sort;
            scanf(" %c", &Sort);//считал букву
            if (Sort == 'S' || Sort == 's') {//
                SelectionSort(Len, massive);
                free(massive);
                return 0;
            }
            if (Sort == 'R' || Sort == 'r') {//
                RadixSort(massive, Len);
                PrintItog(massive, Len);
                free(massive);
                return 0;
            }
            //
        }
    }
    else {
        printf("Не удалось открыть файл\n");
        return 0;
    }
    //*
}
