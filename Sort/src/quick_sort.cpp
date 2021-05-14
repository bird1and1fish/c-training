void quickSort(int *arr, int start, int end) {
	if (start < end) {
		int low = start;
		int high = end;
		int temp = arr[start];
		while (start < end) {
			while (arr[end] >= temp && start < end)
				end--;
			if (start < end) {
				arr[start] = arr[end];
				start++;
			}
			while (arr[start] <= temp && start < end)
				start++;
			if (start < end) {
				arr[end] = arr[start];
				end--;
			}
		}
		arr[start] = temp;
		quickSort(arr, low, start);
		quickSort(arr, start + 1, high);
	}
}