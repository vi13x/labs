#include <stdio.h>м
#include <stdlib.h>
#include "function.h"
int inputInteger() {
    int var, c;
    while (1) {
        while (scanf("%d", &var) != 1) {
            printf("ОШИБКА...введите корректное значение: ");
            while ((c = getchar()) != '\n' && c != EOF);
        }
        if ((c = getchar()) != '\n' && c != EOF && c != ' ') {
            printf("ОШИБКА...введите корректное значение: ");
            while ((c = getchar()) != '\n' && c != EOF);
        } else
            return var;
    }
}

void writeFile(FILE *file) {
    int num;
    printf("Введите числа (0 для завершения ввода): \n");
    while ((num = inputInteger()) != 0) {
        fwrite(&num, sizeof(int), 1, file);
    }
    fflush(file);
}

void readFile(FILE *file) {
    rewind(file);
    int num;
    printf("Содержимое файла:\n");
    while (fread(&num, sizeof(int), 1, file)) {
        printf("%d ", num);
    }
    printf("\n");
    rewind(file);
}
int counter(FILE *file, int target) {
    rewind(file);
    int num, count = 0;
    while (fread(&num, sizeof(int), 1, file)) {
        if (num == target) count++;
    }
    rewind(file);
    return count;
}

void replaceMax(FILE *file, int target) {
    rewind(file);
    int num, max = INT_MIN;

    while (fread(&num, sizeof(int), 1, file)) {
        if (num > max) max = num;
    }

    printf("Найдено максимальное число %d\n", max);

    if (max == INT_MIN) {
        rewind(file);
        return;
    }

    rewind(file);
    while (fread(&num, sizeof(int), 1, file)) {
        if (num == target) {
            fseek(file, -sizeof(int), SEEK_CUR);
            fwrite(&max, sizeof(int), 1, file);
            fflush(file);
        }
    }
    rewind(file);
}


void oddBubbleSort(FILE *file) {
    rewind(file);
    int numbers[1000], count = 0;
    while (fread(&numbers[count], sizeof(int), 1, file)) {
        count++;
    }

    if (count == 0) {
        printf("Файл пуст, сортировка невозможна.\n");
        rewind(file);
        return;
    }

    printf("Прочитано %d чисел из файла.\n", count);


    int odd_indices[1000], odd_values[1000], odd_count = 0;
    for (int i = 0; i < count; i++) {
        if (numbers[i] % 2 != 0) {
            odd_indices[odd_count] = i;
            odd_values[odd_count] = numbers[i];
            odd_count++;
        }
    }

    printf("Найдено %d нечетных чисел.\n", odd_count);


    for (int i = 0; i < odd_count - 1; i++) {
        for (int j = 0; j < odd_count - i - 1; j++) {
            if (odd_values[j] < odd_values[j + 1]) {
                int temp = odd_values[j];
                odd_values[j] = odd_values[j + 1];
                odd_values[j + 1] = temp;
            }
        }
    }

    printf("Отсортированные нечетные числа: ");
    for (int i = 0; i < odd_count; i++) {
        printf("%d ", odd_values[i]);
    }
    printf("\n");

    for (int i = 0; i < odd_count; i++) {
        numbers[odd_indices[i]] = odd_values[i];
    }

    rewind(file);
    fwrite(numbers, sizeof(int), count, file);
    fflush(file);
    rewind(file);
}
