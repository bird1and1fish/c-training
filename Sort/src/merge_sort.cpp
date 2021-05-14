void merge(int *arr, int left, int mid, int right, int *temp);

void mergeSort(int *arr, int left, int right, int *temp) {
	if (left < right) {
		int mid = (left + right) / 2;
		mergeSort(arr, left, mid, temp);
		mergeSort(arr, mid + 1, right, temp);
		merge(arr, left, mid, right, temp);
	}
}

void merge(int *arr, int left, int mid, int right, int *temp) {
	int i = left;
	int j = mid + 1;
	int index = left;
	while (i <= mid && j <= right) {
		if (arr[i] < arr[j])
			temp[index++] = arr[i++];
		else
			temp[index++] = arr[j++];
	}
	while (i <= mid)
		temp[index++] = arr[i++];
	while (j <= right)
		temp[index++] = arr[j++];
	while (left <= right)
		arr[left++] = temp[left];

}