void adjustHeap(int *arr, int i, int length);

void heapSort(int *arr, int length) {
	for (int i = (length - 1) / 2; i >= 0; i--)
		adjustHeap(arr, i, length);
	for (int j = length - 1; j > 0; j--) {
		int temp = arr[j];
		arr[j] = arr[0];
		arr[0] = temp;
		adjustHeap(arr, 0, j);
	}
}

void adjustHeap(int *arr, int i, int length) {
	int temp = arr[i];
	for (int k = 2 * i + 1; k < length; k = 2 * k + 1) {
		if (k + 1 < length && arr[k + 1] > arr[k])
			k = k + 1;
		if (arr[k] > temp) {
			arr[i] = arr[k];
			i = k;
		}
	}
	arr[i] = temp;
}