#include <iostream>
#include "Sort.h"

using namespace std;

int main() {
	int a[100];
	int n = 10;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	int a_copy[100];
	int a_copy1[100];
	int a_copy2[100];
	int temp[100];
	copy(begin(a), end(a), begin(a_copy));
	copy(begin(a), end(a), begin(a_copy1));
	copy(begin(a), end(a), begin(a_copy2));

	quickSort(a, 0, n - 1);
	cout << "quickSort result is: ";
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << ' ';
	}
	cout << endl;

	shellSort(a_copy, n);
	cout << "shellSort result is: ";
	for (int i = 0; i < n; i++)
	{
		cout << a_copy[i] << ' ';
	}
	cout << endl;

	mergeSort(a_copy1, 0, n - 1, temp);
	cout << "mergeSort result is: ";
	for (int i = 0; i < n; i++)
	{
		cout << a_copy1[i] << ' ';
	}
	cout << endl;

	heapSort(a_copy2, n);
	cout << "heapSort result is: ";
	for (int i = 0; i < n; i++)
	{
		cout << a_copy2[i] << ' ';
	}
	cout << endl;

	system("pause");
}