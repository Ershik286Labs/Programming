#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

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

void CompareSelection(int* a, int b, int* index, int j) {
    if (*a > b) {
        *a = b;
        *index = j;
    }
}

void Swap(int Extremum, int i, int index, int massive[]) {
    if (massive[i] > Extremum) {
        int temp = massive[i];
        massive[i] = Extremum;
        massive[index] = temp;
    }
}

void SelectionSort(int Len, int massive[], void CompareSelection(int*, int, int*, int)) {
    int Extremum, index;
    for (int i = 0; i < Len - 1; i++) {
        Extremum = massive[i];
        index = i;
        for (int j = i + 1; j < Len; j++) {
            CompareSelection(&Extremum, massive[j], &index, j);
        }
        Swap(Extremum, i, index, massive);
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

void CompareRadix(int count[]) {
    for (int i = 1; i < 10; i++) { count[i] += count[i - 1]; } //это для возрастания
    //for (int i = 8; i >= 0; i--) { count[i] += count[i + 1]; }//компаратор тут, он неявный у поразрядной сортировки, это для убывания
}

void CountSort(int massive[], int Len, int exp) {
    int* output = (int*)malloc(Len * sizeof(int));
    int i, count[10] = { 0 };
    int minValue = massive[0]; // Ищем минимальное значение
    for (i = 0; i < Len; i++) {
        if (massive[i] < minValue) {
            minValue = massive[i];
        }
    }
    int offset = abs(minValue);  // Абсолютное значение минимума
    for (i = 0; i < Len; i++) { count[((massive[i] + offset) / exp) % 10]++;}
    CompareRadix(count);
    for (i = Len - 1; i >= 0; i--) {
        output[count[((massive[i] + offset) / exp) % 10] - 1] = massive[i];
        count[((massive[i] + offset) / exp) % 10]--;
    }
    for (i = 0; i < Len; i++) { massive[i] = output[i]; }
    free(output);
}

void RadixSort(int massive[], int Len) {
    int m = GetMax(massive, Len);
    for (int exp = 1; m / exp > 0; exp *= 10) {
        CountSort(massive, Len, exp);
    }
    PrintItog(massive, Len);
}

int main() {
    char Ways[256] = "testMillion.txt";//стандартный путь к файлу
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
        fscanf(file, "%d", &Len);
        //while (fscanf(file, "%d", &temp) == 1) {//функция, возвращает int значение, 
        //    Len++;
        //}
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
            scanf(" %c", &Sort);
            if (Sort == 'S' || Sort == 's') {
                SelectionSort(Len, massive, CompareSelection);
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
