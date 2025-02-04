#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//сортировка выбором
void SelectionSort(int Len, int massive[]) {
	int Min = massive[0];
	int index;
	for (int i = 0; i < Len - 1; i++) {//Сортировка выбором
		Min = massive[i];
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
	char CheckWays;
	string ItogWays = "Itog.txt";
	cout << "Считать итоговый путь с клавиатуры или подставить стандартный? [Y/N] " << endl;
	cin >> CheckWays;
	if (CheckWays == 'Y' || CheckWays == 'y') {
		cout << "Введите путь в формате C:/..." << endl;
		cin >> ItogWays;
	}
	fstream ItogFile(ItogWays, ios::out | ios::app);
	if (ItogFile.is_open()) {

		for (int i = 0; i < Len; i++) {
			string text = to_string(massive[i]); // Преобразуем число в строку
			ItogFile << text;                   // Записываем строку в файл
			ItogFile << " ";
		}
		ItogFile.close(); // Закрываем файл
	}
	else {
		cout << "Ошибка, не правильно введен итоговый путь!" << endl;
	}
}

int GetMax(int arr[], int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > mx) { mx = arr[i]; }
	}
	return mx;
}

void CountSort(int massive[], int Len, int exp){
	int* output = new int [Len];
	int i, count[10] = { 0 };
	for (i = 0; i < Len; i++) { count[(massive[i] / exp) % 10]++; }

	for (i = 1; i < 10; i++) { count[i] += count[i - 1]; }

	for (i = Len - 1; i >= 0; i--) {
		output[count[(massive[i] / exp) % 10] - 1] = massive[i];
		count[(massive[i] / exp) % 10]--;
	}
	for (i = 0; i < Len; i++) { massive[i] = output[i]; }
}

void Radixsort(int massive[], int Len){
	int m = GetMax(massive, Len);
	for (int exp = 1; m / exp > 0; exp *= 10) { 
		CountSort(massive, Len, exp);
	}

	char CheckWays;
	string ItogWays = "Itog.txt";
	cout << "Считать итоговый путь с клавиатуры или подставить стандартный? [Y/N] " << endl;
	cin >> CheckWays;
	if (CheckWays == 'Y' || CheckWays == 'y') {
		cout << "Введите путь в формате C:/..." << endl;
		cin >> ItogWays;
	}
	fstream ItogFile(ItogWays, ios::out | ios::app);
	if (ItogFile.is_open()) {

		for (int i = 0; i < Len; i++) {
			string text = to_string(massive[i]); // Преобразуем число в строку
			ItogFile << text;                   // Записываем строку в файл
			ItogFile << " ";
		}
		ItogFile.close(); // Закрываем файл
	}
	else {
		cout << "Ошибка, не правильно введен итоговый путь!" << endl;
	}
}


int main(){
	string Ways = "test.txt";
	char CheckWays;

	cout << "Считать путь с клавиатуры или подставить стандартный? [Y/N] " << endl;
	cin >> CheckWays;
	if (CheckWays == 'Y' || CheckWays == 'y') {
		cout << "Введите путь в формате C:/..." << endl;
		cin >> Ways;
	}
	fstream file(Ways, ios::in | ios::out);
	if (file.is_open()) {

		int Len = 0;
		int temp;
		while (file >> temp){
			Len++;
		}
		cout << Len << endl;
		file.clear(); // Очищаем флаги ошибок, чтобы можно было читать снова
		file.seekg(0, ios::beg); // Перемещаем указатель в начало
		int* massive = new int[Len];//создаем динамический массив с длиной равной количеству элеметов

		int k = 0;
		while (file >> massive[k]) {
			k++;
		}

		file.close();
		while (true) {
			cout << "Выберите тип сортировки" << endl;
			cout << "Для cортировки 'Выбором' нажмите S" << endl;
			cout << "Для 'поразрядной по младшим' нажмите R" << endl;
			char Sort;
			cin >> Sort;
			if (Sort == 'S' || Sort == 's') {
				SelectionSort(Len, massive);
				return 0;
			}
			if (Sort == 'R' || Sort == 'r') {
				Radixsort(massive, Len);
				return 0;
			}
		}
	}
	else {
		cout << "Не удалось открыть файл" << endl;
		return 0;
	}
}