#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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

// Структура для даты начала тура
typedef struct {
    char start_date[11]; // Формат: "YYYY-MM-DD" + '\0'
    int days_count;
} TourDate;

// Структура для экскурсионного тура
typedef struct {
    int price;
    char *name;
    TourDate date;
} ExcursionTour;

// Функция для ввода тура
void input_tour(ExcursionTour *tour) {
    printf("Введите стоимость тура: ");
    scanf("%d", &tour->price);
    
    printf("Введите название тура: ");
    char buffer[100];
    scanf(" %[^\n]", buffer);
    tour->name = (char *)malloc(strlen(buffer) + 1);
    strcpy(tour->name, buffer);
    
    printf("Введите дату начала тура (YYYY-MM-DD): ");
    scanf("%s", tour->date.start_date);
    
    printf("Введите количество дней: ");
    scanf("%d", &tour->date.days_count);
}

// Функция для вывода тура
void print_tour(const ExcursionTour *tour) {
    printf("Тур: %s\n", tour->name);
    printf("Стоимость: %d\n", tour->price);
    printf("Дата начала: %s\n", tour->date.start_date);
    printf("Количество дней: %d\n", tour->date.days_count);
    printf("-------------------\n");
}

// Функция поиска туров по максимальной цене
void find_tours_below_price(const ExcursionTour *tours, int count, int max_price) {
    printf("Туры дешевле %d:\n", max_price);
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (tours[i].price < max_price) {
            print_tour(&tours[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Туров дешевле %d не найдено.\n", max_price);
    }
}

// Функция удаления туров по названию
int delete_tours_by_name(ExcursionTour **tours, int *count, const char *name) {
    int deleted = 0;
    for (int i = 0; i < *count; ) {
        if (strcmp((*tours)[i].name, name) == 0) {
            // Освобождаем память названия
            free((*tours)[i].name);
            
            // Сдвигаем оставшиеся элементы
            for (int j = i; j < *count - 1; j++) {
                (*tours)[j] = (*tours)[j + 1];
            }
            
            (*count)--;
            deleted++;
        } else {
            i++;
        }
    }
    
    // Перераспределяем память
    if (deleted > 0) {
        *tours = (ExcursionTour *)realloc(*tours, (*count) * sizeof(ExcursionTour));
    }
    
    return deleted;
}

// Функция для вывода всех туров
void print_all_tours(const ExcursionTour *tours, int count) {
    printf("Список всех туров:\n");
    for (int i = 0; i < count; i++) {
        print_tour(&tours[i]);
    }
}

// Функция освобождения памяти
void free_tours(ExcursionTour *tours, int count) {
    for (int i = 0; i < count; i++) {
        free(tours[i].name);
    }
    free(tours);
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
