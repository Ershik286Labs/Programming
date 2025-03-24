#define _CRT_SECURE_NO_WARNINGS

//Фамилия: Ершов
//Вариант : 14
//
//Лабораторная работа №6
//Реализация элементарных структур данных на основе динамической памяти
//
//
//Цель работы : изучение структуры и принципов организации программных модулей, закрепление навыков работы с динамической памятью, получение базовых навыков организации работы в режиме командной строки.
//
//Задание :
//	1. Написать программу для работы со структурой данных "Дек".
//	2. Структура данных должна быть реализована на основе динамической памяти.
//	3. Структура данных(поля и методы) должна быть описана в отдельном модуле.
//	4. Работа со структурой должна осуществляться в режиме командной строки(с реализацией автодополнения и истории команд).Предусмотреть наглядную визуализацию содержимого структуры.


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

const int Tab = 9;
const int Enter = 13;
const int BackSpace = 8;

char pushBack[9] = "/pushBack";
char pushFront[10] = "/pushFront";
char popBack[8] = "/popBack";
char popFront[9] = "/popFront";
char isEmpty[8] = "/isEmpty";
char clear[6] = "/clear";
char swap[5] = "/swap";

const int CommandQuantity = 7;

int ChoiseIndex = 0;
int ChoiseFlag = 0;
int tempChoise = 0;

void CommandCopy(char* Function, int NumberCommand) {
	switch (NumberCommand) {
	case 0:
		Function = (char*)malloc(strlen(pushBack) * sizeof(char));
		strcpy(Function, pushBack);
		break;
	case 1:
		Function = (char*)malloc(strlen(pushFront) * sizeof(char));
		strcpy(Function, pushFront);
		break;
	case 2:
		Function = (char*)malloc(strlen(popBack) * sizeof(char));
		strcpy(Function, popBack);
		break;
	case 3:
		Function = (char*)malloc(strlen(popFront) * sizeof(char));
		strcpy(Function, popFront);
		break;
	case 4:
		Function = (char*)malloc(strlen(isEmpty) * sizeof(char));
		strcpy(Function, isEmpty);
		break;
	case 5:
		Function = (char*)malloc(strlen(clear) * sizeof(char));
		strcpy(Function, clear);
		break;
	case 6:
		Function = (char*)malloc(strlen(swap) * sizeof(char));
		strcpy(Function, swap);
		break;
	}
}

int AutoSubstitution(char command[], int CountCommand, int NumberCommand) {
	int k1 = 0;
	char* Function = (char*)malloc(1 * sizeof(char)); // Локальная переменная, а не указатель
	CommandCopy(Function, NumberCommand);
	int strlen1 = strlen(command);
	int strlen2 = strlen(Function);
	int len = strlen2 < strlen1 ? strlen2 : strlen1;

	for (int i = 0; i < len; i++) {
		if (command[i] == Function[i]) k1++;
	}
	free(Function);
	return k1;
}

void Swap(struct Dek* dek, int tempIndex, int ChoiseIndex, int len) {
	int temp = dek[tempIndex].number;
	dek[tempIndex].number = dek[ChoiseIndex].number;
	dek[ChoiseIndex].number = temp;
}

void PushBack(int len, struct Dek* dek) {
	int number;
	printf("Введите число ");
	scanf("%d\n", &number);

	struct Dek* tempMassive = (struct Dek*)malloc(len * sizeof(struct Dek));
	for (int i = 0; i < len; i++) {
		tempMassive[i].number = dek[i].number;
	}
	dek = (struct Dek*)malloc(len + 1 * sizeof(struct Dek));
	for (int i = 0; i < len + 1; i++) {
		dek[i].number = tempMassive[i].number;
		*dek[i].leftEnd = 0;
		*dek[i].rightEnd = len;
	}
	dek[len].number = number;
	*dek[len].leftEnd = 0;
	*dek[len].rightEnd = len;
}

void PushFront(int len, struct Dek* dek) {
	int number;
	while (1) {
		if (scanf("%d\n", &number) == 1) break;
	}

	struct Dek* tempMassive = (struct Dek*)malloc(len * sizeof(struct Dek));
	for (int i = 0; i < len; i++) {
		tempMassive[i].number = dek[i].number;
	}
	dek = (struct Dek*)malloc(len + 1 * sizeof(struct Dek));
	dek[0].number = number;
	for (int i = 1; i < len + 1; i++) {
		dek[i].number = tempMassive[i].number;
		*dek[i].leftEnd = 0;
		*dek[i].rightEnd = len;
	}
}

void PopBack(int len, struct Dek* dek) {
	ChoiseIndex = len - 1;
	if (ChoiseFlag == 0) {
		tempChoise = ChoiseIndex;
		ChoiseFlag = 1;
	}
	else {
		Swap(dek, tempChoise, ChoiseIndex, len);
	}
}

void PopFront(int len, struct Dek* dek) {
	ChoiseIndex = 0;
	if (ChoiseFlag == 0) {
		ChoiseIndex = 0;
		ChoiseFlag = 1;
	}
	else {
		Swap(dek, tempChoise, ChoiseIndex, len);
	}
}

void IsEmpty(int len, struct Dek* dek) {
	int number;
	printf("Введите число");
	scanf("%d", &number);
	for (int i = 0; i < len; i++) {
		if (dek[i].number == number) {
			printf("Выбранное число есть в структуре, его номер: %d\n", i);
			return;
		}
	}
	printf("Выбранного числа нет в структуре. \n");
}

void Clear(int len, struct Dek* dek) {
	for (int i = 0; i < len; i++) {
		dek[i].number = 0;
	}
}

void PrintMassive(int len, struct Dek* dek) {
	for (int i = 0; i < len; i++) {
		printf("%d\n", dek[i].number);
	}
}

void Input(int len, struct Dek* dek, char command[]) {
	system("cls");
	PrintMassive(len, dek);
	int count = 0;
	while (1) {
		char k = getch();
		if ((int)k == BackSpace) {
			count--;
			if (count < 0) count = 0;
			command[count] = "";
			system("cls");
			PrintMassive(len, dek);
			for (int i = 0; i <= count; i++) {
				printf("%c", command[i]);
			}
		}
		else if ((int)k == Tab) {//autosubstitution
			int massiveSubstitution[7];
			int max = 0;
			int maxIndex = 0;
			for (int i = 0; i < 7; i++) {
				massiveSubstitution[i] = AutoSubstitution(command, count, i);
				if (massiveSubstitution[i] > max) max = massiveSubstitution[i]; maxIndex = i;
			}
			CommandCopy(command, maxIndex);
			system("cls");
			PrintMassive(len, dek);
			for (int i = 0; i <= count; i++) {
				printf("%c", command[i]);
			}
		}
		else if ((int)k == Enter) {//End Input
			if (strcmp(command, pushBack)) {
				PushBack(len, dek);
			}
			if (strcmp(command, pushFront)) {
				PushFront(len, dek);
			}
			if (strcmp(command, popBack)) {
				PopBack(len, dek);
			}
			if (strcmp(command, popFront)) {
				PopFront(len, dek);
			}
			if (strcmp(command, isEmpty)) {
				IsEmpty(len, dek);
			}
			if (strcmp(command, clear)) {
				Clear(len, dek);
			}
			break;
		}
		else if (count < maxLenCommand - 1){
			command[count] = k;
			printf("%c", k);
			count++;
		}
		else {
			printf("Команда слишком длинная.");
		}
		//printf("%d\n", (int)k);
	}
}
int main() {
	int len = 1;
	struct Dek* dek;
	dek = (struct Dek*)malloc(len * sizeof(struct Dek));//Start Massive
	char* command = (char*)malloc(1 * sizeof(char));
	dek[0].number = 0;
	dek[0].leftEnd = 0;
	dek[0].rightEnd = 0;
	while (1) {
		Input(len, dek, command);
	}
}