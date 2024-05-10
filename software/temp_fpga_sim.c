#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 1024
#define QUEUE_SIZE 100

typedef struct {
    char data[BUFFER_SIZE];
} QueueData;

typedef struct {
    QueueData items[QUEUE_SIZE];
    int front, rear;
} Queue;

void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isQueueEmpty(Queue *q) {
    return (q->front == -1 && q->rear == -1);
}

int isQueueFull(Queue *q) {
    return ((q->rear + 1) % QUEUE_SIZE == q->front);
}

void enqueue(Queue *q, QueueData item) {
    if (isQueueFull(q)) {
        // printf("Queue is full\n");
        return;
    } else if (isQueueEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % QUEUE_SIZE;
    }
    q->items[q->rear] = item;
}

QueueData dequeue(Queue *q) {
    QueueData item;
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
        exit(1);
    } else if (q->front == q->rear) {
        item = q->items[q->front];
        q->front = q->rear = -1;
    } else {
        item = q->items[q->front];
        q->front = (q->front + 1) % QUEUE_SIZE;
    }
    return item;
}

void *network_thread_f(void *);

int main() {
    pthread_t network_thread;
    Queue dataQueue;
    initializeQueue(&dataQueue);

    // Open the generated messages file
    FILE *file = fopen("generated_messages.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    // Read messages from file and enqueue them
    char line[BUFFER_SIZE];
    while (fgets(line, BUFFER_SIZE, file) != NULL) {
        QueueData newData;
        strcpy(newData.data, line);
        enqueue(&dataQueue, newData);
    }
    fclose(file);

    // Start the network thread
    if (pthread_create(&network_thread, NULL, network_thread_f, (void *)&dataQueue) != 0) {
        perror("Error creating network thread");
        exit(1);
    }

    // Simulated FPGA process
    while (1) {
        // Simulated data generation
        // (Assuming data is already read from the file and enqueued)
        sleep(2); // Simulated delay
    }

    return 0;
}

void *network_thread_f(void *arg) {
    Queue *dataQueue = (Queue *)arg;

    // Simulated printing of data from the queue
    QueueData item;
    while (1) {
        // Dequeue data
        // (Assuming data is already read from the file and enqueued)
        item = dequeue(dataQueue);
        printf("%s", item.data); // Print the data
        sleep(2); // Simulated delay
    }
    return NULL;
}
