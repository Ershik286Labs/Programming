#pragma once

struct Dek {
    int number;
    int* leftEnd;
    int* rightEnd;
};

void Replace(struct Dek* dek, int ChoiseIndex, int* len);

void Swap(struct Dek* dek, int tempIndex, int ChoiseIndex);

void PushBack(int* len, struct Dek** dek);

void PushFront(int* len, struct Dek** dek);

void PopBack(int len, struct Dek* dek);

void PopFront(int len, struct Dek* dek);

void IsEmpty(int len, struct Dek* dek);

void Clear(int len, struct Dek* dek);

void PrintMassive(int len, struct Dek* dek);
