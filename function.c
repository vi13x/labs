#include <stdio.h>
#include <stdlib.h>
int inputInteger() {
    int var;
    int c;
    while (1) {
        while (scanf("%d", &var) != 1) {
            printf("ОШИБКА...введите корректное значение: ");
            while ((c = getchar()) != '\n' && c != EOF);
        }
        if ((c = getchar()) != '\n' && c != EOF && c != ' ') {
            printf("ОШИБКА...введите корректное значение: ");
            while ((c = getchar()) != '\n' && c != EOF);
        }
        else
            return var;
    }
}

void write_to_file(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Ошибка открытия файла");
        exit(1);
    }

    int num;
    printf("Введите числа (0 для завершения ввода): \n");
    while ((num = inputInteger()) != 0) {
        fwrite(&num, sizeof(int), 1, file);
    }
    fclose(file);
}
void readFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Ошибка открытия файла");
        exit(1);
    }

    int num;
    printf("Содержимое файла: \n");
    while (fread(&num, sizeof(int), 1, file)) {
        printf("%d ", num);
    }
    printf("\n");
    fclose(file);
}

int counter(const char *filename, int target) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Ошибка открытия файла");
        exit(1);
    }

    int num, count = 0;
    while (fread(&num, sizeof(int), 1, file)) {
        if (num == target) count++;
    }
    fclose(file);
    return count;
}

void replaceMax(const char *filename, int target) {
    FILE *file = fopen(filename, "r+b");
    if (!file) {
        perror("Ошибка открытия файла");
        exit(1);
    }
    int num, max = INT_MIN;
    while (fread(&num, sizeof(int), 1, file)) {
        if (num > max) max = num;
    }
    printf("DEBUG: Найдено максимальное число %d\n", max);
    if (max == INT_MIN) {
        fclose(file);
        return;
    }
    rewind(file); // Возвращаемся в начало файла
    while (fread(&num, sizeof(int), 1, file)) {
        if (num == target) {
            fseek(file, -sizeof(int), SEEK_CUR);
            fwrite(&max, sizeof(int), 1, file);
            fflush(file);
        }
    }
    fclose(file);
}

void oddBubbleSort(const char *filename) {
    FILE *file = fopen(filename, "r+b");
    if (!file) {
        perror("Ошибка открытия файла");
        exit(1);
    }
    int numbers[1000], count = 0;
    while (fread(&numbers[count], sizeof(int), 1, file)) {
        count++;
    }
    if (count == 0) {
        printf("Файл пуст, сортировка невозможна.\n");
        fclose(file);
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
    fclose(file);
}
