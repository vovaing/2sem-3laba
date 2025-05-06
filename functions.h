typedef struct {
    int *data;
    int front, rear, size, capacity;
} IntQueue;

IntQueue* createIntQueue(int capacity) {
    IntQueue *q = malloc(sizeof(IntQueue));
    if (!q) return NULL;
    q->data = malloc(sizeof(int) * capacity);
    if (!q->data) { free(q); return NULL; }
    q->front = q->rear = q->size = 0;
    q->capacity = capacity;
    return q;
}

int isIntQueueFull(IntQueue *q) {
    return q->size == q->capacity;
}

int enqueueInt(IntQueue *q, int value) {
    if (isIntQueueFull(q)) {
        printf("Очередь полна. Удаляется: %d\n", q->data[q->front]);
        q->front = (q->front + 1) % q->capacity;
        q->size--;
    }
    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % q->capacity;
    q->size++;
    return SUCCESS;
}

void displayIntQueue(IntQueue *q) {
    printf("Содержимое очереди: ");
    for (int i = 0; i < q->size; i++)
        printf("%d ", q->data[(q->front + i) % q->capacity]);
    printf("\n");
}

void freeIntQueue(IntQueue *q) {
    free(q->data);
    free(q);
}



typedef struct {
    float *data;
    int front, rear, size, capacity;
} FloatDeque;

FloatDeque* createFloatDeque(int capacity) {
    FloatDeque *dq = malloc(sizeof(FloatDeque));
    if (!dq) return NULL;
    dq->data = malloc(sizeof(float) * capacity);
    if (!dq->data) { free(dq); return NULL; }
    dq->front = 0;
    dq->rear = -1;
    dq->size = 0;
    dq->capacity = capacity;
    return dq;
}

int isFloatDequeFull(FloatDeque *dq) {
    return dq->size == dq->capacity;
}

int pushBackFloat(FloatDeque *dq, float value) {
    if (isFloatDequeFull(dq)) {
        printf("Дек полон. Удаляется левый элемент: %.2f\n", dq->data[dq->front]);
        dq->front = (dq->front + 1) % dq->capacity;
        dq->size--;
    }
    dq->rear = (dq->rear + 1) % dq->capacity;
    dq->data[dq->rear] = value;
    dq->size++;
    return SUCCESS;
}

void displayFloatDeque(FloatDeque *dq) {
    printf("Содержимое дека: ");
    for (int i = 0; i < dq->size; i++)
        printf("%.2f ", dq->data[(dq->front + i) % dq->capacity]);
    printf("\n");
}

void freeFloatDeque(FloatDeque *dq) {
    free(dq->data);
    free(dq);
}



void inputString(char *buffer, int maxLength, const char *msg) {
    while (1) {
        printf("%s", msg);
        if (fgets(buffer, maxLength, stdin) == NULL) {
            printf("Ошибка ввода. Попробуйте снова.\n");
            continue;
        }
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';

        if (strlen(buffer) == 0) {
            printf("Ввод не может быть пустым. Попробуйте снова.\n");
            continue;
        }
        break;
    }
}

int inputInteger(const char *msg) {
    char buffer[100];
    char *endptr;
    long val;

    while (1) {
        inputString(buffer, sizeof(buffer), msg);
        val = strtol(buffer, &endptr, 10);
        if (*endptr == '\0') return (int)val;
        printf("Ошибка: введите допустимое целое число.\n");
    }
}

float inputFloat(const char *msg) {
    char buffer[100];
    char *endptr;
    float val;

    while (1) {
        inputString(buffer, sizeof(buffer), msg);
        val = strtof(buffer, &endptr);
        if (*endptr == '\0') return val;
        printf("Ошибка: введите допустимое число с плавающей точкой.\n");
    }
}



void workWithQueue() {
    int qSize = inputInteger("Введите максимальный размер очереди: ");
    IntQueue *q = createIntQueue(qSize);
    for (int i = 0; i < qSize; i++) {
        int val = inputInteger("Введите целое число: ");
        enqueueInt(q, val);
    }
    displayIntQueue(q);

    char ch;
    do {
        int val = inputInteger("Введите новое целое число: ");
        enqueueInt(q, val);
        displayIntQueue(q);
        
        while (1) {
            printf("Продолжить ввод? (y/n): ");
            scanf(" %c", &ch);
            while (getchar() != '\n');
            
            if (ch == 'y' || ch == 'Y' || ch == 'n' || ch == 'N') {
                break;
            }
            printf("Некорректный ввод. Пожалуйста, введите 'y' или 'n'.\n");
        }
    } while (ch == 'y' || ch == 'Y');
    freeIntQueue(q);
}

void workWithDeque() {
    int dSize = inputInteger("Введите максимальный размер дека: ");
    FloatDeque *dq = createFloatDeque(dSize);
    for (int i = 0; i < dSize; i++) {
        float val = inputFloat("Введите число с плавающей точкой (x.y): ");
        pushBackFloat(dq, val);
    }
    displayFloatDeque(dq);

    char ch;
    do {
        float val = inputFloat("Введите новое число: ");
        pushBackFloat(dq, val);
        displayFloatDeque(dq);
        
        while (1) {
            printf("Продолжить ввод в дек? (y/n): ");
            scanf(" %c", &ch);
            while (getchar() != '\n'); // Очистка буфера ввода
            
            if (ch == 'y' || ch == 'Y' || ch == 'n' || ch == 'N') {
                break;
            }
            printf("Некорректный ввод. Пожалуйста, введите 'y' или 'n'.\n");
        }
    } while (ch == 'y' || ch == 'Y');
    freeFloatDeque(dq);
}
