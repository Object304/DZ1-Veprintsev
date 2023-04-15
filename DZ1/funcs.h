#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <time.h>
#include <chrono>
#include <fstream>
#include <stdio.h>
#include <string>

void Heapify(int* ar, int n, int i);
void Merge(int* ar, int l, int m, int r);
int ModifiedPartition(int* ar, int low, int high);
int Partition(int* ar, int first, int last);
int GetMax(int* ar, int size);

void InsertionSort(int* ar, int left, int right);
void TimSort(int* ar, int len);
void BubbleSort(int* ar, int len);
void ModifiedQuicksort(int* ar, int low, int high);
void QuickSort(int* ar, int last, int first);
void SelectionSort(int* ar, int size);
void CountingSort(int* ar, int len);
void MergeSort(int* ar, int right, int left);
void ShellSort(int* ar, int len);
void GnomeSort(int* ar, int len);
void HeapSort(int* ar, int len);

int GetRandomNumber(int min, int max);
void ResAdd(int Time, int len, int x, int y);
void OutputData(FILE*& fLog);
void MashUp(int* ar, int len);
void Check(int* ar, int len);
void Sort(int index, int* ar, int len);
void ResMake();
void ResToFile();
void Test();