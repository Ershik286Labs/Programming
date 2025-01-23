struct stek {
 int num;
 int* nextNumber;
 char* sign;
};

int main() {
 setlocale(LC_ALL, "rus");
 int len;
 cout << "Введите длину последовательности" << endl;
 cin >> len;
 if (len <= 0) {
  cout << "Ошибка, длина должна быть больше или равна 1" << endl;
  return 0;
 }
 int Number1;
 cout << "Введите последовательность" << endl;
 cin >> Number1;//вводим первое число
 int k = 1;
 stek massive[1000];
 int number;
 char sign;
 massive[0].num = Number1;
 for (int i = 0; i < len; i++) {//счетчик для кол-ва вычислений структур

  cout << "Текущее число: " << massive[i].num << endl;
  massive[i].nextNumber = new int;
  cin >> number;
  *massive[i].nextNumber = number;
  k++;

  cout << "Следующее число: " << *massive[i].nextNumber << endl;
  massive[i].sign = new char;
  cin >> sign;
  *massive[i].sign = sign;
  k++;

  if (*massive[i].sign == '+') {
   *massive[i].nextNumber = massive[i].num + *massive[i].nextNumber;
  }
  if (*massive[i].sign == '-') {
   *massive[i].nextNumber = massive[i].num - *massive[i].nextNumber;
  }
  if (*massive[i].sign == '*') {
   *massive[i].nextNumber = massive[i].num * *massive[i].nextNumber;
  }
  if (*massive[i].sign == '/') {
   *massive[i].nextNumber = massive[i].num / *massive[i].nextNumber;
  }
  cout << "Номер выполнения: " << i << endl;
  cout << "Число которое передается дальше число: " << *massive[i].nextNumber << endl;
  massive[i + 1].num = *massive[i].nextNumber;
  if (k == len) {
   cout << "Итоговое значение: " << massive[i + 1].num;
   return 0;
  }
 }
}