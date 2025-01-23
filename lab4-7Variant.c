#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct stek {
    int index;
    int number;
    int next_index;
    int next_number;
};

void calc(int len, int massive[]) {
    struct stek results[1000];

    for (int i = 0; i < len; i++) { //��������� ����� ������ ��������
        results[i].index = i;
        results[i].number = massive[i];
        if (i == len - 1) { //��������� �������
            results[i].next_index = i;
            results[i].next_number = results[i].number;
            break;
        }
        results[i].next_index = i + 1;//���������� ��������� ������
        results[i].next_number = massive[i + 1];
    }

    for (int i = 0; i < len; i++) {
        int max_index = -1;//������, �� ��������
        int max_number = results[i].number;

        for (int j = i; j < len - 1; j++) {
            if (max_number < results[j].number) {
                printf("���� ������ �������� %d ", j);
                max_index = results[j].index;
                printf("������� ����� �������� %d � ���������� max_index \n", j);
                printf("\n");
                break;
            }
            if (max_number < results[j].next_number) {
                printf("���� ������ �������� %d ", j + 1);
                max_index = results[j].next_index;
                printf("������� ����� �������� %d � ���������� max_index \n", j + 1);
                printf("\n");
                break;
            }
        }
        printf("��������� ��������� �������: ");
        if (max_index == -1) {
            printf(" �� ������\n");
        }
        else {
            printf("%d\n", max_index);
        }
        printf("====================================\n");
        printf("\n");
    }
}

int main() {
    setlocale(LC_ALL, "rus");

    int len;
    int massive[1000];

    printf("������� ����� ������� ");
    scanf("%d", &len);

    printf("������� �������� �������: ");
    for (int i = 0; i < len; i++) {
        scanf("%d", &massive[i]);
    }

    calc(len, massive);

    return 0;
}