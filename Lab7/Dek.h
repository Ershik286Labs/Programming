#pragma once
#ifndef DEK_H
#define DEK_H

struct Dek {
    int number;
    int leftEnd;
    int rightEnd;
};

extern const char* help;
extern const char* pushBack;
extern const char* pushFront;
extern const char* popBack;
extern const char* popFront;
extern const char* isEmpty;
extern const char* clear;
extern const char* swap;
extern const char* replace;

// Объявления функций
void Clear(int* len, struct Dek** dek, int ChoiseIndex);
void Replace(struct Dek* dek, int ChoiseIndex, int* len);
void Swap(struct Dek* dek, int tempIndex, int ChoiseIndex);
void PushBack(int* len, struct Dek** dek);
void PushFront(int* len, struct Dek** dek);
void PopBack(int len, struct Dek* dek, int ChoiseIndex, int ChoiseFlag, int tempChoise);
void PopFront(int len, struct Dek* dek, int ChoiseIndex, int ChoiseFlag, int tempChoise);
void IsEmpty(int len, struct Dek* dek);
void PrintMassive(int len, struct Dek* dek);

#endif
