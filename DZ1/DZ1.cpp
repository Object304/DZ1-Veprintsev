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

//ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ

void Heapify(int* ar, int n, int i) {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && ar[l] > ar[largest])
		largest = l;

	if (r < n && ar[r] > ar[largest])
		largest = r;

	if (largest != i) {
		swap(ar[i], ar[largest]);
		Heapify(ar, n, largest);
	}
}

void Merge(int* ar, int l, int m, int r) {
	int len1 = m - l + 1, len2 = r - m;
	int* left = new int[len1];
	int* right = new int[len2];
	for (int i = 0; i < len1; i++)
		left[i] = ar[l + i];
	for (int i = 0; i < len2; i++)
		right[i] = ar[m + 1 + i];

	int i = 0;
	int j = 0;
	int k = l;

	while (i < len1 && j < len2) {
		if (left[i] <= right[j]) {
			ar[k] = left[i];
			i++;
		}
		else {
			ar[k] = right[j];
			j++;
		}
		k++;
	}

	while (i < len1) {
		ar[k] = left[i];
		k++;
		i++;
	}

	while (j < len2) {
		ar[k] = right[j];
		k++;
		j++;
	}
	delete[] left;
	delete[] right;
}

int ModifiedPartition(int* ar, int low, int high) {
	int pivot = ar[high];
	int pIndex = low;
	for (int i = low; i < high; i++) {
		if (ar[i] <= pivot) {
			swap(ar[i], ar[pIndex]);
			pIndex++;
		}
	}
	swap(ar[pIndex], ar[high]);
	return pIndex;
}

int Partition(int* ar, int first, int last) {
	int pivot = ar[(first + last) / 2];
	int i = first, j = last;
	while (true) {
		while (ar[i] < pivot)
			i++;
		while (ar[j] > pivot)
			j--;
		if (i >= j)
			break;
		swap(ar[i], ar[j]);
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

//ФУНКЦИИ СОРТИРОВОК

void InsertionSort(int* ar, int left, int right) {
	for (int i = left + 1; i <= right; i++) {
		int temp = ar[i];
		int j = i - 1;
		while (j >= left && ar[j] > temp) {
			ar[j + 1] = ar[j];
			j--;
		}
		ar[j + 1] = temp;
	}
}

void TimSort(int* ar, int len)
{
	for (int i = 0; i < len; i += 32)
		InsertionSort(ar, i, min((i + 32 - 1), (len - 1)));
	for (int size = 32; size < len; size = 2 * size) {
		for (int left = 0; left < len; left += 2 * size) {
			int mid = left + size - 1;
			int right = min((left + 2 * size - 1), (len - 1));
			if (mid < right)
				Merge(ar, left, mid, right);
		}
	}
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

void ModifiedQuicksort(int* ar, int low, int high) {
	while (low < high) {
		if (high - low < 10) {
			InsertionSort(ar, low, high);
			break;
		}
		else {
			int pivot = ModifiedPartition(ar, low, high);
			if (pivot - low < high - pivot) {
				ModifiedQuicksort(ar, low, pivot - 1);
				low = pivot + 1;
			}
			else {
				ModifiedQuicksort(ar, pivot + 1, high);
				high = pivot - 1;
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
			Merge(ar, left, left + (right - left) / 2, right);
		}
}

void ShellSort(int* ar, int len) {
	for (int d = len / 2; d > 0; d /= 2)
		for (int i = d; i < len; i += d)
			for (int j = i; j > 0; j -= d)
				if (ar[j] < ar[j - d])
					swap(ar[j], ar[j - d]);
}

void GnomeSort(int* ar, int len) {	
	for (int i = 0; i < len;) {
		if (i == 0)
			i++;
		if (ar[i] >= ar[i - 1])
			i++;
		else {
			swap(ar[i], ar[i - 1]);
			i--;
		}
	}
}

void HeapSort(int* ar, int len) {
	for (int i = len / 2 - 1; i >= 0; i--)
		Heapify(ar, len, i);
	for (int i = len - 1; i >= 0; i--) {
		swap(ar[0], ar[i]);
		Heapify(ar, i, 0);
	}
}

//ПРОЧИЕ ФУНКЦИИ

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

void MashUp(int* ar, int len) {
	for (int i = 0; i < len; i++)
		ar[i] = GetRandomNumber(-1000, 1000);
}

void Check(int* ar, int len) {
	bool ok = true;
	for (int i = 0; i < len - 1; i++)
		if (ar[i] > ar[i + 1])
			ok = false;
	if (ok)
		cout << "SORTED CORRECTLY!" << endl;
	else
		cout << "SORT FAILED" << endl;
}

void Test() {
	srand(static_cast<unsigned int>(time(NULL)));
	cout << "Enter length: " << endl;
	int len;
	cin >> len;
	int* ar = new int[M];
	auto begin = std::chrono::steady_clock::now();
	MashUp(ar, len);
	QuickSort(ar, len - 1, 0);
	Check(ar, len);
	MashUp(ar, len);
	BubbleSort(ar, len);
	Check(ar, len);
	MashUp(ar, len);
	SelectionSort(ar, len);
	Check(ar, len);
	MashUp(ar, len);
	InsertionSort(ar, 0, len);
	Check(ar, len);
	MashUp(ar, len);
	CountingSort(ar, len);
	Check(ar, len);
	MashUp(ar, len);
	MergeSort(ar, len - 1, 0);
	Check(ar, len);
	MashUp(ar, len);
	ShellSort(ar, len);
	Check(ar, len);
	MashUp(ar, len);
	GnomeSort(ar, len);
	Check(ar, len);
	MashUp(ar, len);
	TimSort(ar, len + 1);
	Check(ar, len);
	MashUp(ar, len);
	ModifiedQuicksort(ar, 0, len - 1);
	Check(ar, len);
	MashUp(ar, len);
	HeapSort(ar, len);
	Check(ar, len);
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	int Time = elapsed_ms.count();
	cout << "Time = " << Time << " milliseconds" << endl;
	
	FileWrite(Time, len);

	delete[] ar;
}

int main()
{
	Test();
    return 0;
}