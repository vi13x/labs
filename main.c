#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
#include "function.h"
int main() {
    SetConsoleOutputCP(CP_UTF8);
    const char *filename = "data.bin";
    write_to_file(filename);
    readFile(filename);
    int target;
    printf("Введите число для поиска: ");
   target=inputInteger();
    printf("Число %d встречается %d раз(а)\n", target,counter(filename, target));
    printf("Введите число для замены на максимальный элемент: ");
    target=inputInteger();
    replaceMax(filename, target);
    readFile(filename);
    printf("Сортируем нечетные числа по убыванию...\n");
    oddBubbleSort(filename);
    readFile(filename);
    return 0;
}