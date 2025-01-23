//������������ ������ �3
//�������� ������� ��������� ����������� �������� � �������
//
//
//���� ������ : ������� ��������� ���������� �������� � �������, ������� ������� �������� ������ � ������������, �������� ������ ����������� ������������ ����������������� ����������.
//
//������� :
//    1. ����������� ���������� ���������� ������� ������, ������������ ������
//    1 * x ^ 3 + (2) * x ^ 2 + (4) * x + (12) � ���� OX(� ������������� ����� �� ��� OY).
//    2. ���������� ������������� ��������� ������ ����������� ��������, � ����������� ������ ������� ���������������.
//    3. ������� �������������� �������� �������������.
//    4. �������������� � ������������� ������ �������������� ����������� case-����.
//    5. ��������� ����������� ����������� ������ ����������� ����������� ����������.
//    6. ���������� ������������ ��������� � ������� ���, ��� ��� �������������.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <locale.h>

//���������� ����������, �������� �� ���� ��������
int number = 0;//����� ������ ����

double UpLimits = 0;
double LowLimits = 0;
int rectangles = 0;

int error1 = 0;
int error2 = 0;
int error3 = 0;
int error4 = 0;
double Nul = -2.41;
double integralNewLeib = 0.0;
double integral = 0.0;

double AbsolError = 0.0;
double OtnError = 0.0;

char* menu[6] = {
    "[1] ������� ������",
    "[2] ������ ������",
    "[3] ������������ ���",
    "[4] ������ ���������",
    "[5] �����������",
    "[6] �����"
};

double function(double x) {
    return (x * x * x + 2 * x * x + 4 * x + 12);
}

double CalculatedIntegral(double integral) {
    double h = (UpLimits - LowLimits) / rectangles;  // ������ �������
    double sum = 0.0;
    double mid;

    for (int i = 0; i < rectangles; i++) {
        mid = LowLimits + h * (i + 0.5);// �������� �������
        if (function(mid) >= 0) {//������ � ������������� ����� �� Oy
            sum += function(mid);
        }
    }
    integral = sum * h;
    return integral;
}

double primitive(int x) { //�������������
    return x * x * x * x / 4 + 2 * x * x * x / 3 + 2 * x * x + 12 * x; // ������������� ��� ������� x^4/4 + 2x^3/3 + 2x^2 + 12x
}

double integrateNewtonLeibniz() {
    return (primitive(UpLimits) - primitive(LowLimits));//������� ��������� �� �������-��������
}

void Menu() {
    int k = 0;
    int k1 = 0;//�������� �� ���� ����������, k1 - ������� ������
    int k2 = 0;//k2 - ������
    int k3 = 0;//k3 - ���
    int k4 = 0;//������� ���������
    while (k == 0) {
        system("cls");//������� �������
        printf("��� ���������� ����������� ������� �����/����\n");
        printf("\n");
        for (int i = 0; i < 6; i++) {//����� ������� � ����
            if (i == number) {//���� ����� �� ���������� ������
                printf("=>");
            }
            else {
                printf("  ");//������ ��� �������� ����
            }
            printf("%s", menu[i]);//������ �������
            if (i == number) {
                printf("<=\n");//����� �� ���������� ��������
            }
            else {
                printf("\n");
            }
        }
        if (error1 == 1) {//������������ �������
            printf("=======================\n");
            printf("������� ���� �������������, ��� ������� ������ ������ �������");
            error1 = 0;
        }
        if (error2 == 1) {//����� � ������ ���������, ���� �� ���� ������� ���� �� ��������
            printf("=======================\n");
            printf("�� �� ������ ��������� ��������, �� ���� �������� ��� ��������.");
            error2 = 0;
        }
        if (error3 == 1) {//������ ����� �������, ������������ �����, ���� ������ � ������������� ����� �� Oy
            printf("=======================\n");
            printf("��������� ������ ������ ����� �������, �� ��� ��������� %.2f", Nul);
            error3 = 0;
        }
        if (error4 == 1) {
            printf("=======================\n");
            printf("�� �� ������ ��������� �����������, �� ��� �������� ��������.");
            error4 = 0;
        }
        int key = getch();
        if (key == 72) {//������� ����
            number--;
            system("cls");
            number = number > 5 ? 0 : number;//���� number > 5, �� number = 0, ���� ���: number = number; ������� �������
            number = number < 0 ? 5 : number;//���� number < 0, �� number = 5, ���� ���: number = number; ������� �������
            continue;
        }
        if (key == 80) {//������� �����
            number++;
            system("cls");
            number = number > 5 ? 0 : number;//����������
            number = number < 0 ? 5 : number;
            continue;
        }
        if (key == 13) {//Enter
            if (number == 0) {//������ ������ �����
                while (k1 == 0) {
                    system("cls");
                    printf("������� ������� ������\n");
                    double UpLimitsCopy;//������� ����� ��� �������� �� ������������ �����, ����� ������� � ��������� ����� ������ ��������
                    if (scanf("%lf", &UpLimitsCopy) == 0) {
                        printf("��������� �������� �� �����\n");
                        printf("���������� �����\n");
                        printf("\n");
                        printf("��� ����������� ������� ����� �������");
                        k4 = _getch();
                        // ������� ������ �����
                        while (getchar() != '\n');
                        continue;
                    }
                    if (UpLimitsCopy < Nul) {//Nul - ���� ������� � ������ ����������
                        UpLimitsCopy = Nul;
                        error3 = 1;
                    }
                    if (k2 == 1 && UpLimitsCopy < LowLimits) {//������ �������
                        UpLimits = LowLimits;
                        LowLimits = UpLimitsCopy;
                        error1 = 1;
                        k1 = 1;
                        break;
                    }
                    UpLimits = UpLimitsCopy;
                    k1 = 1;
                }
            }
            if (number == 1) {//������ ������ �����
                while (k2 == 0) {
                    system("cls");
                    printf("������� ������ ������\n");
                    double LowLimitsCopy;
                    if (scanf("%lf", &LowLimitsCopy) == 0) {
                        printf("��������� �������� �� �����\n");
                        printf("���������� �����\n");
                        printf("\n");
                        printf("��� ����������� ������� ����� �������");
                        k4 = _getch();
                        // ������� ������ �����
                        while (getchar() != '\n');
                        continue;
                    }
                    if (LowLimitsCopy < Nul) {
                        LowLimitsCopy = Nul;
                        error3 = 1;
                    }
                    if (k1 == 1 && LowLimitsCopy > UpLimits) {//������ �������
                        LowLimits = UpLimits;
                        LowLimits = UpLimits;
                        error1 = 1;
                        k2 = 1;
                        break;
                    }
                    LowLimits = LowLimitsCopy;
                    k2 = 1;
                }
            }
            if (number == 2) {
                while (k3 == 0) {
                    system("cls");
                    printf("������� ������������ ���\n");
                    int rectanglesCopy;
                    if (scanf("%d", &rectanglesCopy) == 0) {//���� ���� �� ������� (������� �����), �� �� ������� scanf �������� 0, �������������, ���� �� ����������, ������ ������������ ��������� ����
                        printf("��������� �������� �� �����\n");
                        printf("���������� �����\n");
                        printf("\n");
                        printf("��� ����������� ������� ����� �������");
                        k4 = _getch();
                        // ������� ������ �����
                        while (getchar() != '\n');
                        continue;
                    }
                    rectangles = rectanglesCopy;
                    k3 = 1;
                }
            }
            if (number == 3) {
                k4 = 0;
                if (k1 != 1 || k2 != 1 || k3 != 1) {
                    error2 = 1;
                    continue;
                }
                else { //���� ������� -2.41
                    printf("���� ������� - %.2f\n", Nul);
                    integralNewLeib = integrateNewtonLeibniz();
                    integral = CalculatedIntegral(integral);
                    printf("�������� �� ������ ������� ���������������: %.2f\n", integral);
                    printf("�������� �� �������-��������: %.2f\n", integralNewLeib);
                    printf("\n");
                    printf("��� ����������� ������� ����� �������");
                    k4 = _getch();
                    k4 = 1;
                }
            }
            if (number == 4) {
                if (k4 == 0) {
                    error4 = 0;
                    continue;
                }
                AbsolError = fabs(integral - integralNewLeib);
                printf("���������� �����������: %.2f\n", AbsolError);
                OtnError = AbsolError / (integralNewLeib / 100);
                printf("������������� �����������: %.2f%%\n", OtnError);
                printf("\n");
                printf("��� ����������� ������� ����� �������");
                int k5 = getch();
            }
            if (number == 5) {
                break;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    Menu();
}