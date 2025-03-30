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
extern const char* list;

// Объявления функций
void PushBack(int* len, struct Dek** dek);
void PushFront(int* len, struct Dek** dek);
void PopBack(int* len, struct Dek* dek);
void PopFront(int* len, struct Dek** dek);
void IsEmpty(int len, struct Dek* dek);
void PrintMassive(int len, struct Dek* dek);
void Clear(struct Dek** dek, int* len);

#endif
