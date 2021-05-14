void shellSort(int *arr, int length) {
	for (int gap = length / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < length; i++){
			int temp = arr[i];
			for (int j = i - gap; j >= 0; j -= gap) {
				if (arr[j] > temp) {
					arr[j + gap] = arr[j];
					if (j - gap < 0) {
						arr[j] = temp;
						break;
					}
				}
				else {
					arr[j + gap] = temp;
					break;
				}
			}
		}
	}

}