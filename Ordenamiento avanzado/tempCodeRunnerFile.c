void quicksort(int arr[], int n) {
        int start = 0;
    int end = n - 1;

    while (start < end) {
        int i = start;
        int j = end;
        int pivot = arr[start + (end - start) / 2];

        // Partición estilo Hoare
        while (i <= j) {
            while (arr[i] < pivot) i++;
            while (arr[j] > pivot) j--;
            if (i <= j) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                i++;
                j--;
            }
        }

        // Procesamos el subrango más pequeño primero
        if (j - start < end - i) {
            if (start < j) {
                end = j;
                continue;
            }
            start = i;
        } else {
                if (i < end) {
                start = i;
                continue;
            }
            end = j;
        }
    }

    // Segunda pasada para subrangos restantes
    for (int s = 0; s < n - 1; s++) {
        int a = s;
        int b = n - 1;
        while (a < b) {
            int i = a;
            int j = b;
            int pivot = arr[a + (b - a) / 2];

            while (i <= j) {
                    while (arr[i] < pivot) i++;
                    while (arr[j] > pivot) j--;
                    if (i <= j) {
                    int tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                    i++;
                    j--;
                }
            }
            if (j - a < b - i) {
                    if (a < j) b = j;
                    else a = i;
                } else {
                        if (i < b) a = i;
                        else b = j;
            }
        }
    }
}