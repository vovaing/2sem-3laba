#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "functions.h"

/*
Задания:
1. Для целого числа (int) вывести содержимое каждого байта (в десятичной системе счисления).
2. Структура содержит информацию об экскурсионных турах: стоимость (число), название (указатель),
   вложенную структуру – дату начала (строка фиксированной длины) и количество дней.
   Найти туры со стоимостью меньше заданной. Удалить туры с заданным названием.

Автор: Палакян Владимир
Дата: 28.03.2025
*/

// Задача 1: Вывод содержимого байтов целого числа
void print_bytes_of_int() {
    int num;
    printf("Введите целое число: ");
    scanf("%d", &num);
    
    // Используем указатель на байты для доступа к отдельным байтам числа
    unsigned char *bytes = (unsigned char *)&num;
    
    printf("Байты числа %d (в десятичной системе):\n", num);
    for (size_t i = 0; i < sizeof(int); i++) {
        printf("Байт %zu: %d\n", i + 1, bytes[i]);
    }
}


int main() {
    // Задача 1
    print_bytes_of_int();
    
    // Задача 2
    ExcursionTour *tours = NULL;
    int tour_count = 0;
    
    int choice;
    do {
        printf("\nМеню:\n");
        printf("1. Добавить тур\n");
        printf("2. Показать все туры\n");
        printf("3. Найти туры дешевле заданной цены\n");
        printf("4. Удалить туры по названию\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                // Добавление нового тура
                tours = (ExcursionTour *)realloc(tours, (tour_count + 1) * sizeof(ExcursionTour));
                if (!tours) {
                    printf("Ошибка выделения памяти!\n");
                    return 1;
                }
                input_tour(&tours[tour_count]);
                tour_count++;
                break;
            }
            case 2:
                print_all_tours(tours, tour_count);
                break;
            case 3: {
                int price;
                printf("Введите максимальную цену: ");
                scanf("%d", &price);
                find_tours_below_price(tours, tour_count, price);
                break;
            }
            case 4: {
                char name[100];
                printf("Введите название тура для удаления: ");
                scanf(" %[^\n]", name);
                int deleted = delete_tours_by_name(&tours, &tour_count, name);
                printf("Удалено %d туров с названием '%s'\n", deleted, name);
                break;
            }
            case 0:
                break;
            default:
                printf("Неверный выбор!\n");
        }
    } while (choice != 0);
    
    // Освобождение памяти
    free_tours(tours, tour_count);
    
    return 0;
}
