/*
    Задание:
    1. Очередь для целых чисел. Максимальный размер очереди вводится с экрана.
       Функции для ввода и вывода. При переполнении — удаляется первый элемент.
    
    2. Дек для чисел с плавающей точкой. Максимальный размер дека вводится с экрана.
       Функции для ввода и вывода. При переполнении — удаляется левый элемент.
    
    Фамилия студента: Палакян
    Дата написания кода: 29.04.2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE -1
#include "function.h"

int main() {
    int choice;
    do {
        printf("\n=== Главное меню ===\n");
        printf("1. Работа с очередью (целые числа)\n");
        printf("2. Работа с деком (числа с плавающей точкой)\n");
        printf("3. Выход\n");
        choice = inputInteger("Выберите задание (1-3): ");

        switch (choice) {
            case 1:
                workWithQueue();
                break;
            case 2:
                workWithDeque();
                break;
            case 3:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 3);

    return SUCCESS;
}
