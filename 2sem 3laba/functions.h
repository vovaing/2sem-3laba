#define MAX_NAME_LEN 50
#define DATE_LEN 11  // "YYYY-MM-DD" + '\0'

// Структура для даты тура
typedef struct {
    char date[DATE_LEN];
    int days;
} TourDate;

// Структура для тура
typedef struct {
    int price;
    char* name;
    TourDate tour_date;
} ExcursionTour;

// Функция для проверки, является ли строка числом
int is_string_numeric(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

// Функция для проверки формата даты (YYYY-MM-DD)
int is_valid_date(const char* date) {
    // Проверка длины строки
    int len = 0;
    while (date[len] != '\0') len++;
    if (len != 10) return 0;

    // Проверка формата
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            if (date[i] != '-') return 0;
        } else {
            if (!isdigit(date[i])) return 0;
        }
    }

    return 1;
}

// Функция для проверки корректности даты (YYYY-MM-DD) с упрощенной логикой
int is_valid_date_simple(const char* date) {
    // Сначала проверяем базовый формат
    if (!is_valid_date(date)) {
        return 0;
    }

    // Разбираем дату на компоненты
    int year, month, day;
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3) {
        return 0;
    }

    // Проверяем месяц (1-12)
    if (month < 1 || month > 12) {
        return 0;
    }

    // Проверяем день (1-31)
    if (day < 1 || day > 31) {
        return 0;
    }

    // Проверяем месяцы с 30 днями (апрель, июнь, сентябрь, ноябрь)
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return 0;
    }

    // Для февраля просто проверяем, что день <= 29 (без проверки високосности)
    if (month == 2 && day > 29) {
        return 0;
    }

    return 1;
}

// Функция для вывода байтов числа
void print_bytes(int num) {
    unsigned char* bytes = (unsigned char*)&num;
    printf("Байты числа %d: ", num);
    for (size_t i = 0; i < sizeof(int); i++) {
        printf("%d ", bytes[i]);
    }
    printf("\n");
}

// Функция для ввода строки (аналог gets)
void my_gets(char* buffer, int max_len) {
    int i = 0;
    char c;
    while ((c = getchar()) != '\n' && c != EOF && i < max_len - 1) {
        buffer[i++] = c;
    }
    buffer[i] = '\0';
}

// Функция для сравнения строк (аналог strcmp)
int my_strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

// Функция для копирования строк (аналог strcpy)
void my_strcpy(char* dest, const char* src) {
    while ((*dest++ = *src++));
}

// Функция для ввода тура
void input_tour(ExcursionTour* tour) {
    char buffer[100];
    int valid = 0;
    
    // Ввод названия
    printf("Введите название тура: ");
    my_gets(buffer, MAX_NAME_LEN);
    tour->name = (char*)malloc(MAX_NAME_LEN * sizeof(char));
    my_strcpy(tour->name, buffer);
    
    // Ввод стоимости с проверкой
    while (!valid) {
        printf("Введите стоимость тура: ");
        my_gets(buffer, 100);
        
        int price;
        if (sscanf(buffer, "%d", &price) == 1) {
            // Дополнительная проверка на положительное значение
            if (price > 0) {
                tour->price = price;
                valid = 1;
            } else {
                printf("Стоимость должна быть положительной\n");
            }
        } else {
            printf("Некорректный ввод.\n");
        }
    }
    
    valid = 0;
    // Ввод даты с проверкой формата и логики
    while (!valid) {
        printf("Введите дату начала тура (YYYY-MM-DD): ");
        my_gets(buffer, DATE_LEN);
        if (is_valid_date_simple(buffer)) {
            my_strcpy(tour->tour_date.date, buffer);
            valid = 1;
        } else {
            printf("Проверьте формат (YYYY-MM-DD) и корректность даты.\n");
        }
    }
    
    valid = 0;
    // Ввод количества дней с проверкой
    while (!valid) {
        printf("Введите количество дней: ");
        my_gets(buffer, 100);
        
        int days;
        char extra;
        if (sscanf(buffer, "%d%c", &days, &extra) == 1) {
            if (days >= 1 && days <= 365) {
                tour->tour_date.days = days;
                valid = 1;
            } else {
                printf("Число должно быть от 1 до 365\n");
            }
        } else {
            printf("Введите целое число.\n");
        }
    }
}

// Функция для вывода тура
void print_tour(const ExcursionTour* tour) {
    printf("Название: %s\n", tour->name);
    printf("Стоимость: %d\n", tour->price);
    printf("Дата начала: %s\n", tour->tour_date.date);
    printf("Количество дней: %d\n\n", tour->tour_date.days);
}

// Функция поиска туров дешевле заданной цены
void find_cheaper_tours(ExcursionTour* tours, int count, int max_price) {
    printf("\nТуры дешевле %d:\n", max_price);
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (tours[i].price < max_price) {
            print_tour(&tours[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Нет туров дешевле указанной цены.\n");
    }
}

// Функция удаления туров по названию
int delete_tours_by_name(ExcursionTour** tours, int* count, const char* name) {
    int deleted = 0;
    for (int i = 0; i < *count; i++) {
        if (my_strcmp((*tours)[i].name, name) == 0) {
            // Освобождаем память для названия
            free((*tours)[i].name);
            
            // Сдвигаем оставшиеся элементы
            for (int j = i; j < *count - 1; j++) {
                (*tours)[j] = (*tours)[j+1];
            }
            
            (*count)--;
            i--; // Проверяем текущий индекс снова
            deleted++;
        }
    }
    
    // Перераспределяем память
    if (deleted > 0) {
        ExcursionTour* temp = (ExcursionTour*)realloc(*tours, (*count) * sizeof(ExcursionTour));
        if (temp != NULL || *count == 0) {
            *tours = temp;
        }
    }
    
    return deleted;
}

// Основное меню
void menu() {
    printf("\nМеню:\n");
    printf("1. Просмотреть все туры\n");
    printf("2. Добавить тур\n");
    printf("3. Найти туры дешевле заданной цены\n");
    printf("4. Удалить туры по названию\n");
    printf("5. Выход\n");
    printf("Выберите действие: ");
}


