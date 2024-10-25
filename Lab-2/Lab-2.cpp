#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma comment(linker, "/STACK:16726272216")

/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void multiply_and_time(int size) {
    int a[size][size], b[size][size], c[size][size], elem_c;
    int i, j, r;

    srand(time(NULL));
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            a[i][j] = rand() % 100 + 1;

    srand(time(NULL));
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            b[i][j] = rand() % 100 + 1;

    clock_t start = clock();
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            elem_c = 0;
            for (r = 0; r < size; r++) {
                elem_c += a[i][r] * b[r][j];
            }
            c[i][j] = elem_c;
        }
    }
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Size %d: Multiplication time: %.6f seconds\n", size, time_spent);
}

int main(void) {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    int sizes[] = {200, 400, 800}; // Example sizes
    for (int i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
        multiply_and_time(sizes[i]);
    }

    return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <clocale>

#define N 10000 // размер массива

// Реализация сортировки Шелла
void shell(int* items, int count) {
    int i, j, gap, k;
    int x, a[5] = { 9, 5, 3, 2, 1 };

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

// Реализация быстрой сортировки
void qs(int* items, int left, int right) {
    int i = left, j = right;
    int x = items[(left + right) / 2], y;

    do {
        while (items[i] < x && i < right) i++;
        while (x < items[j] && j > left) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

// Функция для генерации случайного массива
void generate_random_array(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000; // случайные числа от 0 до 9999
    }
}

// Функция для генерации массива с возрастающей последовательностью
void generate_ascending_array(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
}

// Функция для генерации массива с убывающей последовательностью
void generate_descending_array(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
}

// Функция для генерации массива, где первая половина возрастающая, а вторая убывающая
void generate_mixed_array(int* arr, int size) {
    for (int i = 0; i < size / 2; i++) {
        arr[i] = i;
    }
    for (int i = size / 2; i < size; i++) {
        arr[i] = size - i;
    }
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void test_sorting(void (*sort_func)(int*, int), int* arr, int size, const char* sort_name, const char* data_type) {
    clock_t start, end;
    int* copy = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        copy[i] = arr[i];
    }

    start = clock();
    sort_func(copy, size);
    end = clock();

    printf("%s на %s данных заняло %.3f секунд\n", sort_name, data_type, (double)(end - start) / CLOCKS_PER_SEC);
    free(copy);
}

void test_qsort(int* arr, int size, const char* data_type) {
    clock_t start, end;
    int* copy = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        copy[i] = arr[i];
    }

    start = clock();
    qsort(copy, size, sizeof(int), compare);
    end = clock();

    printf("qsort на %s данных заняло %.3f секунд\n", data_type, (double)(end - start) / CLOCKS_PER_SEC);
    free(copy);
}

void qs_wrapper(int* items, int count) {
    qs(items, 0, count - 1);
}

int main() {

    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    system("chcp 65001");

    int arr[N];

    // Случайные данные
    generate_random_array(arr, N);
    test_sorting(shell, arr, N, "ShellSort", "случайных");
    test_sorting(qs_wrapper, arr, N, "QuickSort", "случайных");
    test_qsort(arr, N, "случайных");

    // Возрастающая последовательность
    generate_ascending_array(arr, N);
    test_sorting(shell, arr, N, "ShellSort", "возрастающих");
    test_sorting(qs_wrapper, arr, N, "QuickSort", "возрастающих");
    test_qsort(arr, N, "возрастающих");

    // Убывающая последовательность
    generate_descending_array(arr, N);
    test_sorting(shell, arr, N, "ShellSort", "убывающих");
    test_sorting(qs_wrapper, arr, N, "QuickSort", "убывающих");
    test_qsort(arr, N, "убывающих");

    // Первая половина - возрастающая, вторая - убывающая
    generate_mixed_array(arr, N);
    test_sorting(shell, arr, N, "ShellSort", "смешанных");
    test_sorting(qs_wrapper, arr, N, "QuickSort", "смешанных");
    test_qsort(arr, N, "смешанных");

    return 0;
}

