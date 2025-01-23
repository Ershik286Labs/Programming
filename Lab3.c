//Лабораторная работа №3
//Изучение базовых принципов организации процедур и функций
//
//
//Цель работы : освоить синтаксис построения процедур и функций, изучить способы передачи данных в подпрограммы, получить навыки организации минимального пользовательского интерфейса.
//
//Задание :
//    1. Реализовать программму вычисления площади фигуры, ограниченной кривой
//    1 * x ^ 3 + (2) * x ^ 2 + (4) * x + (12) и осью OX(в положительной части по оси OY).
//    2. Вычисление определенного интеграла должно выполняться численно, с применением метода средних прямоугольников.
//    3. Пределы интегрирования вводятся пользователем.
//    4. Взаимодействие с пользователем должно осуществляться посредством case-меню.
//    5. Требуется реализовать возможность оценки погрешности полученного результата.
//    6. Необходимо использовать процедуры и функции там, где это целесообразно.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <locale.h>

//глобальные переменные, работают во всех функциях
int number = 0;//выбор пункта меню

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
    "[1] Верхний предел",
    "[2] Нижний предел",
    "[3] Интегральный шаг",
    "[4] Расчет интеграла",
    "[5] Погрешность",
    "[6] Выход"
};

double function(double x) {
    return (x * x * x + 2 * x * x + 4 * x + 12);
}

double CalculatedIntegral(double integral) {
    double h = (UpLimits - LowLimits) / rectangles;  // Ширина отрезка
    double sum = 0.0;
    double mid;

    for (int i = 0; i < rectangles; i++) {
        mid = LowLimits + h * (i + 0.5);// середина отрезка
        if (function(mid) >= 0) {//только в положительной части по Oy
            sum += function(mid);
        }
    }
    integral = sum * h;
    return integral;
}

double primitive(int x) { //первообразная
    return x * x * x * x / 4 + 2 * x * x * x / 3 + 2 * x * x + 12 * x; // Первообразная для функции x^4/4 + 2x^3/3 + 2x^2 + 12x
}

double integrateNewtonLeibniz() {
    return (primitive(UpLimits) - primitive(LowLimits));//формула интеграла по Ньютону-Лейбницу
}

void Menu() {
    int k = 0;
    int k1 = 0;//отвечают за ввод переменных, k1 - верхний предел
    int k2 = 0;//k2 - нижний
    int k3 = 0;//k3 - Шаг
    int k4 = 0;//подсчет интеграла
    while (k == 0) {
        system("cls");//очистка консоли
        printf("Для управления используйте стрелки вверх/вниз\n");
        printf("\n");
        for (int i = 0; i < 6; i++) {//вывод массива с меню
            if (i == number) {//если дошли до выбранного пункта
                printf("=>");
            }
            else {
                printf("  ");//пробел для внешнего вида
            }
            printf("%s", menu[i]);//вывели элемент
            if (i == number) {
                printf("<=\n");//дошли до выбранного элемента
            }
            else {
                printf("\n");
            }
        }
        if (error1 == 1) {//перестановка предела
            printf("=======================\n");
            printf("Пределы были переставленны, так верхний предел меньше нижнего");
            error1 = 0;
        }
        if (error2 == 1) {//заход в расчет интеграла, если не было введено одно из значений
            printf("=======================\n");
            printf("Вы не можете посчитать интеграл, не были введенны все значения.");
            error2 = 0;
        }
        if (error3 == 1) {//меньше нулей функции, приравниваем нулям, надо только в положительной части по Oy
            printf("=======================\n");
            printf("Введенный предел меньше нулей функции, он был приравнен %.2f", Nul);
            error3 = 0;
        }
        if (error4 == 1) {
            printf("=======================\n");
            printf("Вы не можете посчитать погрешность, не был посчитан интеграл.");
            error4 = 0;
        }
        int key = getch();
        if (key == 72) {//стрелка вниз
            number--;
            system("cls");
            number = number > 5 ? 0 : number;//если number > 5, то number = 0, если нет: number = number; Краткое условие
            number = number < 0 ? 5 : number;//если number < 0, то number = 5, если нет: number = number; Краткое условие
            continue;
        }
        if (key == 80) {//стрелка вверх
            number++;
            system("cls");
            number = number > 5 ? 0 : number;//аналогично
            number = number < 0 ? 5 : number;
            continue;
        }
        if (key == 13) {//Enter
            if (number == 0) {//выбран первый пункт
                while (k1 == 0) {
                    system("cls");
                    printf("Введите верхний предел\n");
                    double UpLimitsCopy;//создаем копию для проверки на правильность ввода, нулей функции и отношения между другим пределом
                    if (scanf("%lf", &UpLimitsCopy) == 0) {
                        printf("Введенное значение не число\n");
                        printf("Попробуйте снова\n");
                        printf("\n");
                        printf("Для продолжения нажмите любую клавишу");
                        k4 = _getch();
                        // Очистка буфера ввода
                        while (getchar() != '\n');
                        continue;
                    }
                    if (UpLimitsCopy < Nul) {//Nul - нули функции в глобал переменных
                        UpLimitsCopy = Nul;
                        error3 = 1;
                    }
                    if (k2 == 1 && UpLimitsCopy < LowLimits) {//меняем местами
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
            if (number == 1) {//выбран второй пункт
                while (k2 == 0) {
                    system("cls");
                    printf("Введите нижний предел\n");
                    double LowLimitsCopy;
                    if (scanf("%lf", &LowLimitsCopy) == 0) {
                        printf("Введенное значение не число\n");
                        printf("Попробуйте снова\n");
                        printf("\n");
                        printf("Для продолжения нажмите любую клавишу");
                        k4 = _getch();
                        // Очистка буфера ввода
                        while (getchar() != '\n');
                        continue;
                    }
                    if (LowLimitsCopy < Nul) {
                        LowLimitsCopy = Nul;
                        error3 = 1;
                    }
                    if (k1 == 1 && LowLimitsCopy > UpLimits) {//меняем местами
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
                    printf("Введите Интегральный шаг\n");
                    int rectanglesCopy;
                    if (scanf("%d", &rectanglesCopy) == 0) {//если ввод не успешен (Введена буква), то от функции scanf подается 0, следовательно, ввод не правильный, просим пользователя повторить ввод
                        printf("Введенное значение не число\n");
                        printf("Попробуйте снова\n");
                        printf("\n");
                        printf("Для продолжения нажмите любую клавишу");
                        k4 = _getch();
                        // Очистка буфера ввода
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
                else { //нули функции -2.41
                    printf("Нули функции - %.2f\n", Nul);
                    integralNewLeib = integrateNewtonLeibniz();
                    integral = CalculatedIntegral(integral);
                    printf("Интеграл по Методу средних прямоугольников: %.2f\n", integral);
                    printf("Интеграл по Ньютону-Лейбницу: %.2f\n", integralNewLeib);
                    printf("\n");
                    printf("Для продолжения нажмите любую клавишу");
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
                printf("Абсолютная погрешность: %.2f\n", AbsolError);
                OtnError = AbsolError / (integralNewLeib / 100);
                printf("Относительная погрешность: %.2f%%\n", OtnError);
                printf("\n");
                printf("Для продолжения нажмите любую клавишу");
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