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
