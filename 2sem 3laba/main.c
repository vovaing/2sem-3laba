/*
Задание:
1. Для целого числа (int) вывести содержимое каждого байта (в десятичной системе счисления)
2. Работа с экскурсионными турами (структуры):
   - Найти туры дешевле заданной стоимости
   - Удалить туры по названию
   - Проверка формата даты (YYYY-MM-DD)
   - Проверка ввода чисел
Автор: Владимир Палакян
Дата: 28.03.2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "functions.h"


int main() {
    // Задача 1: вывод байтов числа
    int num;
    printf("Введите целое число: ");
    scanf("%d", &num);
    getchar(); // Очистка буфера
    print_bytes(num);
    
    // Задача 2: работа с турами
    ExcursionTour* tours = NULL;
    int count = 0;
    int capacity = 0;
    
    int choice;
    do {
        menu();
        char buffer[100];
        my_gets(buffer, 100);
        choice = atoi(buffer);
        
        switch (choice) {
            case 1: // Просмотр всех туров
                if (count == 0) {
                    printf("Нет доступных туров.\n");
                } else {
                    printf("\nВсе туры:\n");
                    for (int i = 0; i < count; i++) {
                        printf("Тур #%d:\n", i+1);
                        print_tour(&tours[i]);
                    }
                }
                break;
                
            case 2: // Добавление тура
                if (count == capacity) {
                    capacity = capacity == 0 ? 1 : capacity * 2;
                    ExcursionTour* temp = (ExcursionTour*)realloc(tours, capacity * sizeof(ExcursionTour));
                    if (temp == NULL) {
                        printf("Ошибка выделения памяти!\n");
                        break;
                    }
                    tours = temp;
                }
                
                input_tour(&tours[count]);
                count++;
                printf("Тур успешно добавлен.\n");
                break;
                
            case 3: { // Поиск по цене
                if (count == 0) {
                    printf("Нет доступных туров.\n");
                    break;
                }
                
                int max_price;
                int valid = 0;
                while (!valid) {
                    printf("Введите максимальную стоимость: ");
                    my_gets(buffer, 100);
                    if (is_string_numeric(buffer)) {
                        max_price = atoi(buffer);
                        valid = 1;
                    } else {
                        printf("Ошибка! Введите число.\n");
                    }
                }
                
                find_cheaper_tours(tours, count, max_price);
                break;
            }
                
            case 4: { // Удаление по названию
                if (count == 0) {
                    printf("Нет доступных туров.\n");
                    break;
                }
                
                char name[MAX_NAME_LEN];
                printf("Введите название тура для удаления: ");
                my_gets(name, MAX_NAME_LEN);
                
                int deleted = delete_tours_by_name(&tours, &count, name);
                printf("Удалено %d туров.\n", deleted);
                break;
            }
                
            case 5: // Выход
                printf("Завершение программы.\n");
                break;
                
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 5);
    
    // Освобождение памяти
    for (int i = 0; i < count; i++) {
        free(tours[i].name);
    }
    free(tours);
    
    return 0;
}
