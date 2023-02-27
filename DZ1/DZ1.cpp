#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <time.h>
#include <chrono>
#include <fstream>
#include <stdio.h>

using namespace std;

const int M = 10000000;
bool filewriting = false;
FILE* fLog;

int Partition(int a[], int first, int last) {
	int pivot = a[(first + last) / 2];
	int i = first, j = last;
	while (true) {
		while (a[i] < pivot)
			i++;
		while (a[j] > pivot)
			j--;
		if (i >= j)
			break;
		swap(a[i], a[j]);
		i++;
		j--;
	}
	return j;
}

int GetMax(int* ar, int size) {
	int max = 0;
	int i = 1;
	while (i < size) {
		if (ar[max] < ar[i])
			max = i;
		i++;
	}
	return max;
}

void InsertionSort(int ar[], int len) {
	for (int i = 1; i < len; i++)
		for (int j = i; j > 0; j--)
			if (ar[j] < ar[j - 1])
				swap(ar[j], ar[j - 1]);
}

void BubbleSort(int* ar, int len) {
	for (int k = len - 1; k > 0; k--) {
		for (int i = 0; i < k; i++) {
			if (ar[i] > ar[i + 1]) {
				swap(ar[i], ar[i + 1]);
			}
		}
	}
}

void QuickSort(int* ar, int last, int first) {
	if (first < last) {
		int p = Partition(ar, first, last);
		QuickSort(ar, p, first);
		QuickSort(ar, last, p + 1);
	}
}

void SelectionSort(int* ar, int size) {
	while (size) {
		int indMax = GetMax(&ar[0], size);
		swap(ar[indMax], ar[size - 1]);
		size--;
	}
}

void CountingSort(int* ar, int len) {
	int i, max = -1;
	int* counter;
	for (i = 0; i < len; i++)
		if (abs(ar[i]) > max) 
			max = abs(ar[i]);
	counter = new int[max * 2 + 1];
	for (i = 0; i < max * 2 + 1; i++)
		counter[i] = 0;
	for (i = 0; i < len; i++)
		counter[ar[i] + max]++;
	for (int i = 0, j, k = 0; i < max * 2 + 1; i++) {
		if (counter[i] > 0) {
			j = counter[i];
			for (; j > 0; j--) {
				ar[k] = i - max;
				k++;
			}
		}
	}
	delete[] counter;
}

void Merging(int* ar, int begin, int end) {
	int i = begin, t = 0, mid = begin + (end - begin) / 2, j = mid + 1;
	int* d = new int[M];
	while (i <= mid && j <= end) {
		if (ar[i] <= ar[j]) {
			d[t] = ar[i]; 
			i++;
		}
		else {
			d[t] = ar[j]; 
			j++;
		}
		t++;
	}
	while (i <= mid) {
		d[t] = ar[i]; 
		i++; 
		t++;
	}
	while (j <= end) {
		d[t] = ar[j]; 
		j++; 
		t++;
	}
	for (i = 0; i < t; i++)
		ar[begin + i] = d[i];
	delete[] d;
}

void MergeSort(int* ar, int right, int left) {
	if (left < right)
		if (right - left == 1) {
			if (ar[right] < ar[left]) {
				swap(ar[right], ar[left]);
			}
		}
		else {
			MergeSort(ar, left + (right - left) / 2, left);
			MergeSort(ar, right, left + (right - left) / 2 + 1);
			Merging(ar, left, right);
		}
}

int GetRandomNumber(int min, int max) {
	int num = min + rand() % (max - min + 1);
	return num;
}

void FileWrite(int Time, int len) {
	fLog = fopen("test1", "a");
	fprintf(fLog, "%d\t%d\n", Time, len);
	fclose(fLog);
}

void OutputData(FILE* &fLog) {
	fLog = fopen("test1", "r");
	int Time;
	int len;
	while (fscanf(fLog, "%d\t%d\n", &Time, &len) != EOF)
		cout << Time << "\t" << len << "\t" << endl;
	fclose(fLog);
}

void Test(int a) {
	srand(static_cast<unsigned int>(time(NULL)));
	cout << "Enter length: " << endl;
	int len;
	cin >> len;
	int* ar = new int[M];
	for (int i = 0; i < len; i++)
		ar[i] = GetRandomNumber(-1000, 1000);

	auto begin = std::chrono::steady_clock::now();

	switch (a) {
	case 1:
		QuickSort(ar, len - 1, 0);
		break;
	case 2:
		BubbleSort(ar, len);
		break;
	case 3:
		SelectionSort(ar, len);
		break;
	case 4:
		InsertionSort(ar, len);
		break;
	case 5:
		CountingSort(ar, len);
		break;
	case 6:
		MergeSort(ar, len - 1, 0);
		break;
	}

	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	int Time = elapsed_ms.count();
	cout << "Time = " << Time << " milliseconds" << endl;
	
	if (filewriting)
		FileWrite(Time, len);

	bool ok = true;
	for (int i = 0; i < len - 1; i++)
		if (ar[i] > ar[i + 1])
			ok = false;
	if (ok)
		cout << "SORTED CORRECTLY!" << endl;
	else
		cout << "SORT FAILED" << endl;

	for (int i = 0; i < len; i++)
		cout << ar[i] << ' ';

	delete[] ar;
}

int main()
{
	int command = 2;
	do {
		cout << endl << "Enter function number:" << endl << "1. QuickSort" << endl << "2. BubbleSort" << endl << "3. SelectionSort" << endl << "4. InsertionSort" << endl << "5. CountingSort" << endl << "6. MergeSort" << endl << "7. Leave program" << endl << "8. Start writing" << endl << "9. Finish Writing" << endl << "10. Output data" << endl << "11. Remove data" << endl;
		int a;
		cin >> a;
		switch (a) {
		case 1:
			Test(1);
			break;
		case 2:
			Test(2);
			break;
		case 3:
			Test(3);
			break;
		case 4:
			Test(4);
			break;
		case 5:
			Test(5);
			break;
		case 6:
			Test(6);
			break;
		case 7:
			command = 10;
			break;
		case 8:
			filewriting = true;
			break;
		case 9:
			filewriting = false;
			break;
		case 10:
			OutputData(fLog);
			break;
		case 11:
			remove("C:\\Users\\Zhon1\\Desktop\\ОБУЧЕНИЕ\\Инфа\\2 семестр\\ОП\\ДЗ1\\DZ1\\test1");
		}
	} while (command != 10);
    return 0;
}